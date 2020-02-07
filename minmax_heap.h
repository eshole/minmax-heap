#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class minmax_heap {
    vector<T> arr;
    int leftChild(int index) {return 2*index+1;}
    int rightChild(int index) {return 2*index+2;}
    int parent(int index) {return (index-1)/2;}
    int grandParent(int index) {return (index-3)/4;}
    void upHeap(int index);
    void downHeap(int index);
    void upHeapMin(int index);
    void upHeapMax(int index);
    void downHeapMin(int index);
    void downHeapMax(int index);
    int minOrMax(int index) { return (int)floor(log2(index+1))%2 == 1 ? 1 : 0; } // parni nivo je 0, neparni 1
    void makeHeap();
public:
    minmax_heap() {}
    minmax_heap(const vector<T>& a):arr(a) {makeHeap();}
    bool Empty() {return arr.size() == 0;}
    T getMin();
    T getMax();
    void deleteMin();
    void deleteMax();
    void Insert(const T& element);
    void print();
};

template <typename T>
void minmax_heap<T>::makeHeap() {
    for (int i=arr.size()/2; i>=0; i--) {
        downHeap(i);
    }
}

template <typename T>
T minmax_heap<T>::getMax() {
    if (Empty()) throw "The heap is empty!";
    if (arr.size() == 1) return arr[0];
    if (arr.size() == 2) return arr[1];
    return max(arr[1], arr[2]);
}

template <typename T>
T minmax_heap<T>::getMin() {
    if (Empty()) throw "The heap is empty!";
    return arr[0];
}

template <typename T>
void minmax_heap<T>::downHeap(int index) {
    if (minOrMax(index)) downHeapMax(index); // element je na neparnom nivou
    else downHeapMin(index); // element je na parnom nivou
}

template <typename T>
void minmax_heap<T>::downHeapMax(int index)  { // downHeap na neparnom nivou
    //cout << arr[index] << endl;
    if (leftChild(index) >= arr.size()) return; // nema djece
    if (rightChild(index) >= arr.size()) { // ima samo lijevo dijete
        if (arr[leftChild(index)] > arr[index]) {
            swap (arr[leftChild(index)], arr[index]);
            return; // to znaci da nema ni pra-potomaka
        }
    }
    int maximum;
    if (arr[leftChild(index)] < arr[rightChild(index)]) maximum = rightChild(index);
    else maximum = leftChild(index);
    for (int i=4*index+3; i<4*index+7; i++) { // trazimo indeks najveceg od potomaka
        if (i >= arr.size()) break;
        if (arr[i] > arr[maximum]) maximum = i;
    }
    if (arr[maximum] > arr[index]) { // ako postoji veci potomak
        if (index == grandParent(maximum)) { // ako je to pra-potomak
            swap(arr[maximum], arr[index]);
            if (arr[maximum] < arr[parent(maximum)]) // u slucaju da se poremeti poredak parnih nivoa
                swap(arr[maximum], arr[parent(maximum)]); // parni elementi imaju roditelje manje od njih
        downHeapMax(maximum);
        } else { // najveci potomak je njegovo dijete
            swap(arr[maximum], arr[index]);
        }
    }
}


template <typename T>
void minmax_heap<T>::downHeapMin(int index)  { // downHeap na parnom nivou
    //cout << arr[index] << endl;
    if (leftChild(index) >= arr.size()) return; // nema djece
    if (rightChild(index) >= arr.size()) { // ima samo lijevo dijete
        if (arr[leftChild(index)] < arr[index]) {
            swap (arr[leftChild(index)], arr[index]);
            return; // to znaci da nema ni pra-potomaka
        }
    }
    int minimum;
    if (arr[leftChild(index)] < arr[rightChild(index)]) minimum = leftChild(index);
    else minimum = rightChild(index);
    for (int i=4*index+3; i<4*index+7; i++) { // trazimo indeks najmanjeg od potomaka
        if (i >= arr.size()) break;
        if (arr[i] < arr[minimum]) minimum = i;
    }
    if (arr[minimum] < arr[index]) { // ako postoji manji potomak
        if (index == grandParent(minimum)) { // ako je to pra-potomak
            swap(arr[minimum], arr[index]);
            if (arr[minimum] > arr[parent(minimum)]) // u slucaju da se poremeti poredak neparnih nivoa
                swap(arr[minimum], arr[parent(minimum)]); // neparni elementi imaju roditelje vece od njih
        downHeapMin(minimum);
        } else { // najmanji potomak je njegovo dijete
            swap(arr[minimum], arr[index]);
        }
    }
}

template <typename T>
void minmax_heap<T>::upHeapMin(int index) {
    if (index == 0) return;
    if (arr[index] < arr[grandParent(index)]) {
        swap (arr[index], arr[grandParent(index)]);
        upHeapMin(grandParent(index));
    }
}

template <typename T>
void minmax_heap<T>::upHeapMax(int index) {
    if (index == 1 || index == 2) return;
    if (arr[index] > arr[grandParent(index)]) {
        swap (arr[index], arr[grandParent(index)]);
        upHeapMax(grandParent(index));
    }
}


template <typename T>
void minmax_heap<T>::Insert(const T& element) {
    if (arr.size() == 0) {
        arr.push_back(element);
        return;
    }
    arr.push_back(element);
    if (minOrMax(arr.size()-1)) { // ako je element umetnut na neparni nivo
        if (arr[arr.size()-1] < arr[parent(arr.size()-1)]) { // svi elementi ovog nivoa su veci od svojih roditelja
            swap(arr[arr.size()-1], arr[parent(arr.size()-1)]);
            upHeapMin(parent(arr.size()-1));
        } else
            upHeapMax(arr.size()-1);
    } else { // ako je element umetnut na parni nivo
        if (arr[arr.size()-1] > arr[parent(arr.size()-1)]) { // svi elementi ovog nivoa su manji od svojih roditelja
            swap(arr[arr.size()-1], arr[parent(arr.size()-1)]);
            upHeapMax(parent(arr.size()-1));
        } else // dobar poredak
            upHeapMin(arr.size()-1);
    }
}

template <typename T>
void minmax_heap<T>::deleteMin() {
    if (arr.size() == 0) throw "The heap is empty!";
    if (arr.size() == 1) {
        arr.pop_back();
        return;
    }
    swap(arr[0], arr[arr.size()-1]);
    arr.pop_back();
    downHeapMin(0);
}

template <typename T>
void minmax_heap<T>::deleteMax() {
    if (arr.size() == 0) throw "The heap is empty!";
    if (arr.size() == 1 || arr.size() == 2) {
        arr.pop_back();
        return;
    }
    int maxIndex;
    if (arr[1] > arr[2]) maxIndex = 1;
    else maxIndex = 2;
    swap(arr[maxIndex], arr[arr.size()-1]);
    arr.pop_back();
    downHeapMax(maxIndex);
}


template <typename T>
void minmax_heap<T>::print() {
    for (int i=0; i<arr.size(); i++) cout << arr[i] << " ";
    cout << endl;
}

#endif // MINMAXHEAP_H

