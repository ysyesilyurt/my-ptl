#ifndef _PTL_INSERTION_SORT_HPP_
#define _PTL_INSERTION_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void insertion_sort(T arr[], size_t length) {
        int next, j;
        for (int i = 1; i < length; ++i) {
            next = arr[i]; // get the next unsorted number
            j = i - 1; // start comparison from previous index
            for (; j >= 0; --j) {
                if (next < arr[j])
                    arr[j + 1] = arr[j]; // swap as long as needed
                else
                    break;
            }
            arr[j + 1] = next; // put the number to its right place
        }
    }
}


#endif /* _PTL_INSERTION_SORT_HPP_ */
