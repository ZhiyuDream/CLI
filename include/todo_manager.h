#ifndef TODO_MANAGER_H
#define TODO_MANAGER_H

#include <string>
#include <vector>
#include "todo_item.h"

namespace todo {

/** 待办集合管理：增删改查、按分类筛选 */
class TodoManager {
public:
    TodoManager();

    bool add(const std::string& title, const std::string& category = "");
    bool remove(int id);
    bool setDone(int id, bool done);
    bool updateTitle(int id, const std::string& title);

    void listAll(std::vector<TodoItem>& out) const;
    void listByCategory(const std::string& category, std::vector<TodoItem>& out) const;
    void listPending(std::vector<TodoItem>& out) const;

    const TodoItem* find(int id) const;
    size_t size() const;

    /** 供 Storage 使用：替换全部项（加载后） */
    void setItems(const std::vector<TodoItem>& items);
    /** 供 Storage 使用：获取全部项 */
    void getAll(std::vector<TodoItem>& out) const;

private:
    std::vector<TodoItem> items_;
    int nextId() const;
};

}  // namespace todo

#endif  // TODO_MANAGER_H
