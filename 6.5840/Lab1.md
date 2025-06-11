### 6.5840 - 2025年春季  
[MIT - 6.824 全课程 + Lab 博客总览-CSDN博客](https://blog.csdn.net/weixin_51322383/article/details/132307746)
[詠夏日記 - Blog](https://blog.yomi.moe/)
[Kaede's Blog](https://blog.akinokae.de/)
#### 6.5840 实验1：MapReduce  

---

### 简介  
在本实验中，你将构建一个MapReduce系统。你需要实现一个**工作进程（worker）和一个协调进程（coordinator）**：  
- **工作进程**负责调用应用程序的Map和Reduce函数，处理文件读写。  
- **协调进程**负责任务分配，并处理工作进程的故障。  
（注：本实验使用"coordinator"替代论文中的"master"。）

---

### 实验准备  
1. **配置Go环境**  
   确保已安装Go语言环境。  

2. **获取实验代码**  
   通过git克隆初始代码库：  
   ```bash  
   $ git clone git://g.csail.mit.edu/6.5840-golabs-2025 6.5840  
   $ cd 6.5840  
   $ ls  
   Makefile src  
   ```  

3. **示例程序**  
   - 顺序执行的MapReduce实现：`src/main/mrsequential.go`  
   - 提供的应用：  
     - 词频统计：`mrapps/wc.go`  
     - 文本索引：`mrapps/indexer.go`  

   运行词频统计示例：  
   ```bash  
   $ cd src/main  
   $ go build -buildmode=plugin ../mrapps/wc.go  # 编译插件  
   $ rm mr-out*  
   $ go run mrsequential.go wc.so pg*.txt        # 运行顺序版本  
   $ more mr-out-0                               # 查看输出  
   A 509  
   ABOUT 2  
   ACT 8  
   ...  
   ```  
   - 输入文件：`pg-xxx.txt`  
   - 输出文件：`mr-out-0`  

---

### 你的任务
#### 目标  
实现分布式MapReduce系统：  
1. **协调器（1个进程）**  
   - 分配任务（Map/Reduce）给工作器  
   - 处理工作器故障（10秒超时后重新分配任务）  

2. **工作器（多个并行进程）**  
   - 循环请求任务 → 执行任务 → 提交结果  
   - 通过RPC与协调器通信  

#### 文件结构  
- **禁止修改**：`main/mrcoordinator.go`, `main/mrworker.go`  
- **实现位置**：  
  - 协调器逻辑：`mr/coordinator.go`  
  - 工作器逻辑：`mr/worker.go`  
  - RPC通信：`mr/rpc.go`  

#### 运行流程  
1. 编译词频统计插件：  
   ```bash  
   $ go build -buildmode=plugin ../mrapps/wc.go  
   ```  
2. 启动协调器（输入文件为`pg-*.txt`）：  
   ```bash  
   $ rm mr-out*  
   $ go run mrcoordinator.go pg-*.txt  
   ```  
3. 启动工作器（需另开终端）：  
   ```bash  
   $ go run mrworker.go wc.so  
   ```  
4. 验证输出：  
   ```bash  
   $ cat mr-out-* | sort | more  
   A 509  
   ABOUT 2  
   ACT 8  
   ...  
   ```  

#### 测试脚本  
```bash  
$ bash test-mr.sh  
*** Starting wc test.  
--- wc test: PASS  
*** Starting indexer test.  
--- indexer test: PASS  
...  
*** PASSED ALL TESTS  
```  
- 测试内容：  
  - 正确性（词频统计、索引器）  
  - 并行性（Map/Reduce任务并发）  
  - 容错性（工作器崩溃恢复）  

---

### 规则与提示  
#### 关键规则  
1. **中间文件分桶**  
   - Map阶段需将中间键分到`nReduce`个桶中（对应Reduce任务数）。  
   - 命名格式：`mr-X-Y`（X为Map任务编号，Y为Reduce任务编号）。  

2. **输出格式**  
   - Reduce输出文件：`mr-out-X`  
   - 每行格式：`%v %v`（键 值），参考`mrsequential.go`中的注释。  

3. **进程终止**  
   - 协调器的`Done()`返回`true`时，所有进程退出。  
   - 工作器若无法联系协调器，可自行终止。  

#### 技术提示  
- **JSON序列化**：用`encoding/json`读写中间键值对文件。  
   ```go  
   // 写入示例  
   enc := json.NewEncoder(file)  
   enc.Encode(&kv)  

   // 读取示例  
   dec := json.NewDecoder(file)  
   dec.Decode(&kv)  
   ```  
- **并发控制**：协调器需加锁保护共享状态。  
- **超时处理**：任务超时设为10秒。  
- **原子文件写入**：使用临时文件+`os.Rename`避免崩溃导致数据损坏。  

#### 调试建议  
- 使用Go竞态检测：`go run -race`  
- 测试中间文件：查看`mr-tmp/`目录  
- 多次运行测试：`bash test-mr-many.sh 10`（重复10次）  

---

### 额外挑战（不计分）  
1. **实现新应用**：如分布式Grep（参考MapReduce论文2.3节）。  
2. **多机部署**：  
   - 协调器与工作器运行在不同机器  
   - RPC改用TCP/IP（非Unix Socket）  
   - 共享文件系统（如AWS S3）  

--- 

（注：技术术语如Map/Reduce、RPC等保留英文，长句按中文习惯拆分，关键操作步骤保留代码块格式。）