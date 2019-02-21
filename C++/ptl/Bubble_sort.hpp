#ifndef _PTL_BUBBLE_SORT_HPP_
#define _PTL_BUBBLE_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void bubble_sort(T arr[], size_t length) {
        bool sorted = false;
        T temp;
        while(!sorted) // iterate over array as long as array is not sorted
        {
            sorted = true;
            for (size_t i = 0; i < length; ++i) {
                if (arr[i+1] && (arr[i] > arr[i+1])) // carry current greatest number to the end
                {
                    temp = arr[i+1];
                    arr[i+1] = arr[i];
                    arr[i] = temp;
                    sorted = false; // a swapping operation took place ~ array is still not sorted
                }
            }
        }
    }
}

#endif /* _PTL_BUBBLE_SORT_HPP_ */
