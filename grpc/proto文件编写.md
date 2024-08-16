创建一个 .proto文件
![[Pasted image 20240731163305.png]]
编写完上面的内容后，在当前目录执行如下命令
```
protoc --go_out=. hello.proto
protoc --go-grpc_out=. hello.proto
```

之后会在当前目录下生成两个文件
![[Pasted image 20240731163741.png]]
