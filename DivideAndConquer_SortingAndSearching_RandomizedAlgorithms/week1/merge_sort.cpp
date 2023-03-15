/*
Author: Efe Murat Uçarlı             
*/
#include <iostream>
#include <vector>
#include <iterator>

template<typename I2, typename I1>
void merge(I1 begin, I1 middle, I1 end, I2 temp_begin);

template<typename I>
void merge_sort(I begin, I end);

template<typename I1, typename I2>
void merge_sort_buffer(I1 begin , I1 end, I2 temp_data_begin);

int main()
{
    std::vector<char> a {'a','z','b','d','c'};
    merge_sort(std::begin(a),std::end(a));
    for (auto i: a)
    {
        std::cout << i << ' ';
    }
}

template<typename I>
void merge_sort(I begin, I end)
{
    typedef std::vector<typename std::iterator_traits<I>::value_type> TempVector;
    TempVector temp_data(std::make_move_iterator(begin), std::make_move_iterator(end)); //only uses O(n) extra memory space and this space is allocated only once(same space used in sub recursive calls as well)
    merge_sort_buffer(begin, end, std::begin(temp_data));
}

template<typename I1, typename I2>
void merge_sort_buffer(I1 begin , I1 end, I2 temp_data_begin)
{
    auto size = std::distance(begin, end);

    if (size < 2) 
    {
        return;
    }
    I1 middle   = std::next(begin, size/2);
    I2 temp_middle  = std::next(temp_data_begin, size/2);

    merge_sort_buffer(begin, middle,temp_data_begin);
    merge_sort_buffer(middle, end,temp_middle);
    merge(begin, middle, end, temp_data_begin);
}

template<typename I1, typename I2>
void merge(I1 begin, I1 middle, I1 end, I2 temp_begin)
{
    I1 left = begin;
    I1 right = middle;
    I2 buffer = temp_begin;

    while(left < middle && right < end)
    {
        *buffer = std::move((*left <= *right) ? *left++ : *right++);
        buffer++;
    }

    std::move(left, middle, buffer);
    std::move(right, end, buffer);
    int size = std::distance(begin, end);
    std::move(temp_begin, std::next(temp_begin, size), begin);
}