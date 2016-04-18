//借助strtok实现split
#include <string.h>
#include <stdio.h>
#include <cstdlib.h>

#include <string>
#include <vector> 
#include <algorithm>

using namespace std;

std::vector<std::string> split(std::string str, std::string & pattern)
{
    std::string::size_type pos = 0, start = 0;
    std::vector<std::string> result;
    if (pattern.empty()) return result;
    str += pattern.substr(0, 1);
    pos = str.find_first_of(pattern, start);
    while (pos != string::npos) {
        if (pos != start) {
            result.push_back(str.substr(start, pos - start));
        }
        start = pos + 1;
        pos = str.find_first_of(pattern, start);
    }
    return result;
}
 
std::vector<std::string> strtok_split(char* s, const char* d)
{
    char *p;
    std::vector<std::string> result;
    p = strtok(s,d);
    while(p)
    {
        std::string ss(p);
        result.push_back(ss);
        p=strtok(NULL,d);
    }
 
    return result;
}

int toInt(const std::string& s) {
    return atoi(s.c_str());
}