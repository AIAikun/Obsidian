#  find查看命令
Linux find 命令用于在指定目录下查找文件和目录，它可以使用不同的选项来过滤和限制查找的结果。
语法
`find [路径] [匹配条件][动作]`
匹配条件常用部分：
- `name pattern`：按文件名查找，支持使用通配符 `*` 和 `?`。
- `type type`：按文件类型查找，可以是 `f`（普通文件）、`d`（目录）、`l`（符号链接）等。
- `user username`：按文件所有者查找。
- `group groupname`：按文件所属组查找。
**动作:** 可选的，用于对匹配到的文件执行操作，比如删除、复制等。
find 命令中用于时间的参数如下：
- amin n`：查找在 n 分钟内被访问过的文件。
- `time n`：查找在 n24 小时内被访问过的文件。
- `cmin n`：查找在 n 分钟内状态发生变化的文件（例如权限）。
- `ctime n`：查找在 n*24 小时内状态发生变化的文件（例如权限）。
- `mmin n`：查找在 n 分钟内被修改过的文件。
- `mtime n`：查找在 n24小时内被修改过的文件
# 进程管理
[参考](https://www.cnblogs.com/8313tzx/p/17863457.html)
[参考](https://www.freecodecamp.org/chinese/news/how-to-manage-linux-processes/)
#### 1. **什么是 Linux 进程**
理论上，一个进程被称为一个正在执行的程序，就是一个系统目前正在进行的任务。你在系统上的每一个动作都会导致一个新的进程。用户的操作被转化为一个命令，在执行该命令时将会创建一个新的进程。
每一个进程都有唯一的一个PID号码标识自己，系统启动后的第一个进程是init，它的PID是1。init是唯一一个由系统内核直接运行的进程。除了init之外，每个进程都有父进程（PPID标识）
- `ps`：显示当前系统中的所有进程。
- `top`：实时显示当前系统中的进程状态。
- `pstree`：显示进程的树形结构。
#### 2. 前台进程和后台进程
- `前台进程` 指一个程序控制着标准输入/输出，在程序运行时，shell 被暂时挂起，直到该程序运行结束后，才退回到 shell。在这个过程中，用户不能再执行其它程序
- `后台进程` 用户不必等待程序运行结束就可以执行其它程序。运行后台进程的方法是在命令行最后加上 “&”
#### 3. 作业控制
- `bg`：将暂停的进程转到后台运行。
- `fg`：将后台进程转到前台运行。
#### 4. 信号控制
可以使用信号来控制后台作业的行为。信号是一种发送给进程的软件中断，用于通知进程执行特定的操作。以下是一些常用的信号和它们的作用：
- `SIGKILL`：终止进程。
- `SIGINT`：中断进程。
- `SIGQUIT`：终止进程并产生 core 文件。
- `SIGSTOP`：停止进程。
- `SIGCONT`：恢复进程的运行。
`kill -SIGKILL pid`
#### 5. 父进程子进程
每个进程都有父进程
子进程会继承父进程的全局变量
# systemd守护进程
参考连接：<https://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html>
#### 1. 系统管理
1. systemctl
`systemctl`是 Systemd 的主命令，用于管理系统
````bash
# 重启系统
$ sudo systemctl reboot

# 关闭系统，切断电源
$ sudo systemctl poweroff

# CPU停止工作
$ sudo systemctl halt

# 暂停系统
$ sudo systemctl suspend

# 让系统进入冬眠状态
$ sudo systemctl hibernate

# 让系统进入交互式休眠状态
$ sudo systemctl hybrid-sleep

# 启动进入救援状态（单用户状态）
$ sudo systemctl rescue
````
2. systemd-analyze
`systemd-analyze`命令用于查看启动耗时。
````bash
# 查看启动耗时
$ systemd-analyze                                                                                       

# 查看每个服务的启动耗时
$ systemd-analyze blame
````
3. hostnamectl
`hostnamectl`命令用于查看当前主机的信息。
````bash
# 显示当前主机的信息
$ hostnamectl

# 设置主机名。
$ sudo hostnamectl set-hostname rhel7
````
4. localectl
`localectl`命令用于查看本地化设置。
````bash
# 查看本地化设置
$ localectl

# 设置本地化参数。
$ sudo localectl set-locale LANG=en_GB.utf8
$ sudo localectl set-keymap en_GB
````
5. timedatectl
`timedatectl`命令用于查看当前时区设置。
````bash
# 查看当前时区设置
$ timedatectl

# 显示所有可用的时区
$ timedatectl list-timezones                                                                                   

# 设置当前时区
$ sudo timedatectl set-timezone America/New_York
$ sudo timedatectl set-time YYYY-MM-DD
$ sudo timedatectl set-time HH:MM:SS
````
6.  loginct
`loginctl`命令用于查看当前登录的用户。
````bash
# 列出当前session
$ loginctl list-sessions

# 列出当前登录用户
$ loginctl list-users

# 列出显示指定用户的信息
$ loginctl show-user ruanyf
````
#### 2. Unit(单位)
##### 2.1含义
Systemd 可以管理所有系统资源。不同的资源统称为 Unit（单位）。Unity分为12种。
- Service unit：系统服务
- Target unit：多个 Unit 构成的一个组
- Device Unit：硬件设备
- Mount Unit：文件系统的挂载点
- Automount Unit：自动挂载点
- Path Unit：文件或路径
- Scope Unit：不是由 Systemd 启动的外部进程
- Slice Unit：进程组
- Snapshot Unit：Systemd 快照，可以切回某个快照
- Socket Unit：进程间通信的 socket
- Swap Unit：swap 文件
- Timer Unit：定时器
`systemctl list-units`命令可以查看当前系统的所有 Unit 。
##### 2.2 Unit的状态
`systemctl status`命令用于查看系统状态和单个 Unit 的状态。
````bash
# 显示系统状态
$ systemctl status

# 显示单个 Unit 的状态
$ sysystemctl status bluetooth.service
````
##### 2.3 Unit管理
对于用户来说，最常用的是下面这些命令，用于启动和停止 Unit（主要是 service）。
````bash
# 立即启动一个服务
$ sudo systemctl start apache.service

# 立即停止一个服务
$ sudo systemctl stop apache.service

# 重启一个服务
$ sudo systemctl restart apache.service

# 杀死一个服务的所有子进程
$ sudo systemctl kill apache.service

# 重新加载一个服务的配置文件
$ sudo systemctl reload apache.service

# 重载所有修改过的配置文件
$ sudo systemctl daemon-reload

# 显示某个 Unit 的所有底层参数
$ systemctl show httpd.service

# 显示某个 Unit 的指定属性的值
$ systemctl show -p CPUShares httpd.service

# 设置某个 Unit 的指定属性
$ sudo systemctl set-property httpd.service CPUShares=500
````
##### 2.4依赖关系
Unit 之间存在依赖关系：A 依赖于 B，就意味着 Systemd 在启动 A 的时候，同时会去启动 B。`systemctl list-dependencies`命令列出一个 Unit 的所有依赖。
````bash
$ systemctl list-dependencies nginx.service
````
上面命令的输出结果之中，有些依赖是 Target 类型，默认不会展开显示。如果要展开 Target，就需要使用`--all`参数。
````bash
$ systemctl list-dependencies --all nginx.service
````
#### 3. Unit的配置文件
##### 3.1 概述
每一个 Unit 都有一个配置文件，告诉 Systemd 怎么启动这个 Unit 。
Systemd 默认从目录`/etc/systemd/system/`读取配置文件。但是，里面存放的大部分文件都是符号链接，指向目录`/usr/lib/systemd/system/`，真正的配置文件存放在那个目录。
`systemctl enable`命令用于在上面两个目录之间，建立符号链接关系。
````bash
$ sudo systemctl enable clamd@scan.service
# 等同于
$ sudo ln -s '/usr/lib/systemd/system/clamd@scan.service' '/etc/systemd/system/multi-user.target.wants/clamd@scan.service'
````
如果配置文件里面设置了开机启动，`systemctl enable`命令相当于激活开机启动。
与之对应的，`systemctl disable`命令用于在两个目录之间，撤销符号链接关系，相当于撤销开机启动。
````bash
$ sudo systemctl disable clamd@scan.service
````
配置文件的后缀名，就是该 Unit 的种类，比如`sshd.socket`。如果省略，Systemd 默认后缀名为`.service`，所以`sshd`会被理解成`sshd.service`。
##### 3.2配置文件的状态 
`systemctl list-unit-files`命令用于列出所有配置文件。
````bash
# 列出所有配置文件
$ systemctl list-unit-files

# 列出指定类型的配置文件
$ systemctl list-unit-files --type=service
````
这个命令会输出一个列表。列表显示每个配置文件的状态，一共有四种。
- enabled：已建立启动链接。
-  disabled：没建立启动链接。
- static：该配置文件没有`[Install]`部分（无法执行），只能作为其他配置文件的依赖。
- masked：该配置文件被禁止建立启动链接。
注意：从配置文件的状态无法看出，该 Unit 是否正在运行。这必须执行前面提到的`systemctl status`命令。
一旦修改配置文件，就要让 Systemd重新加载配置文件，然后重新启动，否则修改不会生效。
````bash
$ sudo systemctl daemon-reload
$ sudo systemctl restart httpd.service
````
##### 3.3 配置文件的格式
配置文件就是普通的文本文件，可以用文本编辑器打开。`systemctl cat`命令可以查看配置文件的内容。
配置文件分成几个区块。每个区块的第一行，是用方括号表示的区别名，比如`[Unit]`。注意，配置文件的区块名和字段名，都是大小写敏感的。
每个区块内部是一些等号连接的键值对，而且键值对的等号两侧不能有空格。
##### 3.4 配置文件的区块
`[Unit]`区块通常是配置文件的第一个区块，用来定义 Unit 的元数据，以及配置与其他 Unit 的关系。
`Install]`通常是配置文件的最后一个区块，用来定义如何启动，以及是否开机启动。它的主要字段如下。
`[Service]`区块用来 Service 的配置，只有 Service 类型的 Unit 才有这个区块。它的主要字段如下。
Unit 配置文件的完整字段清单，请参考[官方文档](https://www.freedesktop.org/software/systemd/man/systemd.unit.html)。
#### 4. Target
启动计算机的时候，需要启动大量的 Unit。如果每一次启动，都要一一写明本次启动需要哪些 Unit，显然非常不方便。Systemd 的解决方案就是 Target。
简单说，Target 就是一个 Unit 组，包含许多相关的 Unit 。启动某个 Target 的时候，Systemd 就会启动里面所有的 Unit。从这个意义上说，Target 这个概念类似于"状态点"，启动某个 Target 就好比启动到某种状态。
传统的`init`启动模式里面，有 RunLevel 的概念，跟 Target 的作用很类似。不同的是，RunLevel 是互斥的，不可能多个 RunLevel 同时启动，但是多个 Target 可以同时启动。
````bash
# 查看当前系统的所有 Target
$ systemctl list-unit-files --type=target

# 查看一个 Target 包含的所有 Unit
$ systemctl list-dependencies multi-user.target

# 查看启动时的默认 Target
$ systemctl get-default

# 设置启动时的默认 Target
$ sudo systemctl set-default multi-user.target

# 切换 Target 时，默认不关闭前一个 Target 启动的进程，
# systemctl isolate 命令改变这种行为，
# 关闭前一个 Target 里面所有不属于后一个 Target 的进程
$ sudo systemctl isolate multi-user.target
````
#### 5. 日志管理
Systemd 统一管理所有 Unit 的启动日志。带来的好处就是，可以只用`journalctl`一个命令，查看所有日志（内核日志和应用日志）。日志的配置文件是`/etc/systemd/journald.conf`。
````bash
# 查看所有日志（默认情况下 ，只保存本次启动的日志）
$ sudo journalctl
# 查看内核日志（不显示应用日志）
$ sudo journalctl -k
# 查看系统本次启动的日志
$ sudo journalctl -b
$ sudo journalctl -b -0
# 实时滚动显示最新日志
$ sudo journalctl -f
# 查看指定服务的日志
$ sudo journalctl /usr/lib/systemd/systemd
# 查看指定进程的日志
$ sudo journalctl _PID=1
````
# 重定向
[参考](https://www.runoob.com/linux/linux-shell-io-redirections.html)
在编程和脚本编写中，重定向（redirection）是一种改变程序输出或输入流的目的地的技术。在 Bash 脚本和命令行中，重定向经常用来控制命令的输入和输出，使其可以被发送到文件、从文件中读取，或者在不同的命令和程序之间传递
一般情况下，每个 Unix/Linux 命令运行时都会打开三个文件：
- 标准输入文件(stdin)：stdin的文件描述符为0，Unix程序默认从stdin读取数据。
- 标准输出文件(stdout)：stdout 的文件描述符为1，Unix程序默认向stdout输出数据。
- 标准错误文件(stderr)：stderr的文件描述符为2，Unix程序会向stderr流中写入错误信息。
#### 重定向的操作
- `>`:输出重定向
    
- `<`输入重定向
    
- `>>`追加重定向
    
- `>&`描述符修改，比如`2>&1`,错误输出指向标准输出
    
- `<&`描述符复制 ，比如`4<&1`,`4`为`1`的副本
    
- `<>()`建立管道
    
#### 管道
[参考](https://www.jianshu.com/p/9c0c2b57cb73)
管道是一种通信机制，通常用于进程间的通信，它表现出来的形式将前面每一个进程的输出（stdout）直接作为下一个进程的输入（stdin）。
`ls * | grep *.c | vim -` 管道实例，`-`代表标准输出
`tee` 保存管道的输入内容，同时传递给下一个管道
#### 例：
经典的组面题 - 如何输出一个文件夹的前 / 后 X 个文件的文件名
- 前X个文件（按字母顺序）：
`ls | sort | head -n X`
- 后X个文件（按字母顺序的逆序）：
`ls | sort -r | head -n X`
如何输出最新的X个文件
`ls -lt | head -n 5`
# 构建工具make
 安排编译的先后、链接等等的工具就是make
[参考](https://www.liaoxuefeng.com/wiki/1599771213037600)
## Makefile
  核心的语句其实就一个

```C++
target … : prerequisites …
        recipe
        …
        …
```

  如果你想得到_target_，那么你提前要有_prerequisites，_然后去用_recipe_得到_target。_

#### 一个简单的例子

```Makefile
dian.txt: student.txt teacher.txt
    cat student.txt teacher.txt > dian.txt
student.txt: /bin/vim
    vim student.txt
teacher.txt: /bin/vim
    vim teacher.txt
/bin/vim:
    sudo apt install vim
clean:
    rm -f ./student.txt ./teacher.txt ./dian.txt 
```

  试试`make dian.txt`？

  如果先`make student.txt`再`make dian.txt`呢？

  如果在你make的时候，target已经存在，并且它对应的prerequisites都没有修改过，那么他也会再生成一遍吗？

## makefile语法（简化）

  我们写一个最简单的例子。

```Makefile
main1: add.o minus.o mul.o main1.o square.o 
    gcc -o main1 add.o minus.o mul.o main1.o square.o
main2: add.o minus.o mul.o main2.o square.o 
    gcc -o main2 add.o minus.o mul.o main2.o square.o
add.o: add.c add.h
    gcc -c add.c
minus.o: minus.c minus.h 
    gcc -c minus.c
mul.o: mul.c mul.h 
    gcc -c mul.c
square.o: square.c square.h 
    gcc -c square.c
main1.o: main1.c 
    gcc -c main1.c
main2.o: main2.c
    gcc -c main2.c
clean:
    rm -f ./*.o main1 main2
```

又臭又长

makefile有很多语法，这些语法可以帮助我们简化它，

- 变量：
    

```Makefile
fuc = add.o minus.o mul.o square.o 
main1: ${fuc} main1.o 
    gcc -o main1 ${fuc} main1.o 
...
```

- 自动推导
    

  根据{file}.o,推到要用{file}.c和gcc编译

```Makefile
add.o: add.h
minus.o: minus.h 
mul.o: mul.h 
square.o: square.h 
main1.o: main1.c 
main2.o: main2.c
```
## 例：
对于Makefile⼯具，可以考虑如何通过写Makefile启动你的项⽬。比如通过 make start启动项⽬⽽不是使⽤裸命令。
`touch Makefile // 新建Makefile`
`vim Makefile`
makefile内容如下
`start:
	go run ./main.go -arg1 -arg2 -arg3`