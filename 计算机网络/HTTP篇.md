# 1. HTTP常见面试题
![[Pasted image 20250125220553.png]]
### 1.1 HTTP基本概念
#### HTTP是什么
HTTP：超文本传输协议。（**双向协议**）
#### HTTP常见状态码
![[Pasted image 20250125221144.png]]
####  HTTP 常见字段
_Host_ 字段
客户端发送请求时，用来指定服务器的域名。Host: www.A.com

_Content-Length 字段_
服务器在返回数据时，会有 `Content-Length` 字段，表明本次回应的数据长度。Content-Length: 1000
**HTTP 协议通过设置回车符、换行符作为 HTTP header 的边界，通过 Content-Length 字段作为 HTTP body 的边界，这两个方式都是为了解决“粘包”的问题**

_Connection 字段_
`onnection` 字段最常用于客户端要求服务器使用「HTTP 长连接」机制，以便其他请求复用。（HTTP 长连接的特点是，只要任意一端没有明确提出断开连接，则保持 TCP 连接状态。）
![[Pasted image 20250125222010.png]]
HTTP/1.1 版本的默认连接都是长连接，但要指定 `Connection` 首部字段的值为 `Keep-Alive`。   Connection: Keep-Alive

_Content-Type 字段_
`Content-Type` 字段用于服务器回应时，告诉客户端，本次数据是什么格式。
Content-Type: text/html; Charset=utf-8
客户端请求的时候，可以使用 `Accept` 字段声明自己可以接受哪些数据格式。
```
Accept: */*
```

_Content-Encoding 字段_
`Content-Encoding` 字段说明数据的压缩方法。表示服务器返回的数据使用了什么压缩格式          Content-Encoding: gzip
客户端在请求时，用 `Accept-Encoding` 字段说明自己可以接受哪些压缩方法。
Accept-Encoding: gzip, deflate
### 1.2 GET与POST
#### GET与POST的区别
根据 RFC 规范：
**GET 的语义是从服务器获取指定的资源**GET 请求的参数位置一般是写在 URL 中
**POST 的语义是根据请求负荷（报文body）对指定的资源做出处理**，POST 请求携带数据的位置一般是写在报文 body 中，body 中的数据可以是任意格式的数据。
#### GET 和 POST 方法都是安全和幂等的吗？
如果从 RFC 规范定义的语义来看：
**GET 方法就是安全且幂等的，可以对 GET 请求的数据做缓存，这个缓存可以做到浏览器本身上（彻底避免浏览器发请求），也可以做到代理上（如nginx），而且在浏览器中 GET 请求可以保存为书签**。
**POST是不安全不幂等的，所以浏览器一般不会缓存 POST 请求，也不能把 POST 请求保存为书签**。
但是开发者不一定会按照 RFC 规范定义的语义来实现 GET 和 POST 方法。
RFC 规范并没有规定 GET 请求不能带 body 的。理论上，任何请求都可以带 body 的。另外，URL 中的查询参数也不是 GET 所独有的，POST 请求的 URL 中也可以有参数的。
### 1.3 HTTP缓存技术
#### 缓存的实现方式
对于一些具有重复性的 HTTP 请求，可以把这对「请求-响应」的数据都**缓存在本地**
HTTP 缓存有两种实现方式，分别是**强制缓存和协商缓存**。
#### 强制缓存
强缓存指的是只要浏览器判断缓存没有过期，则直接使用浏览器的本地缓存，决定是否使用缓存的主动性在于浏览器这边。
size 项中标识的是 from disk cache，就是使用了强制缓存。
![[Pasted image 20250125225457.png]]
强缓存是利用下面这两个 HTTP 响应头部（Response Header）字段实现的，它们都用来表示资源在客户端缓存的有效期：
- `Cache-Control`， 是一个相对时间；
- `Expires`，是一个绝对时间；
**Cache-Control 的优先级高于 Expires** 。
Cache-control流程：
- 当浏览器第一次请求访问服务器资源时，服务器会在返回这个资源的同时，在 Response 头部加上 Cache-Control，Cache-Control 中设置了过期时间大小；
- 浏览器再次请求访问服务器中的该资源时，会先**通过请求资源的时间与 Cache-Control 中设置的过期时间大小，来计算出该资源是否过期**，如果没有，则使用该缓存，否则重新请求服务器；
- 服务器再次收到请求后，会再次更新 Response 头部的 Cache-Control。