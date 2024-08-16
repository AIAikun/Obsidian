# 1. 下载protocol buffers
- https://github.com/protocolbuffers/protobuf/releases
- ![[Pasted image 20240730213321.png]]
- 解压下载好的.zip文件后，配置环境变量
	`vim .zshrc`
	`export PATH=$PATH:/home/jmh/snap/protoc/bin/`
- 检查是否配置好
	终端输入`protoc`
# 2. 安装grpc的核心库
`go get google.golang.org/grpc`
# 3. 安装代码生成工具
![[Pasted image 20240730214936.png]]
```
go install google.golang.org/protobuf/cmd/protoc-gen-go@latest
go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@latest
```