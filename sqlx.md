## 说明

这是一个 sql migrate 的工具，能将 sql 的建表语句执行

它有一些其他的功能，我们不去使用，只用 migrate 功能

每个 sql 都有时间，和标签，所有会维护一个类似于 git commit 的记录

当我们要增加新的表或者给字段重命名时 新增一个 sql 即可

## 基本用法

```
sqlx migrate
Group of commands for creating and running migrations

Usage: sqlx migrate <COMMAND>

Commands:
  add           Create a new migration with the given description
  run           Run all pending migrations
  revert        Revert the latest migration with a down file
  info          List all available migrations
  build-script  Generate a `build.rs` to trigger recompilation when a new migration is added
  help          Print this message or the help of the given subcommand(s)

Options:
  -h, --help  Print help
```

### 增加将 key prompt 字段从 node 表删除的 migration

```
sqlx migrate add delete_keyprompt_from_node -r
```

然后修改 `migrations/20250911105407_delete_keyprompt_from_node.up.sql`

### 执行 migration

```
sqlx migrate run

sqlx migrate revert
```

### 强行重置数据库

```
sqlx database reset -f
```