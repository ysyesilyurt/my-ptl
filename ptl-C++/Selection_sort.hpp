#ifndef _PTL_SELECTION_SORT_HPP_
#define _PTL_SELECTION_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void selection_sort(T arr[], size_t length) {
        size_t minIndex;
        T temp;
        for (size_t i = 0; i < length; ++i) {
            minIndex = i; // set current as the minimum 
            for (size_t j = i + 1; j < length ; ++j) { // search remaining array iteratively
                if (arr[minIndex] > arr[j])            // for finding the actual minimum 
                    minIndex = j;
            }
            temp = arr[i]; // swap for current minimum number
            arr[i] = arr[minIndex];
            arr[minIndex] = temp; 
        }
    }
}

#endif /* _PTL_SELECTION_SORT_HPP_ */
