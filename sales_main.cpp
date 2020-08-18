#include<iostream>
#include "sales_data.h"
#include <vector>

int main()
{
    sales_data data1, data2;
    std::vector<sales_data> vect_of_sales_data;
    decltype(vect_of_sales_data.size()) vect_index = 0;
    data1.bookNo = "1st book";
    data2.bookNo = "2nd book";
    vect_of_sales_data.push_back(data1);
    vect_of_sales_data.push_back(data2);
    std::cout << data1.bookNo << std::endl;
    std::cout << vect_of_sales_data[vect_index].bookNo<< std::endl;
    
    return 0;
}