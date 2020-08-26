#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Blob_str
{
public:
    typedef vector<string>::size_type size_t;
    
    Blob_str();
    Blob_str(initializer_list<string> il);
    size_t size() const {return data->size();}
    bool empty() const { return data->empty();}
    void push_back(const string &t) { data->push_back(t);}
    void pop_back();
    string& front();
    string& back();

    ~Blob_str();
private:
    shared_ptr<vector<string>> data;
    void check(size_t i , const string &msg) const;
};

Blob_str::Blob_str()
    :data(make_shared <vector <string> >()) {}

Blob_str::Blob_str(initializer_list<string> il)
    :data(make_shared <vector <string> > (il)) {}

void Blob_str::check(size_t i, const string &msg) const{
    if(i >= data->size()){
        throw out_of_range(msg);
    }
}

void Blob_str::pop_back(){
    check(0, "popback on empty Blob_str");
    data->pop_back();
}

string& Blob_str::front(){
    check(0, "front() on empty Blob_str");
    return data->front();
}

string& Blob_str::back(){
    check(0,"back() on empty Blob_str");
    return data->back();
}