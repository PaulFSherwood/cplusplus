#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    std::string folder;
    char *input_folder = NULL;
   
    folder = "cmd ";
    if (argc > 1)
    {
     input_folder = argv[1];       
     folder.append(argv[1]);
     system(folder.c_str());
    }
   
    return EXIT_SUCCESS;
}

