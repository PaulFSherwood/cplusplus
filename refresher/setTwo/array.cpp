#include <iostream>
#include <vector>

// void do_something(const int array[])
// {
//     std::cout << *array << std::endl;
//     int *p;
//     p = array;

// }

void print_array(const int data[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << data[i] << "\t";
    }
    std::cout << std::endl;
    // do_something(data);
}

int main()
{
    int data[] = {1, 2, 3};
    print_array(data, 3);
    // std::cout << data[0] << std::endl;

    return 0;
}