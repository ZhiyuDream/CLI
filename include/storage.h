#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "todo_item.h"

namespace todo {

/** 待办数据持久化：从文件加载、保存到文件 */
class Storage {
public:
    explicit Storage(const std::string& filepath = "todos.txt");

    void setFilepath(const std::string& filepath);
    const std::string& getFilepath() const;

    bool load(std::vector<TodoItem>& items) const;
    bool save(const std::vector<TodoItem>& items) const;

private:
    std::string filepath_;
};

}  // namespace todo

#endif  // STORAGE_H
