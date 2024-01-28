/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Lucas Birkenstock and Alvaro Espinoza
 * @brief This is the implementation file for the table class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new table object of the given size (number of PCBs)
 *
 * @param size: the capacity of the table
 */
PCBTable::PCBTable(int size) {

    for( int i = 0; i < size; i++){
        PCB* pcb = new PCB();
        table.push_back(pcb);
    }
}

/**
 * @brief Destroy the table object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // TODO: add your code here
   // Delete all the PCBs in the table

    std::destroy(table.begin(), table.end());

}

/**
 * @brief Get the PCB at index "idx" of the table.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    // TODO: add your code here
    return table.at(idx);
}

/**
 * @brief Add a PCB pointer to the table at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {

    table.insert(table.begin()+idx,pcb);
}

void PCBTable::displayTable() {

    for (const PCB* i : table) {
        i->display();
    }


}
