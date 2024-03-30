/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"
#include <algorithm>


// TODO: add implementation of SchedulerRR constructor, destrcutor and 
// member functions init, print_results, and simulate here


SchedulerRR :: SchedulerRR(int time_quantum) {
    this->time_quantum = time_quantum;
}

SchedulerRR :: ~SchedulerRR(){

}

void SchedulerRR :: init(std::vector<PCB>& process_list){
    this->process_list = process_list;
    this->wait_queue = process_list;

}

bool check_time(std::vector<PCB>& process_list){
    for(PCB& pcb : process_list){
        if(pcb.burst_time != 0 ){
            return true;
        }
    }
    return false;
}



void SchedulerRR::simulate() {

    unsigned int  waitTime = 0;
    int count = 112;

    int current = 0;

    bool allComplete = false;

    //We shouldnt erase any of the values from the list;
    //instead we should be checking once all of the values  burst time variable has reached zero
    //create a function that goes through all of the PCBs to see if they all have a burst time of zero
    //if we erase them from the wait queue the data from the original queue and the wait queue will be
    //desynced as they will be different sizes

    while(check_time(this->wait_queue )){

        PCB* pcb = &this->wait_queue[current];

//        cout<<"\nPROCESS BEFORE CHECK!"<<endl;
//        cout<<"BEFORE Process "<< pcb->name <<" with  "<<pcb->burst_time<<" time units"<< endl;

        //checks if we are at the end of the scheduler
        //get the current process

        //if the process has no current burst move onto the next part
        while(pcb->burst_time == 0){
            current += 1;
            if(current > this->wait_queue.size()-1){
                current = 0;
            }
            pcb = &this->wait_queue[current];
        }

//        cout<<"PROCESS AFTER CHECK!"<<endl;
//        cout<<"AFTER Process "<< pcb->name <<" with  "<<pcb->burst_time<<" time units"<< endl;



        //subtract the time quantum as long as burstime is greter
        //else this implies that the burst time needs to be reduced by the remaining amount of time
        if (this->time_quantum <= pcb->burst_time){
            cout<<"i:"<<count<<"|Running Process "<< pcb->name <<" for "<<this->time_quantum<<" time units"<< endl;

            pcb->burst_time -= this->time_quantum;

            waitTime +=  this->time_quantum;
        }
        else{
            cout<<"i:"<<count<<"|Running Process "<< pcb->name <<" for "<<pcb->burst_time<<" time units"<< endl;
            waitTime += pcb->burst_time;
            pcb->burst_time = 0 ;

        }


//        cout<<"PROCESS AFTER RUNNING!"<<endl;
//        cout<<"AFTER RUNNING Process "<< pcb->name <<" BURST time left :  "<<pcb->burst_time<<" time units"<< endl;

        if(pcb->burst_time == 0){
//            cout<<"PROCESS COMPLETE!"<<endl;
//            cout<<"Completed Process "<< pcb->name <<" with  "<<pcb->burst_time<<" time units"<< endl;

//            PCB& final_data = this->process_list[current];
            PCB* final_data = &this->process_list[current];

            final_data->arrival_time = waitTime - final_data->burst_time;
            final_data->burst_time = waitTime;

        }


        count += 1;
        current += 1;

        //For some reason process T6 is getting replaced at i 133
//        cout<<"Process List:"<<endl;
//        for(PCB pcb : this->wait_queue){
//            cout<<"|PCB "<< pcb.name <<" : "<<pcb.burst_time<<" time units"<< endl;
//        }




        if(current > this->wait_queue.size()-1){
            current = 0;
        }

//        cout<<"NEXT CURRENT:"<<current<< endl;





//        if(current > this->wait_queue.size()-1){
//            current = 0;
//        }
//        cout<<"Process List:"<<endl;
//        for(PCB& pcb : this->wait_queue){
//            cout<<"|PCB "<< pcb.name <<" : "<<pcb.burst_time<<" time units"<< endl;
//        }
//
//
//        PCB& pcb = this->wait_queue[current];
//
//        while(pcb.burst_time == 0){
//            current += 1;
//            if(current > this->wait_queue.size()-1){
//                current = 0;
//            }
//            pcb = this->wait_queue[current];
//
//        }
//
//
//        //subtract the time quantum as long as burstime is greter
//        //else this implies that the burst time needs to be reduced by the remaining amount of time
//        if (this->time_quantum < pcb.burst_time){
//            cout<<"i:"<<count<<"|Running Process "<< pcb.name <<" for "<<this->time_quantum<<" time units"<< endl;
//
//            pcb.burst_time -= this->time_quantum;
//
//            waitTime +=  this->time_quantum;
//        }
//        else{
//            cout<<"i:"<<count<<"|Running Process "<< pcb.name <<" for "<<pcb.burst_time<<" time units"<< endl;
//            waitTime += pcb.burst_time;
//            pcb.burst_time -= pcb.burst_time;
//
//        }
//
//
//
//        // once the pcb burst time has reached zero this means that we need to
//        // calulate the turn around time for the process
//
//        if(pcb.burst_time == 0){
////            this->wait_queue.erase(this->wait_queue.begin() + current);
////            FIX THIS ; they may not have the same position after values get removed etc!
//            PCB& final_data = this->process_list[current];
//
//            cout<<"PCB id: "<<pcb.name<<":"<<pcb.burst_time<<" time units"<< endl;
////            cout<<"Current Wait:"<<waitTime<<endl;
////            cout<<"final_data burst time id: "<<final_data.name<<":"<<final_data.burst_time<<" time units"<< endl;
//            final_data.arrival_time = waitTime - final_data.burst_time;
//
//            final_data.burst_time = waitTime;
//
//        }
//
//        current += 1 ;
//        count += 1;

    }

}

void SchedulerRR::print_results() {
    for(PCB pcb : this->process_list){

        this->tTime+= pcb.burst_time;
        this->wTime += pcb.arrival_time;

        cout<<pcb.name <<"  turn-around time = "<< pcb.burst_time<< " waiting time "<< pcb.arrival_time <<endl;
    }

    cout<<"Average turn-around time = "<< this->tTime / this->process_list.size() << ", Average waiting time = "<< this->wTime / this->process_list.size() <<endl;

}