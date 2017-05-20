#include <iostream>
#include "codeWithHeader.hpp"

void f();

int main(int argc, const char * argv[]) {
    f();
    myClass obj = *new myClass(15);
    std::cout << "from header(17): " << myClass::getSeventeen() << std::endl;
    std::cout << "from header(val): " << obj.getValue() << std::endl;
    return 0;
}
