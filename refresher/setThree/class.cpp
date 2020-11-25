#include <iostream>
#include <vector>

class User // starting custom datatypes with a capital letter
{
    // default access in a class is private
    public:
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

int add_user_if_not_exists(std::vector<User> &users, User user)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].first_name == user.first_name && users[i].last_name  == user.last_name)
        {
            return i;
        }
    }
    users.push_back(user);
    return users.size() - 1;
}

int main()
{
    // User me;
    // me.first_name = "paul";
    // me.last_name = "lname";
    // me.set_status("bacon");
    // std::vector<User> my;
    // my.push_back(me);

    // for (int i = 0; i < my.size(); i++)
    // {
    //     std::cout << "my[" << i << "]: " << my[i].first_name << std::endl;
        
    // }

    std::vector<User> users;
    //users.push_back(User());

    User user1, user2, user3;
    user1.first_name = "Sally";
    user1.last_name  = "Swan";

    user2.first_name = "Jake";
    user2.last_name  = "Johnson";

    user3.first_name = "Caleb";
    user3.last_name  = "Curry";

    users.push_back(user1);
    users.push_back(user2);
    users.push_back(user3);

    User user;
    user.first_name = "Jacob";
    user.last_name  = "Johnson";

    std::cout <<add_user_if_not_exists(users, user) << std::endl;

    std::cout << users.size() << std::endl;

    // std::cout << "Fname: " << me.first_name << std::endl;
    // std::cout << "Lname: " << me.last_name << std::endl;
    // std::cout << "Status: " << me.get_status() << std::endl;


    return 0;
}