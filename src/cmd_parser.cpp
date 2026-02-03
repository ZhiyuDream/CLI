#include "cmd_parser.h"
#include <iostream>
#include <sstream>
#include <cctype>

namespace todo {

static void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) s.pop_back();
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    s = s.substr(i);
}

static void split(const std::string& line, std::vector<std::string>& out) {
    out.clear();
    std::istringstream iss(line);
    std::string token;
    while (iss >> token)
        out.push_back(token);
}

ParsedCommand parseLine(const std::string& line) {
    ParsedCommand result{Command::Unknown, {}};
    std::string trimmed = line;
    trim(trimmed);
    if (trimmed.empty()) return result;

    std::vector<std::string> tokens;
    split(trimmed, tokens);
    if (tokens.empty()) return result;

    std::string cmd = tokens[0];
    for (auto& c : cmd)
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c + 32);

    if (cmd == "add" || cmd == "a") {
        result.cmd = Command::Add;
        if (tokens.size() >= 2) {
            size_t start = tokens[0].size();
            while (start < trimmed.size() && std::isspace(static_cast<unsigned char>(trimmed[start]))) ++start;
            std::string rest = trimmed.substr(start);
            std::string category;
            size_t pos = rest.find("--category");
            if (pos != std::string::npos) {
                size_t catStart = rest.find_first_not_of(" \t", pos + 10);
                if (catStart != std::string::npos)
                    category = rest.substr(catStart);
                rest = rest.substr(0, pos);
                trim(rest);
            }
            trim(rest);
            if (!rest.empty()) {
                result.args.push_back(rest);
                if (!category.empty()) result.args.push_back(category);
            }
        }
        return result;
    }

    if (cmd == "done" || cmd == "d") {
        result.cmd = Command::Done;
        if (tokens.size() >= 2) result.args.push_back(tokens[1]);
        return result;
    }

    if (cmd == "undone" || cmd == "u") {
        result.cmd = Command::Undone;
        if (tokens.size() >= 2) result.args.push_back(tokens[1]);
        return result;
    }

    if (cmd == "remove" || cmd == "r" || cmd == "rm") {
        result.cmd = Command::Remove;
        if (tokens.size() >= 2) result.args.push_back(tokens[1]);
        return result;
    }

    if (cmd == "update" || cmd == "up") {
        result.cmd = Command::Update;
        if (tokens.size() >= 3) {
            result.args.push_back(tokens[1]);
            size_t start = trimmed.find(tokens[2]);
            if (start != std::string::npos)
                result.args.push_back(trimmed.substr(start));
        }
        return result;
    }

    if (cmd == "list" || cmd == "ls" || cmd == "l") {
        result.cmd = tokens.size() >= 2 ? Command::ListCategory : Command::List;
        if (tokens.size() >= 2) result.args.push_back(tokens[1]);
        return result;
    }

    if (cmd == "clear" || cmd == "c") {
        result.cmd = Command::Clear;
        return result;
    }

    if (cmd == "quit" || cmd == "q" || cmd == "exit") {
        result.cmd = Command::Quit;
        return result;
    }

    if (cmd == "help" || cmd == "h" || cmd == "?") {
        result.cmd = Command::Help;
        return result;
    }

    return result;
}

void printHelp() {
    std::cout << "命令:\n"
              << "  add <标题> [--category <分类>]  添加待办\n"
              << "  done <id>                       标记为已完成\n"
              << "  undone <id>                     标记为未完成\n"
              << "  remove <id>                     删除待办\n"
              << "  update <id> <新标题>            修改标题\n"
              << "  list [分类]                     列出全部或指定分类\n"
              << "  clear                           清空全部待办\n"
              << "  quit / exit                     退出（数据自动保存）\n"
              << "  help                            显示此帮助\n";
}

}  // namespace todo
