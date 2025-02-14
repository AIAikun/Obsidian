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
#### 协商缓存
在浏览器使用开发者工具的时候，某些请求的响应码是 `304`，这个是告诉浏览器可以使用本地缓存的资源。
**协商缓存就是与服务端协商之后，通过协商结果来判断是否使用本地缓存**。
![[Pasted image 20250204092747.png]]
协商缓存可以基于两种头部来实现。
第一种：请求头部中的 `If-Modified-Since` 字段与响应头部中的 `Last-Modified` 字段实现
- 响应头部中的 `Last-Modified`：标示这个响应资源的最后修改时间；
- 请求头部中的 `If-Modified-Since`：当资源过期了，发现响应头中具有 Last-Modified 声明，则再次发起请求的时候带上 Last-Modified 的时间，服务器收到请求后发现有 If-Modified-Since 则与被请求资源的最后修改时间进行对比（Last-Modified），如果最后修改时间较新（大），说明资源又被改过，则返回最新资源，HTTP 200 OK；如果最后修改时间较旧（小），说明资源无新修改，响应 HTTP 304 走缓存。
第⼆种：请求头部中的 If-None-Match 字段与响应头部中的 ETag 字段
- 响应头部中 Etag ：唯⼀标识响应资源；
- 请求头部中的 If-None-Match ：当资源过期时，浏览器发现响应头⾥有 Etag，则再次向服务器发起请求时，会将请求头 If-None-Match 值设置为 Etag 的值。服务器收到请求后进⾏⽐对，如果资源没有变化返回 304，如果资源变化了返回 200。
Etag和 Last-Modified同时存在时，**Etag 的优先级更⾼**
**协商缓存这两个字段都需要配合强制缓存中 Cache-Control 字段来使⽤，只有在未能命中强制缓存的时候，才能发起带有协商缓存字段的请求。**
![[Pasted image 20250204095810.png]]
### 1.4 HTTP特性
到⽬前为⽌，HTTP 常⻅到版本有 HTTP/1.1，HTTP/2.0，HTTP/3.0。
HTTP 协议是基于 TCP/IP
#### HTTP/1.1 的优点
HTTP 最突出的优点是「简单、灵活和易于扩展、应⽤⼴泛和跨平台」。
- HTTPS 就是在 HTTP 与 TCP 层之间增加了 SSL/TLS 安全传输层； 
- HTTP/1.1 和 HTTP/2.0 传输协议使⽤的是 TCP 协议，⽽到了 HTTP/3.0 传输协议改⽤了 UDP 协议。
#### HTTP/1.1 的缺点
HTTP 协议是「⽆状态、明⽂传输」，「不安全」。
对于⽆状态的问题，解法⽅案有很多种，其中⽐较简单的⽅式⽤ Cookie 技术。 Cookie 通过在请求和响应报⽂中写⼊ Cookie 信息来控制客户端的状态。
**相当于在客户端第⼀次请求后，服务器会下发⼀个装有客户信息的「⼩贴纸」，后续客户端请求服务器的时候，带上「⼩贴纸」，服务器就能认得了了**
#### HTTP/1.1 的性能
1. 长连接（持久连接）
持久连接的特点是，只要任意⼀端没有明确提出断开连接，则保持 TCP 连接状态。
如果某个 HTTP ⻓连接超过⼀定时间没有任何数据交互，服务端就会主动断开这个连接。
![[Pasted image 20250204101825.png]]
2. 管道⽹络传输
可在同⼀个 TCP 连接⾥⾯，客户端可以发起多个请求，只要第⼀个请求发出去了，不必等 其回来，就可以发第⼆个请求出去，可以减少整体的响应时间。
服务器必须按照接收请求的顺序发送对这些管道化请求的响应。
如果服务端在处理 A 请求时耗时⽐较⻓，那么后续的请求的处理都会被阻塞住，这称为「队头堵塞」。
**HTTP/1.1 管道解决了请求的队头阻塞，但是没有解决响应的队头阻塞。**
实际上 HTTP/1.1 管道化技术不是默认开启，⽽且浏览器基本都没有⽀持，这个功能基本没有被使用。
### 1.5 HTTP 与 HTTPS
#### HTTP 与 HTTPS的区别
- HTTP 是超⽂本传输协议，信息是明⽂传输，存在安全⻛险的问题。HTTPS 则解决 HTTP 不安全的缺陷，在 TCP 和 HTTP ⽹络层之间加⼊了 SSL/TLS 安全协议，使得报⽂ 能够加密传输。 
 ![[Pasted image 20250204103232.png]]
- HTTP 连接建⽴相对简单， TCP 三次握⼿之后便可进⾏ HTTP 的报⽂传输。⽽ HTTPS 在 TCP 三次握⼿之后，还需进⾏ SSL/TLS 的握⼿过程，才可进⼊加密报⽂传输。
- 两者的默认端⼝不⼀样，HTTP 默认端⼝号是 80，HTTPS 默认端⼝号是 443。 
- HTTPS 协议需要向 CA（证书权威机构）申请数字证书，来保证服务器的身份是可信的
#### HTTPS 解决了 HTTP 的哪些问题？
1.  混合加密
通过混合加密的⽅式可以保证信息的机密性，解决了窃听的⻛险。
![[Pasted image 20250204103600.png]]
HTTPS 采⽤的是对称加密和⾮对称加密结合的「混合加密」⽅式：
- 在通信建⽴前采⽤**⾮对称加密**的⽅式交换「会话秘钥」，后续就不再使⽤⾮对称加密。
- 在通信过程中全部使⽤**对称加密**的「会话秘钥」的⽅式加密明⽂数据。
采⽤「混合加密」的⽅式的原因：
- 对称加密只使⽤⼀个密钥，运算速度快，密钥必须保密，⽆法做到安全的密钥交换。
- ⾮对称加密使⽤两个密钥：公钥和私钥，公钥可以任意分发⽽私钥保密，解决了密钥交换问题但速度慢。
2. 摘要算法 + 数字签名 
