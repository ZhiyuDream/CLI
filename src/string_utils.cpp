#include "string_utils.h"
#include <sstream>
#include <cctype>

namespace todo {

void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) s.pop_back();
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    s = s.substr(i);
}

void split(const std::string& line, std::vector<std::string>& out) {
    out.clear();
    std::istringstream iss(line);
    std::string token;
    while (iss >> token)
        out.push_back(token);
}

}  // namespace todo
