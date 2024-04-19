/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Alvaro Espinoza Merida and Rutilo Maciel
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <semaphore.h>
#include <pthread.h>
#include <iostream>
using namespace std;

Buffer::~Buffer() {

    sem_close(full);
    sem_unlink("/full");
    sem_close(empty);
    sem_unlink("/empty");


    delete[] buffer;                 // Free the allocated buffer
    pthread_mutex_destroy(&lock);


}

bool Buffer::insert_item(buffer_item item) {

    pthread_mutex_lock(&lock);

    if(count == size ){
        pthread_mutex_unlock(&lock);
        return false;
    }

    buffer[in] = item;

    in = (in + 1) % size;

    count ++;

    pthread_mutex_unlock(&lock);

    return true;
}

bool Buffer::remove_item(buffer_item *item) {

    pthread_mutex_lock(&lock);

    if(count == 0){
        pthread_mutex_unlock(&lock);
        return false;
    }


    *item = buffer[out];

    buffer[out] = 0;


    out = (out + 1) % size;
    count --;

    pthread_mutex_unlock(&lock);

    return true;
}

int Buffer::get_size() {
    return size;
}

int Buffer::get_count() {
    return count;
}

bool Buffer::is_empty() {
    return count == 0 ;
}

bool Buffer::is_full() {
    return count == size;
}

void Buffer::print_buffer() {
    cout << "Buffer: [";
    int nonZeroCount = 0;

    for (size_t i = 0; i < size; ++i) {

        if (buffer[i] != 0 ){

            if (nonZeroCount > 0) {
                cout << ", ";
            }
            cout << buffer[i];
            nonZeroCount++;
        }

    }
    cout << "]" << endl;


}