#include <bits/stdc++.h>

using namespace std;

long int midSquare(long int seed)
{
    long long bp = seed * seed;
    string str1 = to_string(seed);
    string str2 = to_string(bp);
    str2.pop_back();
    str2.pop_back();
    string ans = str2.substr(str2.length() - 4, 4);
    long long res = stoll(ans);
    return res;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}
long int digitExtraction(long int seed,int* extractDigits,int size)
{
    string str = to_string(seed);
    long long res = 0;
    for (int i = 0; i < size; i++){
        res = res * 10 + (str[extractDigits[i]] - '0');
    }
    return  res;
}

int main(){
    cout <<midSquare(9452);
}