#include <cstdlib>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <new>
#include <algorithm>
using namespace std;
#define string my_string

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
    if (!buf)
        throw bad_alloc();
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
    {}

    string(char const* str)
    {
        size = my_strlen(str);
        capacity = size;
        buffer = my_strdup(str, size);
    }

    string(string const& s)
    {
        char const* s_buf = s.buffer;
        size = my_strlen(s_buf);
        capacity = size;
        buffer = my_strdup(s_buf, size);
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

    void str_swap(string& other)
    {
        swap(buffer, other.buffer);
        swap(size, other.size);
        swap(capacity, other.capacity);
    }

    string& operator=(string rhs) //rhs = right hand size
    {
        str_swap(rhs);

        return *this;
    }

private:

    char* buffer;
    size_t size;
    size_t capacity;

};

int main(int argc, const char * argv[])
{
    string a("hello");
    string b(" world!");
    string s = a;
    //s[2] = 'G';
    //f(s);
    printf("%s\n", s.c_str());
    return 0;
}
