[https://www.bilibili.com/video/BV1S24y1U7Xp/?spm_id_from=333.1007.top_right_bar_window_default_collection.content.click&vd_source=931062d9b4842126e0b650ed79389e43](https://www.bilibili.com/video/BV1S24y1U7Xp/?spm_id_from=333.1007.top_right_bar_window_default_collection.content.click&vd_source=931062d9b4842126e0b650ed79389e43)
# 1.protobuf优势
1. 序列化后体积比Json和XML很小，适合网络传输
2. 支持跨平台多语言
3. 消息格式升级和兼容性好
4. 序列化反序列化速度快
# 2.gRPC的工作流程
1. **服务定义**：使用`.proto`文件定义服务接口和数据结构。
2. **代码生成**：使用Protobuf工具生成客户端和服务器代码。
3. **客户端调用**：客户端通过生成的Stub调用远程服务。
4. **序列化和传输**：请求和响应被序列化为二进制数据，通过HTTP/2传输。
5. **服务端处理**：服务端接收请求，执行相应的方法，并返回结果。
# 3.gRPC的主要特性

- **高性能**：利用HTTP/2提供高效的网络传输，支持双向流、头部压缩、多路复用
    
    - **性能指标**：相比HTTP/1.1，gRPC可以减少延迟，提高吞吐量。
- **跨语言支持**：支持多种编程语言间的无缝通信和集成
    
    - **支持语言**：C、C++、Java、Go、Python等。
- **自动化生成代码**：使用Protobuf定义服务，自动生成客户端和服务器代码
    
    - **工具**：Protobuf编译器（protoc）用于生成代码。
- **多样化的通信模式**：支持一对一、服务端流、客户端流、双向流等多种RPC通信模型
# 4.gRPC解决的问题

gRPC主要解决以下问题：

- **提高性能和效率**：通过HTTP/2和Protocol Buffers实现高效的数据传输
    
    - **性能提升**：相比传统的RESTful API，gRPC可以减少延迟，提高吞吐量。
- **简化分布式系统的构建**：提供跨语言的RPC框架，简化不同服务之间的通信
    
- **减少通信协议的开发和维护成本**：通过自动化生成代码和标准化的数据序列化，降低开发和维护成本
    
    - **开发效率**：使用Protobuf定义服务接口，可以快速生成客户端和服务器代码，减少手动编写代码的时间和错误。
