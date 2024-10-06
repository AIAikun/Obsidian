# 培训大纲

## Linux系统基础

- 环境变量
    
- 进程管理
    
- 重定向
    
- Bash脚本
    
      .bashrc .profile
    

## Git

Git的基本概念

Git的基本操作:

- 建立、克隆仓库
    
- 修改、提交
    
- 推送
    
- 分支管理
    
- 撤销修改
    
- ssh密钥认证
    
- Ssh-agent
    

## 序章

### 问题1：怎么学好计算机相关的东西？

互联网上我们能接触到的资料其实可以分为两种，中文互联网和外文互联网，后者是整个计算机的发源地，前者是学习追赶的后浪。这就意味着如果你仅仅想入门使用的话，中文互联网够了，但是如果想要深入的研究某个问题，你必须去英文社区阅读英文。尽管中文互联网仍然有很多优秀的文档，但是英文才是计算机原文档的第一语言，很多中文文档都是直接翻译的英文文档，这样会丢失很多原文档的原信息，同时夹带翻译带来的曲解，并且中文互联网又是一大抄，各种二次山寨的文章泛滥，导致信息混乱，良莠不齐。

当然作为初学者的我们还没有入门这个领域，可以选择中文文档建立基本的概念。

这里推荐一个[自学网站](https://csdiy.wiki/)，几乎包罗了一个计算机/信息领域大学生所需的全部课程。

### 问题2：有没有其他教程推荐？

Bash教程推荐：**[阮一峰 Bash 脚本教程](https://www.bookstack.cn/books/bash-tutorial)**

Git教程推荐：官方[教程](https://git-scm.com/book/zh/v2/)

## Linux系统基础

### 环境变量

[参考](https://www.freecodecamp.org/chinese/news/how-to-set-an-environment-variable-in-linux/)

在编程时，你使用变量来临时存储信息，如字符串和数字，变量可以在整个代码中反复使用，或者由你的操作系统提供数值。你可以编辑它们、覆盖它们，并删除它们，在本教程中，我将教你什么是环境变量以及如何在 Linux 中设置它们。

环境变量是特定环境中的变量。例如，操作系统中的每个用户都有自己的环境，一个管理员用户拥有与其他用户不同的环境。下面是一些常见的环境变量

- `USER` 这指的是当前登录的用户。
    
- `HOME` 这显示了当前用户的主目录。
    
- `SHELL` 这存储了当前用户的 shell 路径，如 bash 或 zsh。
    
- `LANG` 这个变量指向当前的语言 /locales 设置。
    
- `MAIL` 这显示了当前用户的邮件存储的位置。
    

#### 查看环境变量

- `env` 查看所有环境变量
    
- `printenv VARIABLE_NAME` 查看单个环境变量
    
- `echo $varname` 查看单个环境变量
    

#### 创建环境变量

- `var=value` 创建局部变量
    
- `export var=value` 创建全局环境变量
    

有何区别见下文的进程

#### 环境变量的分类

环境变量分为数字类型、字符串类型

- `$((a+4))` 提供数学表达式功能呢
    

### 进程管理

[参考](https://www.cnblogs.com/8313tzx/p/17863457.html)

[参考](https://www.freecodecamp.org/chinese/news/how-to-manage-linux-processes/)

#### **什么是 Linux 进程**

理论上，一个进程被称为一个正在执行的程序，就是一个系统目前正在进行的任务。你在系统上的每一个动作都会导致一个新的进程。例如，打开一个浏览器就会启动一个进程。简单地说，一个进程是一个程序的实例。用户的操作被转化为一个命令，在执行该命令时将会创建一个新的进程。

每一个进程都有唯一的一个PID号码标识自己，系统启动后的第一个进程是init，它的PID是1。init是唯一一个由系统内核直接运行的进程。除了init之外，每个进程都有父进程（PPID标识）

#### 查看系统进程

- `ps`：显示当前系统中的所有进程。
    
- `top`：实时显示当前系统中的进程状态。
    
- `pstree`：显示进程的树形结构。
    

#### 前台进程和后台进程

- `前台进程` 指一个程序控制着标准输入/输出，在程序运行时，shell 被暂时挂起，直到该程序运行结束后，才退回到 shell。在这个过程中，用户不能再执行其它程序
    
- `后台进程` 用户不必等待程序运行结束就可以执行其它程序。运行后台进程的方法是在命令行最后加上 “&”
    

#### 作业控制

- `bg`：将暂停的进程转到后台运行。
    
- `fg`：将后台进程转到前台运行。
    

#### 信号控制

可以使用信号来控制后台作业的行为。信号是一种发送给进程的软件中断，用于通知进程执行特定的操作。以下是一些常用的信号和它们的作用：

- `SIGKILL`：终止进程。
    
- `SIGINT`：中断进程。
    
- `SIGQUIT`：终止进程并产生 core 文件。
    
- `SIGSTOP`：停止进程。
    
- `SIGCONT`：恢复进程的运行。
    

`kill -SIGKILL pid`

#### 父进程子进程

每个进程都有父进程

子进程会继承父进程的全局变量

  

### 重定向

  

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

### Bash脚本

[参考](https://www.runoob.com/linux/linux-shell.html)

#### 基本概念

`shell` Shell 是一种命令行界面，它提供了用户与操作系统交互的途径,可以是`sh`、`bash`、`zsh`等等

`bash`bash是一种命令，但是bash是一个可以提供shell的命令，同样也可以指向脚本

`bash script` 用bash来解释的脚本文件

#### 基本写法

```Bash
#!/bin/bash 
# 第一行的写法表示该脚本使用的解释器
# 使用#来写注释
...
# 可以声明变量,注意等号之间不能有空格
a=1
b=test
```

#### 变量引用

- `$var`：引用变量
    
- `"$var"`：在字符串内替换变量
    
- `${var}`：引用变量，拓展引用提供更多的功能
    
- `'$var'`：视为普通字符串
    
- `$((var))`：数学表达式
    

#### **shell变量**

Shell 提供了一些内置的特殊变量，例如：

- `$0`: 脚本的名称。
    
- `$1`, `$2`, ...: 传递给脚本的第一个、第二个等参数。
    
- `$#` 传递到脚本的参数个数
    
- `$*` 显示所有向脚本传递的参数 #与位置变量不同，此选项参数可超过9个
    
- `$$` 获取当前shell的进程号
    
- `$!` 执行上一个指令的进程号
    
- `$?` 获取执行的上一个指令的返回值 #0为执行成功，非零为执行失败
    
- `$-` 显示shell使用的当前选项，与set命令功能相同
    
- `$@` 与$*相同，但是使用时加引号，并在引号中返回每个参数
    

#### 拓展写法

##### **条件控制**

```Plaintext
if [ conditions ]
then
        commands
elif [ conditions ]
    then 
        commands
else
    commands
fi
```

##### **遍历控制**

```Plaintext
for i in {1..5}
do 
    echo $i
done

for x in string1 string2 string3
do 
    echo $x
done
```

##### **循环控制**

```Plaintext
i=1
while [[ $i -le 10 ]] ; do
   echo "$i"
  (( i += 1 ))
done
```

##### 定义函数

```Bash
#!/bin/bash

demoFun(){
    echo "这是我的第一个 shell 函数!"
}
echo "-----函数开始执行-----"
demoFun 
echo "-----函数执行完毕-----"
```

##### 条件表达

数字比较

```Plaintext
-eq -ge -gt -le -lt -ne
```

字符串比较

```Plaintext
== != 
```

#### .bashrc

[参考](https://blog.csdn.net/Heyyellman/article/details/111565781)

`.bashrc`是home目录下的一个shell文件，用于储存用户的个性化设置。在bash每次启动时都会加载`.bashrc`文件中的内容，并根据内容定制当前bash的配置和环境。

`.profile`文件类似

#### 脚本启动的多种方式

`bash/sh xx.sh`：启动一个子进程运行脚本，脚本中的全局变量不会被当前的Bash继承

`./xx.sh`：需要具有执行权限，需要在第一行指定解释器，效果通bash xx.sh

`source xx.sh`：在当前的bash中执行，可以继承脚本的全局变量

### 加餐

为什么叫加餐呢？我想大概是下面的内容在中文互联网我几乎遇不到，只有在逛英文社区的时候我才遇到这些有趣的东西，意思是给在中文互联网的你加一加来自英文社区的餐，感受一下来自互联网发源地的震撼

#### 命令行的艺术

下面的内容可以在行编辑的时候加快你的行为

- CTRL-a: 跳到结束
    
- CTRL-e: 跳到结尾
    
- CTRL-u：删除到开头
    
- CTRL-k：删除到结尾
    
- CTRL-w；删除到上一个单词开头
    
- CTRL-x：选中上一次修改
    
- CTRL-b: 后退一个单词
    
- CTRL-f: 前进一个单词
    
- CTRL-y: 回退修改
    

命令行默认可以转换为`vi`和`emacs`的编辑模式

- set -o emacs
    
- set -o vi
    

#### 目录树

- dirs：查看目录树
    
- pushd ：压入目录树
    
- popd：弹出目录树
    
- Cd -:进入上一次目录
    
- Cd ~n：进入目录树的第几个
    

## Git

[参考](https://www.liaoxuefeng.com/wiki/896043488029600)

[参考](https://www.runoob.com/git/git-tutorial.html)

这里有一份官方[教程](https://git-scm.com/book/zh/v2/)

### **基本概念**

`Git`:Git是一种去中心化的版本管理工具

`Svn`:Svn是一种中心化的版本管理工具

`Github`: Github是一个用Git工具来管理的代码托管平台。Gitee同理

#### **工作区、暂存区、仓库**

工作区:当前的工作目录

暂存区:你追踪的修改

仓库区:你提交的修改（分为本地和远程）

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDE0MzJjOWNkZTUyNjJiYjE0YWRhZTM3NmRkYjdmYTJfTHhWTmlXRGpaVVJPVTN6TlBGa2dTTDFCZzg3V05kWDRfVG9rZW46UG5xb2JEdG5EbzdqSHN4MFRtUGNmeEo1blNoXzE3MjgyMDYxMDU6MTcyODIwOTcwNV9WNA)

  

### **基本命令**

**本地管理**

下面是一常用的命令

`git init` 初始化本地仓库

`git add .` 添加追踪文件

注意第一次提交前需要配置

```Bash
git config --global user.name  yourname
git config --global user.email  youremail
```

`git commit -m` 提交修改

`git commit --amend -m ""` 覆盖上一次提交

`git status`查看当前工作区状态

`git status -s`

`git log`查看本地仓库的提交记录

`git log --oneline --graph --all`

#### Git add

`git add` 是 Git 版本控制系统中的一个命令，用于将更改添加到暂存区（staging area 或 index）。暂存区是一个临时存放更改的地方，它允许你预先选择哪些更改将被包含在下一次提交（commit）中。

- **添加单个文件**:
    

```Bash
git add <file>
```

- 将指定的 `<file>` 文件添加到暂存区。如果文件尚未被跟踪（即之前没有被提交过），你需要先使用 `git add` 添加它，Git 才会开始跟踪这个文件。
    
- **添加多个文件**:
    

```Bash
git add <file1> <file2> ...
```

- 你可以一次添加多个文件到暂存区。
    
- **添加当前目录下的所有更改**:
    

```Bash
git add .
```

- 使用点（`.`）作为参数，表示添加当前目录及其所有子目录下的所有更改。
    
- **添加特定模式的文件**:
    

```Bash
git add '*.txt'
```

- 使用通配符（如 `*`）可以添加所有匹配该模式的文件。在这个例子中，所有 `.txt` 文件都会被添加到暂存区。
    
- **添加所有更改**:
    

```Bash
git add -A
```

- `-A` 选项（或 `--all`）会添加所有更改，包括新文件、修改过的文件和已删除的文件。
    

#### Git commit

`git commit` 是 Git 版本控制系统中的一个核心命令，用于将暂存区（staging area）中的更改永久保存到仓库历史中。每次提交都是仓库的一个快照，记录了文件在特定时间点的状态。提交时，你需要提供一个提交信息（commit message），用于描述这次更改的内容和目的。

- **提交暂存区中的更改**:
    

```Bash
git commit -m "Your commit message"
```

- `-m` 选项后面跟着的是你提交信息的简短描述。提交信息应该简洁明了，说明更改的内容和原因。
    
- **使用文本编辑器编写提交信息**:
    

```Bash
git commit
```

- 如果不使用 `-m` 选项，Git 会调用默认的文本编辑器（配置在 `core.editor` 中），让你输入提交信息。在提交信息中，你可以提供更详细的更改描述。
    

#### Git status

`git status` 是 Git 版本控制系统中的一个命令，用于显示当前工作目录和暂存区的状态。这个命令会列出有更改的文件、未跟踪的新文件、以及暂存区和上次提交之间的差异。`git status` 是非常有用的，因为它可以帮助你了解哪些更改已经暂存，哪些更改还没有暂存，以及哪些文件被 Git 跟踪。

- **查看状态**:
    

```Bash
git status
```

- 这将显示当前分支的信息、更改的文件列表，以及工作目录和暂存区的状态。
    

**输出说明**

- **On branch**: 显示你当前所在的分支名。
    
- **Changes not staged for commit**: 列出已修改但尚未暂存的文件。
    
- **Changes to be committed**: 列出已暂存的文件，这些更改将在下一次提交时被保存。
    
- **Untracked files**: 列出新文件，这些文件还没有被 Git 跟踪。
    
- **Both** **modified** **and deleted**: 如果文件被修改并删除，它们会同时出现在两个列表中
    

**文件状态说明**

1. **未跟踪 (Untracked)**:
    
2. **已修改 (****Modified****)**:
    
3. **已暂存 (Staged)**:
    
4. **未合并 (Unmerged)**:
    
5. **已删除 (Deleted)**:
    
6. **忽略 (Ignored)**:
    
7. **类型变更 (Typechange)**:
    

#### Git log

`git log` 是 Git 版本控制系统中用于查看提交历史记录的命令。通过 `git log`，你可以查看所有的提交记录，包括每次提交的作者、日期、提交信息以及更改的内容。这个命令对于理解项目的历史变更和追踪特定问题的发展非常有用。

- **查看提交历史**:
    

```Bash
git log
```

- 这将显示当前分支的提交历史，每个提交占据一行。
    

### **Git配置**

  

`Git`通过`.gitconfig`文件来管理配置，通常而言会有三份，分为`system`，`global`，`local`三个级别，当`Git`需要读取配置的时候优先级是`local>global>system`,local文件存在于你当前的git仓库里，`global`存在于你的家目录，`system`存在于系统目录

```Bash
[core]
    sshCommand = C:/Windows/System32/OpenSSH/ssh.exe
[user]
    email = xxx
    name = xxx
```

  

`git config --local --list` 查看本地配置

`git config --list --show-origin` 查看所以配置并且列出来源

`git config` 是 Git 版本控制系统中的一个命令，用于获取和设置配置变量。这些配置变量可以是全局的（影响整个系统上的 Git 行为）、局部的（只影响当前仓库的行为），或者是针对单个用户的。

#### Git config

- **查看所有 Git 配置**:
    
    ```Bash
    git config --list
    ```
    
- **查看特定 Git 配置**:
    
    ```Bash
    git config <key>
    ```
    
      例如，要查看 `user.name` 的配置值，可以执行：
    
    ```Bash
    git config user.name
    ```
    

  

- **设置 Git 配置**:
    
    ```Bash
    git config --global <key> <value>
    ```
    
      例如，设置全局用户名：
    
    ```Bash
    git config --global user.name "Your Name"
    ```
    
      设置全局电子邮件地址：
    
    ```Bash
    git config --global user.email "your_email@example.com"
    ```
    

  

**选项**

- `--global`: 用于设置全局配置，影响用户的所有仓库。
    
    ```Bash
    git config --global core.editor "nano"
    ```
    

  

- `--local`: 用于设置当前仓库的本地配置。
    
    ```Bash
    git config --local core.autocrlf false
    ```
    

  

- `--system`: 用于设置系统级别的配置，这通常与 Git 安装相关。
    
    ```Bash
    git config --system core.pager "less"
    ```
    

  

- `--add`: 用于向列表类型的配置添加新的值。
    
    ```Bash
    git config --add alias.co checkout
    ```
    

  

- `--remove`: 用于从列表类型的配置中移除一个值。
    
    ```Bash
    git config --remove alias.co
    ```
    

  

- `--reset`: 用于重置配置到默认值或删除指定的配置项。
    
    ```Bash
    git config --global --remove section.key
    git config --global --reset section
    ```
    

  

- `--edit`: 打开配置文件进行编辑。
    
    ```Bash
    git config --global --edit
    ```
    

**示例**

1. 设置全局用户名和电子邮件地址：
    
    ```Bash
    git config --global user.name "Your Name"
    git config --global user.email "your_email@example.com"
    ```
    
2. 设置默认文本编辑器：
    
    ```Bash
    git config --global core.editor "nano"
    ```
    
3. 设置提交信息的默认模板文件：
    
    ```Bash
    git config --global commit.template /path/to/commit-message-template.txt
    ```
    
4. 配置 Git 以在提交时使用特定的挂钩脚本：
    
    ```Bash
    git config --global core.hooksPath /path/to/hooks
    ```
    
5. 查看当前仓库的配置文件路径：
    
    ```Bash
    git config --local --edit
    ```
    
6. 列出所有配置项，包括局部、全局和系统级别的配置：
    
    ```Bash
    git config --list --show-origin
    ```
    

  

通过使用 `git config` 命令，你可以自定义 Git 的行为，以适应你的工作流程和偏好。配置 Git 可以帮助你提高效率，确保提交信息的一致性，并简化日常的 Git 操作。

### **分支管理**

`git`采用的是树的形式管理你的每次提交，对于每次提交都有一个`commit`，这个`commit`是哈希生成的唯一标识，而当前的工作目录处于``HEAD`指针指向的`commit``，你可以通过分支指向不同的`commit`,同时`git`还支持`tag`，也就是说你可以通过`commit hash`、`branch`、`HEAD`、`tag`四种方式访问某一次提交`commit`，

  

[d3网站-可视化学Git](https://onlywei.github.io/explain-git-with-d3/#revert)

  

`git branch name` 创建分支

`git branch -a -v` 查看分支

`git branch --track <remote-branchname>`: 创建一个新分支，并设置它跟踪远程分支。

`git branch -u origin/main`

`Git checkout <commit>`移动HEAD指针

`Git checkout -b name` 建立并切换到新分支

`Git reset <commit>`移动HEAD指针和当前分支

- `git reset --soft <commit_hash>` //不修改工作区、暂存区
    
- `git reset --mixed <commit_hash>` //不修改工作区，修改暂存区
    
- `git reset --hard <commit_hash>` //修改工作区，修改暂存区
    

`git merge <commit>` 合并分支

`git rebase <commit>` 变基合并分支

`git revert <commit>` 逆向提交

  

#### Git branch

`git branch` 是 Git 版本控制系统中的一个命令，用于创建、列出、删除和切换分支。分支是 Git 中的一个核心特性，它允许开发者在不同的线路上独立工作，而不会相互干扰。这在进行新功能开发、修复错误或尝试新想法时非常有用。

**基本用法**

  

- **列出所有本地分支**:
    
    ```Bash
    git branch
    ```
    
      这将列出所有本地分支，当前检出的分支前面会有一个星号（*）标记。
    

  

- **创建一个新分支但不切换到它**:
    
    ```Bash
    git branch <branchname>
    ```
    
      例如，创建一个名为 `feature-branch` 的新分支：
    
    ```Bash
    git branch feature-branch
    ```
    

  

- **创建并切换到新分支**:
    
    ```Bash
    git checkout -b <newbranchname>
    ```
    
      使用 `-b` 选项可以在创建新分支的同时切换到它。例如：
    
    ```Bash
    git checkout -b new-feature
    ```
    

  

- **列出所有远程分支**:
    
    ```Bash
    git branch -r
    ```
    
      这将列出所有远程分支。
    

  

- **列出所有分支（本地和远程）**:
    
    ```Bash
    git branch -a
    ```
    

  

- **删除一个本地分支**:
    
    ```Bash
    git branch -d <branchname>
    ```
    
      使用 `-d` 选项可以删除一个已经合并到当前分支的本地分支。如果要删除一个未合并的分支，可以使用 `-D` 选项：
    
    ```Bash
    git branch -D obsolete-branch
    ```
    

  

- **重命名分支**:
    
    ```Bash
    git branch -m <oldname> <newname>
    ```
    
      使用 `-m` 选项可以重命名当前分支。如果要重命名其他分支，需要指定分支名：
    
    ```Bash
    git branch -m temp-branch finished-branch
    ```
    

  

- **查看分支的最后一次提交**:
    
    ```Bash
    git branch -v
    ```
    

  

**示例**

  

1. 创建并切换到一个名为 `fix-bug` 的新分支：
    
    ```Bash
    git checkout -b fix-bug
    ```
    

  

2. 列出所有本地分支和它们的最后一次提交信息：
    
    ```Bash
    git branch -v
    ```
    

  

3. 删除一个名为 `deprecated-feature` 的本地分支：
    
    ```Bash
    git branch -d deprecated-feature
    ```
    

  

4. 重命名当前分支为 `improved-feature`：
    
    ```Bash
    git branch -m improved-feature
    ```
    

  

5. 切换到名为 `production` 的远程分支，并在本地创建一个跟踪分支：
    
    ```Bash
    git checkout production
    git checkout -b local-production tracking production
    ```
    

  

通过 `git branch` 命令，你可以轻松地管理你的分支，这对于开发工作流程和团队协作至关重要。确保你了解何时创建分支、何时合并分支以及如何切换分支，这样可以有效地利用 Git 的分支特性来提高你的开发效率。

#### Git checkout

`git checkout` 是 Git 版本控制系统中的一个命令，用于切换分支、检出文件、以及恢复工作目录中的文件。这个命令非常强大，因为它涉及到多个方面的操作，包括切换开发线路、更新工作目录的内容以及保存或放弃更改。

  

**基本用法**

  

1. **切换分支**:
    
    ```Bash
    git checkout <branchname>
    ```
    
      这个命令会切换到指定的分支。如果分支不存在，使用 `-b` 选项可以创建并切换到新分支。
    
    ```Bash
    git checkout -b <newbranchname>
    ```
    

  

2. **检出文件**:
    
    ```Bash
    git checkout <commit> <filepath>
    ```
    
      这个命令会用指定提交（commit）中的文件内容来替换工作目录中的文件。这对于恢复旧版本的文件或查看历史版本非常有用。
    

  

3. **恢复工作目录中的更改**:
    
    ```Bash
    git checkout -- <filepath>
    ```
    
      使用这个命令可以放弃对指定文件的本地更改。这对于撤销未暂存的更改非常有用。
    

  

4. **使用远程分支作为上游分支**:
    
    ```Bash
    git checkout --track <remotename>/<remotebranchname>
    ```
    
      这个命令会创建一个新的本地分支，并设置它跟踪远程分支。
    

  

5. **切换回之前的分支**:
    
    ```Bash
    git checkout -
    ```
    
      这个命令会切换回上一次所在的分支。
    

  

**选项**

  

- `-b`: 创建一个新的分支并切换到它。
    
- `--track`: 创建一个新的分支并设置它跟踪远程分支。
    
- `--detach`: 切换到一个临时的分支，通常用于查看历史提交。
    
- `--force`: 强制切换到一个分支，即使这会导致未暂存更改的丢失。
    
- `--ours` 和 `--theirs`: 在合并冲突时，选择保留我们的更改或他们的更改。
    

  

**示例**

  

1. 切换到名为 `main` 的分支：
    
    ```Bash
    git checkout main
    ```
    

  

2. 创建并切换到一个名为 `feature-branch` 的新分支：
    
    ```Bash
    git checkout -b feature-branch
    ```
    

  

3. 检出特定提交中的 `README.md` 文件：
    
    ```Bash
    git checkout 5d83c56 README.md
    ```
    

  

4. 放弃对 `index.html` 文件的本地更改：
    
    ```Bash
    git checkout -- index.html
    ```
    

  

5. 切换到一个名为 `remote-branch` 的远程分支，并创建一个本地跟踪分支：
    
    ```Bash
    git checkout --track origin/remote-branch
    ```
    

  

6. 切换回之前的分支：
    
    ```Bash
    git checkout -
    ```
    

  

`git checkout` 命令是 Git 中使用非常频繁的一个命令，它在不同场景下有着不同的用途。无论是切换分支、恢复文件还是查看历史版本，都需要掌握这个命令的正确用法。在使用时，务必注意命令的影响，特别是在使用 `--detach` 或 `--force` 选项时要格外小心，以免丢失重要的更改。

#### Git reset

`git reset` 是 Git 版本控制系统中的一个强大命令，用于撤销更改、回退到之前的提交或者修改提交历史。这个命令可以用于多种情况，包括撤销工作目录中的更改、撤销暂存区（staging area 或 index）中的更改、以及重写历史提交。

  

**基本用法**

  

1. **撤销工作目录中的更改**:
    
    ```Bash
    git reset <commit>
    ```
    
      将 HEAD 指向指定的提交，并更新工作目录和暂存区以匹配该提交。未跟踪的文件和子模块不会被影响。
    

  

2. **撤销暂存区中的更改**:
    
    ```Bash
    git reset -- <file>
    ```
    
      使用 `--` 可以将指定的文件从暂存区移除，但不会影响工作目录中的文件。
    

  

3. **撤销所有暂存区中的更改**:
    
    ```Bash
    git reset --hard
    ```
    
      这将撤销所有暂存区中的更改，并将工作目录中的文件恢复到最后一次提交的状态。
    

  

4. **修改最后一次提交**:
    
    ```Bash
    git reset --soft HEAD^
    ```
    
      这将回退到上一次提交，但保留更改在暂存区中，允许你修改提交信息或重新提交。
    

  

5. **删除最后一次提交**:
    
    ```Bash
    git reset --soft HEAD^
    git commit -m "New commit message"
    ```
    
      这将取消最后一次提交，并将更改保留在暂存区中。之后，你可以提交一个新的提交。
    

  

6. **交互式暂存区修改**:
    
    ```Bash
    git reset -- <file>
    ```
    
      使用 `--` 可以进入交互式模式，让你选择性地暂存或取消暂存文件。
    

  

**选项**

  

- `--soft`: 只回退提交指针（HEAD），保留工作目录和暂存区的更改。
    
- `--hard`: 回退提交指针，并重写工作目录和暂存区以匹配指定的提交。这将丢失所有未提交的更改。
    
- `--mixed`: 默认选项，回退提交指针，并撤销暂存区中的更改，但保留工作目录中的更改。
    
- `--keep`: 与 `--soft` 类似，但保留暂存区中的更改。
    
- `--force`: 强制执行 `git reset`，即使这可能导致更改的丢失。
    

  

**示例**

  

1. 回退到特定的提交，并保留更改在暂存区中：
    
    ```Bash
    git reset --soft HEAD^
    ```
    

  

2. 撤销暂存区中的所有更改：
    
    ```Bash
    git reset --mixed
    ```
    

  

3. 撤销工作目录中的所有未暂存更改：
    
    ```Bash
    git reset --hard
    ```
    

  

4. 修改上一次提交的信息：
    
    ```Bash
    git reset --soft HEAD^
    git commit -m "Corrected commit message"
    ```
    

  

5. 撤销对特定文件的更改：
    
    ```Bash
    git reset -- <file>
    ```
    

  

`git reset` 命令是 Git 中一个非常重要的工具，它可以帮助你修正错误、清理提交历史或者撤销未完成的更改。在使用 `git reset` 时，特别是在使用 `--hard` 选项时，需要非常小心，因为这可能会导致未提交更改的永久丢失。在团队协作环境中，重写公共历史之前应该与团队成员沟通，以避免潜在的冲突。

#### Git merge

`git merge` 是 Git 版本控制系统中的一个命令，用于合并两个或多个分支的历史。当你在不同的分支上工作时，可能会有独立的更改和提交。`git merge` 允许你将这些独立的更改合并到一个单一的线性历史中，以便统一管理和维护代码。

  

**基本用法**

  

1. **合并一个分支到当前分支**:
    
    ```Bash
    git merge <branchname>
    ```
    
      这个命令会将指定的分支 `<branchname>` 合并到当前分支。如果两个分支的历史有共同的祖先，Git 会自动创建一个合并提交来结合两个分支的更改。
    

  

2. **合并一个提交到当前分支**:
    
    ```Bash
    git merge <commit>
    ```
    
      你也可以指定一个具体的提交 `<commit>` 来合并。
    

  

**选项**

  

- `--no-ff`: 禁用快进合并。即使 Git 可以进行快进合并，也会创建一个新的合并提交。
    
    ```Bash
    git merge --no-ff <branchname>
    ```
    

  

- `--squash`: 将合并转换为一系列已提交的更改，但不创建单独的提交。这允许你编辑、重新排序或删除更改，然后作为一个单一的提交来提交。
    
    ```Bash
    git merge --squash <branchname>
    ```
    

  

- `--no-commit`: 执行合并但不自动创建合并提交。这允许你在合并后手动提交更改。
    
    ```Bash
    git merge --no-commit <branchname>
    ```
    

  

- `--abort`: 中止正在进行的合并操作，恢复到合并前的状态。
    
    ```Bash
    git merge --abort
    ```
    

  

**示例**

  

1. 合并 `feature-branch` 到当前分支，并创建一个合并提交：
    
    ```Bash
    git merge feature-branch
    ```
    

  

2. 合并 `feature-branch` 到当前分支，但禁用快进合并，强制创建一个新的合并提交：
    
    ```Bash
    git merge --no-ff feature-branch
    ```
    

  

3. 将 `feature-branch` 的更改合并到当前分支，并立即提交合并后的更改：
    
    ```Bash
    git merge --squash feature-branch
    git commit -m "Merge feature-branch into current branch"
    ```
    

  

4. 如果合并操作产生了冲突，你可以解决冲突后使用以下命令完成合并：
    
    ```Bash
    git add .
    git commit
    ```
    

  

5. 如果你决定不合并更改，并希望恢复到合并前的状态：
    
    ```Bash
    git merge --abort
    ```
    

  

`git merge` 是一个非常有用的命令，可以帮助你整合特性分支、修复分支或其他临时分支的更改到你的主分支或其他分支。在使用 `git merge` 时，了解合并策略和选项是非常重要的，这样可以确保合并过程顺利，同时保持代码历史的清晰和可维护性。在合并过程中可能会遇到冲突，需要手动解决这些冲突，然后完成合并提交。

### **文件撤销**

  

旧命令：

`git checkout <commit> -- file`

`git reset --soft <commit> file` //不修改工作区、暂存区

`git reset --mixed <commit> file` //不修改工作区，修改暂存区,git reset 默认是mix的

`git reset --hard <commit> file` //修改工作区，修改暂存区

新命令:

`git restore README.md`

`git restore --staged`

`git restore --patch`:交互式恢复更改

`git restore --source=feature-branch`

#### Git restore

`git restore` 是 Git 版本控制系统中的一个命令，用于撤销工作目录中的更改。这个命令在 Git 2.23 版本中引入，旨在提供一个更简单、更直观的方式来撤销工作目录中的文件更改，相比于之前使用的 `git checkout` 或 `git reset` 命令。

  

**基本用法**

  

- **恢复单个文件到上次提交的状态**:
    
    ```Bash
    git restore <file>
    ```
    
      这将恢复指定文件到最近一次提交时的状态，撤销所有未暂存的更改。
    

  

- **恢复多个文件到上次提交的状态**:
    
    ```Bash
    git restore <file1> <file2> ...
    ```
    
      你可以一次恢复多个文件。
    

  

- **恢复工作目录中的所有文件到上次提交的状态**:
    
    ```Bash
    git restore .
    ```
    
      使用点（`.`）作为参数，表示恢复工作目录中的所有文件和子目录。
    

  

- **恢复暂存区中的更改**:
    
    ```Bash
    git restore --staged <file>
    ```
    
      使用 `--staged` 选项，你可以撤销已经暂存的更改，将文件从暂存区移回到工作目录。
    

  

**选项**

  

- `--staged`: 恢复暂存区中的更改，即将更改从暂存区移除，但不会影响工作目录中的文件。
    
    ```Bash
    git restore --staged <file>
    ```
    

  

- `--patch`: 交互式模式，允许你选择性地恢复或撤销更改。
    
    ```Bash
    git restore --patch
    ```
    

  

- `--source=<branch>`: 从指定的分支中恢复更改，而不是从当前分支。
    
    ```Bash
    git restore --source=<branch> <file>
    ```
    

  

- `--allow-idempotent`: 允许对已删除文件执行无副作用的操作。
    
    ```Bash
    git restore --allow-idempotent <file>
    ```
    

  

**示例**

  

1. 恢复 `README.md` 文件到上次提交的状态：
    
    ```Bash
    git restore README.md
    ```
    

  

2. 恢复工作目录中的所有文件到上次提交的状态：
    
    ```Bash
    git restore .
    ```
    

  

3. 撤销 `config.txt` 文件的暂存区更改：
    
    ```Bash
    git restore --staged config.txt
    ```
    

  

4. 交互式地选择性地恢复或撤销更改：
    
    ```Bash
    git restore --patch
    ```
    

  

`git restore` 命令提供了一种更加灵活和直观的方式来处理工作目录中的更改，使得撤销操作更加简单和安全。在使用这个命令时，请确保你了解每个选项的含义，以避免意外地丢失工作进度。

### **标签管理**

`git`的标签分为两种：轻量标签（lightweight）与附注标签（annotated），通过标签，我们可以找到我们希望的Commit

```Bash
git tag # 查看标签
git tag -l "1.8.*" # 查看标签
git tag -a v1.4 -m "my version 1.4" # 附注标签，没有-m会知道编辑器让你编写
git show # 通过使用 git show 命令可以看到标签信息和与之对应的提交信息
git tag v1.4 # 轻量标签
git tag -d v1.4 
git push origin --tags ##tag必须主动push
```

`git tag` 是 Git 版本控制系统中的一个命令，用于创建、列出、删除和验证标签（tag）。标签是指向特定提交的指针，通常用于标记发布版本、重要更改或里程碑。

#### Git tag

**基本用法**

  

1. **列出所有标签**:
    
    ```Bash
    git tag
    ```
    
      这个命令会列出仓库中所有的标签。
    

  

2. **创建一个新标签**:
    
    ```Bash
    git tag <tagname>
    ```
    
      这将创建一个新的标签，指向当前提交。如果不指定提交，标签将指向最近的提交。
    

  

3. **创建一个带有消息的标签**:
    
    ```Bash
    git tag -a <tagname> -m "Tag message"
    ```
    
      使用 `-a` 选项可以创建一个带注释的标签，`-m` 后面跟着的是标签消息。
    

  

4. **查看标签信息**:
    
    ```Bash
    git show <tagname>
    ```
    
      这个命令会显示指定标签的详细信息，包括标签消息和指向的提交。
    

  

5. **删除一个标签**:
    
    ```Bash
    git tag -d <tagname>
    ```
    
      使用 `-d` 选项可以删除一个标签。请注意，这只会从本地仓库中删除标签。
    

  

6. **推送标签到远程仓库**:
    
    ```Bash
    git push origin <tagname>
    ```
    
      这个命令会将指定的标签推送到远程仓库。如果你想一次性推送所有标签，可以使用：
    
    ```Bash
    git push origin --tags
    ```
    

  

7. **拉取所有标签**:
    
    ```Bash
    git pull origin --tags
    ```
    
      当你克隆一个仓库时，默认情况下不会包含标签。使用这个命令可以从远程仓库拉取所有标签。
    

  

**示例**

  

1. 创建一个名为 `v1.0` 的标签，指向当前提交：
    
    ```Bash
    git tag v1.0
    ```
    

  

2. 创建一个带有描述的标签 `v2.0` 并推送到远程仓库：
    
    ```Bash
    git tag -a v2.0 -m "Release version 2.0"
    git push origin v2.0
    ```
    

  

3. 删除本地标签 `v1.0` 并从远程仓库删除：
    
    ```Bash
    git tag -d v1.0
    git push origin --delete tag v1.0
    ```
    

  

4. 拉取远程仓库的所有标签到本地仓库：
    
    ```Bash
    git pull origin --tags
    ```
    

  

标签是 Git 中的一个重要特性，它使得版本控制更加清晰和有序。通过使用标签，你可以轻松地引用特定版本的代码，这对于发布软件、追踪问题或比较不同版本的更改非常有用。在使用标签时，建议使用有意义的命名约定，以便其他开发者能够快速理解每个标签的目的。

### **远程管理**

下面是一些常用的命令，暂时不需要记录，我们会慢慢用到

`git clone` 克隆仓库

`git remote` 查看管理的远程仓库

`git push` 推送当前分支到本分支关联的远程仓库分支

`git pull` 从远程仓库中拉取并和并本地关联分支

`git fetch` 只取不合并

#### Git clone

`git clone` 是 Git 版本控制系统中的一个命令，用于创建一个本地副本（克隆）的远程仓库。这个命令会下载所有的提交历史、分支、标签和其他元数据，以便你可以在本地进行开发、测试和贡献。

  

**基本用法**

  

- **克隆一个远程仓库**:
    
    ```Bash
    git clone <repository-url>
    ```
    
      这个命令会创建一个新的目录（默认与远程仓库同名），并将远程仓库的所有内容克隆到这个目录中。
    

  

**选项**

  

- `--branch <branchname>`: 指定一个分支来克隆，而不是默认的 `master` 或 `main` 分支。
    
    ```Bash
    git clone --branch=feature-branch <repository-url>
    ```
    

  

- `--depth <depth>`: 指定克隆的提交历史深度。这可以减少下载的数据量，适用于不需要完整历史的场合。
    
    ```Bash
    git clone --depth=1 <repository-url>
    ```
    

  

- `--no-checkout`: 克隆仓库，但不检出任何文件。这通常用于初始化一个裸仓库（bare repository）。
    
    ```Bash
    git clone --no-checkout <repository-url>
    ```
    

  

- `--progress`: 显示克隆过程中的进度信息。
    
    ```Bash
    git clone --progress <repository-url>
    ```
    

  

- `-v` 或 `--verbose`: 显示详细的输出信息。
    
    ```Bash
    git clone -v <repository-url>
    ```
    

  

- `--config`: 用于设置克隆过程中的配置选项。
    
    ```Bash
    git clone --config core.autocrlf=false <repository-url>
    ```
    

  

**示例**

  

1. 克隆一个名为 `my-repo` 的远程仓库到当前目录：
    
    ```Bash
    git clone https://github.com/user/my-repo.git
    ```
    

  

2. 克隆 `main` 分支到一个名为 `my-app` 的本地目录：
    
    ```Bash
    git clone --branch=main --single-branch https://github.com/user/my-repo.git my-app
    ```
    

  

3. 克隆一个仓库并限制历史深度为最近的 10 次提交：
    
    ```Bash
    git clone --depth=10 https://github.com/user/my-repo.git
    ```
    

  

4. 克隆仓库并显示进度信息：
    
    ```Bash
    git clone --progress https://github.com/user/my-repo.git
    ```
    

  

5. 克隆仓库并设置 `autocrlf` 为 `false` 以避免行尾换行符问题：
    
    ```Bash
    git clone --config core.autocrlf=false https://github.com/user/my-repo.git
    ```
    

  

`git clone` 命令是开始使用远程 Git 仓库的第一步。通过克隆仓库，你可以获得完整的代码库，包括所有的版本历史和分支。这对于参与开源项目、备份代码或开始一个新的项目非常有用。在使用 `git clone` 时，确保你了解远程仓库的位置和结构，以便正确地克隆和使用代码。

#### Git remote

`git remote` 是 Git 版本控制系统中的一个命令，用于管理和查看远程仓库的信息。通过这个命令，你可以添加、删除、查看和修改远程仓库的连接。这对于与远程团队协作和共享代码至关重要。

  

**基本用法**

  

- **添加一个新的远程仓库**:
    
    ```Bash
    git remote add <remote> <url>
    ```
    
      `<remote>` 是远程仓库的简称（如 `origin`），`<url>` 是远程仓库的 URL。
    

  

- **删除一个远程仓库**:
    
    ```Bash
    git remote remove <remote>
    ```
    
      这将删除指定的远程仓库。
    

  

- **查看所有远程仓库**:
    
    ```Bash
    git remote -v
    ```
    
      或者简写为：
    
    ```Bash
    git remote
    ```
    
      这将列出所有配置的远程仓库及其 URL。
    

  

- **获取远程仓库的详细信息**:
    
    ```Bash
    git remote show <remote>
    ```
    
      这将显示指定远程仓库的详细信息，包括 URL、跟踪的分支和本地分支与远程分支的对应关系。
    

  

- **设置或修改远程仓库的** **URL**:
    
    ```Bash
    git remote set-url <remote> <newurl>
    ```
    
      这将修改指定远程仓库的 URL。
    

  

- **切换远程仓库的分支跟踪**:
    
    ```Bash
    git remote set-head <remote> <branch>
    ```
    
      这将设置远程仓库的默认分支。
    

  

**示例**

  

1. 添加一个新的远程仓库 `origin` 指向 `https://github.com/user/repo.git`:
    
    ```Bash
    git remote add origin https://github.com/user/repo.git
    ```
    

  

2. 删除远程仓库 `origin`:
    
    ```Bash
    git remote remove origin
    ```
    

  

3. 查看所有远程仓库的 URL:
    
    ```Bash
    git remote -v
    ```
    

  

4. 显示远程仓库 `origin` 的详细信息:
    
    ```Bash
    git remote show origin
    ```
    

  

5. 修改远程仓库 `origin` 的 URL:
    
    ```Bash
    git remote set-url origin https://github.com/user/new-repo.git
    ```
    

  

6. 设置远程仓库 `origin` 的默认分支为 `main`:
    
    ```Bash
    git remote set-head origin main
    ```
    

  

通过 `git remote` 命令，你可以轻松地管理你的远程仓库，这对于远程团队协作和代码共享至关重要。确保你了解每个远程仓库的作用，并正确配置它们的 URL 和分支跟踪设置。

#### Git push

`git push` 是 Git 版本控制系统中的一个命令，用于将本地仓库的更改推送到远程仓库。这个命令会将你的提交、分支和标签等更新发送到远程服务器，使得其他人能够看到你所做的更改或者与你的更改同步。

  

**基本用法**

  

- **推送当前分支到远程仓库**:
    
    ```Bash
    git push
    ```
    
      如果当前分支已经配置了上游分支（tracking branch），这个命令会推送当前分支到对应的远程分支。
    

  

- **指定远程仓库和分支**:
    
    ```Bash
    git push <remote> <branch>
    ```
    
      这个命令会推送指定的 `<branch>` 分支到指定的 `<remote>` 仓库。例如，推送 `main` 分支到 `origin` 远程仓库：
    
    ```Bash
    git push origin main
    ```
    

  

- **使用标签**:
    
    ```Bash
    git push <remote> <tag>
    ```
    
      这个命令会推送指定的 `<tag>` 到远程仓库。
    

  

- **强制推送**:
    
    ```Plain
    git push --force <remote> <branch>
    ```
    
      使用 `--force` 选项可以强制推送更改，即使这会导致远程仓库的历史改变。这通常用于修复错误或者撤销已经推送的提交。请谨慎使用此选项，因为它可能会影响其他协作者的工作。
    

  

**选项**

  

- `-u` 或 `--set-upstream`: 设置推送的分支作为当前分支的上游分支，以后可以使用 `git push` 命令直接推送。
    
    ```Bash
    git push -u origin main
    ```
    

  

- `--force`: 强制推送到远程仓库，可能会重写历史。
    
    ```Bash
    git push --force origin main
    ```
    

  

- `--tags`: 推送所有标签到远程仓库。
    
    ```Bash
    git push --tags
    ```
    

  

- `--dry-run`: 执行干运行，查看将要推送的更改，但不实际推送。
    
    ```Bash
    git push --dry-run
    ```
    

  

- `--quiet`: 静默模式，不显示推送的更改和进度。
    
    ```Bash
    git push --quiet
    ```
    

  

**示例**

  

1. 推送当前分支到远程仓库，并设置上游分支：
    
    ```Bash
    git push -u origin main
    ```
    

  

2. 推送特定的 `feature` 分支到远程仓库的 `feature-branch`：
    
    ```Bash
    git push origin feature:feature-branch
    ```
    

  

3. 推送所有标签到远程仓库：
    
    ```Bash
    git push --tags
    ```
    

  

4. 强制推送到远程仓库，覆盖远程分支的历史：
    
    ```Bash
    git push --force origin main
    ```
    

  

`git push` 命令是与远程仓库同步更改的关键。在推送更改之前，确保你已经与远程分支同步，并且你的本地更改不会与远程更改冲突。如果你不确定推送的影响，可以先执行 `git push --dry-run` 来预览将要进行的更改。在团队协作环境中，强制推送应该谨慎使用，因为它可能会影响其他成员的工作。

#### Git pull

`git pull` 是 Git 版本控制系统中的一个命令，用于从远程仓库拉取更改并合并到你当前的本地分支。这个命令实际上是 `git fetch` 和 `git merge` 两个命令的组合，它会自动拉取远程分支的最新更改并与你的本地分支合并。

  

**基本用法**

  

- **拉取并合并远程分支的更改**:
    
    ```Bash
    git pull <remote> <branch>
    ```
    
      默认情况下，`git pull` 会拉取当前分支配置的上游分支（tracking branch）的更改。`<remote>` 是远程仓库的名称（如 `origin`），`<branch>` 是远程分支的名称。
    

  

**选项**

  

- `--rebase`: 使用 `git rebase` 而不是 `git merge` 来整合更改。这会产生一个更干净的提交历史。
    
    ```Bash
    git pull --rebase <remote> <branch>
    ```
    

  

- `--no-ff`: 即使可以进行快进合并（fast-forward merge），也创建一个新的合并提交。
    
    ```Bash
    git pull --no-ff <remote> <branch>
    ```
    

  

- `--progress`: 显示拉取过程中的进度信息。
    
    ```Bash
    git pull --progress <remote> <branch>
    ```
    

  

- `--allow-unrelated-histories`: 允许拉取两个没有共同历史的分支。
    
    ```Bash
    git pull --allow-unrelated-histories <remote> <branch>
    ```
    

  

- `--autostash`: 在拉取之前，自动暂存本地未提交的更改。
    
    ```Bash
    git pull --autostash <remote> <branch>
    ```
    

  

- `--no-commit`: 拉取更改但不自动创建合并提交。
    
    ```Bash
    git pull --no-commit <remote> <branch>
    ```
    

  

- `--quiet`: 静默模式，不显示拉取的详细信息。
    
    ```Bash
    git pull --quiet <remote> <branch>
    ```
    

  

**示例**

  

1. 拉取远程 `origin` 仓库的 `main` 分支更改并合并到当前分支：
    
    ```Bash
    git pull origin main
    ```
    

  

2. 使用 `--rebase` 选项拉取更改，以便在提交历史中保持线性：
    
    ```Bash
    git pull --rebase origin main
    ```
    

  

3. 拉取远程分支的更改并在合并时创建一个新的提交：
    
    ```Bash
    git pull --no-ff origin main
    ```
    

  

4. 拉取更改并显示进度信息：
    
    ```Bash
    git pull --progress origin main
    ```
    

  

5. 拉取两个历史不相关的分支的更改：
    
    ```Bash
    git pull --allow-unrelated-histories origin main
    ```
    

  

`git pull` 命令是与远程仓库同步更改的重要工具。在拉取更改之前，确保你的本地更改已经提交或暂存，以免在合并过程中丢失。使用 `--rebase` 选项可以帮助你保持提交历史的清洁，但请注意，它改写了历史，可能不适用于公共分支。在使用 `git pull` 时，如果遇到冲突，你需要手动解决这些冲突，然后完成合并。

#### Git fetch

`git fetch` 是 Git 版本控制系统中的一个命令，用于从远程仓库下载所有更改，但不会立即合并到你的本地分支。这个命令会更新你的远程跟踪分支（remote tracking branches），让你能够查看和比较远程仓库的最新状态。

  

**基本用法**

  

- **获取远程仓库的所有更新**:
    
    ```Bash
    git fetch
    ```
    
      这个命令会从所有配置的远程仓库获取更新，但不会自动合并或修改你的工作目录。
    

  

- **获取特定远程仓库的更新**:
    
    ```Bash
    git fetch <remote>
    ```
    
      `<remote>` 是远程仓库的名称，如 `origin`。这个命令会获取指定远程仓库的所有分支更新。
    

  

- **获取特定远程分支的更新**:
    
    ```Bash
    git fetch <remote> <branch>
    ```
    
      这个命令会获取指定远程仓库的特定分支更新。例如，获取 `origin` 远程仓库的 `main` 分支：
    
    ```Bash
    git fetch origin main
    ```
    

  

**选项**

  

- `--all`: 获取所有远程仓库的更新。
    
    ```Bash
    git fetch --all
    ```
    

  

- `-v` 或 `--verbose`: 显示详细的输出信息。
    
    ```Bash
    git fetch -v
    ```
    

  

- `--tags`: 除了分支更新，还获取所有标签。
    
    ```Bash
    git fetch --tags
    ```
    

  

- `--prune`: 删除已经从远程仓库删除的远程跟踪分支。
    
    ```Bash
    git fetch --prune
    ```
    

  

**示例**

  

1. 获取所有远程仓库的更新：
    
    ```Bash
    git fetch --all
    ```
    

  

2. 获取 `origin` 远程仓库的 `main` 分支更新：
    
    ```Bash
    git fetch origin main
    ```
    

  

3. 显示详细信息地获取 `origin` 远程仓库的更新：
    
    ```Bash
    git fetch -v origin
    ```
    

  

4. 获取并删除已经从远程仓库删除的分支：
    
    ```Bash
    git fetch --prune origin
    ```
    

  

`git fetch` 命令是安全地与远程仓库同步的有效方式。它允许你在合并之前检查和评估远程更改，从而避免潜在的合并冲突。在执行 `git pull` 之前，通常建议先使用 `git fetch` 来查看远程仓库的更新情况。这样，你可以更好地控制合并过程，并决定何时以及如何将更改合并到你的本地分支。

### **本地远程实践**

  

我们在本地创建一个远程仓库,并且推送

```Bash
git clone 
git checkout -b v1
git push local_remote 
git branch -a
```

  

### Github远程

如果我们想要在互联网上和他人合作，一个可以联网的远程仓库是必须的Github和Gitee，或者部署在之间服务器上的Gitlab都可以,

实际上Github提供的功能和上文中的本地远程类似

#### 仓库地址的区别

`https://github.com/`：任何人都可以克隆，但是无法修改仓库

`git@github.com`：必须添加密钥，可以修改仓库

  

#### Git上的SSh密钥认证

按照流程走，把你生成的ssh密钥添加上去即可

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDVmYjBiNjA5OTc2MTVjYTBiYjc5M2FjMmU1MWEzYjNfRDlzUUkxRGQ3VEJtaDV3RGhQTmp1NE9JZVdYT0Z0aEpfVG9rZW46R3ZhT2JVa29Gb2diTmh4WWZ5ZWM5TGVnbnBkXzE3MjgyMDYxMDU6MTcyODIwOTcwNV9WNA)

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=MmE4ZGRhZTkyZjRjYTVmMGY3OTQ1NTUzMDRhZTI3N2JfeWFaTWxrMjlZZ2lRV0tlUG9HQlBoeUJOSXlKeWhtc0xfVG9rZW46U0RKRGJyaE9Ob2tkbVB4MFZyUWNtTFQzbm1nXzE3MjgyMDYxMDU6MTcyODIwOTcwNV9WNA)

#### SSh-agent

`ssh-agent` 是一个程序，用于管理你的 SSH（Secure Shell）密钥，使得你可以在多个会话中重用一个单一的 SSH 会话。它缓存你的私钥和密码，因此你只需要在第一次使用 SSH 时输入密码，之后在 `ssh-agent` 会话中启动的任何 SSH 操作都不需要再次输入密码。

1. **启动** **`ssh-agent`**: 通常，当你使用 `ssh` 命令时，`ssh-agent` 会自动启动。但是，你也可以手动启动它：
    

```Bash
eval $(ssh-agent -s)
```

这个命令会启动 `ssh-agent` 并设置相应的环境变量，使得 SSH 客户端可以找到它。

2. **添加****私钥****到** **`ssh-agent`**: 启动 `ssh-agent` 后，你需要将你的私钥添加到它的会话中：
    

```Bash
ssh-add ~/.ssh/id_rsa
```

如果你的私钥文件有不同的名称或路径，需要相应地修改这个命令。如果你的私钥有密码，`ssh-add` 会提示你输入它。

3. **使用** **`ssh-agent`**: 一旦你的私钥被添加到 `ssh-agent`，你就可以在任何新的终端会话中使用 SSH，而不需要再次输入密码。例如，你可以使用 `ssh` 命令连接到远程服务器：
    

```Bash
ssh user@remote_host
```

4. **管理多个密钥**: 如果你有多个 SSH 密钥（例如，用于不同的服务器或账户），你可以使用 `ssh-add` 将它们全部添加到 `ssh-agent`：
    

```Bash
ssh-add ~/.ssh/id_rsa_work
ssh-add ~/.ssh/id_rsa_personal
```

5. **查看** **`ssh-agent`** **会话中的密钥**: 你可以列出 `ssh-agent` 会话中当前添加的所有密钥：
    

```Bash
ssh-add -l
```

6. **停止** **`ssh-agent`**: 当你完成工作并想要停止 `ssh-agent` 时，可以简单地杀掉它的进程：
    

```Bash
kill $SSH_AGENT_PID
```

`$SSH_AGENT_PID` 是 `ssh-agent` 的进程 ID，它在启动 `ssh-agent` 时设置的环境变量。

  

  

## 结束

感谢大家参与到本次培训中！

如果有什么疑问或意见或建议，都可以直接联系我@方衍贵 ，同时欢迎参观我的博客[Introduction · teamtee's home](https://teamtee.github.io/teamtee/)(目前还在初步建设中...,有点乱)

谢谢大家！