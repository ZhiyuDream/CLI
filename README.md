# todo-cli

命令行待办事项小工具，纯 C++ 实现，结构简单易读。

## 功能

- 添加待办（可选分类：`add 标题 --category 分类`）
- 标记完成/未完成：`done <id>`、`undone <id>`
- 删除：`remove <id>`
- 修改标题：`update <id> 新标题`
- 列出全部或按分类：`list`、`list 分类`
- 退出时自动保存到当前目录下的 `todos.txt`

## 目录结构

```
todo-cli/
├── include/          # 头文件
│   ├── todo_item.h   # 单条待办
│   ├── storage.h     # 文件持久化
│   ├── todo_manager.h# 待办集合管理
│   └── cmd_parser.h  # 命令解析
├── src/              # 实现
│   ├── main.cpp
│   ├── todo_item.cpp
│   ├── storage.cpp
│   ├── todo_manager.cpp
│   └── cmd_parser.cpp
├── CMakeLists.txt
└── README.md
```

## 构建与运行

在项目根目录执行：

```bash
mkdir build && cd build
cmake ..
make
./todo_cli
```

数据文件 `todos.txt` 会在运行 `todo_cli` 时的当前工作目录下创建。

## 命令速查

| 命令 | 说明 |
|------|------|
| add \<标题\> [--category \<分类\>] | 添加待办 |
| done \<id\> | 标记已完成 |
| undone \<id\> | 标记未完成 |
| remove \<id\> | 删除 |
| update \<id\> \<新标题\> | 修改标题 |
| list [分类] | 列出全部或指定分类 |
| quit / exit | 退出并保存 |
| help | 显示帮助 |
