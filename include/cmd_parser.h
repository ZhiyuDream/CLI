#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include <string>
#include <vector>

namespace todo {

/** 命令类型 */
enum class Command {
    Add,
    Done,
    Undone,
    Remove,
    Update,
    List,
    ListCategory,
    Clear,
    Quit,
    Help,
    Unknown
};

/** 解析结果：命令 + 参数 */
struct ParsedCommand {
    Command cmd;
    std::vector<std::string> args;
};

/** 解析用户输入行，得到命令与参数 */
ParsedCommand parseLine(const std::string& line);

/** 打印帮助信息 */
void printHelp();

}  // namespace todo

#endif  // CMD_PARSER_H
