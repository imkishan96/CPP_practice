#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include <map>

using namespace std;

int main(){
    fstream input_story;
    string word;
    map<string,size_t> word_count;

    input_story.open("story.txt");

    while (input_story >> word)
    {   
        ++word_count[word];
    }

    cout <<"-----------end of while-----------" << endl;

    for(auto it : word_count)
    {
        cout << it.first << " occured: " << it.second << endl;
    }
}