  // Convert this program to C++

  // change to C++ io

  // change to one line comments

  //change defines of constants to const

  // change array to vector<>

  // inline any short function


#include <iostream>
#include <vector>
using namespace ::std;
const int N = 40;

template<class summable>
inline void sum(summable* sum, int size, vector<summable> data)//inline sum
{
    *sum = 0;
    for (int i = 0; i < size; i++) *sum = *sum + data[i];
}

int main()
{
    int i;

    int accum = 0;

    vector<int> data(N);

    for (i = 0; i < N; ++i)

        data[i] = i;

    sum(&accum, N, data);

    cout <<"sum is "<< accum << endl;

    return 0;

}