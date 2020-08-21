
#include"screen.h"
#include <string>

void window_mgr::clear(screenIndex i){
    screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}