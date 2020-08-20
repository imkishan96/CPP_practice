#include <iostream>
#include "sales_data.h"

double sales_data::avg_price() const
{
    // if unit sold is not zero return avg price or else return 0
    return (unit_sold) ? (revenue/unit_sold) : 0;    
} 

std::istream& read(std::istream& is, sales_data& item){
    double price = 0;
    is>> item.bookNo >> item.unit_sold >> price;
    item.revenue = item.unit_sold * price;
    return is;
}

std::ostream& print(std::ostream& os, const sales_data& item){
    os << item.isbn() << " " << item.unit_sold << " " 
    << item.revenue << " " <<item.avg_price() << std::endl;
}   

sales_data add(const sales_data& lhs, const sales_data& rhs){
    sales_data temp = lhs;
    temp.combine(rhs);
    return temp;
}
sales_data& sales_data::combine(const sales_data& item){
    
    this->unit_sold += item.unit_sold;
    this->revenue += item.revenue;
    return *this;
}