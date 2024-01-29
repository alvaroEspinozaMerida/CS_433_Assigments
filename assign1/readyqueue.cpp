#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code

#include "pcb.h"

/**
 * @brief Constructor for the ReadyQueue class.
 */
ReadyQueue::ReadyQueue(){
}

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {

}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    //TODO: add your code here
    // When adding a PCB to the queue, you must change its state to READY.
    pcbPtr->state = ProcState::READY;
    mQueue->insert(pcbPtr);
    mQueue->heapify();
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
    T removed = mQueue->removeMax();
    removed->state = ProcState::RUNNING;
    return  removed;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    //TODO: add your code here
    return mQueue->size();
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    cout<<mQueue->toString()<<endl;
}