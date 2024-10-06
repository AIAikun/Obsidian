go module是go官方自带的go依赖管理库,在1.13版本正式推荐使用

Go module 构建模式是在 Go 1.11 版本正式引入的，为的是彻底解决 Go 项目复杂版本依赖的问题，在 Go 1.16 版本中，Go module 已经成为了 Go 默认的包依赖管理机制和 Go 源码构建机制。

go module可以将某个项目(文件夹)下的所有依赖整理成一个 go.mod 文件，里面写入了依赖的版本等

**使用go module之后我们可不用将代码放置在src下了，module 隐含了一个命名空间的概念，module 下每个包的导入路径都是由 module path 和包所在子目录的名字结合在一起构成。**

使用 go module 管理依赖后会在项目根目录下生成两个文件 go.mod 和 go.sum。

参考资料：

- https://www.cnblogs.com/niuben/p/12560104.html
    
- https://zhuanlan.zhihu.com/p/105556877
    
- https://cloud.tencent.com/developer/article/1593734
    
- https://zhuanlan.zhihu.com/p/269719543