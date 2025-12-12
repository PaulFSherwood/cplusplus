/**
 *  strategy_runtime_dispatch.cpp
 *
 *  Demonstrates changing program behavior at runtime by swapping
 *  the function object that performs an operation.  This is an example
 *  of the Strategy Pattern implemented using:
 *    - function pointers
 *    - std::function
 *    - lambda expressions
 *
 *  KDE Coding Style Guidelines:
 *    * 4-space indentation
 *    * Braces on separate lines
 *    * No "using namespace std"
 *    * Meaningful comments explaining intent
 */

#include <iostream>
#include <functional>
#include <string>

/* -------------------------------------------------------------------------
 *  Example operations the player can choose from.
 *  Each operation has the signature: int func(int, int)
 * ------------------------------------------------------------------------- */

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

/**
 * A C-like function pointer type for integer operations.
 * Note: This is equivalent to: int (*)(int, int)
 */
typedef int (*IntegerOpFn)(int, int);

/* -------------------------------------------------------------------------
 *  Runtime selection using Strategy Pattern
 * ------------------------------------------------------------------------- */

int main()
{
    std::cout << "=== Runtime Operation Selector (Strategy Pattern) ===\n";
    std::cout << "Choose an operation:\n";
    std::cout << " 1 = add\n";
    std::cout << " 2 = subtract\n";
    std::cout << " 3 = multiply\n\n";

    int choice = 0;
    std::cin >> choice;

    int a = 0;
    int b = 0;

    std::cout << "Enter two integers:\n";
    std::cin >> a >> b;

    /* ---------------------------------------------------------------------
     * 1) Function pointer implementation
     * --------------------------------------------------------------------- */

    IntegerOpFn opFn = nullptr;

    if (choice == 1)
    {
        opFn = add;
    }
    else if (choice == 2)
    {
        opFn = subtract;
    }
    else if (choice == 3)
    {
        opFn = multiply;
    }
    else
    {
        std::cout << "Invalid selection.\n";
        return 1;
    }

    std::cout << "\n[Function Pointer] Result: " << opFn(a, b) << "\n";

    /* ---------------------------------------------------------------------
     * 2) std::function implementation (more flexible than raw pointers)
     * --------------------------------------------------------------------- */

    std::function<int(int, int)> opStdFunc;

    if (choice == 1)
    {
        opStdFunc = add;
    }
    else if (choice == 2)
    {
        opStdFunc = subtract;
    }
    else
    {
        opStdFunc = multiply;
    }

    std::cout << "[std::function]  Result: " << opStdFunc(a, b) << "\n";

    /* ---------------------------------------------------------------------
     * 3) Using a lambda to replace behavior at runtime
     *    This shows true power: behavior is fully replaced with no new function.
     * --------------------------------------------------------------------- */

    std::function<int(int, int)> lambdaOp;

    if (choice == 1)
    {
        lambdaOp = [] (int x, int y) { return x + y + 100; };
        /**
         * NOTE: This lambda intentionally changes behavior.
         * Instead of normal addition, it adds an extra 100.
         * This is to demonstrate true runtime behavior replacement.
         */
    }
    else if (choice == 2)
    {
        lambdaOp = [] (int x, int y) { return (x - y) * 2; };
    }
    else
    {
        lambdaOp = [] (int x, int y) { return (x * y) + 1; };
    }

    std::cout << "[Lambda Strategy] Result: " << lambdaOp(a, b) << "\n";

    std::cout << "\nDone.\n";
    return 0;
}
/*
    Why this is a real example of the technique
    
    This shows what's happening in your original code:
    
    ✔️ You change the meaning of op() at runtime
    
    By assigning:
    
        opFn = add;       // opFn(x,y) means addition
        opFn = multiply;  // now opFn(x,y) means multiplication
    
    
    This is exactly the Strategy Pattern — swapping algorithms at runtime.
    
    ✔️ std::function makes it even more powerful
    
    You can replace the algorithm with:
    
    a function pointer
    
    a lambda
    
    a functor object
    
    a moved function object
    
    ✔️ Demonstrates dynamic behavior changes
    
    In a real game (like your LOTGD example), this is used for:
    
    changing combat behavior
    
    swapping enemy AI strategies
    
    equipping new abilities
    
    selecting spells
    
    dynamic menus
*/
