#include "todo_item.h"
#include <sstream>
#include <algorithm>
#include <vector>

namespace todo {

static const char kDelim = '\t';

TodoItem::TodoItem() : id_(0), done_(false) {}

TodoItem::TodoItem(int id, const std::string& title, bool done,
                   const std::string& category)
    : id_(id), title_(title), done_(done), category_(category) {}

int TodoItem::getId() const { return id_; }
const std::string& TodoItem::getTitle() const { return title_; }
bool TodoItem::isDone() const { return done_; }
const std::string& TodoItem::getCategory() const { return category_; }

void TodoItem::setTitle(const std::string& title) { title_ = title; }
void TodoItem::setDone(bool done) { done_ = done; }
void TodoItem::setCategory(const std::string& category) { category_ = category; }

std::string TodoItem::serialize() const {
    std::ostringstream oss;
    oss << id_ << kDelim << title_ << kDelim << (done_ ? "1" : "0") << kDelim << category_;
    return oss.str();
}

bool TodoItem::deserialize(const std::string& line) {
    if (line.empty()) return false;
    std::istringstream iss(line);
    std::string part;
    std::vector<std::string> parts;
    while (std::getline(iss, part, kDelim))
        parts.push_back(part);
    if (parts.size() < 3) return false;
    try {
        id_ = std::stoi(parts[0]);
        title_ = parts[1];
        done_ = (parts[2] == "1");
        category_ = parts.size() > 3 ? parts[3] : "";
        return true;
    } catch (...) {
        return false;
    }
}

}  // namespace todo
