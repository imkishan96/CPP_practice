#include<iostream>
#include "screen.h"
//#include "window_mgr.h"

using namespace std;

int main(){
    screen myscreen(5,5,'-');
    cout << myscreen.get() << ::endl;
    myscreen.set(2,2,'X').display(cout);
    cout << "||||||" <<myscreen.get(1,1) <<endl;
    cout << myscreen.move(2,2).get() << endl;
    window_mgr w;
    window_mgr::screenIndex s_index;
    s_index = w.add_screen(myscreen);
    cout<< "jgfksygfklskuhkfysfiashfyhjfhjshf" << endl;
    w.get(s_index).display(cout);
    w.clear(s_index);
    w.get(s_index).display(cout);
    cout << endl;
}