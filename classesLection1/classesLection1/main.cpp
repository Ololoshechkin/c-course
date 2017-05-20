#include <cstdlib>
#include <cstdio>
using namespace std;

size_t my_strlen(char const* str)
{
    char const* p = str;
    while (*p != '\0')
        ++p;
    return p - str;
}

void my_memcpy(void* dst, void const* src, size_t size)
{
    char* cdst = (char*)dst;
    char const* csrc = (char const*)src;
    for (size_t i = 0; i != size; ++i)
        cdst[i] = csrc[i];
}

char* my_strdup(char const* str)
{
    size_t size = my_strlen(str);
    char* buf = (char*)malloc(size + 1);
    my_memcpy(buf, str, size);
    return buf;
}

char* my_strdup(char const* str, size_t size)
{
    char* buf = (char*)malloc(size + 1);
    my_memcpy(buf, str, size);
    return buf;
}

struct string
{
public:
    
    string()
        : buffer(nullptr)
        , size(0)
        , capacity(0)
    {
    }
    
    string(char const* str)
    {
        size = my_strlen(str);
        capacity = size;
        buffer = my_strdup(str, size);
    }
    
    void print()
    {
        for (size_t i = 0; i != size; ++i)
            printf("%c", buffer[i]);
    }
    
    char& operator[] (size_t i)
    {
        return buffer[i];
    }
    
    char const& operator[] (size_t i) const//const значит, что this у этой функции имеет тип не string*, a string const* (т.е. мы не меняемся)
    {
        return buffer[i];
    }
    
    char const* c_str() const
    {
        return buffer;
    }
    
    ~string()
    {
        free(buffer);
    }
    
    string& operator=(string const& rhs)//rhs = right hand size
    {
        if (this == &rhs)
            return *this;
        free(buffer);
        buffer = my_strdup(rhs.buffer);
        size = rhs.size;
        capacity = rhs.capacity;
        return *this;
    }
    
private:
    
    char* buffer;
    size_t size;
    size_t capacity;
    
};

//lvalue - объекты, с которыми можно работать (что-либо делать/менять)
//rvalue - временные объекты
//константные ссылки умеют каститься ко всему(и к rvalue в т.ч.)
//обычные - ожидают только lvalue
//NB: (a=2) - это lvalue (можно написать "(a = 2) = 5" )
//NB': a+=2 - это тоже lvalue ((a += 2) += 3)
//NB'': ++a - lvalue (++++++a - так можно)
//NB''': a++ - это уже rvalue
//NB: *a - lvalue!


string operator + (string const& a, string const& b)
{
    //TODO
    return string();
}

void f(string const& s)
{
    char c = s[0];
}

int main(int argc, const char * argv[])
{
    string a("hello");
    string b(" world!");
    string s;
    s = a;
    //s[2] = 'G';
    //f(s);
    printf("%s\n", s.c_str());
    return 0;
}
