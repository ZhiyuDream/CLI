#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

namespace todo {

void trim(std::string& s);
void split(const std::string& line, std::vector<std::string>& out);

}  // namespace todo

#endif
