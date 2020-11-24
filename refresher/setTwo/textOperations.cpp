#include <iostream>     // regular input output
#include <fstream>      // working with files
#include <vector>

void writeToFile(std::string addMe) 
{
    // Writing to a file
    std::ofstream file("textFile", std::ios::app);
    std::vector<std::string> names;
    names.push_back(addMe);
    for (std::string name : names) { file << name << std::endl; }
    file.close();
}
void readFromFile()
{
    // Reading from a file
    std::ifstream file("textFile");
    std::vector<std::string> names;
    std::string input;
    while (file >> input) { names.push_back(input); }
    for(std::string name : names) { std::cout << name << std::endl; }
}
int main()
{
    /*
    std::string filename;
    std::cin >> filename;
    std::ofstream file(filename, std::ios::app);
    // more notes
    // read one line
    std::string line;       // this holds the line that will be pulled otu of the file
    getline(file, line);    // this will pull the first line out of the file and save it to line variable
    std::cout << line << endl; // show the output
    */
    std::string addMe;
    std::cin >> addMe;
    // made a function out of writing to make sure everything goes out of scope
    writeToFile(addMe);
    // readfunction to .. um read the file to the user
    readFromFile();

    
    return 0;
}
