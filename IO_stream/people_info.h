#include<vector>
#include<string>
#include <cctype>

struct people_info
{
    std::string name;
    std::vector<std::string> phones;
};

bool valid(std::string& test_phone){
    if(test_phone.size()!=10){
        return false;        
    }
    
    for(auto c :test_phone){
        if (std::isdigit(c)==false) {return false;}
    }
    return true;
}