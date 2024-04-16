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
#include <iostream>
using namespace std;

Buffer::~Buffer() {}

bool Buffer::insert_item(buffer_item item) {
    unique_lock<mutex> lock(mtx);
    if (buffer.size() >= size) {
        not_full.wait(lock, [this]() {return buffer.size() < size; });
    }
    buffer.push_back(item);
    not_empty.notify_all();
    return true;
}

bool Buffer::remove_item(buffer_item *item) {
    unique_lock<mutex> lock(mtx);
    if (buffer.empty()) {
        not_empty.wait(lock, [this]() {return !buffer.empty();});
    }
    *item = buffer.front();
    buffer.erase(buffer.begin());
    not_full.notify_all();
    return true;
}

int Buffer::get_size() {
    return size;
}

int Buffer::get_count() {
    return buffer.size();
}

bool Buffer::is_empty() {
    return buffer.empty();
}

bool Buffer::is_full() {
    return buffer.size() == size;
}

void Buffer::print_buffer() {
    cout << "Buffer: [";
    for (size_t i = 0; i < buffer.size(); i++) {
        cout << buffer[i];
        if (i != buffer.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}