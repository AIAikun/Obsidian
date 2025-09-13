## mysql下载

MYSQL官网：[https://www.mysql.com/downloads/]

## 网课

B站：[https://www.bilibili.com/video/BV1Kr4y1i7ru/]

## mysql的使用
打开

1、打开下载安装好mysql后的应用——mysql......clint.....unicode,输入密码（输错会闪退）

2、配置了mysql的path环境后：可以在本机的任意目录的控制面板下（win+r cmd）输入mysql -u root -p
# 1.SQL通用语法

1. SQL可以单行和多行书写，以分号结尾。
    
2. SQL语句可以使用空格/缩进来增强语句的可读性。
    
3. MYSQL数据库的SQL语句不区分大小写。
    
4. 注释：
    
    1. 单行注释：--注释内容 或 #注释内容（MYSQL特有）
        
    2. 多行注释：/*注释内容*/
        

# 2.SQL分类

SQL语句，根据其功能，主要分为4类：DDL、DML、DQL、DCL。
![[Pasted image 20241006211105.png]]
# 3.DDL(【】表示是可选项)-数据库操作

## 1.数据库操作

1. 查询所有数据库

```Go
show databases;
```

2. 创建数据库
    

```Go
create database [ if not exists ] 数据库名 [ default charset 字符集 ] [ collate 排序 规则 ] ;
```
![[Pasted image 20241006211117.png]]

3. 删除DB
    

```Go
drop database [ if exists ] 数据库名 ;
```

4. 使用/切换数据库
    

```Go
use 数据库名 ;
```

我们要操作某一个数据库下的表时，就需要通过该指令，切换到对应的数据库下，否则是不能操作的。

5. 查询当前数据库
    

```Go
select database();
```

## 2.DML-表操作
    

### 1.查询创建
    

1. 查询当前数据库所有表
    

```Go
show tables;
```

2. 查询表结构
    

```Go
desc 表名; 
```

3. 查询指定表的建表语句
    

```Go
show create table 表名;
```

4. 创建表结构
    

```sql
creat table 表名(
    字段1 字段1类型 [ comment 字段1注释 ],
    字段2 字段2类型 [ comment 字段2注释 ],
    字段3 字段3类型 [ comment 字段3注释 ],
    ......
    字段n 字段n注释 [ comment 字段n注释 ]
    }[comment 表注释]
```
 create table 表名(
   字段1 字段1类型 [comment 字段1注释]，
   ==id int comment '编号',==
   字段2 字段2类型 [comment 字段2注释]，
   ==name varchar(50) comment '姓名',==
   )[comment 表注释]；

注：[...]为可选参数，最后一个字段后面没有逗号

### 2.数据类型
    

MySQL中的数据类型有很多，主要分为三类：数值类型、字符串类型、日期时间类型。

1. 数值类型
![[Pasted image 20241006211157.png]]
![[Pasted image 20241006211210.png]]

2. 字符串类型
![[Pasted image 20241006211220.png]]

3. 日期时间类型
  ![[Pasted image 20241006211230.png]]

### 3.表修改

1. 添加字段
    

```sql
ALTER TABLE 表名 ADD 字段名 类型 (长度) [ COMMENT 注释 ] [ 约束 ];
```

```sql
alter table mytable add nickname varchar(20) comment '昵称'；
```
2. 修改数据类型
    

```Go
ALTER TABLE 表名 MODIFY 字段名 新数据类型 (长度); 
```

3. 修改字段名和字段类型
    

```sql
ALTER TABLE 表名 CHANGE 旧字段名 新字段名 类型 (长度) [ COMMENT 注释 ] [ 约束 ];
```

```sql
 alter table mytable change nickname username varchar(30) comment '昵称'；
```
4. 删除字段
    

```Go
ALTER TABLE 表名 DROP 字段名;
```

5. 修改表名
    

```Go
ALTER TABLE 表名 RENAME TO 新表名;
```

### 4.表删除
    

1. 删除表
    

```Go
DROP TABLE [ IF EXISTS ] 表名; 
```

2. 删除指定表, 并重新创建表
    

```Go
TRUNCATE TABLE 表名; 
```

# 4.DML
    

DML英文全称是Data Manipulation Language(数据操作语言)，用来对数据库中表的数据记录进行增、删、改操作。 添加数据（INSERT） 修改数据（UPDATE） 删除数据（DELETE）

## 1.添加数据
    

1. 给指定字段添加数据
    

```Go
INSERT INTO 表名 (字段名1, 字段名2, ...) VALUES (值1, 值2, ...); 
```

2. 给全部字段添加数据
    

```Go
INSERT INTO 表名 VALUES (值1, 值2, ...);
```

3. 批量添加数据
    

```Go
INSERT INTO 表名 (字段名1, 字段名2, ...) VALUES (值1, 值2, ...), (值1, 值2, ...), (值 1, 值2, ...) ;
```

或者

```Go
INSERT INTO 表名 VALUES (值1, 值2, ...), (值1, 值2, ...), (值1, 值2, ...) ;
```

注意事项:

- 插入数据时，指定的字段顺序需要与值的顺序是一一对应的。
    
- • 字符串和日期型数据应该包含在引号中。
    
- 插入的数据大小，应该在字段的规定范围内。
    

## 2.修改数据
    

修改数据的具体语法为:

```Go
UPDATE 表名 SET 字段名1 = 值1 , 字段名2 = 值2 , .... [ WHERE 条件 ] ;
```

注意事项: 修改语句的条件可以有，也可以没有，如果没有条件，则会修改整张表的所有数据。

## 3.删除数据
    

```Go
DELETE FROM 表名 [ WHERE 条件 ] ; 
```

注意事项:

- DELETE 语句的条件可以有，也可以没有，如果没有条件，则会删除整张表的所有数据。
    
- DELETE 语句不能删除某一个字段的值(可以使用UPDATE，将该字段值置为NULL即 可)。
    
- 当进行删除全部数据操作时，datagrip会提示我们，询问是否确认删除，我们直接点击 Execute即可。
    

# 5.DQL
    

DQL英文全称是Data Query Language(数据查询语言)，数据查询语言，用来查询数据库中表的记录。

查询关键字: SELECT
![[Pasted image 20241120230421 1.png]]
## 1.基本语法
    

DQL 查询语句，语法结构如下：

```Go
select 
    字段列表
from 
    表明列表
where
    条件列表
group by
    分组字段列表
having
    分组后条件列表
order by
    排序字段列表
limit
    分页参数         
```

将上面的完整语法进行拆分，分为以下几个部分：

- 基本查询（不带任何条件）
    
- 条件查询（WHERE）
    
- 聚合函数（count、max、min、avg、sum）
    
- 分组查询（group by）
    
- 排序查询（order by）
    
- 分页查询（limit）
    

## 2.基础查询
    

在基本查询的DQL语句中，不带任何的查询条件，查询的语法如下：

### 1.查询多个字段
    

```Go
SELECT 字段1, 字段2, 字段3 ... FROM 表名 ;
```

```Go
SELECT * FROM 表名 ;  --查询返回所有字段
```

### 2.字段设置别名
    

```Go
SELECT 字段1 [ AS 别名1 ] , 字段2 [ AS 别名2 ] ... FROM 表名;  --as 可用可不用
```

### 3.去除重复记录
    

```Go
SELECT DISTINCT 字段列表 FROM 表名;
```

## 3.条件查询
    

1. 语法
    

```Go
SELECT 字段列表 FROM 表名 WHERE 条件列表 ; 
```

2. 条件
   ![[Pasted image 20241006211456.png]]
![[Pasted image 20241006211503.png]]

## 4.聚合函数

1. 介绍：将一列数据作为一个整体，进行纵向计算 。
    
2. 常见的聚合函数
    
![[Pasted image 20241006211523.png]]

3. 语法
    

```sql
SELECT 聚合函数(字段列表) FROM 表名 ;
```

注意 : NULL值是不参与所有聚合函数运算的。

## 5.分组查询
    

1. 语法
    

```Go
SELECT 字段列表 FROM 表名 [ WHERE 条件 ] GROUP BY 分组字段名 [ HAVING 分组 后过滤条件 ];
```

2. where与having区别
    

- 执行时机不同：where是分组之前进行过滤，不满足where条件，不参与分组；而having是分组 之后对结果进行过滤。
    
- 判断条件不同：where不能对聚合函数进行判断，而having可以。
    

注意事项:

- 分组之后，查询的字段一般为聚合函数和分组字段，查询其他字段无任何意义。
    
- 执行顺序: where > 聚合函数 > having 。
    
- 支持多字段分组, 具体语法为 : group by columnA,columnB
    

## 6.排序查询
    

排序在日常开发中是非常常见的一个操作，有升序排序，也有降序排序。

1. 语法
    

```Go
SELECT 字段列表 FROM 表名 ORDER BY 字段1 排序方式1 , 字段2 排序方式2 ; 
```

2. 排序方式
    

- ASC :升序（默认值）
    
- DESC：降序
    

注：如果是多字段排序，当第一个字段值相同时，才会根据第二个字段进行排序。

## 7.分页查询
    

1. 语法
    

```Go
SELECT 字段列表 FROM 表名 LIMIT 起始索引, 查询记录数 ;
```

注意事项:

- 起始索引从0开始，起始索引 = （查询页码 - 1）* 每页显示记录数。
    
- 分页查询是数据库的方言，不同的数据库有不同的实现，MySQL中是LIMIT。
    
- 如果查询的是第一页数据，起始索引可以省略，直接简写为 limit 10。
    
## 8.多表查询
[多表查询网站](https://liaoxuefeng.com/books/sql/query/multi-tables/index.html)
[连接查询网站](https://liaoxuefeng.com/books/sql/query/join/index.html)
#### 1.概述&&分类
直接`select * from table_a, table_b;`会出现笛卡尔积现象。
![[Pasted image 20250728232138_副本.png]]
分类：
![[Pasted image 20250728230652.png]]
#### 2.多表关系
一对多：
![[Pasted image 20250728231005.png]]
多对多：
![[Pasted image 20250728231608.png]]
一对一：
![[Pasted image 20250728231534.png]]
#### 3. 连接查询
内连接：现在一般用显式内连接
![[Pasted image 20250728232713.png]]
外连接：
![[Pasted image 20250728233159.png]]
	example：
1. 查询员工（emp表）所有数据，和对应的部门（dept表）信息 ![[Pasted image 20250728234015.png]]
2. 右连接![[Pasted image 20250728233933.png]]
## 9.执行顺序
已经学习了DQL语句的完整语法，及编写顺序，接下来，我们要来说明的是DQL语句在执行时的执行顺序，也就是先执行哪一部分，后执行哪一部分。
![[Pasted image 20241006211606.png]]

| 步骤  | 执行内容                                                    |
| --- | ------------------------------------------------------- |
| 1️⃣ | `FROM recharge e`：加载主表数据（给 recharge 起别名为 `e`）           |
| 2️⃣ | `JOIN ... ON ...`：执行 JOIN（这里是 LEFT JOIN），合并 user 子查询的数据 |
| 3️⃣ | `SELECT`：从 JOIN 后的结果中选择需要的字段                            |
| 4️⃣ | `GROUP BY`（如果有的话）                                       |
| 5️⃣ | `ORDER BY`、`LIMIT`（最后）                                  |

# 6.DCL
    

DCL英文全称是Data Control Language(数据控制语言)，用来管理数据库用户、控制数据库的访问权限。

## 1.管理用户
    

1. 查询用户
    

```Go
use mysql;
select * from mysql.user;
```

2. 创建用户
    

```Go
CREATE USER '用户名'@'主机名' IDENTIFIED BY '密码';
```

localhost表示当前主机，%表示任意主机

3. 修改用户密码
    

```Go
ALTER USER '用户名'@'主机名' IDENTIFIED WITH mysql_native_password BY '新密码' ;
```

4. 删除用户
    

```Go
DROP USER '用户名'@'主机名' ; 
```

注意事项:

- 在MySQL中需要通过用户名@主机名的方式，来唯一标识一个用户。
    
- 主机名可以使用 % 通配。
    
- 这类SQL开发人员操作的比较少，主要是DBA（ Database Administrator 数据库 管理员）使用。
    

## 2.权限控制

MySQL中定义了很多种权限，但是常用的就以下几种：

![[Pasted image 20241006211638.png]]

1. 查询权限
    

```Go
SHOW GRANTS FOR '用户名'@'主机名' ;
```

2. 授予权限
    

```Go
GRANT 权限列表 ON 数据库名.表名 TO '用户名'@'主机名'; 
```

3. 撤销权限
    

```Go
REVOKE 权限列表 ON 数据库名.表名 FROM '用户名'@'主机名';
```

注意事项：

- 多个权限之间，使用逗号分隔
    
- 授权时， 数据库名和表名可以使用 * 进行通配，代表所有。