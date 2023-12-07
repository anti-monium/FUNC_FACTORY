#include <iostream>

#include "lib/FuncFactory.hpp"

int main() {
    FunctionFactory F;
    auto f1 = F.Create("polynomial", {3, -1, 3, 4, 5});
    auto f2 = F.Create("exp", 2);
    auto f = *f1 - *f2;
    std::cout << (*f1).ToString() << "\n";
    std::cout << (*f2).ToString() << "\n";
    std::cout << f.ToString() << "\n";
    std::cout << FindRoot(f, 3, 100000, 0.000000001) << "\n";
}