#include <iostream>

class Dog { // base class
    public:
        Dog() {
        }

        void Bark() {
            std::cout << "Bark!" << std::endl;
        }

        void Walk() {
            x+=1;
            y+=1;
        }
       
        bool Eat() {
            std::cout << "Dog has ate" << std::endl;
            return hungry = false;
        }

        bool Drinking() {
            std::cout << "Dog has drank" << std::endl;
            return thristy = false;
        }

        bool Sleepy() {
            std::cout << "Dog has slept" << std::endl;
            return tired = false;
        }

        float x, y;
        bool hungry = true;
        bool thristy = true;
        bool tired = true;
};

class Golden : public Dog {
    public:
        Golden() {
            m_sticksRetrieved = 0;
        }
        void Retrieve() {
            std::cout << "retrieving a stick\n";
            m_sticksRetrieved++;
        }
        float m_sticksRetrieved;
};

class Huskey : public Dog {
    public:
        void HowlLoud() {
            std::cout << "Huskey howls loudly" << std::endl;
        }
};

int main() {
    
    Golden dog1;
    dog1.Bark();
    dog1.Walk();
    dog1.Retrieve();

    Huskey dog2;
    dog2.Bark();

    std::cout << "sizeof(Dog)" << sizeof(Dog) << std::endl;
    std::cout << "sizeof(Golden)" << sizeof(Golden) << std::endl;

    return 0;
}

