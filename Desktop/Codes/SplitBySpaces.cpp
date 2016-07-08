#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
vector < int >Split(string str)
{

    std::string str = "This is a string";
    std::istringstream buf(str);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);
    return tokens;
}
