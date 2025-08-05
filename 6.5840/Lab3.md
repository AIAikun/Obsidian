### MIT 6.5840 分布式系统实验 - Lab 3：Raft共识算法（2025春季）

#### 实验基本信息

#### 实验介绍
本实验是构建容错键值存储系统的第一个实验。您将实现Raft——一个复制状态机协议。在后续实验中，您将基于Raft构建键值服务，并通过分片（sharding）技术提升性能。

#### 基本原理
复制服务通过在多个副本服务器上存储完整的状态副本来实现容错。即使部分服务器发生故障（崩溃或网络问题），服务仍能继续运行。关键挑战在于故障可能导致副本间数据不一致。

Raft通过以下机制解决这个问题：
1. 将客户端请求组织成有序的日志序列
2. 确保所有副本服务器看到相同的日志
3. 各副本按日志顺序执行请求，应用到本地状态
4. 故障恢复后自动同步日志

#### 实验要求
您需要实现一个Go语言版本的Raft模块，其主要接口包括：
```go
// 创建Raft实例
rf := Make(peers, me, persister, applyCh)

// 提交新日志条目
rf.Start(command interface{}) (index, term, isleader)

// 查询当前状态
rf.GetState() (term, isLeader)

// 已提交日志消息结构
type ApplyMsg {
    CommandValid bool
    Command      interface{}
    CommandIndex int
    // 快照相关字段
    SnapshotValid bool
    Snapshot      []byte
    SnapshotTerm  int
    SnapshotIndex int
}
```

#### 实验准备
1. 获取最新代码：
```bash
$ cd ~/6.5840
$ git pull
$ cd src/raft1
$ go test
```

2. 初始代码结构：
- 框架代码：src/raft/raft.go
- 测试用例：src/raft/raft_test.go

#### 实验阶段

##### 3A阶段：领导者选举（中等难度）
**核心任务**：
- 实现RequestVote RPC
- 领导者定期发送心跳（空AppendEntries RPC）
- 选举超时设置：150-300毫秒（需适配测试框架限制）

**关键提示**：
```go
type Raft struct {
    currentTerm int        // 必须持久化
    votedFor    int        // 必须持久化
    log         []LogEntry // 操作日志
    state       StateType  // 节点状态
    // 其他字段见论文图2
}
```

##### 3B阶段：日志复制（高难度）
**实现要点**：
1. 日志索引从1开始（建议用0作为虚拟起始条目）
2. 实现选举限制条件（论文5.4.1节）
3. 通过applyCh提交已共识日志

**日志快速回滚优化**：
```go
type AppendEntriesReply struct {
    Term    int
    Success bool
    XTerm  int // 冲突条目的任期
    XIndex int // 该任期的首个索引
    XLen   int // 日志长度
}
```

##### 3C阶段：持久化（高难度）
**关键方法**：
```go
func (rf *Raft) persist() {
    w := new(bytes.Buffer)
    e := labgob.NewEncoder(w)
    e.Encode(rf.currentTerm)
    e.Encode(rf.votedFor)
    e.Encode(rf.log)
    rf.persister.Save(w.Bytes(), nil)
}
```

##### 3D阶段：日志压缩（高难度）
**核心接口**：
```go
func (rf *Raft) Snapshot(index int, snapshot []byte) {
    rf.mu.Lock()
    defer rf.mu.Unlock()
    
    if index <= rf.lastIncludedIndex {
        return
    }
    // 截断日志并保存快照
    rf.log = rf.log[index-rf.lastIncludedIndex:]
    rf.lastIncludedTerm = rf.log[0].Term
    rf.lastIncludedIndex = index
    rf.persister.Save(rf.persistData(), snapshot)
}
```

#### 测试与评分
**测试输出示例**：
```bash
$ go test -run 3A
Test (3A): initial election...
  ... Passed --   3.6  3   106    0
# 参数说明：时间(秒) 节点数 RPC次数 提交日志数
```

**评分标准**：
1. 所有测试总时间不超过600秒
2. 单个测试不超过120秒
3. 必须通过竞态检测（-race）

#### 调试建议
1. 使用可视化时间线分析失败案例
2. 添加调试标记：
```go
tester.Annotate("Server 1", "Election timeout", "Term 3")
```
3. 多次运行测试确保稳定性：
```bash
for i in {1..10}; do go test -run 3B; done
```

#### 性能指标
| 测试模式       | 最大实际时间 | 最大CPU时间 |
|----------------|--------------|-------------|
| 非竞态模式     | 6分钟        | 1分钟       |
| 竞态检测模式   | 10分钟       | 2分钟       |

> 注：所有技术术语（如Raft/AppendEntries等）保留英文原名，代码块严格保持原始格式。实验分为四个阶段提交，每个阶段有独立截止日期。