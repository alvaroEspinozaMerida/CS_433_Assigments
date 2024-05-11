/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"

// TODO: Add your implementation here
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Complete this constructor
}

// TODO: Add your implementations for desctructor, touch_page, load_page, replace_page here
LRUReplacement::~LRUReplacement()
{
    // TODO: Add necessary code here
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
//    // TODO: Update your data structure LRU replacement
//    if (pageFrameMap.find(page_num) != pageFrameMap.end()) {
//
//        int frame_num = pageFrameMap[page_num];
//        ageQueue.erase(frames[frame_num].iterator);
//        ageQueue.push_front(page_num);
//        frames[frame_num].iterator = ageQueue.begin();
//    }
//    std::cout << "Page " << page_num << " was touched (LRU)" << std::endl;
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    // TODO: Update your data structure LRU replacement and pagetable
//    if (num_free_frames() > 0) {
//        int frame_num = allocate_frame(page_num);
//        page_table[page_num].frame_num = frame_num;
//        page_table[page_num].valid = true;
//
//        ageQueue.push_front(page_num);
//        frames[frame_num].iterator = ageQueue.begin();
//        pageFrameMap[page_num] = frame_num;
//    }
//    std::cout << "Page " << page_num << " was loaded (LRU)" << std::endl;
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    // TODO: Update your data structure LRU replacement and pagetable
//    int victim_page_num = ageQueue.back();
//    ageQueue.pop_back();
//
//    int victim_frame_num = pageFrameMap[victim_page_num];
//    page_table[victim_page_num].valid = false;
//    pageFrameMap.erase(victim_page_num);
//
//    page_table[page_num].frame_num = victim_frame_num;
//    page_table[page_num].valid = true;
//    ageQueue.push_front(page_num);
//    frames[victim_frame_num].iterator = ageQueue.begin();
//    pageFrameMap[page_num] = victim_frame_num;
//
//    std::cout << "Page " << victim_page_num << " was replaced (LRU)" << std::endl;
//    return victim_page_num;
}