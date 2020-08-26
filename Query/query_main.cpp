#include "query.h"

int main(){
    ifstream infile;
    infile.open("text.txt");
    TextQuery tq(infile);

    while (true)
    {
        cout << "Enter the word you are looking for, or q to quit;" << endl;
        string s;
        if(!(cin >> s) || s == "q") break;
        print(cout,tq.query(s)) << endl;
    }
    
}