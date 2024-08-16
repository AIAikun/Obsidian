## 1.message
message：protobuf中定义一个消息类型式是通过关键字message字段指定的。==消息就是需要传输的数据格式的定义。==
message关键字类似于go中的struct。
在消息中承载的数据分别对应于每一个字段，其中每个字段都有一个名字和一种类型。
一个proto文件中可以定义多个消息类型。
## 2. 字段规则
optional:消息体中可选字段。protobuf3都默认为optional。
repeated:消息体中可重复字段，重复的值的顺序会保留在go中，重复的会被定义为切片。
## 3. 消息号
在消息体的定义中，每个字段都必须要有一个唯一的标识号，标识好是大于等于1的一个整数。
## 4. 嵌套消息
可以在其他消息类型中定义、使用消息，在下面的例子中，person消息就定义在PersonInfo消息内
```protobuf
message PersonInfo{
	message Person{
		string name=1;
		int32 height=2;
		repeated int32 weight=3;
	}
	repeated Person info=1;
}
```
如果要在它的父消息类型的外部重用这个消息类型，需要PersonInfo.Person的形式使用它。
## 5. 服务定义
如果想要将消息类型用在RPC系统中，可以在.proto文件中定义一个RPC服务接口，protocol buffer编译器将会根据所选择的不同语言生成服务接口代码及存根。
```protobuf
service SearchService{
	# rpc 服务函数名 （参数） 返回（返回参数）
	rpc Search(SearchRequest) returns (SearchResponse)
}
```