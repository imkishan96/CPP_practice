#include "Blob.h"
#include<vector>

template <typename T> using myvec = std::vector<T>;

int main(){
    Blob<std::string> blah{"a", "aa", "aaa"};
    blah.push_back("aaaa");
    myvec<std::string> blah2 = {"a", "aa", "aaa"};
    for(auto it = 0 ; it < blah.size() ; it++)
    {
        std::cout << blah[it] << "       " << std::endl;
    }
    
    
}