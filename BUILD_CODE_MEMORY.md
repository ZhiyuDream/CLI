# todo-cli 建图（代码记忆）

## 1. 生成 compile_commands.json

在仓库根目录执行（首次或 CMake 配置变更后）：

```bash
cd /home/zhiyu_zheng/DCL/Others/test/todo-cli
mkdir -p build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

完成后 `compile_commands.json` 在 `build/` 目录下。

## 2. 建图命令

在 **H-SEAM-CODE** 项目根目录执行：

```bash
cd /home/zhiyu_zheng/DCL/Others/H-SEAM-CODE

python3 scripts/build_code_memory.py \
  --repo /home/zhiyu_zheng/DCL/Others/test/todo-cli \
  --namespace todo_cli \
  --compile-commands /home/zhiyu_zheng/DCL/Others/test/todo-cli/build
```

可选：指定 clangd（默认 clangd-20）：

```bash
python3 scripts/build_code_memory.py \
  --repo /home/zhiyu_zheng/DCL/Others/test/todo-cli \
  --namespace todo_cli \
  --compile-commands /home/zhiyu_zheng/DCL/Others/test/todo-cli/build \
  --clangd clangd-20
```

## 前提

- Neo4j 已启动，且 `.env` 中 `USE_NEO4J=true`、Neo4j 连接配置正确。
- 已安装 clangd（如 `clangd-20`）并在 PATH 中，或通过 `--clangd` 指定路径。
