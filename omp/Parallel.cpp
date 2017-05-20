#include <bits/stdc++.h>
#include "omp.h"
using namespace std;
#define ll long long
const ll p = 239 * 2 + 1, mod = (int)1e9 + 7;

ll getHash(vector<ll>& v) {
    ll h = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        h = (p * h + v[i]) % mod;
    }
    return h;
}

void parallelCout() {
#pragma omp parallel
    {
        cout << "OpenMP Test\n";
    }
}

void sum(vector<ll>& a, vector<ll>& b, vector<ll>& c, bool isParallel) {
    size_t n = c.size();
    if (!isParallel)
    {
        for (size_t i = 0; i < n; ++i)
            c[i] = a[i] + b[i];
    }
    else
    {
        #pragma omp parallel for
        for (ptrdiff_t i = 0; i < n; ++i)
        {
            c[i] = a[i] + b[i];
        }
    }
}



int main()
{
    srand(42);
    parallelCout();
    int n = (int)1e7;
    vector<ll> a(n), b(n), c(n);
    
    for (size_t i = 0; i < n; ++i)
    {
        a[i] = rand();
        b[i] = rand();
    }
    
    int st1 = clock();
    sum(a, b, c, false);
    int end1 = clock();
    ll hash1 = getHash(c);
    
    int st2 = clock();
    sum(a, b, c, true);
    int end2 = clock();
    ll hash2 = getHash(c);
    
    printf("non-parallel time : %f (hash: %lld)\nparallel time : %f (hash: %lld)\nhash test passed : %s\n",
           (end1 - st1) / 1e6, hash1,
           (end2 - st2) / 1e6, hash2,
           hash1 == hash2 ? "true" : "false");
}
