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
    PageTable table(num_pages);
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable

}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    return 0;
}


PageEntry FIFOReplacement ::getPageEntry(int page_num) {


    return  page_table[page_num];
}

bool FIFOReplacement::access_page(int page_num, int is_write) {

    if( page_table[page_num].valid == 0){
        page_table[page_num].valid = 1;
        page_table[page_num].frame_num = page_table.frameCounter;
        page_table.frameCounter += 1;
        return false;
    }

    return true;
}