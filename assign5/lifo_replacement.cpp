/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

// TODO: Add your implementation here
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
LIFOReplacement::~LIFOReplacement() {
    // TODO: Add necessary code here
}

void LIFOReplacement ::print_statistics() {
    cout<<"\nNumber of references:     "<< referenceCounter;
    cout<<"\nNumber of page faults:    "<<numFaults;
    cout<<"\nNumber of page replacements:  "<< numReplacements<<endl;
}


// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    ageQueue.push_back(page_num);
    frames.push_back(page_num);
    pageFrameMap[page_num] = frames.size() - 1;

    page_table[page_num].valid = true;
    page_table[page_num].frame_num = frames.size() - 1;
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {

    //    find the oldest page number in the age queue ie the
//the page number at the start of the queue

//    cout<<"\nPage Number to be added:"<<page_num<<endl;

    int oldestPage = ageQueue.back();
//    cout<<"Oldes Number to be remove:"<<oldestPage<<endl;
//    Get rid of the oldest page so it is no longer in the age queue
    ageQueue.pop_back();
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
    page_table[page_num].frame_num = oldPagePos;
//    remove the old page map because this page is no longer in physical memory
//and needs to have the value that represented its location in physical memory removed

    pageFrameMap.erase(oldestPage);
    pageFrameMap[page_num] = oldPagePos;

    ageQueue.push_back(page_num);


    return oldPagePos;
}


PageEntry LIFOReplacement ::getPageEntry(int page_num) {

    return  page_table[page_num];
}

bool LIFOReplacement::access_page(int page_num, bool is_write) {

    referenceCounter +=1;


//    Page Fault occurs here since page is not valid meaning it has not been loaded into physical memory
    if( !page_table[page_num].valid){

//  check if frames are available and call the load_page function
//if the size of the number of frames in physical memory is less then the number of freams we load in pages
        if(frames.size() < this->num_frames){
            load_page(page_num);
        }
//    represents not enough frames to place the page num into
//if the size of the number of items in the physical memory is greeter then max number of frames we replace
        else {
//        cout<<"Replace!"<<endl;
            numReplacements +=1;
            replace_page(page_num);
        }
        numFaults += 1;
        return true;
    }


    return false;
}