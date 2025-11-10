https://zirunhua.github.io/MIT6.824-6.5840/docs/lab4/README.html
https://tecy-blog.com/2025/08/07/mit-6-5840-distributed-system-lab4/
https://blog.csdn.net/2403_87793978/article/details/149228673
https://blog.csdn.net/2403_87793978/article/details/149254561?spm=1001.2014.3001.5502
https://blog.csdn.net/2403_87793978/article/details/149332121?spm=1001.2014.3001.5502
6.5840 实验 4：容错键/值服务
## 介绍

在本实验中，您将使用您在实验 3 中构建的 Raft 库构建一个容错的键/值存储服务。对于客户端而言，该服务看起来类似于实验 2 的服务器。但是，与单个服务器不同，该服务由一组服务器组成，这些服务器使用 Raft 来帮助它们维护相同的数据库。只要大多数服务器存活并且可以通信，您的键/值服务就应该继续处理客户端请求，即使发生其他故障或网络分区。在实验 4 之后，您将实现 Raft 交互图中显示的所有部分（Clerk、Service 和 Raft）。

客户端将通过 Clerk 与您的键/值服务交互，就像在实验 2 中一样。Clerk 实现了与实验 2 语义相同的 `Put` 和 `Get` 方法：`Put` 操作具有最多一次语义，并且 `Put`/`Get` 操作必须形成可线性化的历史记录。

对于单个服务器来说，提供可线性化相对容易。如果服务被复制，则会更加困难，因为所有服务器必须为并发请求选择相同的执行顺序，必须避免使用过时的状态回复客户端，并且必须在故障后以一种保留所有已确认客户端更新的方式恢复其状态。

本实验包含三个部分。在 A 部分，您将使用您的 Raft 实现实现一个复制状态机包 `rsm`；`rsm` 与它复制的请求无关。在 B 部分，您将使用 `rsm` 实现一个复制的键/值服务，但不使用快照。在 C 部分，您将使用您在实验 3D 中实现的快照功能，这将允许 Raft 丢弃旧的日志条目。请在各自的截止日期前提交每个部分。

您应该复习扩展的 Raft 论文，特别是第 7 节（但不包括第 8 节）。为了更广阔的视角，可以看看 Chubby、Paxos Made Live、Spanner、Zookeeper、Harp、Viewstamped Replication 和 Bolosky 等人的论文。

请尽早开始。

## 开始

我们在 `src/kvraft1` 中为您提供了骨架代码和测试。骨架代码使用骨架包 `src/kvraft1/rsm` 来复制服务器。服务器必须实现 `rsm` 中定义的 `StateMachine` 接口，以便使用 `rsm` 复制自身。您的大部分工作将是实现 `rsm` 以提供与服务器无关的复制。您还需要修改 `kvraft1/client.go` 和 `kvraft1/server.go` 来实现服务器特定的部分。这种拆分允许您在下一个实验中重用 `rsm`。您也许能够重用您实验 2 的一些代码（例如，通过复制或导入 `"src/kvsrv1"` 包来重用服务器代码），但这不是必须的要求。

要开始运行，请执行以下命令。不要忘记执行 `git pull` 来获取最新的软件。

```bash
$ cd ~/6.5840
$ git pull
..
```

## A 部分：复制状态机 (RSM)（中等/困难）

```bash
$ cd src/kvraft1/rsm
$ go test -v
=== RUN   TestBasic
Test RSM basic (reliable network)...
..
    config.go:147: one: took too long
```

在使用 Raft 进行复制的客户端/服务器服务的常见情况下，服务以两种方式与 Raft 交互：服务领导者通过调用 `raft.Start()` 提交客户端操作，并且所有服务副本通过 Raft 的 `applyCh` 接收已提交的操作并执行它们。在领导者上，这两个活动相互作用。在任何给定时间，一些服务器 goroutine 正在处理客户端请求，已经调用了 `raft.Start()`，并且每个都在等待其操作提交并找出执行操作的结果。当已提交的操作出现在 `applyCh` 上时，每个操作都需要由服务执行，并且需要将结果交给调用 `raft.Start()` 的 goroutine，以便它可以向客户端返回结果。

`rsm` 包封装了上述交互。它作为服务（例如键/值数据库）和 Raft 之间的一个层。在 `rsm/rsm.go` 中，您需要实现一个读取 `applyCh` 的 "reader" goroutine，以及一个 `rsm.Submit()` 函数，该函数为客户端操作调用 `raft.Start()`，然后等待 reader goroutine 将执行该操作的结果交给它。

使用 `rsm` 的服务对 `rsm` reader goroutine 显示为一个提供 `DoOp()` 方法的 `StateMachine` 对象。reader goroutine 应该将每个已提交的操作交给 `DoOp()`；`DoOp()` 的返回值应该被提供给相应的 `rsm.Submit()` 调用以返回。`DoOp()` 的参数和返回值具有类型 `any`；实际值应该与服务传递给 `rsm.Submit()` 的参数和返回值具有相同的类型。

服务应该将每个客户端操作传递给 `rsm.Submit()`。为了帮助 reader goroutine 将 `applyCh` 消息与等待的 `rsm.Submit()` 调用匹配，`Submit()` 应该用唯一的标识符将每个客户端操作包装在一个 `Op` 结构中。然后，`Submit()` 应该等待操作被提交并执行，并返回执行的结果（`DoOp()` 返回的值）。如果 `raft.Start()` 指示当前对等方不是 Raft 领导者，`Submit()` 应该返回一个 `rpc.ErrWrongLeader` 错误。`Submit()` 应该检测并处理在其调用 `raft.Start()` 后领导权发生变化的情况，这会导致操作丢失（从未提交）。

对于 A 部分，`rsm` 测试程序充当服务，提交它解释为对由单个整数组成的状态进行递增的操作。在 B 部分，您将使用 `rsm` 作为实现 `StateMachine`（和 `DoOp()`）的键/值服务的一部分，并调用 `rsm.Submit()`。

如果一切顺利，客户端请求的事件序列是：

1.  客户端向服务领导者发送请求。
2.  服务领导者使用该请求调用 `rsm.Submit()`。
3.  `rsm.Submit()` 使用该请求调用 `raft.Start()`，然后等待。
4.  Raft 提交该请求并将其发送到所有对等方的 `applyCh` 上。
5.  每个对等方上的 `rsm` reader goroutine 从 `applyCh` 读取请求并将其传递给服务的 `DoOp()`。
6.  在领导者上，`rsm` reader goroutine 将 `DoOp()` 返回值交给最初提交请求的 `Submit()` goroutine，然后 `Submit()` 返回该值。

您的服务器不应直接通信；它们应仅通过 Raft 相互交互。

实现 `rsm.go`：`Submit()` 方法和一个 reader goroutine。如果您通过了 `rsm` 4A 测试，则您已完成此任务：

```bash
  $ cd src/kvraft1/rsm
  $ go test -v -run 4A
=== RUN   TestBasic4A
Test RSM basic (reliable network)...
  ... Passed --   1.2  3    48    0
--- PASS: TestBasic4A (1.21s)
=== RUN   TestLeaderFailure4A
  ... Passed --  9223372036.9  3    31    0
--- PASS: TestLeaderFailure4A (1.50s)
PASS
ok      6.5840/kvraft1/rsm      2.887s
```

*   您不需要向 Raft ApplyMsg 或 Raft RPC（例如 AppendEntries）添加任何字段，但您被允许这样做。
*   您的解决方案需要处理这样一种情况：一个 `rsm` 领导者已经为通过 `Submit()` 提交的请求调用了 `Start()`，但在请求提交到日志之前失去了其领导地位。一种方法是让 `rsm` 通过注意到 Raft 的任期已更改或在 `Start()` 返回的索引处出现了不同的请求来检测它已失去领导权，并从 `Submit()` 返回 `rpc.ErrWrongLeader`。如果前领导者被自身分区，它将不会知道新的领导者；但是同一分区中的任何客户端也将无法与新的领导者通信，因此在这种情况下，服务器无限期等待直到分区修复是可以的。
*   测试程序在关闭一个对等方时会调用您的 Raft 的 `rf.Kill()`。Raft 应该关闭 `applyCh`，以便您的 `rsm` 了解到关闭，并且可以退出所有循环。

## B 部分：无快照的键/值服务（中等）

```bash
$ cd src/kvraft1
$ go test -v -run TestBasic4B
=== RUN   TestBasic4B
Test: one client (4B basic) (reliable network)...
    kvtest.go:62: Wrong error 
$
```

现在您将使用 `rsm` 包来复制一个键/值服务器。每个服务器（"kvservers"）将有一个关联的 `rsm`/Raft 对等方。Clerk 向其关联的 Raft 是领导者的 kvserver 发送 `Put()` 和 `Get()` RPC。kvserver 代码将 Put/Get 操作提交给 `rsm`，后者使用 Raft 复制它并在每个对等方调用您服务器的 `DoOp`，这应该将操作应用于对等方的键/值数据库；目的是让服务器维护键/值数据库的相同副本。

Clerk 有时不知道哪个 kvserver 是 Raft 领导者。如果 Clerk 向错误的 kvserver 发送 RPC，或者无法连接到 kvserver，Clerk 应通过发送到不同的 kvserver 来重试。如果键/值服务将操作提交到其 Raft 日志（从而将操作应用于键/值状态机），领导者通过响应其 RPC 向 Clerk 报告结果。如果操作未能提交（例如，如果领导者被替换），服务器报告错误，并且 Clerk 使用其他服务器重试。

您的 kvservers 不应直接通信；它们应仅通过 Raft 相互交互。

您的第一个任务是实现一个在没有消息丢失和服务器故障的情况下工作的解决方案。
可以随意将您的客户端代码从实验 2 (`kvsrv1/client.go`) 复制到 `kvraft1/client.go` 中。您需要添加逻辑来决定每个 RPC 发送到哪个 kvserver。

您还需要在 `server.go` 中实现 `Put()` 和 `Get()` RPC 处理程序。这些处理程序应使用 `rsm.Submit()` 将请求提交给 Raft。当 `rsm` 包从 `applyCh` 读取命令时，它应该调用 `DoOp` 方法，您将必须在 `server.go` 中实现该方法。

当您可靠地通过测试套件中的第一个测试 `go test -v -run TestBasic4B` 时，您就完成了此任务。

*   如果 kvserver 不是多数派的一部分（以便它不提供过时的数据），它不应完成 `Get()` RPC。一个简单的解决方案是使用 `Submit()` 将每个 `Get()`（以及每个 `Put()`）输入到 Raft 日志中。您不必实现第 8 节中描述的针对只读操作的优化。
*   最好从一开始就添加锁，因为避免死锁的需要有时会影响整体代码设计。使用 `go test -race` 检查您的代码是否存在竞争条件。

现在您应该修改您的解决方案以在网络和服务器故障面前继续运行。您将面临的一个问题是，Clerk 可能必须多次发送 RPC，直到找到一个肯定回复的 kvserver。如果领导者在将条目提交到 Raft 日志后立即发生故障，Clerk 可能不会收到回复，因此可能会将请求重新发送给另一个领导者。每个对 `Clerk.Put()` 的调用对于特定版本号应仅导致单次执行。
添加代码来处理故障。您的 Clerk 可以使用与实验 2 中类似的重试计划，包括在重试的 Put RPC 响应丢失时返回 `ErrMaybe`。当您的代码可靠地通过所有 4B 测试 `go test -v -run 4B` 时，您就完成了。

*   回想一下，`rsm` 领导者可能会失去其领导权并从 `Submit()` 返回 `rpc.ErrWrongLeader`。在这种情况下，您应该安排 Clerk 将请求重新发送到其他服务器，直到找到新的领导者。
*   您可能必须修改您的 Clerk，以记住哪个服务器是最后一个 RPC 的领导者，并首先将下一个 RPC 发送到该服务器。这将避免在每个 RPC 上浪费时间为领导者搜索，这可能有助于您足够快地通过一些测试。

您的代码现在应该通过实验 4B 测试，如下所示：

```bash
$ cd kvraft1
$ go test -run 4B
Test: one client (4B basic) ...
  ... Passed --   3.2  5  1041  183
Test: one client (4B speed) ...
  ... Passed --  15.9  3  3169    0
Test: many clients (4B many clients) ...
  ... Passed --   3.9  5  3247  871
Test: unreliable net, many clients (4B unreliable net, many clients) ...
  ... Passed --   5.3  5  1035  167
Test: unreliable net, one client (4B progress in majority) ...
  ... Passed --   2.9  5   155    3
Test: no progress in minority (4B) ...
  ... Passed --   1.6  5   102    3
Test: completion after heal (4B) ...
  ... Passed --   1.3  5    67    4
Test: partitions, one client (4B partitions, one client) ...
  ... Passed --   6.2  5   958  155
Test: partitions, many clients (4B partitions, many clients (4B)) ...
  ... Passed --   6.8  5  3096  855
Test: restarts, one client (4B restarts, one client 4B ) ...
  ... Passed --   6.7  5   311   13
Test: restarts, many clients (4B restarts, many clients) ...
  ... Passed --   7.5  5  1223   95
Test: unreliable net, restarts, many clients (4B unreliable net, restarts, many clients ) ...
  ... Passed --   8.4  5   804   33
Test: restarts, partitions, many clients (4B restarts, partitions, many clients) ...
  ... Passed --  10.1  5  1308  105
Test: unreliable net, restarts, partitions, many clients (4B unreliable net, restarts, partitions, many clients) ...
  ... Passed --  11.9  5  1040   33
Test: unreliable net, restarts, partitions, random keys, many clients (4B unreliable net, restarts, partitions, random keys, many clients) ...
  ... Passed --  12.1  7  2801   93
PASS
ok      6.5840/kvraft1  103.797s
```

每个 `Passed` 后面的数字是实时（秒）、对等方数量、发送的 RPC 数量（包括客户端 RPC）和执行的键/值操作数量（Clerk Get/Put 调用）。

## C 部分：带快照的键/值服务（中等）

就目前情况而言，您的键/值服务器不会调用您的 Raft 库的 `Snapshot()` 方法，因此重新启动的服务器必须重放完整的持久化 Raft 日志才能恢复其状态。现在，您将修改 kvserver 和 `rsm` 以与 Raft 协作，使用实验 3D 中的 Raft 的 `Snapshot()` 来节省日志空间并减少重启时间。

测试程序将 `maxraftstate` 传递给您的 `StartKVServer()`，后者将其传递给 `rsm`。`maxraftstate` 表示您的持久化 Raft 状态（包括日志，但不包括快照）允许的最大大小（以字节为单位）。您应该将 `maxraftstate` 与 `rf.PersistBytes()` 进行比较。每当您的 `rsm` 检测到 Raft 状态大小接近此阈值时，它应通过调用 Raft 的 `Snapshot` 来保存快照。`rsm` 可以通过调用 `StateMachine` 接口的 `Snapshot` 方法来创建此快照，以获取 kvserver 的快照。如果 `maxraftstate` 为 -1，则您不需要进行快照。`maxraftstate` 限制适用于您的 Raft 作为第一个参数传递给 `persister.Save()` 的 GOB 编码字节。

您可以在 `tester1/persister.go` 中找到 persister 对象的源代码。

修改您的 `rsm`，使其检测到持久化的 Raft 状态何时过大，然后将快照交给 Raft。当 `rsm` 服务器重新启动时，它应使用 `persister.ReadSnapshot()` 读取快照，如果快照的长度大于零，则将快照传递给 `StateMachine` 的 `Restore()` 方法。如果您在 `rsm` 中通过了 `TestSnapshot4C`，则您已完成此任务。

```bash
$ cd kvraft1/rsm
$ go test -run TestSnapshot4C
=== RUN   TestSnapshot4C
  ... Passed --  9223372036.9  3   230    0
--- PASS: TestSnapshot4C (3.88s)
PASS
ok      6.5840/kvraft1/rsm      3.882s
```

*   考虑 `rsm` 应该在何时快照其状态，以及除了服务器状态之外，快照中还应包含什么。Raft 使用 `Save()` 将每个快照与相应的 Raft 状态一起存储在 persister 对象中。您可以使用 `ReadSnapshot()` 读取最新存储的快照。
*   将存储在快照中的结构的所有字段首字母大写。
*   实现 `rsm` 调用的 `kvraft1/server.go` 中的 `Snapshot()` 和 `Restore()` 方法。修改 `rsm` 以处理包含快照的 `applyCh` 消息。

*   您的 Raft 和 `rsm` 库中可能存在此任务暴露的错误。如果您对 Raft 实现进行了更改，请确保它继续通过所有实验 3 的测试。
*   完成实验 4 测试的合理时间是 400 秒实时和 700 秒 CPU 时间。

您的代码应通过 4C 测试（如此处示例所示）以及 4A+B 测试（并且您的 Raft 必须继续通过实验 3 的测试）。

```bash
$ go test -run 4C
Test: snapshots, one client (4C SnapshotsRPC) ...
Test: InstallSnapshot RPC (4C) ...
  ... Passed --   4.5  3   241   64
Test: snapshots, one client (4C snapshot size is reasonable) ...
  ... Passed --  11.4  3  2526  800
Test: snapshots, one client (4C speed) ...
  ... Passed --  14.2  3  3149    0
Test: restarts, snapshots, one client (4C restarts, snapshots, one client) ...
  ... Passed --   6.8  5   305   13
Test: restarts, snapshots, many clients (4C restarts, snapshots, many clients ) ...
  ... Passed --   9.0  5  5583  795
Test: unreliable net, snapshots, many clients (4C unreliable net, snapshots, many clients) ...
  ... Passed --   4.7  5   977  155
Test: unreliable net, restarts, snapshots, many clients (4C unreliable net, restarts, snapshots, many clients) ...
  ... Passed --   8.6  5   847   33
Test: unreliable net, restarts, partitions, snapshots, many clients (4C unreliable net, restarts, partitions, snapshots, many clients) ...
  ... Passed --  11.5  5   841   33
Test: unreliable net, restarts, partitions, snapshots, random keys, many clients (4C unreliable net, restarts, partitions, snapshots, random keys, many clients) ...
  ... Passed --  12.8  7  2903   93
PASS
ok      6.5840/kvraft1  83.543s
```