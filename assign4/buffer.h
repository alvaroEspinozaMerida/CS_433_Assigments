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

    //Mutex is in charge of making sure that only one thread is accessing the shared
    //buffer resource at a time ; whenever a thread is accesing the critical area
    // irregardless of removal or insertion ; whenever one of these
    //actions is taking place the buffer should not be accessed by any other process
    //so the mutex locks at the start of the insertion/deletion and unlocks at the end

    pthread_mutex_t lock;


    //SEMAPHORES: Purpose is to make sure the threads have items to cosume
    // and enough room to produce new items
    //


    //Full semaphore keeps track of how many bufferitems are in the buffer
    // have been produced inital value is whenever a new bufferitem
    // gets created by a producer thread; the semaphore
    //post that this new item has been created by iterating the semaphore by one
    // the consumer also use this semaphore to make sure that their are items to
    // to consume ; this semaphore prevents the cosumer from consuming items if the
    // the semaphore is at 0
    sem_t *full;

    //Empty semaphore keeps track of how many empty slots their are in the buffer
    //the initial value is the size passed into the constructor of the buffer;
    //whenever a new item gets added to the buffer the semaphore gets decremented by 1
    //however if the semaphore is already at 0 then the producer must wait for the semaphore to go back to 1
    //whenever a consumer consumes a buffer item
    // the semaphore post that a new slot is available by increment up by 1

    sem_t *empty;

    /**
     * Buffer(int)- contstucts the buffer object
     * cleans up any previous uses of the named semaphores by unlinking
     * intializes the mutex so it can be used by the buffer
     * sets variables for in, out, count that makes sure placement of items is crrect at start
     * count is how many items are currently in the buffer
     *
     * semaphores get created full is 0 for how many items are in the buffer
     * empty is set to size to represent how many empty slots are in the buffer
     * */
    Buffer(int size = 5) : size(size) {
        //semaphore clean up from previous run just in case destrcuotor does not work
        //function is used specifically for named semaphores.
        // removes a named semaphore from the system, effectively deleting its name so that it can no longer be opened.
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

    Buffer& operator=(Buffer other);

    Buffer(const Buffer& other);


};
#endif //ASSIGN4_BUFFER_H
