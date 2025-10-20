## 快速入门

macos

```
brew install kafka
```

使用docker部署

```
# https://hub.docker.com/r/apache/kafka/
docker pull apache/kafka:4.1.0

docker run -d --name kafka -p 9092:9092 apache/kafka:4.1.0
```

使用docker-compose部署kafka集群

## 原理

#### （1）基础架构与名词解释

![[Pasted image 20251014095450.png]]

- Producer：Producer即生产者，消息的产生者，是消息的入口。
    
- Broker：Broker是kafka实例，每个服务器上有一个或多个kafka的实例，我们姑且认为每个broker对应一台服务器。每个kafka集群内的broker都有一个不重复的编号，如图中的broker-0、broker-1等……
    
- Topic：消息的主题，可以理解为消息的分类，kafka的数据就保存在topic。在每个broker（Kafka实例）上都可以创建多个topic。
    
- Partition：Topic的分区，每个topic可以有多个分区，分区的作用是做负载，提高kafka的吞吐量。同一个topic在不同的分区的数据是不重复的，partition的表现形式就是一个一个的文件夹！
    
- Replication:每一个分区都有多个副本，副本的作用是做备胎。当主分区（Leader）故障的时候会选择一个备胎（Follower）上位，成为Leader。在kafka中默认副本的最大数量是10个，且副本的数量不能大于Broker的数量，follower和leader绝对是在不同的机器，同一机器对同一个分区也只可能存放一个副本（包括自己）。
    
- Message：每一条发送的消息主体。
    
- Consumer：消费者，即消息的消费方，是消息的出口。
    
- Consumer Group：我们可以将多个消费组组成一个消费者组，在kafka的设计中同一个分区的数据只能被消费者组中的某一个消费者消费。同一个消费者组的消费者可以消费同一个topic的不同分区的数据，这也是为了提高kafka的吞吐量！
    
- Zookeeper：kafka集群依赖zookeeper来保存集群的的元信息，来保证系统的可用性。
    

#### （2）工作流程分析

##### （1）发送数据

Producer在写入数据的时候永远的找leader，不会直接将数据写入follower 消息写入leader后，follower是主动的去leader进行同步

![[Pasted image 20251014095457.png]]

producer采用push模式将数据发布到broker，每条消息追加到分区中，顺序写入磁盘，所以保证同一分区内的数据是有序的！

如何保证消息不丢失？（有点像TCP） 通过ACK应答机制！在生产者向队列写入数据的时候可以设置参数来确定是否确认kafka接收到数据，这个参数可设置的值为0、1、all。

- 0代表producer往集群发送数据不需要等到集群的返回，不确保消息发送成功。安全性最低但是效率最高。
    
- 1代表producer往集群发送数据只要leader应答就可以发送下一条，只确保leader发送成功。
    
- all代表producer往集群发送数据需要所有的follower都完成从leader的同步才会发送下一条，确保leader发送成功和所有的副本都完成备份。安全性最高，但是效率最低。
    

参考：[https://zhuanlan.zhihu.com/p/453957145](https://zhuanlan.zhihu.com/p/453957145)