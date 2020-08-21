#ifndef SCREEN_H
#define SCREEN_H

#include<string>
#include<vector>

class screen;

// ------------------class : window_mgr-----------------------
class window_mgr{
public:
    using screenIndex = std::vector<screen>::size_type;
    void clear(screenIndex);
    window_mgr();
    screenIndex add_screen(const screen& new_screen);
    screen& get(const screenIndex);
private:
    std::vector<screen> screens; //{screen(24,80,' ')};    
};

// ------------------class : screen--------------------------------------

class screen{
    friend void window_mgr::clear(screenIndex);

public:
    typedef std::string::size_type pos;
    screen() = default;
    screen(pos ht,pos wd,char c)
        :   height(ht), width(wd),contents(ht*wd, c) { }
    screen(pos ht,pos wd)
        :   height(ht), width(wd),contents(ht*wd,' '){ }
    
    char get() const ;
    char get(pos ht, pos wd) const;

    screen &set(char ch) ;
    screen &set(pos row, pos col, char ch) ;

    screen &move(pos r, pos c);
    void some_member() const;


    screen &display(std::ostream &os);
    const screen &display(std::ostream &os) const;

private:
    pos cursor = 0, height = 0, width = 0;
    std::string contents;
    mutable size_t access_ctr;
    void do_display(std::ostream &os) const;
};

//---------------------- definitions----------------------------------

inline 
char screen::get() const {
    return contents[cursor];
}

inline 
char screen::get(pos r, pos c) const{
    pos row = r * width;
    return contents[row + c];
}

inline 
screen &screen::move(pos r, pos c){
    pos row = r * width;
    cursor = row + c;
    return *this;
}

inline 
void screen::some_member() const{
    ++access_ctr;
}

inline 
screen &screen::set(char ch) {
    contents[cursor] = ch;
    return *this;
}

inline 
screen &screen::set(pos r, pos c,char ch) {
    contents[r * width + c] = ch;
    return *this;
}

inline 
screen &screen::display(std::ostream &os){
    do_display(os);
    return *this;
}

inline 
const screen &screen::display(std::ostream &os) const{
    do_display(os);
    return *this;
}

inline 
void screen::do_display(std::ostream &os) const{
    os << contents;
}

window_mgr::window_mgr(): screens{screen(24,80)} {}

void window_mgr::clear(screenIndex i){
    screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

window_mgr::screenIndex 
window_mgr::add_screen(const screen& new_screen){
    screens.push_back(new_screen);
    return screens.size() -1;
}

screen& window_mgr::get(const screenIndex s_index){
    return screens[s_index];
}

#endif