#include "heap.h"

// @brief gets the maximum value in the heap
// @return the highest value integer in the heap
T Heap::getMax() const {
    return heaparray[0];
}



// @brief default constructor. Construct an empty heap with initial capacity
Heap::Heap(int capacity) {
    this->capacity = capacity;
    this->count = 0;
    heaparray = new T[capacity];
}

// @brief destructor
Heap::~Heap() {
    delete[] heaparray;
}

/**
 * @brief constructor to build a heap from an array of values
 * @param values array of values to be added to the heap
 * @param length the size of the array
 */
Heap::Heap(T *values, int length) {
    capacity = 100;
    count = 0;
    heaparray = new T[capacity];

    for(int i = 0; i < length; i ++){
        insert(values[i]);
    }


}

/**
* @brief Copy constructor
* @param other the heap to be copied
*/
Heap::Heap(const Heap &other) {
    delete heaparray;
    capacity = other.capacity;
    heaparray = new T[count];
    count = 0;
    for(int i = 0; i < other.count ; i++){
//        heaparray[i] = other.heaparray[count];
        insert(other.heaparray[i]);
    }
}

/**
* @brief Assignment operator
* @param other the heap to be copied
* @return Heap& a reference to the heap
*/
Heap & Heap::operator=(const Heap &other) {

    if (this == &other)
        return *this;

    delete heaparray;
    capacity = other.capacity;
    heaparray = new T[count];
    count = other.count;
    for(int i = 0; i < other.count ; i++){
//        heaparray[i] = other.heaparray[count];
        heaparray[i] = other.heaparray[i];
    }

    return *this;
}


/**
 * @brief   organizes the values in the heap to satisfy heap property.
 */
void Heap::heapify() {

    for(int i = count/2 - 1; i >= 0; i--){
        percolateDown(i);
    }

}

/**
 * @brief  Runs percolate down on the heap for the node stored in index.
 */
void Heap::percolateDown(int index) {


    int childIndex = 2*index + 1;
    int value = heaparray[index]->priority;

    if(childIndex < count){
        int i = 0;
        int max  = value;
        int maxIndex = -1;

        while(i < 2 && i + childIndex < count){
            if(heaparray[i+childIndex]->getPriority() > max){
                max = heaparray[i+childIndex]->priority;
                maxIndex = i + childIndex;
            }
            i++;
        }
        if(max == value){
            return;
        }
        else{
            swap(index,maxIndex);
            percolateDown(maxIndex);
        }

    }


}

/**
 * @brief  Runs percolate up on the heap for the node stored in index.
 */
void Heap::percolateUp(int index) {

    if(index > 0){
        int parentIndex = (index-1)/2;
        if (heaparray[index]->priority <= heaparray[parentIndex]->priority){
            return;
        } else{
            swap(index,parentIndex);
            percolateUp(parentIndex);
        }
    }


}

/**
 * @brief  inserts a value into the heap
 *
 */
void Heap::insert(T value) {

    if(count == capacity){
        capacity = capacity * 2;
        T *newArray = new T [capacity];


        for (int i = 0; i < count; i++) {
            newArray[i] = heaparray[i];
        }

        delete heaparray;
        heaparray = newArray;

    }
    heaparray[count] = value;
    count++;
    percolateUp(count-1);
}

/**
 * @brief  Removes the max value from the heap
 * @return the value that was removed
 */
T Heap::removeMax() {

    T max = heaparray[0];
    T replace = heaparray[count-1];
    count -= 1;

    if(count > 0 ){
        heaparray[0] = replace;
        percolateDown(0);
    }
    return  max;

}

//@brief converts the heap into a string
string Heap::toString()
{
    string s = "";
    for (int i = 0; i < count; i++)
    {
        s += heaparray[i]->string_display() + "\n";
    }
    return s;
}

/**
 * @brief  Prints the values in the heap
 */
void Heap::printHeap() {
    cout << toString() << endl;
}

/**
 * @brief  Prints the values in an array
 */
void printArray(T values[], int length) {
    int i;
    cout << "[ ";
    for (i = 0; i < length; i++) {
        cout << values[i]->priority << " ";
    }
    cout << "]\n";
}

/**
 * @brief  Swaps the values in the heap at index1 and index2
 */
void Heap::swap(int index1, int index2) {
    T temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}

/**
 * @brief  Sorts the values of an array by using the heap
 */
void heapSort(T values[], int length) {
    cout << "Array Before Sorting: \n";
    printArray(values, length);
    Heap *tempHeap = new Heap(values,length);


    int count = length-1;
    while(count >= 0){
        values[count] = tempHeap->removeMax();
        count --;
    }


    cout << "Array After Sorting: \n";
    printArray(values, length);

    delete tempHeap;

    return;
}

/**
     * @brief Change the key of the element at position i to the new value.
     *        It maintains the heap property.
     * @param i the position of the element to be decreased
     * @param value the new value
     */
void Heap::changeKey(int i, T new_val) {
    heaparray[i] = new_val;
    heapify();
}