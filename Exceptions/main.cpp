#include <iostream>
#include <cstdio>
#include <stdexcept>

FILE* my_fopen(char const* filename, char const* mode)
{
    FILE* tmp = fopen(filename, mode);
    if (!tmp)
        throw std::runtime_error("cannot open file");
    return tmp;
}


struct file
{
    file(char const* filename, char const* mode)
        : fd(my_fopen(filename, mode))
    {}

    file(file const&) = delete;
    file& operator = (file const&) = delete;

    ~file()
    {
        fclose(fd);
    }

private:
    FILE* fd;
};

template <typename T>
struct scoped_ptr
{

    scoped_ptr()
            : ptr(nullptr)
    {}

    explicit scoped_ptr(T* ptr) //explicit - означает то, что нельзя неявно конвертить
            : ptr(ptr)
    {}
    /*
        пример :
        void f(scoped_ptr<int> b);
        ...
        main() {
        int* a = new int(7);
        f(a); - вот это мы запретили
       }
    */

    scoped_ptr(scoped_ptr const&);
    scoped_ptr&operator =(scoped_ptr const&);

    ~scoped_ptr()
    {
        delete ptr;
    }

    T& operator *() const
    {
        return *ptr;
    }

    T* operator ->() const
    {
        return ptr;
    }

private:
    T* ptr;
};

struct pnt
{
    int x, y;
    pnt(int x, int y) : x(x), y(y)
    {}
};

int main()
{
    try
    {
        file a("1.txt", "r");
        file b("2.txt", "r");
        file c("3.txt", "r");
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}