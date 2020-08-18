#include <iostream>
#include <string>

using namespace std;

int main()
{   
    int arr[3][4] ;
                    // {{0,1,2,3},
                    // {4,5,6,7},
                    // {8,9,10,11}};

    int cnt = 0;
    cout<< *arr << endl;
    cout<< *arr[1] << endl;
    cout<< arr[0][1] << endl;

    for (auto &raw :arr)
    {
        for( auto &col :raw)
        {   
            col = cnt;
            cout << col << "--------" << endl;
            ++cnt;
        }
    }

    return 0;
}