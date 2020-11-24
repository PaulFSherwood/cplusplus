#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> data = {1,2,3};
    data.push_back(12);
    std::cout << data[data.size() - 1] << std::endl;

    // data.pop_back();     // remove last data element
    // data.push_back();    // puts data at the end
    // data.insert();       // inserts data
    data.pop_back();
    data.push_back(9);
    //data.insert(data.begin(), 5, 0);
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << "\t";
    }
    std::cout << std::endl;
    return 0;
}
