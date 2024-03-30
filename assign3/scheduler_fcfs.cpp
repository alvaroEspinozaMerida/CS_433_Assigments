/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here


SchedulerFCFS::SchedulerFCFS(){
    this->wTime = 0;
    this->tTime = 0;
}

SchedulerFCFS::~SchedulerFCFS(){
}



void SchedulerFCFS:: init(std::vector<PCB>& process_list){
    this->process_list = process_list;
}


void SchedulerFCFS::simulate() {
    unsigned int  waitTime = 0;

    for(PCB& pcb : this->process_list){
        cout<<"Running Process "<< pcb.name <<" for "<<pcb.burst_time<<" time units | wait time:"<<waitTime<<endl;
        pcb.arrival_time = waitTime;
        waitTime += pcb.burst_time;
        pcb.burst_time = waitTime;

    }
}


void SchedulerFCFS::print_results() {
    for(PCB pcb : this->process_list){

        this->tTime+= pcb.burst_time;
        this->wTime += pcb.arrival_time;

        cout<<pcb.name <<"  turn-around time = "<< pcb.burst_time<< " waiting time "<< pcb.arrival_time <<endl;
    }

    cout<<"Average turn-around time = "<< this->tTime / this->process_list.size() << ", Average waiting time = "<< this->wTime / this->process_list.size() <<endl;

}




