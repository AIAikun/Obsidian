grpc给哦我们呢提供了一个接口，这个接口有两个方法，接口位于credentials包下，这个接口需要客户端实现
```go
type PerRPCCredentials interface {  
    GetRequestMetadata(context.Context, ...string) (map[string]string, error)  
    RequireTransportSecurity() bool  
}
```
第一个方法作用是获取元数据信息，也就是客户端提供的key value对，context用于控制超时和取消，uri是请求入口处的uri
第二个方法的作用是否需要基于TLS认证进行安全传输，如果返回值是true，则必须加上TLS认证，false则不用
gRPC将各种认证方式浓缩统一到一个凭证(credentials)上，可以单独使用一种凭证，比如只使用TLS凭证或者只使用自定义凭证，也可以多种凭证组合，gRPC提供统一的API验证码机制，使研发人员使用方便，这也是gRPC设计的巧妙之处
# 客户端
```go
package main  
  
import (  
    pb "awesomeProject/hello-server/proto"  
    "context"    "fmt"    "log"  
    "google.golang.org/grpc"    "google.golang.org/grpc/credentials/insecure")  
  
type ClientTokenAuth struct {  
}  
  
func (c ClientTokenAuth) GetRequestMetadata(context.Context, ...string) (map[string]string, error) {  
    return map[string]string{  
       "appid":  "101010",  
       "appkey": "i am key",  
    }, nil  
}  
func (c ClientTokenAuth) RequireTransportSecurity() bool {  
    return false  
}  
  
func main() {  
    var opts []grpc.DialOption  
    opts = append(opts, grpc.WithTransportCredentials(insecure.NewCredentials()))  
    //启用token认证  
    opts = append(opts, grpc.WithPerRPCCredentials(&ClientTokenAuth{}))  
    //连接到server端。此处禁用安全传输，没有加密和验证  
    coon, err := grpc.NewClient("localhost:9090", opts...)  
    if err != nil {  
       log.Fatalf("did not connect: %v", err)  
    }  
    defer coon.Close()  
    //建立连接  
    client := pb.NewSayHelloClient(coon)  
    //执行rpc调用（这个方法在服务器端来实现并返回结果）  
    resp, _ := client.SayHello(context.Background(), &pb.HelloRequest{RequestName: "kaungshen"})  
    fmt.Println(resp.GetResponseMsg())  
}
```
# 服务端
```go
package main  
  
import (  
    pb "awesomeProject/hello-server/proto"  
    "context"    "net"  
    "google.golang.org/grpc"    "google.golang.org/grpc/codes"    "google.golang.org/grpc/metadata")  
  
// hello server  
type server struct {  
    pb.UnimplementedSayHelloServer  
}  
  
// 业务  
func (s *server) SayHello(ctx context.Context, req *pb.HelloRequest) (*pb.HelloResponse, error) {  
    //获取元数据信息  
    md, ok := metadata.FromIncomingContext(ctx)  
    if !ok {  
       return nil, grpc.Errorf(codes.Unauthenticated, "未传输token")  
    }  
    var appId string  
    var appKey string  
    if val, ok := md["appid"]; ok {  
       appId = val[0]  
    }  
    if val, ok := md["appkey"]; ok {  
       appKey = val[0]  
    }  
    if appId != "101010" || appKey != "i am key" {  
       return nil, grpc.Errorf(codes.Unauthenticated, "token不正确")  
    }  
    return &pb.HelloResponse{ResponseMsg: "Hello " + req.RequestName}, nil  
}  
func main() {  
    //开启端口  
    listen, _ := net.Listen("tcp", ":9090")  
    //创建grpc服务  
    grpcServer := grpc.NewServer()  
    //在grpc服务端中去注册我们自己编写的服务  
    pb.RegisterSayHelloServer(grpcServer, &server{})  
    //启动grpc服务  
    err := grpcServer.Serve(listen)  
    if err != nil {  
       panic(err)  
    }  
}
```