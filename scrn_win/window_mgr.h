#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H

#include <vector>
#include "screen.h"

// ------------------class : window_mgr-----------------------

class window_mgr{
public:
    using screenIndex = std::vector<screen>::size_type;
    void clear(screenIndex);
    window_mgr()
        :   screens({screen(24,80,' ')})  {};

private:
    std::vector<screen> screens {screen(24,80,' ')};    
};

// void window_mgr::clear(screenIndex i){
//     screen &s = screens[i];
//     s.contents = std::string(s.height * s.width, ' ');
// }

#endif