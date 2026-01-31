#ifndef TODO_ITEM_H
#define TODO_ITEM_H

#include <string>

namespace todo {

/** 单条待办项：id、标题、是否完成、可选分类 */
class TodoItem {
public:
    TodoItem();
    TodoItem(int id, const std::string& title, bool done = false,
             const std::string& category = "");

    int getId() const;
    const std::string& getTitle() const;
    bool isDone() const;
    const std::string& getCategory() const;

    void setTitle(const std::string& title);
    void setDone(bool done);
    void setCategory(const std::string& category);

    /** 序列化为一行存储格式（制表符分隔）：id, title, done, category */
    std::string serialize() const;
    /** 从一行解析，返回是否成功 */
    bool deserialize(const std::string& line);

private:
    int id_;
    std::string title_;
    bool done_;
    std::string category_;
};

}  // namespace todo

#endif  // TODO_ITEM_H
