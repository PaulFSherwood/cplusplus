#include <iostream>

struct User // starting custom datatypes with a capital letter
{
    // default access in a struct is public
    std::string first_name;
    std::string last_name;
    std::string get_status()
    {
        return status;
    }
    void set_status(std::string name)
    {
        status = name;
    }
    private:
        std::string status;
};

int main()
{
    User me;
    me.first_name = "paul";
    me.last_name = "lname";
    me.set_status("bacon");


    std::cout << "Fname: " << me.first_name << std::endl;
    std::cout << "Lname: " << me.last_name << std::endl;
    std::cout << "Status: " << me.get_status() << std::endl;


    return 0;
}