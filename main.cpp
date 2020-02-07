#include <iostream>
#include <cmath>
#include"minmax_heap.h"

using namespace std;

int main() {
    try {
        vector<int> v{13, 90, 44, 18, 3, 54, 29, 33, 41, 7, 92, 52, 10, 47};
        minmax_heap<int> h(v);
        //h.Insert(73);
        h.Insert(78);
        h.print();
        h.deleteMin();
        h.print();
    //    minmax_heap<int> h1;
    //    h1.Insert(15);
    //    h1.Insert(5);
    //    h1.Insert(13);
    //    h1.Insert(25);
    //    h1.print();
    } catch (const char* e) {
        cout << e << endl;
    }
    return 0;
}
