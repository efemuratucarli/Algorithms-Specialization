#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#define ARRAY_SIZE 100000

template<typename I1, typename I2>
unsigned int count_split_inversions(I1 begin, I1 middle, I1 end, I2 temp_begin);

template<typename I>
unsigned int count_inversions(I begin, I end);

template<typename I1, typename I2>
unsigned int count_inversions_buffer(I1 begin , I1 end, I2 temp_data_begin);

int main()
{
    std::vector<unsigned int> integer_array(ARRAY_SIZE);
    std::ifstream infile {"IntegerArray.txt"};
    std::string line;
    unsigned int data;
    
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
       std::getline(infile,line);
       data = std::stoi(line);
       integer_array[i] = data;
      /*  std::cout << integer_array[i] << "\n"; */
    }
    unsigned int number_of_inversions;
    number_of_inversions = count_inversions(std::begin(integer_array),std::end(integer_array));
    std::cout << number_of_inversions << "\n";
}

template<typename I>
unsigned int count_inversions(I begin, I end)
{
    typedef std::vector<typename std::iterator_traits<I>::value_type> TempVector;
    TempVector temp_data(std::make_move_iterator(begin), std::make_move_iterator(end)); //only uses O(n) extra memory space and this space is allocated only once(same space used in sub recursive calls as well)
    return count_inversions_buffer(begin, end, std::begin(temp_data));
}

template<typename I1, typename I2>
unsigned int count_inversions_buffer(I1 begin , I1 end, I2 temp_data_begin)
{
    auto size = std::distance(begin, end);

    if (size < 2) 
    {
        return 0;
    }
    I1 middle   = std::next(begin, size/2);
    I2 temp_middle  = std::next(temp_data_begin, size/2);

    unsigned int left_inv = count_inversions_buffer(begin, middle,temp_data_begin);
    unsigned int right_inv = count_inversions_buffer(middle, end,temp_middle);
    unsigned int split_inv = count_split_inversions(begin, middle, end, temp_data_begin); //simple merge + count split inversions
    return left_inv + right_inv + split_inv;
}

template<typename I1, typename I2>
unsigned int count_split_inversions(I1 begin, I1 middle, I1 end, I2 temp_begin)
{
    unsigned int split_inv = 0;
    I1 left = begin;
    I1 right = middle;
    I2 buffer = temp_begin;

    while(left < middle && right < end)
    {
        if(*left <= *right)
        {
            *buffer = std::move(*left++);
            buffer++;
        }

        else
        {
            *buffer = std::move(*right++);
            buffer++;
            split_inv = split_inv + std::distance(left,middle);
        }
    }

    std::move(left, middle, buffer);
    std::move(right, end, buffer);
    int size = std::distance(begin, end);
    std::move(temp_begin, std::next(temp_begin, size), begin);
    return split_inv;
}