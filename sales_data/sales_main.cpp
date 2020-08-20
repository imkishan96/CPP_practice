#include<iostream>
#include "sales_data_class.h"
#include <vector>

using namespace std;

int main()
{
    sales_data data1("001",1,1), data2("002",2,2) , data3;
    //sales_data data4("0001",1 , 1);
    //vector<sales_data> vect_of_sales_data;
    //decltype(vect_of_sales_data.size()) vect_index = 0;
    //vect_of_sales_data.push_back(data1);
    //vect_of_sales_data.push_back(data2);
    cout << data1.isbn() << endl;
    //cout << vect_of_sales_data[vect_index].isbn()<< endl;
    
    print(cout,data1);
    cout<< endl<< "this was book" << endl;
    cout << "enter book details : bookNO , unit sold, revenue" << endl;
    read(cin,data3);

    sales_data data4 = add(data1,data3);
    print(cout,data4);
    cout << endl;

    
    return 0;
}