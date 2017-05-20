#include <iostream>

extern int a;

void f();

int main(int argc, const char * argv[]) {
    extern int b;
    f();
    a = 5;
    f();
    return 0;
}
