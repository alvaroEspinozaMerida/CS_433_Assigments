/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Alvaro Espinoza Merida and Rutilo Maciel
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <thread>

using namespace std;

// global buffer object
Buffer *buffer = new Buffer();
// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.

    buffer_item item = *((int *) param);


    while (true) {

        /* sleep for a random period of time */
        usleep(rand()%1000000);

        // TODO: Add synchronization code here
//        Decrements wait semaphore by one ; has to wait if no empty slots exist

        sem_wait(buffer->empty);

        if (buffer->insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer->print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }

        sem_post(buffer->full);

    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {

   while (true) {
        /* sleep for a random period of time */
       usleep(rand() % 1000000);

//     decrements full by 1 if there are values inside of full semaphore ; waits if not

       buffer_item item;
        // TODO: Add synchronization code here

       sem_wait(buffer->full);

        if (buffer->remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer->print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }

//        Increament empty by 1

       sem_post(buffer->empty);

    }
}

int main(int argc, char *argv[]) {


    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <sleep time> <# of producers> <# of consumers" << endl;
    }


    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);



    vector<pthread_t> producer_threads(num_producers);
    vector<pthread_t> consumer_threads(num_consumers);
    std::vector<int> producerIds(num_producers);
    std::vector<int> consumerIds(num_consumers);

    srand(time(NULL));

    for (int i = 0; i < num_producers; i++) {
        producerIds[i] = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, (void*)&producerIds[i]);
    }
    for (int i = 0; i < num_consumers; i++) {
        consumerIds[i] = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer,(void*)&consumerIds[i]);

    }


    sleep(sleep_time);
    for (int i = 0; i < num_producers; i++) {
        pthread_detach(producer_threads[i]);
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_detach(consumer_threads[i]);
    }

    delete buffer;



}
