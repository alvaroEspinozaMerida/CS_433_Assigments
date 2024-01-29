// CS311 heap.h
// INSTRUCTION:
// Heap class - header file template
// You should always comments to each function to describe its PURPOSE and PARAMETERS

#pragma once
#include "pcb.h"
#include <iostream>
using namespace std;

// =======================================================
// Your name: Alvaro Espinoza Merida
// Compiler:  g++
// File type: headher file heap.h
// @brief This file defines a Heap class
//=======================================================

typedef PCB* T;  // the el_t type is int for now

// Print an array of integers
void printArray(T values[], int length);

/**
 * @brief Runs a heap sort by creating a heap out of the values in the array, and then
 * extracting those values one-by-one from the heap back into the array in the proper order.
 *
 */
void heapSort(T values[], int length);

/**
 * @brief Implements a Heap class
 *
 */
class Heap
{
private:
    T *heaparray; // pointer to the array holding the heap
    int capacity;   // the capacity of the heap
    int count;      // how many elements are in the heap
public:
    /**
     * @brief Default constructor: creates an empty heap
     * @param capacity the initial capacity of the heap
     */
    Heap(int capacity = 100);

    /**
     * @brief Destroy the Heap object
     */
    ~Heap();

    /**
     * @brief constructor to build a heap from an array of values
     * @param values array of values to be added to the heap
     * @param length the size of the array
     */
    Heap(T *values, int length);

    /**
     * @brief Copy constructor
     * @param other the heap to be copied
     */
    Heap(const Heap &other);

    /**
     * @brief Assignment operator
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    Heap &operator=(const Heap &other);

    /**
     * @brief reorginzes the heap to maintain the heap property,
     *        by using the percolateDown and/or percolateUp functions.
     *
     */
    void heapify();

    // key functions to implement a priority queue.
    /**
     * @brief removes the maximum element from the heap, maintaining the heap property.
     * @return int the maximum element. return -1 if heap is empty
     */
    T removeMax();

    /*
     * @brief converts the heap into a string
     */
    string toString();

    // @brief Prints the heap
    void printHeap();

    /**
     * @brief Number of elements in the heap
     */
    int size() { return count; }

    /**
     * @brief Inserts a new element into the heap
     *
     * @param h
     * @param value
     * @return int
     */
    /**
     * @brief Inserts a new element into the heap. It maintains the heap property.
     * @param value the value to be inserted
     */
    void insert(T value);

    /**
     * @brief Change the key of the element at position i to the new value.
     *        It should percolate up or down to maintain the heap property after the change.
     * @param i the position of the element to be decreased
     * @param value the new value
     */
    void changeKey(int i, T new_val);

    // Helper functions.
    /**
     * @brief Returns the left child of the node at index
     */
    int leftChild(int index)
    {
        return 2 * index + 1;
    }
    /**
     * @brief Returns the right child of the node at index
     */
    int rightChild(int index)
    {
        return 2 * index + 2;
    };

    /**
     * @brief Returns the index of the parent of the child located at index
     */
    int parent(int index)
    {
        if (index <= 0 || index >= count)
            return -1;
        return (index - 1) / 2;
    }

    /**
     * @brief Percolates down the node at index to maintain the heap property
     *
     * @param index
     */
    // void percolateDown(Heap *h, int index);
    void percolateDown(int index);

    // void percolateDownBinary(Heap* h, int index);
    /**
     * @brief Percolates up the node at index to maintain the heap property
     *
     * @param index
     */
    // void percolateUp(Heap *h, int index);
    void percolateUp(int index);

    /**
     * @brief swaps the values of the two nodes at index1 and index2
     *
     * @param index1
     * @param index2
     */
    void swap(int index1, int index2);

    /**
     * @brief returns the max value in the heap
     *
     * @return int return -1 if the heap is empty, otherwise return the max value in the heap
     */
    T getMax() const;
};