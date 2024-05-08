/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"

// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{

}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    //load in the page number into the physical memory and then also keep track of it inside of the
    //of the age queue
    ageQueue.push(page_num);
    frames.push_back(page_num);
    pageFrameMap[page_num] = frames.size() - 1;

    page_table[page_num].valid = true;
    page_table[page_num].frame_num = frames.size() - 1;

}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {

//    find the oldest page number in the age queue ie the
//the page number at the start of the queue

    int oldestPage = ageQueue.front();
//    Get rid of the oldest page so it is no longer in the age queue
    ageQueue.pop();
//  Get the index position in the pMemory of the oldest page in the queue
    int oldPagePos = pageFrameMap[oldestPage];
    frames[oldPagePos] = page_num;

//    page table gets updated for that page number so that is no longer
//valid meaning it is not loaded into physical memory
//we also change out the frame_num to -1 to represent that is not in any
//physical memory location
    page_table[oldestPage].valid = false;
    page_table[oldestPage].frame_num = -1;

//    update the the newly added page in the table to now be valid
//so that no page faults can occur any more
//update this pages frame number to be the frame number of the old page

    page_table[page_num].valid = true;
    page_table[oldestPage].frame_num = oldPagePos;
//    remove the old page map because this page is no longer in physical memory
//and needs to have the value that represented its location in physical memory removed

    pageFrameMap.erase(oldestPage);

    return oldPagePos;
}
void FIFOReplacement ::print_statistics() {
   cout<<"Number of references:     "<< referenceCounter;
   cout<<"\nNumber of page faults:    "<<numFaults;
   cout<<"\nNumber of page replacements:  "<< numReplacements;
}

PageEntry FIFOReplacement ::getPageEntry(int page_num) {


    return  page_table[page_num];
}

bool FIFOReplacement::access_page(int page_num, int is_write) {

    referenceCounter +=1;

//    Page Fault occurs here since page is not valid meaning it has not been loaded into physical memory
    if( !page_table[page_num].valid){


//  check if frames are available and call the load_page function

    if(frames.size() < num_frames){
        load_page(page_num);
    }
    else{
        numReplacements +=1;
        replace_page(page_num);
    }
// TODO:UPDATE since this will now be done in respective methods
//        Page Entry is set to valid to reperesent that the page number is now loaded into the

        numFaults += 1;

        return true;
    }




    return false;
}