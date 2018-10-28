#ifndef _PTL_COUNTING_SORT_HPP_
#define _PTL_COUNTING_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void counting_sort(T arr[], size_t length, size_t max_value)
    {
        T count_array[max_value + 1] = {}; // construct a count array with size = max value + 1, initialized as 0
        size_t arr_index = 0;
        int count_of_index;

        for (size_t i = 0; i < length; ++i) // increase corresponding indexes of count array w.r.t arr
            count_array[arr[i]]++;

        for (size_t i = 0; i < max_value + 1; ++i) {
            count_of_index = count_array[i]; // get the count of index on count array
            while (count_of_index > 0) // starting with min index, place numbers to arr according
            {                          // to their occurences (numbers ~ indexes on count array)
                arr[arr_index] = i;
                arr_index++;
                count_of_index--;
            }
        }
    }
}

#endif /* _PTL_COUNTING_SORT_HPP_ */
