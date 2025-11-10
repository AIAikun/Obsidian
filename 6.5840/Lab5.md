**6.5840 实验 5：分片键/值服务**
https://blog.csdn.net/2403_87793978/article/details/149597571?spm=1001.2014.3001.5502
https://blog.csdn.net/2403_87793978/article/details/149604681?spm=1001.2014.3001.5502
**介绍**

在本实验中，你将构建一个键/值存储系统，该系统将键"分片"或分区到一组基于 Raft 复制的键/值服务器组（shardgrps）上。一个分片是键/值对的一个子集；例如，所有以"a"开头的键可能是一个分片，所有以"b"开头的键是另一个分片，等等。分片的原因是性能。每个 shardgrp 只处理少数几个分片的 puts 和 gets，并且 shardgrps 并行操作；因此，系统总吞吐量（单位时间内的 puts 和 gets）随着 shardgrps 数量的增加而增加。

![[Pasted image 20251028120616.png]]

分片键/值服务包含如上图所示的组件。Shardgrps（用蓝色方块表示）存储带有键的分片：shardgrp 1 持有一个存储键"a"的分片，shardgrp 2 持有一个存储键"b"的分片。分片键/值服务的客户端通过一个 clerk（用绿色圆圈表示）与服务交互，该 clerk 实现了 Get 和 Put 方法。为了找到传递给 Put/Get 的键对应的 shardgrp，clerk 从 kvsrv（用黑色方块表示）获取配置，这是你在实验 2 中实现的。配置（未显示）描述了从分片到 shardgrps 的映射（例如，分片 1 由 shardgrp 3 服务）。

管理员（即测试程序）使用另一个客户端，即控制器（用紫色圆圈表示），来从集群中添加/移除 shardgrps 并更新哪个 shardgrp 应该服务某个分片。控制器有一个主要方法：`ChangeConfigTo`，它以新配置作为参数，并将系统从当前配置更改为新配置；这涉及将分片移动到加入系统的新 shardgrps，以及将分片移出即将离开系统的 shardgrps。为此，控制器 1) 向 shardgrps 发起 RPC（`FreezeShard`, `InstallShard`, 和 `DeleteShard`），以及 2) 更新存储在 kvsrv 中的配置。

需要控制器的原因是分片存储系统必须能够在 shardgrps 之间转移分片。一个原因是某些 shardgrps 可能比其他 shardgrps 负载更重，因此需要移动分片以平衡负载。另一个原因是 shardgrps 可能会加入和离开系统：可能会添加新的 shardgrps 以增加容量，或者现有的 shardgrps 可能因修复或退役而离线。

本实验的主要挑战是在处理以下情况时确保 Get/Put 操作的线性一致性：1) 分片到 shardgrps 的分配发生变化，以及 2) 从控制器在 `ChangeConfigTo` 期间发生故障或网络分区中恢复。

`ChangeConfigTo` 将分片从一个 shardgrp 移动到另一个 shardgrp。一个风险是一些客户端可能使用旧的 shardgrp，而其他客户端使用新的 shardgrp，这可能会破坏线性一致性。你需要确保在任何时刻，最多只有一个 shardgrp 为每个分片服务请求。
如果 `ChangeConfigTo` 在重新配置过程中失败，一些分片可能变得不可访问，如果它们已经开始但从一个 shardgrp 移动到另一个 shardgrp 的过程尚未完成。为了取得进展，测试程序会启动一个新的控制器，你的工作是确保新的控制器完成前一个控制器开始的重新配置。
本实验使用"配置"来指代分片到 shardgrps 的分配。这与 Raft 集群成员变更不同。你不需要实现 Raft 集群成员变更。

一个 shardgrp 服务器仅是一个 shardgrp 的成员。给定 shardgrp 中的服务器集合永远不会改变。

只有 RPC 可以用于客户端和服务器之间的交互。例如，不允许你的服务器的不同实例共享 Go 变量或文件。

在 A 部分，你将实现一个可工作的 shardctrler，它将在 kvsrv 中存储和检索配置。你还将实现 shardgrp，使用你的 Raft rsm 包进行复制，以及相应的 shardgrp clerk。shardctrler 与 shardgrp clerks 通信以在不同组之间移动分片。

在 B 部分，你将修改你的 shardctrler 以处理配置更改期间的故障和分区。在 C 部分，你将扩展你的 shardctrler 以允许多个控制器并发工作而互不干扰。最后，在 D 部分，你将有机会以任何你喜欢的方式扩展你的解决方案。

本实验的分片键/值服务遵循与 Flat Datacenter Storage, BigTable, Spanner, FAWN, Apache HBase, Rosebud, Spinnaker 等系统相同的一般设计。然而，这些系统在细节上与本实验有许多不同，并且通常更复杂和强大。例如，本实验不改变每个 Raft 组中的对等点集合；其数据和查询模型简单；等等。

实验 5 将使用你来自实验 2 的 kvsrv，以及你来自实验 4 的 rsm 和 Raft。你的实验 5 和实验 4 必须使用相同的 rsm 和 Raft 实现。

你可以为 A 部分使用延迟小时，但不能为 B-D 部分使用延迟小时。

**开始**
执行 `git pull` 以获取最新的实验软件。

我们在 `src/shardkv1` 中为你提供了测试和骨架代码：

*   `client.go` 用于 shardkv clerk
*   `shardcfg` 包用于计算分片配置
*   `shardgrp` 包：用于 shardgrp clerk 和服务器。
*   `shardctrler` 包，其中包含 `shardctrler.go`，包含控制器更改配置 (`ChangeConfigTo`) 和获取配置 (`Query`) 的方法。

要启动并运行，执行以下命令：

```bash
$ cd ~/6.5840
$ git pull
...
$ cd src/shardkv1
$ go test -v
=== RUN  TestInitQuery5A
Test (5A): Init and Query ... (reliable network)...
    shardkv_test.go:46: Static wrong null 0
...
```

**A 部分：移动分片（困难）**
你的第一个任务是在没有故障的情况下实现 shardgrps 以及 `InitConfig`、`Query` 和 `ChangeConfigTo` 方法。我们已经为你提供了描述配置的代码，在 `shardkv1/shardcfg` 中。每个 `shardcfg.ShardConfig` 都有一个唯一的标识号、一个从分片号到组号的映射，以及一个从组号到复制该组的服务器列表的映射。通常分片数量会多于组数量（以便每个组服务多个分片），从而可以相当精细地调整负载。

在 `shardctrler/shardctrler.go` 中实现这两个方法：

*   `InitConfig` 方法接收第一个配置，由测试程序作为 `shardcfg.ShardConfig` 传递给它。`InitConfig` 应该将配置存储在实验 2 的 kvsrv 的一个实例中。
*   `Query` 方法返回当前配置；它应该从 kvsrv 读取配置，该配置之前由 `InitConfig` 存储在那里。

实现 `InitConfig` 和 `Query`，并将配置存储在 kvsrv 中。当你的代码通过第一个测试时，你就完成了。注意这个任务不需要任何 shardgrps。

```bash
$ cd ~/6.5840/src/shardkv1
$ go test -run TestInitQuery5A
Test (5A): Init and Query ... (reliable network)...
  ... Passed --  time  0.0s #peers 1 #RPCs     3 #Ops    0
PASS
ok      6.5840/shardkv1 0.197s
$
```

*   通过从 kvsrv 存储和读取初始配置来实现 `InitConfig` 和 `Query`：使用 `ShardCtrler.IKVClerk` 的 `Get`/`Put` 方法与 kvsrv 通信，使用 `ShardConfig` 的 `String` 方法将 `ShardConfig` 转换为可以传递给 `Put` 的字符串，并使用 `shardcfg.FromString()` 函数将字符串转换为 `ShardConfig`。

通过从你的实验 4 `kvraft` 解决方案复制代码，在 `shardkv1/shardgrp/server.go` 中实现一个初始版本的 shardgrp，并在 `shardkv1/shardgrp/client.go` 中实现相应的 clerk。

在 `shardkv1/client.go` 中实现一个 clerk，它使用 `Query` 方法查找键对应的 shardgrp，然后与该 shardgrp 通信。当你的代码通过 Static 测试时，你就完成了。

```bash
$ cd ~/6.5840/src/shardkv1
$ go test -run Static
Test (5A): one shard group ... (reliable network)...
  ... Passed --  time  5.4s #peers 1 #RPCs   793 #Ops  180
PASS
ok      6.5840/shardkv1 5.632s
$
```

*   从你的 `kvraft` 的 `client.go` 和 `server.go` 复制 `Put` 和 `Get` 的代码，以及你从 `kvraft` 需要的任何其他代码。
*   `shardkv1/client.go` 中的代码为整个系统提供了 `Put`/`Get` clerk：它通过调用 `Query` 方法找出哪个 shardgrp 持有所需键的分片，然后与持有该分片的 shardgrp 通信。
*   实现 `shardkv1/client.go`，包括其 `Put`/`Get` 方法。使用 `shardcfg.Key2Shard()` 查找键的分片号。测试程序在 `shardkv1/client.go` 的 `MakeClerk` 中传递一个 `ShardCtrler` 对象。使用 `Query` 方法检索当前配置。
*   为了从 shardgrp 放入/获取一个键，shardkv clerk 应该通过调用 `shardgrp.MakeClerk` 为该 shardgrp 创建一个 shardgrp clerk，传入在配置中找到的服务器和 shardkv clerk 的 `ck.clnt`。使用 `ShardConfig` 的 `GidServers()` 方法获取分片对应的组。
*   `shardkv1/client.go` 的 `Put` 必须在回复可能丢失时返回 `ErrMaybe`，但这个 `Put` 调用 shardgrp 的 `Put` 来与特定的 shardgrp 通信。内部的 `Put` 可以通过错误来发出信号。
*   在创建时，第一个 shardgrp (`shardcfg.Gid1`) 应该初始化自己以拥有所有分片。

现在，你应该通过实现 `ChangeConfigTo` 方法来支持分片在组之间的移动，该方法将系统从旧配置更改为新配置。新配置可能包含旧配置中不存在的新 shardgrps，并且可能排除旧配置中存在的 shardgrps。控制器应该移动分片（键/值数据），使得每个 shardgrp 存储的分片集合与新配置匹配。

我们建议的移动分片的方法是让 `ChangeConfigTo` 首先在源 shardgrp"冻结"该分片，导致该 shardgrp 拒绝针对正在移动的分片中的键的 `Put` 操作。然后，将分片复制（安装）到目标 shardgrp；然后删除冻结的分片。最后，发布一个新配置，以便客户端可以找到已移动的分片。这种方法的一个优点是它避免了 shardgrps 之间的任何直接交互。它还支持服务不受正在进行配置更改的分片的影响。

为了能够对配置更改进行排序，每个配置都有一个唯一的编号 `Num`（参见 `shardcfg/shardcfg.go`）。A 部分的测试程序顺序调用 `ChangeConfigTo`，并且传递给 `ChangeConfigTo` 的配置的 `Num` 将比前一个大一；因此，具有较高 `Num` 的配置比具有较低 `Num` 的配置新。

网络可能会延迟 RPC，并且 RPC 可能乱序到达 shardgrps。为了拒绝旧的 `FreezeShard`、`InstallShard` 和 `DeleteShard` RPC，它们应该包含 `Num`（参见 `shardgrp/shardrpc/shardrpc.go`），并且 shardgrps 必须记住它们为每个分片见过的最大 `Num`。

实现 `ChangeConfigTo`（在 `shardctrler/shardctrler.go` 中）并扩展 shardgrp 以支持冻结、安装和删除。在 A 部分，`ChangeConfigTo` 应该总是成功，因为测试程序在此部分不会引发故障。你将需要在 `shardgrp/client.go` 和 `shardgrp/server.go` 中使用 `shardgrp/shardrpc` 包中的 RPC 来实现 `FreezeShard`、`InstallShard` 和 `DeleteShard`，并根据 `Num` 拒绝旧的 RPC。你还需要修改 `shardkv1/client.go` 中的 shardkv clerk 来处理 `ErrWrongGroup`，如果一个 shardgrp 不负责该分片，它应该返回此错误。

当你通过 `JoinBasic` 和 `DeleteBasic` 测试时，你就完成了这个任务。这些测试侧重于添加 shardgrps；你暂时不必担心 shardgrps 离开。

*   一个 shardgrp 应该对一个带有该 shardgrp 不负责的键（即，其分片未分配给该 shardgrp 的键）的客户端 `Put`/`Get` 响应一个 `ErrWrongGroup` 错误。你将不得不修改 `shardkv1/client.go` 以重新读取配置并重试 `Put`/`Get`。
*   注意，你将不得不通过你的 rsm 包运行 `FreezeShard`、`InstallShard` 和 `DeleteShard`，就像 `Put` 和 `Get` 一样。
*   你可以在 RPC 请求或回复中发送整个 map 作为你的状态，这可能有助于保持分片传输代码的简单性。
*   如果你的一个 RPC 处理程序在其回复中包含了一个作为你服务器状态一部分的 map（例如一个键/值 map），你可能会因为竞争条件而遇到错误。RPC 系统必须读取该 map 以便将其发送给调用者，但它没有持有覆盖该 map 的锁。然而，你的服务器可能会在 RPC 系统读取该 map 的同时修改同一个 map。解决方案是让 RPC 处理程序在回复中包含该 map 的一个副本。

扩展 `ChangeConfigTo` 以处理离开的 shard groups；即，存在于当前配置但不存在于新配置中的 shardgrps。你的解决方案现在应该通过 `TestJoinLeaveBasic5A`。（你可能已经在之前的任务中处理了这个场景，但之前的测试没有测试 shardgrps 离开的情况。）

让你的解决方案通过所有 A 部分测试，这些测试检查你的分片键/值服务是否支持许多组的加入和离开、shardgrps 从快照重启、在某些分片离线或参与配置更改时处理 Gets，以及在许多客户端与服务交互而测试程序并发调用控制器的 `ChangeConfigTo` 以重新平衡分片时的线性一致性。

```bash
$ cd ~/6.5840/src/shardkv1
$ go test -run 5A
Test (5A): Init and Query ... (reliable network)...
  ... Passed --  time  0.0s #peers 1 #RPCs     3 #Ops    0
Test (5A): one shard group ... (reliable network)...
  ... Passed --  time  5.1s #peers 1 #RPCs   792 #Ops  180
Test (5A): a group joins... (reliable network)...
  ... Passed --  time 12.9s #peers 1 #RPCs  6300 #Ops  180
Test (5A): delete ... (reliable network)...
  ... Passed --  time  8.4s #peers 1 #RPCs  1533 #Ops  360
Test (5A): basic groups join/leave ... (reliable network)...
  ... Passed --  time 13.7s #peers 1 #RPCs  5676 #Ops  240
Test (5A): many groups join/leave ... (reliable network)...
  ... Passed --  time 22.1s #peers 1 #RPCs  3529 #Ops  180
Test (5A): many groups join/leave ... (unreliable network)...
  ... Passed --  time 54.8s #peers 1 #RPCs  5055 #Ops  180
Test (5A): shutdown ... (reliable network)...
  ... Passed --  time 11.7s #peers 1 #RPCs  2807 #Ops  180
Test (5A): progress ... (reliable network)...
  ... Passed --  time  8.8s #peers 1 #RPCs   974 #Ops   82
Test (5A): progress ... (reliable network)...
  ... Passed --  time 13.9s #peers 1 #RPCs  2443 #Ops  390
Test (5A): one concurrent clerk reliable... (reliable network)...
  ... Passed --  time 20.0s #peers 1 #RPCs  5326 #Ops 1248
Test (5A): many concurrent clerks reliable... (reliable network)...
  ... Passed --  time 20.4s #peers 1 #RPCs 21688 #Ops 10500
Test (5A): one concurrent clerk unreliable ... (unreliable network)...
  ... Passed --  time 25.8s #peers 1 #RPCs  2654 #Ops  176
Test (5A): many concurrent clerks unreliable... (unreliable network)...
  ... Passed --  time 25.3s #peers 1 #RPCs  7553 #Ops 1896
PASS
ok      6.5840/shardkv1 243.115s
$
```

你的解决方案必须继续服务不受正在进行的配置更改影响的分片。

**B 部分：处理故障的控制器（简单）**
控制器是一个短暂存在的命令，由管理员调用：它移动分片然后退出。但是，它可能在移动分片时失败或失去网络连接。本实验部分的主要任务是从未能完成 `ChangeConfigTo` 的控制器中恢复。测试程序在对第一个控制器进行分区后启动一个新的控制器并调用其 `ChangeConfigTo`；你必须修改控制器，以便新的控制器完成重新配置。测试程序在启动控制器时调用 `InitController`；你可以修改该函数以检查是否需要完成一个中断的配置更改。

允许控制器完成前一个控制器开始的重新配置的一个好方法是保留两个配置：一个当前配置和一个下一个配置，两者都存储在控制器的 kvsrv 中。当控制器开始重新配置时，它存储下一个配置。一旦控制器完成重新配置，它就将下一个配置设为当前配置。修改 `InitController` 以首先检查是否存在一个配置号比当前配置更高的存储的下一个配置，如果存在，则完成重新配置到下一个配置所需的分片移动。

修改 shardctrler 以实现上述方法。一个接替故障控制器工作的控制器可能会重复 `FreezeShard`、`InstallShard` 和 `Delete` RPC；shardgrps 可以使用 `Num` 来检测重复项并拒绝它们。如果你的解决方案通过 B 部分测试，你就完成了这个任务。

```bash
$ cd ~/6.5840/src/shardkv1
$ go test -run 5B
Test (5B): Join/leave while a shardgrp is down... (reliable network)...
  ... Passed --  time  9.2s #peers 1 #RPCs   899 #Ops  120
Test (5B): recover controller ... (reliable network)...
  ... Passed --  time 26.4s #peers 1 #RPCs  3724 #Ops  360
PASS
ok      6.5840/shardkv1 35.805s
$
```

*   测试程序在启动控制器时调用 `InitController`；你可以在 `shardctrler/shardctrler.go` 的该方法中实现恢复。

**C 部分：并发配置更改（中等）**
在本实验部分，你将修改控制器以允许多个控制器并发工作。当一个控制器崩溃或被分区时，测试程序将启动一个新的控制器，该控制器必须完成旧控制器可能正在进行的工作（即，像 B 部分那样完成移动分片）。这意味着几个控制器可能并发运行并向 shardgrps 和存储配置的 kvsrv 发送 RPC。

主要的挑战是确保这些控制器不会相互干扰。在 A 部分，你已经用 `Num` 对所有 shardgrp RPC 进行了防护，以便旧的 RPC 被拒绝。即使几个控制器并发地接替旧控制器的工作，其中一个成功而其他控制器重复所有 RPC，shardgrps 也会忽略它们。

因此，剩下的具有挑战性的情况是确保只有一个控制器更新下一个配置，以避免两个控制器（例如，一个被分区的控制器和一个新的控制器）在下一個配置中放入不同的配置。为了强调这种情况，测试程序并发运行多个控制器，每个控制器通过读取当前配置并为其离开或加入的 shardgrp 更新它来计算下一个配置，然后测试程序调用 `ChangeConfigTo`；因此多个控制器可能使用具有相同 `Num` 的不同配置调用 `ChangeConfigTo`。你可以使用键的版本号和带版本的 Puts 来确保只有一个控制器更新下一个配置，而其他调用返回而不执行任何操作。

修改你的控制器，使得只有一个控制器可以为某个配置 `Num` 发布下一个配置。测试程序将启动许多控制器，但只有一个应该为新的配置开始 `ChangeConfigTo`。如果你通过 C 部分的并发测试，你就完成了这个任务：

```bash
$ cd ~/6.5840/src/shardkv1
$ go test -run TestConcurrentReliable5C
Test (5C): Concurrent ctrlers ... (reliable network)...
  ... Passed --  time  8.2s #peers 1 #RPCs  1753 #Ops  120
PASS
ok      6.5840/shardkv1 8.364s
$ go test -run TestAcquireLockConcurrentUnreliable5C
Test (5C): Concurrent ctrlers ... (unreliable network)...
  ... Passed --  time 23.8s #peers 1 #RPCs  1850 #Ops  120
PASS
ok      6.5840/shardkv1 24.008s
$
```

*   参见 `test.go` 中的 `concurCtrler` 以了解测试程序如何并发运行控制器。

在这个练习中，你将把旧控制器的恢复与新控制器结合起来：一个新控制器应该执行来自 B 部分的恢复。如果旧控制器在 `ChangeConfigTo` 期间被分区，你必须确保旧控制器不会干扰新控制器。如果所有控制器的更新都已经通过 B 部分的 `Num` 检查进行了适当的防护，你就不需要编写额外的代码。如果你通过 Partition 测试，你就完成了这个任务。

```bash
$ cd ~/6.5840/src/shardkv1
$ go test -run Partition
Test (5C): partition controller in join... (reliable network)...
  ... Passed --  time  7.8s #peers 1 #RPCs   876 #Ops  120
Test (5C): controllers with leased leadership ... (reliable network)...
  ... Passed --  time 36.8s #peers 1 #RPCs  3981 #Ops  360
Test (5C): controllers with leased leadership ... (unreliable network)...
  ... Passed --  time 52.4s #peers 1 #RPCs  2901 #Ops  240
Test (5C): controllers with leased leadership ... (reliable network)...
  ... Passed --  time 60.2s #peers 1 #RPCs 27415 #Ops 11182
Test (5C): controllers with leased leadership ... (unreliable network)...
  ... Passed --  time 60.5s #peers 1 #RPCs 11422 #Ops 2336
PASS
ok      6.5840/shardkv1 217.779s
$
```

你已经完成了一个高可用的分片键/值服务的实现，它具有许多 shard groups 以实现可扩展性，重新配置以处理负载变化，以及一个容错的控制器；恭喜！

重新运行所有测试，检查你对控制器的最新更改是否破坏了早期的测试。

Gradescope 将在你的提交上重新运行实验 3A-D 和实验 4A-C 的测试，以及 5C 的测试。在提交之前，仔细检查你的解决方案是否有效：

```bash
$ go test ./raft1
$ go test ./kvraft1
$ go test ./shardkv1
```

**D 部分：扩展你的解决方案**
在实验的最后一部分，你可以以任何你喜欢的方式扩展你的解决方案。你将需要为你选择实现的任何扩展编写自己的测试。

实现以下想法之一，或者提出你自己的想法。在一个名为 `extension.md` 的文件中写一段描述你的扩展，并将 `extension.md` 上传到 Gradescope。如果你想做一个更难的、开放式的扩展，可以自由地与班上的另一个学生合作。

以下是一些可能的扩展想法（前几个比较简单，后面的更开放）：

*   （简单）更改测试程序以使用 `kvraft` 而不是 `kvsrv`（即，将 `test.go` 中的 `kvsrv.StartKVServer` 替换为 `kvraft.StartKVServer`），以便控制器使用你的 `kvraft` 来存储其配置。编写一个测试，检查当其中一个 `kvraft` 对等点宕机时，控制器是否可以查询和更新配置。测试程序的现有代码分布在 `src/kvtest1`、`src/shardkv1` 和 `src/tester1` 中。
*   （中等）更改 `kvsrv` 以实现像去年实验 2 中的 Put/Get 的恰好一次语义（参见丢弃消息部分）。你可能能够从 2024 年移植一些测试，而不必从头开始编写自己的测试。也在你的 `kvraft` 中实现恰好一次语义。
*   （中等）更改 `kvsrv` 以支持 `Range` 函数，该函数返回从低键到高键的所有键。实现 `Range` 的懒惰方法是遍历服务器维护的键/值 map；更好的方法是使用支持范围搜索的数据结构（例如，B 树）。包含一个测试，该测试在懒惰解决方案上失败，但在更好的解决方案上通过。
*   （困难）修改你的 `kvraft` 实现，允许领导者在不通过 rsm 运行 Get 的情况下服务 Gets。也就是说，实现 Raft 论文第 8 节末尾描述的优化，包括租约，以确保 `kvraft` 保持线性一致性。你的实现应该通过现有的 `kvraft` 测试。你还应该添加一个测试，检查你的优化实现是否更快（例如，通过比较 RPC 的数量），以及一个测试，检查任期切换是否更慢，因为新的领导者必须等待租约到期。
*   （困难）在 `kvraft` 中支持事务，以便开发人员可以原子地执行多个 Puts 和 Gets。一旦你有了事务，你就不再需要带版本的 Puts 了；事务包含了带版本的 Puts。查看 etcd 的事务以获取示例接口。编写测试以证明你的扩展有效。
*   （困难）修改 `shardkv` 以支持事务，以便开发人员可以跨分片原子地执行多个 Puts 和 Gets。这需要实现两阶段提交和两阶段锁定。编写测试以证明你的扩展有效。

**提交程序**
在提交之前，请最后运行一次所有测试。

在提交之前，仔细检查你的解决方案是否适用于：

```bash
$ go test ./raft1
$ go test ./kvraft1
$ go test ./shardkv1
```