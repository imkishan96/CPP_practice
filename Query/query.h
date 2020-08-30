#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
using line_no = vector<string>::size_type ;

class QueryResult;
class TextQuery
{
public:
    using line_no = vector<string>::size_type ;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> file;
    map <string, shared_ptr<set<line_no>> > wm;

};

TextQuery::TextQuery(ifstream& is) :file(new vector<string>)
{
    string text;
    while (getline(is,text))
    {   
        file->push_back(text);
        auto n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word)
        {
            auto &lines = wm[word];
            if(!lines){ lines.reset(new set<line_no>);}
            lines->insert(n);
        }        
    }    
}

class QueryResult
{
friend ostream& print(ostream& , const QueryResult&);
public:
    QueryResult(string s, shared_ptr <set<line_no>> p , shared_ptr<vector<string>> f)
        : sought(s), lines(p), file(f) {};

    set<line_no>::iterator begin() const { return lines->begin();}
    set<line_no>::iterator end() const { return lines->end();}
    shared_ptr<vector<string>> get_file() { return file;}
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;

};

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    
    if(loc==wm.end())
        return QueryResult(sought,nodata,file);
    else
        return QueryResult(sought , loc->second ,file);

}

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occures" << qr.lines->size() << " time(s) " << endl;
    for(auto num: *qr.lines)
    {
        os << "\t(line " <<(num+1) <<")"<< *(qr.file->begin() + num) << endl;
    }
    return os;
}

class Query;
class Query_base
{
    friend class Query;
protected:
    using line_no = vector<string>::size_type ;
    ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0 ;
};

class Query
{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

public:
    Query(const string &s);
    QueryResult eval(const TextQuery &t) const { return q->eval(t);}
    string rep()const {return q->rep();}
    
private:
    Query(shared_ptr<Query_base> query) : q(query) { }
    shared_ptr<Query_base> q;
};

std::ostream & operator<<(ostream &os , const Query &q)
    {return os << q.rep();}

class WordQuery: public Query_base{
    friend class Query;
    WordQuery(const string &s): query_word(s) {}
    QueryResult eval(const TextQuery &tq) const { return tq.query(query_word);}
    string rep() const { return query_word;}
    string query_word;
};

Query::Query(const string &s) : q(new WordQuery(s)) {}

class NotQuery : public Query_base 
{
    friend class Query;
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) {}
    string rep() const { return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery &) const;
    Query query;
};

inline Query operator~(const Query &operand){
    return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery : public Query_base 
{
protected:
    BinaryQuery(const Query &l , const Query &r , string s)
        : lhs(l), rhs(r) , opSym(s) {}
    string rep() const 
    { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";}
    Query lhs , rhs;
    string opSym;
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &l , const Query &r);
    AndQuery(const Query &lhs, const Query &rhs)
        : BinaryQuery(lhs,rhs,"&") { }
    QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

class OrQuery : public BinaryQuery 
{   
    friend Query operator|(const Query& , const Query&);
    OrQuery(const Query &lhs , const Query &rhs)
        : BinaryQuery(lhs,rhs,"|") { }
    QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs , const Query &rhs){
    return shared_ptr<Query_base> (new OrQuery(lhs,rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const
{
    auto right = rhs.eval(text);
    auto left = lhs.eval(text);
    auto ret_lines =  make_shared<set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
    auto right = rhs.eval(text);
    auto left = lhs.eval(text);
    auto ret_lines =  make_shared<set<line_no>>();
    set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines , left.get_file());
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
    
}
