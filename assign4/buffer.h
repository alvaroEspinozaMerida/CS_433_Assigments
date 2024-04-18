/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Alvaro Espinoza Merida and Rutilo Maciel
 * @brief header file for the buffer class
 * @version 0.1
 */

#ifndef ASSIGN4_BUFFER_H
#define ASSIGN4_BUFFER_H

#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <fcntl.h>


// Define the data type of the buffer items
typedef int buffer_item;

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot exceed the size of the buffer.
 */
class Buffer {
private:

//    std::vector<buffer_item> buffer;

    buffer_item* buffer;

    int size, count, in, out ;

//a binary (or mutual-exclusion) semaphore that protects the actual insertion or removal of items in the buffer.

//The bounded-buffer problem uses three semaphores: empty and full, which count the number of empty and full slots in the buffer


public:
    /**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */

    //Purpose: The mutex lock ensures that only one process
    // (either a producer or a consumer) can access the buffer
    // at any one time. This is critical to prevent data corruption
    // or inconsistent state within the buffer.

    //Function: When a process (either producer or consumer) wants
    // to access the buffer, it must first acquire the mutex lock.
    // If the lock is already held by another process, the requesting
    // process must wait until the lock becomes available.
    // Once the process is done with the buffer, it releases
    // the mutex lock, allowing another process to access the buffer.
    pthread_mutex_t lock;


    //Purpose: This semaphore tracks the number of empty slots available
    // in the buffer. It helps manage how many items a producer can
    // add to the buffer before it becomes full.

    //Function: Initially, the "empty" semaphore is set to the total
    // capacity of the buffer (i.e., all slots are empty).
    // When a producer wants to add an item to the buffer,
    // it must wait on the "empty" semaphore (which is decremented).
    // If the semaphore's value is zero, the producer must wait because
    // the buffer is full. Each time an item is consumed (removed from the buffer),
    // the semaphore is incremented, signaling that an empty slot is available.
    sem_t *full;

    //Purpose: This semaphore indicates the number of items currently
    // in the buffer that are available for consumption. It prevents a
    // consumer from trying to retrieve an item from an empty buffer.

    //Function: Initially, the "full" semaphore is set to zero because
    // the buffer is empty. When a producer adds an item to the buffer,
    // it increments the "full" semaphore. A consumer must wait on this
    // semaphore before it can remove an item; if the semaphore's value is zero,
    // the consumer must wait because there are no items to consume. Each time
    // an item is consumed, the semaphore is decremented.
    sem_t *empty;


    Buffer(int size = 5) : size(size) {

        sem_unlink("/full");
        sem_unlink("/empty");


        pthread_mutex_init(&lock, NULL);  // Initialize mutex

        buffer = new buffer_item[size];

        count = 0;
        in = 0;
        out = 0;


        full = sem_open("/full", O_CREAT, 0644, 0);
        empty = sem_open("/empty", O_CREAT, 0644, size);

    };

    /**
     * @brief Destroy the Buffer object
     */
    ~Buffer();

    /**
     * @brief Insert an item into the buffer
     * @param item the item to insert
     * @return true if successful
     * @return false if not successful
     */
    bool insert_item(buffer_item item);

    /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
    bool remove_item(buffer_item *item);

    /**
     * @brief Get the size of the buffer
     * @return the size of the buffer
     */
    int get_size();

    /**
     * @brief Get the number of items in the buffer
     * @return the number of items in the buffer
     */
    int get_count();

    /**
     * @brief Chceck if the buffer is empty
     * @return true if the buffer is empty, else false
     */
    bool is_empty();
    /**
     * @brief Check if the buffer is full
     * @return true if the buffer is full, else false
     */
    bool is_full();

    /**
     * @brief Print the buffer
     */
    void print_buffer();
};
#endif //ASSIGN4_BUFFER_H
