#include "storage.h"
#include <fstream>

namespace todo {

Storage::Storage(const std::string& filepath) : filepath_(filepath) {}

void Storage::setFilepath(const std::string& filepath) { filepath_ = filepath; }
const std::string& Storage::getFilepath() const { return filepath_; }

bool Storage::load(std::vector<TodoItem>& items) const {
    items.clear();
    std::ifstream f(filepath_);
    if (!f.is_open()) return true;  // 无文件视为空列表，不算错误
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        TodoItem item;
        if (item.deserialize(line))
            items.push_back(item);
    }
    return true;
}

bool Storage::save(const std::vector<TodoItem>& items) const {
    std::ofstream f(filepath_);
    if (!f.is_open()) return false;
    for (const auto& item : items)
        f << item.serialize() << "\n";
    return true;
}

}  // namespace todo
