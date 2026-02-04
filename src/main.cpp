#include "todo_manager.h"
#include "storage.h"
#include "cmd_parser.h"
#include <iostream>
#include <string>
#include <cstdlib>

namespace {

const char* kDataFile = "todos.txt";
const char* kVersion = "0.2.0";

void runAdd(todo::TodoManager& mgr, const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "用法: add <标题> [--category <分类>]\n";
        return;
    }
    std::string category = args.size() > 1 ? args[1] : "";
    if (mgr.add(args[0], category))
        std::cout << "已添加。\n";
    else
        std::cout << "添加失败（标题不能为空）。\n";
}

void runDone(todo::TodoManager& mgr, const std::vector<std::string>& args, bool done) {
    if (args.empty()) {
        std::cout << "用法: " << (done ? "done" : "undone") << " <id>\n";
        return;
    }
    int id = std::atoi(args[0].c_str());
    if (mgr.setDone(id, done))
        std::cout << "已更新。\n";
    else
        std::cout << "未找到 id=" << id << "\n";
}

void runRemove(todo::TodoManager& mgr, const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "用法: remove <id>\n";
        return;
    }
    int id = std::atoi(args[0].c_str());
    if (mgr.remove(id))
        std::cout << "已删除。\n";
    else
        std::cout << "未找到 id=" << id << "\n";
}

void runUpdate(todo::TodoManager& mgr, const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "用法: update <id> <新标题>\n";
        return;
    }
    int id = std::atoi(args[0].c_str());
    if (mgr.updateTitle(id, args[1]))
        std::cout << "已更新。\n";
    else
        std::cout << "未找到 id=" << id << " 或标题为空。\n";
}

void printItems(const std::vector<todo::TodoItem>& items) {
    if (items.empty()) {
        std::cout << "（无）\n";
        return;
    }
    for (const auto& item : items) {
        std::cout << "  [" << item.getId() << "] "
                  << (item.isDone() ? "[x] " : "[ ] ")
                  << item.getTitle();
        if (!item.getCategory().empty())
            std::cout << "  #" << item.getCategory();
        std::cout << "\n";
    }
}

void runList(todo::TodoManager& mgr, const std::vector<std::string>& args) {
    std::vector<todo::TodoItem> out;
    if (args.empty())
        mgr.listAll(out);
    else
        mgr.listByCategory(args[0], out);
    printItems(out);
}

void runClear(todo::TodoManager& mgr) {
    mgr.clearAll();
    std::cout << "已清空全部待办。\n";
}

}  // namespace

int main() {
    todo::Storage storage(kDataFile);
    todo::TodoManager manager;

    std::vector<todo::TodoItem> loaded;
    if (storage.load(loaded))
        manager.setItems(loaded);
    else {
        std::cerr << "无法读取 " << kDataFile << "\n";
    }

    std::cout << "\n";
    std::cout << "  ========================================\n";
    std::cout << "      待办 CLI  v" << kVersion << "\n";
    std::cout << "  ========================================\n";
    std::cout << "  输入 help 查看命令\n\n";

    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) break;

        todo::ParsedCommand pc = todo::parseLine(line);

        switch (pc.cmd) {
            case todo::Command::Add:
                runAdd(manager, pc.args);
                break;
            case todo::Command::Done:
                runDone(manager, pc.args, true);
                break;
            case todo::Command::Undone:
                runDone(manager, pc.args, false);
                break;
            case todo::Command::Remove:
                runRemove(manager, pc.args);
                break;
            case todo::Command::Update:
                runUpdate(manager, pc.args);
                break;
            case todo::Command::List:
            case todo::Command::ListCategory:
                runList(manager, pc.args);
                break;
            case todo::Command::Clear:
                runClear(manager);
                break;
            case todo::Command::Quit: {
                std::vector<todo::TodoItem> toSave;
                manager.getAll(toSave);
                if (storage.save(toSave))
                    std::cout << "已保存，再见。\n";
                else
                    std::cerr << "保存失败。\n";
                return 0;
            }
            case todo::Command::Help:
                todo::printHelp();
                break;
            default:
                if (!line.empty())
                    std::cout << "未知命令，输入 help 查看帮助。\n";
                break;
        }
    }

    std::vector<todo::TodoItem> out;
    manager.getAll(out);
    storage.save(out);
    return 0;
}
