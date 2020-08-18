#include<iostream>
#include<string>

using namespace std;

int main()
{
    string text = "0123456789";
    auto beg = text.begin();
    auto end = text.end();
    auto mid = text.begin() + (end-beg)/2;
    char find_me = '2';

    while(mid != end && *mid != find_me)
    {
        cout << *mid << endl;
        if(find_me < *mid){
            end = mid;
        }
        else
        {
            beg = mid +1;
        }
        mid = beg + (end-beg)/2;
        
    }
    cout << "----------final--------" << endl;
    cout << *mid <<endl;
    
}