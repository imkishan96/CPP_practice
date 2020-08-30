#include <string>
#include <memory>

using namespace std;

class strVec
{
public:
    strVec(): elements(nullptr),first_free(nullptr), cap(nullptr){}
    strVec(const strVec&);
    strVec& operator= (const strVec&);
    ~strVec();
    void push_back(string&);
    size_t size() const {return first_free-elements;};
    size_t capacity() const {return cap-elements;};
    string* begin() const { return elements;};
    string* end() const {return first_free;};

private:
    allocator<string> alloc;
    void check_n_alloc() {if(first_free==cap) reallocate();}
    pair<string* ,string*> alloc_n_copy(const string*, const string*);
    void free();
    void reallocate();
    string *elements, * first_free, *cap;
};

strVec::~strVec(){ free();}

void strVec::push_back(string &s){
    check_n_alloc();
    alloc.construct(first_free++ ,s);
}

pair<string*, string*> 
strVec::alloc_n_copy(const string* b, const string* e){
    auto data = alloc.allocate(e-b);
    uninitialized_copy(b,e,data);
    return {data , uninitialized_copy(b,e,data)};
}

void strVec::free(){
    if(elements)
    {
        for (auto p = first_free; p != elements; )
            alloc.destroy(p++);        
        alloc.deallocate(elements, cap-elements);        
    }
}

strVec::strVec(const strVec& s){
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

strVec& strVec::operator=(const strVec& rhs){
    auto data = alloc_n_copy( rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void strVec::reallocate(){
    auto newcapacity = size() ? size() * 2 : 1 ;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;

    for( size_t i=0 ; i != size(); i++)
        alloc.construct(dest++ , std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}