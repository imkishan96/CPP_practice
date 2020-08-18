#include<iostream>
#include<string>

int main()
{
    std::string s("blah blah");
    if( s.begin()!=s.end() )
    {
        auto it = s.begin();
        while(it != s.end())
        {
            *it = toupper(*it);
            ++it;
        }

    }
    std::cout << s << std::endl;
}