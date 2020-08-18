#include<iostream>

using namespace std;

int main(){
    string blah1,blah2;
    cout << "Write two same strings with space in between" << endl;
    while(cin >> blah1 >> blah2)
    {
        try
        {
            if (blah1 !=blah2){
                throw runtime_error("give me the same name god damm it");
            }
            cout << blah1 + blah2 << endl << "now I am happy" << endl;
        }
        catch(runtime_error err)
        {
            std::cerr << err.what() << "\n Try Again? Enter y or n" << endl;
            char c;
            cin >> c;
            if ( !cin ||c == 'n')   {   break;  }
        }
    }
}