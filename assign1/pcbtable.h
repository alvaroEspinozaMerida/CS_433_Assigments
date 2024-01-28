/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Lucas Birkenstock and Alvaro Espinoza
 * @brief This is the header file for the table class, an array(list) of all PCB elements in the system..
 * @version 0.1
 */
#pragma once

#include "pcb.h"
#include <vector>


/**
 * @brief PCTable is an array of all PCB's in the system
 * 
 */
class PCBTable {
private:
    vector <PCB*> table;


public:
    /**
     * @brief Construct a new table object of the given size (number of PCBs)
     *
     * @param size: the capacity of the table
     */
    PCBTable(int size = 100);

    /**
     * @brief Destroy the table object. Make sure to delete all the PCBs in the table.
     *
     */
    ~PCBTable();

    /**
     * @brief Get the PCB at index "idx" of the table.
     *
     * @param idx: the index of the PCB to get
     * @return PCB*: pointer to the PCB at index "idx"
     */
    PCB* getPCB(unsigned int idx);

    /**
     * @brief Overload of the operator [] that returns the PCB at idx
     *
     * @param idx
     * @return PCB*
     */
    PCB *operator[](unsigned int idx) {
        return getPCB(idx);
    }

    /**
     * @brief Add a PCB pointer to the table at index idx.
     *
     * @param pcb: the PCB pointer to add
     * @param idx: the index to add the PCB at
     */
    void addPCB(PCB *pcb, unsigned int idx);

    /**
     * @brief Add a new PCB to the table.
     * @param pid Id of the new PCB
     * @param priority Priority of the new PCB
     * @param idx The index of the new PCB in the table
     */
    void addNewPCB(unsigned int pid, unsigned int priority, unsigned int idx) {
        PCB *pcb = new PCB(pid, priority);
        addPCB(pcb, idx);
    }


    void displayTable();
};
