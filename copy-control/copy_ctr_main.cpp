#include "copy_ctr.h"

using namespace std;
int main(){
    Folder f1,f2;
    Message m1("Hello"), m2("World"), m3("Happy"), m4("NewYear");

    f1.save(m1); f1.save(m3);
    f2.save(m2); f2.save(m4);

    auto m5 = m3;
    f1.save(m5);
    Message m6("blah blah");
    m6.save(f2);
    f1.print();
    cout << "-----------------------" << endl;
    f2.print();
}