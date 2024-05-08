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
#include <queue>

// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code
    std::queue<int> page_queue;
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    if (num_free_frames() > 0) {
        int frame_num = allocate_frame(page_num);
        page_table[page_num].frame_num = frame_num;
        page_table[page_num].valid = true;
    }
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    int victim_page_num = page_queue.front();
    page_queue.pop();
    page_table[victim_page_num].valid = false;

    return victim_page_num;
}