#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

map<string,string> buildMap(ifstream &map_file){
    map<string,string> temp_map;
    string key,value;

    while (map_file >> key && getline(map_file , value))
    {
        if(value.size() > 1){
            temp_map[key] = value.substr(1);
            //cout << key << ":" << value << endl;
        }
        else{
            throw runtime_error(" no rule for key " + key);
        }
    }
    return temp_map;
}

const string& transform_str(const string &s ,const map<string, string> &m){
    auto map_it = m.find(s);
    if (map_it!= m.end()){
        return map_it ->second;
    }
    else
    {
        return s;
    }
}

int main(){
    ifstream input_text;
    map<string,string> rules;
    string temp_str;
    input_text.open("rules.txt");
    
    rules = buildMap(input_text);

    input_text.close();
    input_text.open("text_to_trans.txt");

    while (getline(input_text ,temp_str ))
    {   cout << temp_str << ": ";
        istringstream stream(temp_str);
        while (stream >> temp_str)
        {
            cout << transform_str(temp_str , rules) << " ";
        }
        cout << endl;
        
    }    
}