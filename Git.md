1. ## 配置
    

配置是说明性的,可以随意写

```Go
$ git config --global user.name "我的名字"
$ git config --global user.email laowang@example.com
```

2. ## 创建仓库
    

在本地项目的文件夹里输入

```Go
$ git init
```

文件夹就变成了git仓库

3. ## 克隆网上项目
    

```Go
$ git clone https://github.com/torvalds/linux.git 
```

git clone +网上项目的url

4. ## 跟踪文件和目录
    

```Go
$ git add <name>
```

如果要add一个文件夹，里面有多个文件，则需要

```Go
git add .
```

从 Git 索引中删除跟踪的文件

```Go
$ git rm <name>
```

一是确实要从版本库中删除该文件，那就用命令`git rm`删掉，并且`git commit`

另一种情况是删错了，因为版本库里还有呢，所以可以很轻松地把误删的文件恢复到最新版本：

```Plaintext
$ git checkout -- test.txt
```

`git checkout`其实是用版本库里的版本替换工作区的版本，无论工作区是修改还是删除，都可以“一键还原”。

注意：从来没有被添加到版本库就被删除的文件，是无法恢复的！

保留在目录里，但是不被追踪

```Go
$ git rm --cache <name>
```

5. ## 设置为缓存状态
    

对跟踪的文件可以进行修改，修改完成后通过git add将他的状态设置为缓存状态

```Go
$ git add <file-name>
```

取消文件的缓存状态

```Go
$ git reset HEAD <name>
```

6. ## 提交修改
    

在缓存状态修改后，可以通过git commit命令来提交此次更改

```Go
$ git commit -m
```

## 仓库状态总结

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=M2IwNDg5NTVkN2NkZDgzMGNjN2VlNjJlYjIwZWY0ZGRfNVdxSDlMdmJvdGh1YmsweXVtZVBQYzhudUJ6bzc0UXRfVG9rZW46SXRYaGJDVmZPb1d2WDJ4ZGZESmNiTDlibnNjXzE3MjgyMDY0ODM6MTcyODIxMDA4M19WNA)

7. ## 取消提交
    

取消此次提交，但是不能取消第一次提交，只能取消第二次、第三次等。下面有更详细的解释。

```Go
$ git reset head~--soft
```

`git checkout -- file`可以丢弃工作区的修改：

```Plaintext
$ git checkout -- readme.txt
```

命令`git checkout -- readme.txt`意思就是，把`readme.txt`文件在工作区的修改全部撤销，这里有两种情况：

一种是`readme.txt`自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；

一种是`readme.txt`已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。

总之，就是让这个文件回到最近一次`git commit`或`git add`时的状态。

场景1：当你改乱了工作区某个文件的内容，想直接丢弃工作区的修改时，用命令`git checkout -- file`。

场景2：当你不但改乱了工作区某个文件的内容，还添加到了暂存区时，想丢弃修改，分两步，第一步用命令`git reset HEAD <file>`，就回到了场景1，第二步按场景1操作。

8. ## 查询
    

查询文件状态，查看工作区的状态

```Go
$ git status
```

查询文件修改的内容

```Go
$ git diff
```

查看历史的提交

```Go
$ git log 
```

查看命令历史

```Go
git reflog
```

美化输出

```Go
$ git log --pretty
```

把每次提交的信息都变成一行

```Go
$ git log --pretty=oneline
```

图形化显示

```Go
$ git log --graph
```

9. ## 链接远程仓库
    

```Go
$ git remote add origin https://github.com/gaodijian/test,git
```

git remote add+项目名字（自己起）+远程仓库URL

修改远程仓库的名字

```Go
$ git remote rename <original name> <newname>
```

查看远程仓库

```Go
$ git remote
```

将本地代码推送到远程仓库

```Go
$ git push origin master
```

Git push +仓库名+分支类型

之后需要鉴权

10. ## Token方式鉴权
    

github默认禁止用户名加密码的验证方式了

解决办法：

打开github的settings,打开最后的the developer settings,点击 personal access tokens ，点击tokens，生成一个令牌，用这个令牌去当密码。把有关仓库的权限全部打开，如图

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=ZTQyZDNiN2ViZDQxNWYwNDdjZTU4ZjM1ODVkMDgxOTRfS2p3R200Wlhzalc4WlpIVEh2MEFUeUU2aW8xT0pGQWVfVG9rZW46SktBMWJmNFFHb1JFQXl4ZnBmYmNTUTVXbmJvXzE3MjgyMDY0ODM6MTcyODIxMDA4M19WNA)

点击生成，复制，再次push，密码中复制一下token，即可上传成功。

11. ## SSH协议
    

```Go
cd ~/.ssh
```

进到用户的ssh目录

```Go
ssh-keygen -t rsa -b 4096 -C "目录，随便写，推荐写自己的邮箱"
```

生成ssh密钥

```Go
ls
```

查看，会发现有test（私钥）和test.pub（公钥）。

```Go
cat test.pub
```

查看公钥的内容

将公钥复制，打开github的setting

选择

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=MjE0Y2Y0YTA3MmRiOWVlOGJlYzIyNjk5OGUzZjYwNmJfamZQZ2liS1FlM2xoZ0xmWjBpT2E4RHZ5NXY3c1JsV1NfVG9rZW46VUI4MmJRckZjb2dvSlB4UjJwbGN3ajJibkhzXzE3MjgyMDY0ODM6MTcyODIxMDA4M19WNA)

添加密钥即可。

回到仓库，复制SSH

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=MDJkZTYyNjNjOGQ2MTNmYTkyOGU4NDlkMWU2ZGQ2ZTVfejJnNGRCRlpMc3NDcFhab1dCUWN6SzdLaUNMd0taUmlfVG9rZW46SGZKYmJjeE1Sb2lEUG14cGw2TGNHNk5KbmJoXzE3MjgyMDY0ODM6MTcyODIxMDA4M19WNA)

在空项目里git clone 即可，不需要输入密码。

12. ## Branch分支
    

创建新分支

```Go
git branch feature1
```

Git branch +分支名称

切换分支

```Go
git checkout feature1
```

新建分支并切换到该分支

```Go
git checkout -b feature2
```

创建并切换到新的`dev`分支，也可以使用：

```Plaintext
git switch -c dev
```

直接切换到已有的`master`分支，可以使用：

```Plaintext
git switch master
```

提交

```Go
git commit -am 'feature2'
```

合并分支,将分支合并到当前分支上

```Go
git merge feature2
```

注：当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。

换一个仓库后，拉取分支

```Go
git fetch
```

拉取后的分支还是远程分支，不是本地分支，然后需要新建远程分支的跟踪分支

```Go
git checkout -b feature1 origin/feature1
```

或者

```Go
git check out --track origin/feature1
```

13. ## Git 的储藏stash的功能
    

储存当时我们所修改的东西

```Go
git stash
```

等价于

```Go
git stash push
```

操作完成，切换回当前分支后，恢复刚才我们存储的内容

```Go
git stash apply
```

此外，git stash可以存储多次，回看存储的东西

```Go
git stash list
```

恢复

```Go
git stash apply stash@{2}
```

将最后一次存储的stash恢复,但是同时也会将恢复完后的stash删除掉

```Go
git stash pop
```

删除stash

```Go
git stash drop stash@{0}
```

14. ## 重置功能
    

取消此次提交，但是不能取消第一次提交，只能取消第二次、第三次等。

```Go
$ git reset head~--soft
```

Head 表示当前的提交，head~表示上次的提交，head~2，表示倒数第二次的提交，--soft表示只是撤销提交commit操作，不改变暂存的状态，

合并时,rebase变基操作和merge合并操作功能一样，但是rebase可以让提交记录变好看。

```Go
git checkout B//切换到b分支
```

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDJiMzc4MzE0YzBiZmMwZTA3NzZhMjAzNmM0MTIxNDVfbjMzWE5IOUM0ODQxbDFHeXBQRHUxdHFDRVFlTjMyNDlfVG9rZW46Q0V1VWJZdVd1b1pEMXl4ckJodGNBeGpobmFjXzE3MjgyMDY0ODM6MTcyODIxMDA4M19WNA)

```Go
git rebase A//变基，将A分支合并到B分支
```

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=ODI1ZWY4ZTVjNDY1ZmM1YjMzODA0ZWUwYmM0MDJiZjlfTmozeHU1ajlBWEhmemZCNlZSWHhhMGVOVlNSaDBlNjJfVG9rZW46VEpxSGJEWjRQb2VNTEl4eldEYmNtUjNLblVoXzE3MjgyMDY0ODM6MTcyODIxMDA4M19WNA)

注：若分支提交到了远程分支上，若他人用你的分支进行二次开发，则不能对这个分支rebase了。

rebase还有强大功能：交互式操作

选择前三次提交的分支进行编辑、修改

```Go
git rebase -i head~3
```

会进入到交互式的界面

![](https://diangroup.feishu.cn/space/api/box/stream/download/asynccode/?code=MTQ5NWE4ZDAwYWU2NzI5NWI1YzkxNjA1MWFmODNlNjdfYzVGbHExNU82NWRmSm13NjV1ZFpIWkFKbzdmZDU3cXNfVG9rZW46T2szZ2I1R2ROb1JaU1B4cmc5d2NaZWxpbjVOXzE3MjgyMDY0ODM6MTcyODIxMDA4M19WNA)

Pick 表示不会修改，将pick改成edit,然后保存退出交互界面，就可按照提示修改这次提交。也可以在交互界面直接删除一次提交。将pick改为squash表示压缩这次提交，并将修改内容移到前一个提交上面，

15. ## 标签管理
    

在Git中打标签非常简单，首先，切换到需要打标签的分支上：

- $ git branch dev master $ git checkout master Switched to branch 'master'
    

然后，敲命令`git tag <name>`就可以打一个新标签：

```Plaintext
$ git tag v1.0
```

可以用命令`git tag`查看所有标签：

```Plaintext
$ git tag
v1.0
```

默认标签是打在最新提交的commit上的。有时候，如果忘了打标签，比如，现在已经是周五了，但应该在周一打的标签没有打，怎么办？

方法是找到历史提交的commit id，然后打上就可以了：

```Plaintext
$ git log --pretty=oneline --abbrev-commit
12a631b (HEAD -> master, tag: v1.0, origin/master) merged bug fix 1014c805e2 fix bug 101
e1e9c68 merge with no-ff
f52c633 add merge
cf810e4 conflict fixed
5dc6824 & simple
14096d0 AND simple
b17d20e branch test
d46f35e remove test.txt
b84166e add test.txt
519219b git tracks changes
e43a48b understand how stage works
1094adb append GPL
e475afc add distributed
eaadf4e wrote a readme file
```

比方说要对`add merge`这次提交打标签，它对应的commit id是`f52c633`，敲入命令：

```Plaintext
$ git tag v0.9 f52c633
```

再用命令`git tag`查看标签：

```Plaintext
$ git tag
v0.9
v1.0
```

注意，标签不是按时间顺序列出，而是按字母排序的。可以用`git show <tagname>`查看标签信息：

```Plaintext
$ git show v0.9commit f52c63349bc3c1593499807e5c8e972b82c8f286 (tag: v0.9)
Author: Michael Liao askxuefeng@gmail.com
Date:   Fri May 18 21:56:54 2018 +0800add merge
diff --git a/readme.txt b/readme.txt
...
```

可以看到，`v0.9`确实打在`add merge`这次提交上。

还可以创建带有说明的标签，用`-a`指定标签名，`-m`指定说明文字：

```Plaintext
$ git tag -a v0.1 -m "version 0.1 released" 1094adb
```

用命令`git show <tagname>`可以看到说明文字：

```Plaintext
$ git show v0.1
tag v0.1
Tagger: Michael Liao <askxuefeng@gmail.com
Date:   Fri May 18 22:48:43 2018 +0800
version 0.1 released
commit 1094adb7b9b3807259d8cb349e7df1d4d6477073 (tag: v0.1)
Author: Michael Liao <askxuefeng@gmail.com
Date:   Fri May 18 21:06:15 2018 +0800
    append GPL
diff --git a/readme.txt b/readme.txt
...
```

注意：标签总是和某个commit挂钩。如果这个commit既出现在master分支，又出现在dev分支，那么在这两个分支上都可以看到这个标签。

如果标签打错了，也可以删除：

```Plaintext
$ git tag -d v0.1
Deleted tag 'v0.1' (was f15b0dd)
```

因为创建的标签都只存储在本地，不会自动推送到远程。所以，打错的标签可以在本地安全删除。

如果要推送某个标签到远程，使用命令`git push origin <tagname>`：

```Go
$ git push origin v1.0
Total 0 (delta 0), reused 0 (delta 0)
To github.com:michaelliao/learngit.git
[new tag]         v1.0 -> v1.0
```

或者，一次性推送全部尚未推送到远程的本地标签：

```Go
$ git push origin --tags
Total 0 (delta 0), reused 0 (delta 0)
To github.com:michaelliao/learngit.git
[new tag]         v0.9 -> v0.9
```

如果标签已经推送到远程，要删除远程标签就麻烦一点，先从本地删除：

```Plaintext
$ git tag -d v0.9
Deleted tag 'v0.9' (was f52c633)
```

然后，从远程删除。删除命令也是push，但是格式如下：

```Go
$ git push origin :refs/tags/v0.9
To github.com:michaelliao/learngit.git
[deleted]         v0.9
```

要看看是否真的从远程库删除了标签，可以登陆GitHub查看。