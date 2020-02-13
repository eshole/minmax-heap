#include <iostream>
#include <cmath>
#include"minmax_heap.h"

using namespace std;

int main() {
    try {
        vector<int> v{13, 32, 45};
        vector<int> v1 = {4,79,59,32,12,11,23,63,54,42,20,31,19};
        minmax_heap<int> h(v);
        //h.Insert(54);
        h.deleteMin();
        h.print();
        cout << ();
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
