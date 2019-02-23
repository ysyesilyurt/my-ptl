#ifndef _PTL_RADIX_SORT_HPP_
#define _PTL_RADIX_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    int get_max(T[]);
    template <typename T>
    void cSort_radix(T[], size_t , size_t);

    template <typename T>
    void radix_sort(T arr[], size_t length)
    {
        // Do counting sort for every digit.
        int max_value = get_max(arr);
        for (size_t exp = 1; max_value/exp > 0; exp *= 10)
            cSort_radix(arr, length, exp);
    }

    // A function to do counting sort of arr[] according to
    // the digit represented by exp.
    template <typename T>
    void cSort_radix(T arr[], size_t length, size_t exp)
    {
        T count_array[10] = {};
        T temp[length];

        for (size_t i = 0; i < length; i++)
            count_array[(arr[i]/exp)%10]++;

        for (size_t i = 1; i < 10; i++)
            count_array[i] += count_array[i - 1];

        for (int i = (int)length - 1; i >= 0; i--)
        {
            temp[count_array[ (arr[i]/exp)%10 ] - 1] = arr[i];
            count_array[ (arr[i]/exp)%10 ]--;
        }

        for (size_t i = 0; i < length; i++)
            arr[i] = temp[i];
    }

    template <typename T>
    int get_max(T arr[])
    {
        int max = arr[0];
        for (int i = 0; arr[i] ; ++i) {
            if(arr[i] > max)
                max = arr[i];
        }
        return max;
    }

}

#endif /* _PTL_RADIX_SORT_HPP_ */





