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

    //semaphore deletion and name deletion from file system
    sem_close(full);
    sem_unlink("/full");
    sem_close(empty);
    sem_unlink("/empty");


    delete[] buffer;
    pthread_mutex_destroy(&lock);


}

Buffer::Buffer(const Buffer& other) : size(other.size), buffer(new buffer_item[other.size]) {
    buffer = new buffer_item[size];

    count = other.count;
    in = other.in;
    out = other.out;

    full = sem_open("/full", O_CREAT, 0644, 0);
    empty = sem_open("/empty", O_CREAT, 0644, size);


    std::copy(other.buffer, other.buffer + other.size, buffer);

}


Buffer& Buffer::operator=(Buffer other) {

    std::swap(count, other.count);
    std::swap(in, other.in);
    std::swap(out, other.out);

    std::swap(full, other.full);
    std::swap(empty, other.empty);


    std::swap(size, other.size);
    std::swap(buffer, other.buffer);
    return *this;
}


bool Buffer::insert_item(buffer_item item) {
    //locking the mutex so no other threads have access to this shared
    //resource while this thread works on this shared resource
    pthread_mutex_lock(&lock);

    //CRITCAL AREA:
    //if the buffer is full meaning the count == size then we unlock this
    //thread so then maybe one of the other threads is able to remove a bufferitem
    if(count == size ){
        pthread_mutex_unlock(&lock);
        return false;
    }

    //buffer in element gets set to the inserted item
    buffer[in] = item;

    //in gets updated
    in = (in + 1) % size;

    count ++;

    pthread_mutex_unlock(&lock);
    //exiting of the

    return true;
}

bool Buffer::remove_item(buffer_item *item) {

    //locking the mutex so no other threads have access to this shared
    //resource while this thread works on this shared resource
    pthread_mutex_lock(&lock);

    //CRITCAL AREA:
    //if the buffer is empty meaning the count == s0 then we unlock this
    //thread so then maybe one of the other threads is able to add a bufferitem

    if(count == 0){
        pthread_mutex_unlock(&lock);
        return false;
    }

    //item gets set to removed item so it can be seen outside the function
    *item = buffer[out];

    //buffer out index gets set to 0
    buffer[out] = 0;

    //out position gets updated
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