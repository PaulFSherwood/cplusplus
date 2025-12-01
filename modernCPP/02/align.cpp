    #include <print>
    // align of: A variable must start at a memory address that is a multple of some number of bytes.
    // That number is the type's alignment requirement.
    // example: double(8 bytes) 0, 8, 16, 24, 32, ... not 3, 7, 11, 19, etc.
    struct MyStruct {
        char c;
        int i;
    };

    int main() {
        std::print("Alignment of char: {}\n", alignof(char));
        std::print("Alignment of int: {}\n", alignof(int));
        std::print("Alignment of MyStruct: {}\n", alignof(MyStruct)); 
        std::print("Size of MyStruct: {}\n", sizeof(MyStruct)); 
        return 0;
    }
