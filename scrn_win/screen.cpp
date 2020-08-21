#include"screen.h"

char screen::get() const {
    return contents[cursor];
}

char screen::get(pos r, pos c) const{
    pos row = r * width;
    return contents[row + c];
}

screen &screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

void screen::some_member() const{
    ++access_ctr;
}

screen &screen::set(pos r, pos c,char ch) {
    contents[r * width + c] = ch;
    return *this;
}

screen &screen::display(std::ostream &os){
    do_display(os);
    return *this;
}

const screen &screen::display(std::ostream &os) const{
    do_display(os);
    return *this;
}

void screen::do_display(std::ostream &os) const{
    os << contents;
}

void window_mgr::clear(screenIndex i){
    screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}