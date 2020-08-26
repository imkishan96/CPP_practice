#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

// void filter_strings(string& input_string){
//     string::iterator found = input_string.begin();
//     while (found != input_string.end())
//     {
//         found = remove(input_string.begin(),input_string.end(),".");
//     }
// } 


void elimDups(vector<string> &vec){
    sort(vec.begin(),vec.end());
    auto end_unique = unique(vec.begin(),vec.end());
    vec.erase(end_unique, vec.end());

}

bool isShorter(const string &s1, const string &s2){
    return s1.size()< s2.size();
}

void biggies( vector<string> &vec , size_t sz){

    elimDups(vec);  // short alphabatially and removes duplicates
    
    stable_sort(vec.begin(), vec.end(),
        [](const string &a, const string &b){return a.size() < b.size();});
    
    auto wc = find_if(vec.begin(),vec.end(),
        [sz](const string &check){ return check.size() >= sz;} );

    auto count = vec.end() - wc;
    cout << count << " No of elliments are bigger than: " << sz << endl;

    for_each ( wc , vec.end() , 
        [](const string &print_word){ cout << print_word << " "; } );

    cout << endl;
}

int main(){
    fstream input_story;
    string word;
    vector<string> story;

    input_story.open("story.txt");

    while (input_story >> word)
    {   
        word.erase(remove(word.begin(),word.end(),'.') , word.end());
        story.push_back(word);
    }

    cout <<"-----------end of while-----------" << endl;

    biggies(story,5);

    for(auto it : story)
    {
        cout << it << ' ';
    }

}