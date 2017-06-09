#include <iostream>
#include <memory>
using namespace std;

struct data
{
	int sz;
	union
	{
		int a[4];
		shared_ptr<uint32_t> p;
	}
	bool is_small()
	{
		return sz <= 4;
	}
	data(int sz)
	: sz(sz)
	{
		if (is_small)
			memset(a, 0, sizeof(a));
		else
		{
			new (&p) std::shared_ptr<uint32_t>(
	                new uint32_t[sz],
	                std::default_delete<uint32_t[]>()
	        );
	        memset(data.)
		}
	}
};

int main(int argc, char const *argv[])
{
	
	return 0;
}