#ifndef _PTL_SHELL_SORT_HPP_
#define _PTL_SHELL_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void shell_sort(T arr[], size_t length) {
        T next;
        int k;
        for (size_t h = length / 3; h > 0; h /= 3) // h = gap size between subarrays, will be divided by 3 on each loop
        {
            for (size_t i = 0; i < h; ++i) // to be able to sort all gapped subarrays first i = 0 to h index
            {                           // will be used as 'first index' for corresponding subarrays

                for (size_t j = h + i; j < length; j+=h+i) {   // Insertion sort for gapped subarrays
                    next = arr[j]; // get the next unsorted number
                    k = j - (h + i); // start comparison from previous index
                    for (; k >= 0; k-=h+i) {
                        if (next < arr[k])
                            arr[k + (h+i)] = arr[k]; // swap as long as needed
                        else
                            break;
                    }
                    arr[k + (h + i)] = next; // put the number to its right place
                }

            }

        }
    }
}

#endif /* _PTL_SHELL_SORT_HPP_ */
