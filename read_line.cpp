#include <iostream>
#include <string>

using namespace std;

int main()
{
    string line;
    auto size_of_line = line.size();
    getline(cin, line);
    cout << line << endl;
    size_of_line = line.size();
    cout << size_of_line << endl;
    return 0;

}

