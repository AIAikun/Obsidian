## 1.数据库操作
    

redis默认有16哥数据库，编号为0到15，且默认访问0号数据库

| select 数据编号 | 选择指定数据库      |
| ----------- | ------------ |
| dbsize      | 获取当前数据库键值对数量 |

|   |   |
|---|---|
|save|将数据保存至磁盘|
|bgsave|将数据异步保存至磁盘（后台：Background)|
|lastsave|获取最后一次成功保存的unix时间，可以用来检验是否bgsave后台保存成功|

|   |   |
|---|---|
|flushdb|清空当前数据库|
|flushall|清空所有数据库|

1. sudo service redis-server start （进入redis客户端命令行界面）
    
2. redis-cli（redis-cli是一个命令行工具，用于与Redis服务器进行交互。它允许用户通过命令行界面发送命令给Redis服务器，并接收服务器的响应。）
    
3. 实际操作
    
![[Pasted image 20241006213358.png]]

## 2.通用数据操作
    

操作范围为当前数据库

| keys 格式                | 查看符合指定格式的key，*为通配符， |
| ---------------------- | ------------------- |
| exists key1 [key2 ...] | 查看是否存在一至多个指定的key    |
| type key               | 按key查看value的数据类型    |
| del key1[key2 ...]     | 按key删除一至多个键值对       |

| rename key1 key2   | 重命名key1,如果key2已经存在，其值会被覆盖 |
| ------------------ | ------------------------- |
| renamenx key1 key2 | key2不存在时重命名key1           |

![[Pasted image 20241006213441.png]]

| move key 数据库编号 | 按key将一个键值对移动到指定数据库 |
| -------------- | ------------------ |
| copy key1 key2 | 将key1的值拷贝给key2     |

![[Pasted image 20241006213452.png]]