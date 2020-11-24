#include <iostream>  // regular input output
#include <fstream>
#include <vector>

int main()
{
    std::ofstream file("textFile", std::ios::app);

    std::vector<std::string> names;
    names.push_back("one");
    names.push_back("two");
    names.push_back("three");

    for (std::string name : names)
    {
        file << name << std::endl;
    }

    file.close();

    return 0;
}
