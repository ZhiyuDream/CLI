#include "todo_manager.h"
#include <algorithm>

namespace todo {

TodoManager::TodoManager() {}

int TodoManager::nextId() const {
    int maxId = 0;
    for (const auto& item : items_)
        if (item.getId() > maxId) maxId = item.getId();
    return maxId + 1;
}

bool TodoManager::add(const std::string& title, const std::string& category) {
    if (title.empty()) return false;
    items_.emplace_back(nextId(), title, false, category);
    return true;
}

bool TodoManager::remove(int id) {
    auto it = std::find_if(items_.begin(), items_.end(),
        [id](const TodoItem& x) { return x.getId() == id; });
    if (it == items_.end()) return false;
    items_.erase(it);
    return true;
}

bool TodoManager::setDone(int id, bool done) {
    TodoItem* p = const_cast<TodoItem*>(find(id));
    if (!p) return false;
    p->setDone(done);
    return true;
}

bool TodoManager::updateTitle(int id, const std::string& title) {
    TodoItem* p = const_cast<TodoItem*>(find(id));
    if (!p || title.empty()) return false;
    p->setTitle(title);
    return true;
}

void TodoManager::listAll(std::vector<TodoItem>& out) const {
    out = items_;
}

void TodoManager::listByCategory(const std::string& category, std::vector<TodoItem>& out) const {
    out.clear();
    for (const auto& item : items_)
        if (item.getCategory() == category)
            out.push_back(item);
}

void TodoManager::listPending(std::vector<TodoItem>& out) const {
    out.clear();
    for (const auto& item : items_)
        if (!item.isDone())
            out.push_back(item);
}

const TodoItem* TodoManager::find(int id) const {
    for (const auto& item : items_)
        if (item.getId() == id) return &item;
    return nullptr;
}

size_t TodoManager::size() const { return items_.size(); }

void TodoManager::setItems(const std::vector<TodoItem>& items) { items_ = items; }

void TodoManager::getAll(std::vector<TodoItem>& out) const { out = items_; }

}  // namespace todo
