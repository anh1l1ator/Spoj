#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
using namespace std;
vector < string  >Split(string str)
{
    std::istringstream buf(str);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);
    return tokens;
}
int main()
{

    std::string str = "This is a string";
    vector < string > X=Split(str);
    for(auto S:X)
        cout<<S<<"\n";
    return 0;
}
