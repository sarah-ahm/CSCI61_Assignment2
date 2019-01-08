#ifndef MINPQ_H
#define MINPQ_H
using namespace std;

#include "random.h"

//Priority Queue template that orders elements based on user-defined compare function
template <class T>
class minPQ{ 
public:
    minPQ(){N = 0; pq[0] = nullptr;} 
    //Inserts element and restores heap 
    void insert(T v);
    //Removes smallest element
    void deleteMin(); 
    //Checks if PQ is empty
    bool isEmpty(); 
    //Returns smallest element
    T getMin(); 
    //Returns number of elements in pq. NOT the array size.
    int size(); 

    //heap operations 
    void swap(int i, int j);
    void swim(int k);
    void sink(int k);

    virtual bool compare(T* x, T* y) { return 0; }

    int N; //current number of elements 
    T* pq[20]; //heap
};


template <class T>
void minPQ<T>::swap(int i, int j){
    T* temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;  
}

template <class T>
void minPQ<T>::swim(int k){
    compare(pq[k/2], pq[k]);
    while (k > 1 && compare(pq[k/2], pq[k])){
        swap(k/2, k);
        k = k/2; 
    }
}

template <class T>
void minPQ<T>::sink(int k){
    while (2*k <= N){
        int j = 2*k;
        if (j < N && compare(pq[j], pq[j+1])){ 
            j++;
        }
        if (!compare(pq[k], pq[j])){ 
            break;
        }
        swap(k, j); 
        k = j;
    } 
}

template <class T>
void minPQ<T>::insert(T v){
    pq[++N] = &v;
    swim(N);    
}

template <class T>
void minPQ<T>::deleteMin(){
    if(!isEmpty()){
        
        swap(1, N);
        pq[N] = NULL;
        N--;
        sink(1);
       
    }
    else if (isEmpty()){
        cout << "Error. Priority Queue is empty." << endl;
        exit(1);
    }
}

template <class T>
bool minPQ<T>::isEmpty(){
    if (N == 0){
        return true;
    }else{
        return false;
    }
} 

template <class T>
T minPQ<T>::getMin(){
    return *pq[1];
} 

template <class T>
int minPQ<T>::size(){
    return N; 
} 

#endif //minPQ