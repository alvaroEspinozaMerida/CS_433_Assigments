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
//    std::deque<int>::iterator it;
//    for (it = ageQueue.begin(); it != ageQueue.end(); it++) {
//        if (*it == page_num) {
//            ageQueue.erase(it);
//            break;
//        }
//    }
//    ageQueue.push_back(page_num);

    for (auto it = ageQueue.begin(); it != ageQueue.end(); it++) {
        if (*it == page_num) {
            ageQueue.erase(it);
            break;
        }
    }
    ageQueue.push_back(page_num);


//    std::cout << "Page " << page_num << " was touched (LRU)" << std::endl;
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    ageQueue.push_back(page_num);
    frames.push_back(page_num);
    pageFrameMap[page_num] = frames.size() - 1;

    page_table[page_num].valid = true;
    page_table[page_num].frame_num = frames.size() - 1;

//    std::cout << "Page " << page_num << " was loaded (LRU)" << std::endl;
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    int victim_page_num = ageQueue.front();
    ageQueue.pop_front();

    int oldPagePos = pageFrameMap[victim_page_num];
    frames[oldPagePos] = page_num;

    page_table[victim_page_num].valid = false;
    page_table[victim_page_num].frame_num = -1;

    page_table[page_num].valid = true;
    page_table[page_num].frame_num = oldPagePos;

    pageFrameMap.erase(victim_page_num);
    pageFrameMap[page_num] = oldPagePos;

    ageQueue.push_back(page_num);

    return oldPagePos;

//    std::cout << "Page " << victim_page_num << " was replaced (LRU)" << std::endl;
//    return victim_page_num;
}

void LRUReplacement::print_statistics() {
    // Print statistics for the LRU algorithm
    cout << "\nNumber of references:     " << referenceCounter;
    cout << "\nNumber of page faults:    " << numFaults;
    cout << "\nNumber of page replacements:  " << numReplacements << endl;
}
PageEntry LRUReplacement::getPageEntry(int page_num) {
    // Retrieve the page entry for a given page number
    return page_table[page_num];
}

bool LRUReplacement::access_page(int page_num, bool is_write) {
    // Access a page using the LRU algorithm and update statistics accordingly
    referenceCounter++;

    // Check if the page is not valid, indicating a page fault
    if (!page_table[page_num].valid) {
        // If there are available frames, load the page
//        if (frames.size() < this->num_frames) {
        if (frames.size() < num_frames) {
            load_page(page_num);
        } else {
            // If there are no available frames, replace a page using LRU
            numReplacements++;
            replace_page(page_num);
        }
        numFaults ++;
        return true;
    }

    // Update the access time of the page to reflect its recent use
    // This is specific to LRU, where the least recently used page is replaced
    touch_page(page_num);

    return false;

}