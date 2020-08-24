#include <fstream>
#include <iostream>
#include <sstream>
#include "people_info.h"

using namespace std;

int main(int argc, char* argv[]){

    //get the file name from argv and open it.

    if (argc < 2){      //confirm file name were passed in the argument    

        std::cerr << "No file name given: try again" << endl;
        return 0;
    }
        
    fstream input_file(argv[1],fstream::in) , output_file;

    if(! input_file){   // confirm given file is accessible
        cerr << "Cannot access file named:" << argv[1] << " try again" << endl;
        return 0;
    }    

    //read the individual lines and seperate the names and phone numbers
    vector<people_info> people;
    string line,phone;

    while (getline(input_file,line))    { // read all the lines from the file
        people_info temp_info;
        istringstream record(line);
        record >> temp_info.name;

        while (record >> phone)        {    // get all the numbers from line
            temp_info.phones.push_back(phone);
        }
        people.push_back(temp_info);        
    }
    

    //confirm phone numbers are valid and store them into a vector
    output_file.open("formatted_phone.txt",ofstream::out);
    output_file.clear();
    for (auto &entry : people)
    {   ostringstream badNums,formated;

        for(auto test_phone_numbers : entry.phones){
            if (!valid(test_phone_numbers)){
                badNums << " " << test_phone_numbers;
            }
            else{
                formated << test_phone_numbers <<","; 
            }   
        }
        if (badNums.str().empty()){
            output_file << entry.name << ": " << formated.str() <<endl;
        }
        else{
            cerr << "Input Error:" <<entry.name << " Invalid Num(s): " << badNums.str() << endl;
        }
    }
    output_file.close();
    

    // write formated data into a file



}