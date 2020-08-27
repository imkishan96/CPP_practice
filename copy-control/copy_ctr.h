#include <string>
#include <set>
#include <iostream>
using namespace std;

class Message;
class Folder;
void swap(Message& , Message&);
void swap(Folder& , Folder&);

//--------------------------------- Folder-----------------------
class Folder
{
    friend class Message;
public:
    Folder() = default;
    Folder(const Folder&);
    Folder &operator=(const Folder&);
    void save(Message&);
    void remove(Message&);
    ~Folder();
    void print();

private:
    set<Message*> msgs_set;
    void addMsg(Message* m);
    void remMsg(Message* m);
};

//-----------------------------------------Message--------------
class Message
{
    friend class Folder;
public:
    explicit Message(const string &str =" ")
        : contents(str), folders_set() {}      //initializer
    Message(const Message&);    // copy constructor
    Message& operator=(const Message&); // copy assignment
    ~Message();                 //destructor
    void save(Folder&);
    void remove(Folder&);

private:
    string contents;
    set<Folder*> folders_set;
    void add_to_folders(const Message &);
    void remove_from_folders();
};//_____________________________________________________________

Message::Message(const Message& m)
    :contents(m.contents), folders_set(m.folders_set){
    add_to_folders(m);
}

void Message::save(Folder& f){
    folders_set.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder& f){
    folders_set.erase(&f);
    f.remMsg(this);
}

void Message::add_to_folders(const Message &m){
    for(auto it : m.folders_set)
        it->addMsg(this);
}

void Message::remove_from_folders(){
    for( auto it: folders_set)
        it->remMsg(this);
    folders_set.clear();
}

Message::~Message(){
    remove_from_folders();
}

Message& Message::operator=(const Message &rhs){
    string temp_con = rhs.contents;
    set<Folder*> temp_fol = rhs.folders_set;
    remove_from_folders();
    contents = temp_con;
    folders_set = temp_fol;
    add_to_folders(*this);
    return *this;
}

//___________________________________________
Folder::Folder(const Folder& f) : msgs_set(f.msgs_set){
    for(auto it : msgs_set)
        it->folders_set.insert(this);
}

Folder& Folder::operator=(const Folder& rhs){
    set<Message*> temp_set = rhs.msgs_set;
    for(auto it : msgs_set)
        it->folders_set.erase(this);
    msgs_set.clear();
    msgs_set = temp_set;
    for(auto it: msgs_set)
        it->folders_set.insert(this);
    
    return *this;
}

void Folder::addMsg(Message* m){
    msgs_set.insert(m);
}

void Folder::remMsg(Message* m){
    msgs_set.erase(m);
}
void Folder::save(Message &m){
    msgs_set.insert(&m);
    m.folders_set.insert(this);
}

void Folder::remove(Message &m){
    msgs_set.erase(&m);
    m.folders_set.erase(this);
}

void Folder::print(){
    cout << "Folder" << this << " containes " << msgs_set.size() 
    << " messages: \n";
    for(auto it : msgs_set)
        cout << it->contents << endl;   
}

Folder::~Folder(){
    for(auto it : msgs_set)
    it->folders_set.erase(this);
    msgs_set.clear();
}