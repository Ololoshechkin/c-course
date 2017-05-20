#include <iostream>
#include <vector>
using namespace std;

struct A
{
    int x = 0;
    
    void f();
    void g(int val)
    {
        cout << "g(" << val << ")\n";
    }
    
};

struct B : virtual A
{
    void f()
    {
        cout << "f\n";
    }
};

struct C: virtual A
{
    /*void g(int val)
    {
        cout << "g(" << val << ")\n";
    }*/
};

struct D: B, C
{
    
};

int main(int argc, const char * argv[]) {
    D d;
    d.B::f();
    d.A::g(17);
    if (dynamic_cast<B*>(d))
    {
        
    }
    return 0;
}
