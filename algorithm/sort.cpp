#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
void Merge(std::vector<T>& merged_array, std::vector<T>& left, std::vector<T>& right);
struct gen_rand {
    double range;
public:
    gen_rand(double r=1.0) : range(r) {}
    double operator()() {
        return (rand()/(double)RAND_MAX) * range;
    }
};

/*
Make multiple passes through the array, each time moving the largest unsorted
value to the right (end) of the array.
BEST = O(n)
AVERAGE = O(n^2)
WORST = O(n^2)
*/
template<typename T>
void BubbleSort(std::vector<T>& array)
{
    bool did_pass = false;
    do {
        did_pass = false;
        for (size_t i = 0; i < array.size() - 1; i++) {
            if (array[i] > array[i+1]) {
                std::swap(array[i], array[i+1]);
                did_pass = true;
            }
        }
    } while (did_pass);
}

/*
BEST = O(n)
AVERAGE = O(n^2)
WORST = O(n^2)
*/
template<typename T>
void InsertionSort(std::vector<T>& array)
{
    for (size_t i = 1; i < array.size(); i++) {
        // Find index to insert in the array [0:i-1]
        size_t j = 0;
        for (; j < i; j++) {
            if (array[i] < array[j]) {
                break; // j is the index to insert.
            }
        }

        // now insert value into the array. We are going to swap values.
        // Step 1.
        T temp = array[j];

        // Step 2.

        array[j] = array[i];

        // Step 3.
        for (int current = i; current > j; current--)
        {
            array[current] = array[current - 1];
        }

        // Step 4.
        array[j + 1] = temp;
    }
}

/*
Find first the smallest unsorted value and put it to the most left side of the
unsorted array.
BEST = O(n)
AVERAGE = O(n^2)
WORST = O(n^2)
*/
template<typename T>
void SelectionSort(std::vector<T>& array)
{
    for (size_t i = 0; i < array.size() - 1; i++) {
        //Find the smallest value.

        int tmp_smallest_index = i;
        for (size_t j = i + 1; j < array.size(); j++) {
            if (array[tmp_smallest_index] > array[j]) {
                tmp_smallest_index = j;
            }
        }

        // Then put tmp_smallest_index at index i
        std::swap(array[i], array[tmp_smallest_index]);
    }
}

/*
    MergeSort.
    divide first, then merge and sort.
    BEST = O(n log n)
    AVERAGE = O(n log n)
    WORST = O(n log n)
*/
template<typename T>
void MergeSort(std::vector<T>& array)
{
    if (array.size() <= 1) {
        return;
    }

    int half_size = array.size() /2;
    std::vector<T> left(array.begin(), array.begin() + half_size);
    std::vector<T> right(array.begin() + half_size, array.end());

    // Now, sort the left and right arrays.
    MergeSort(left);
    MergeSort(right);
    Merge(array, left, right);
}

template<typename T>
void Merge(std::vector<T>& merged_array, std::vector<T>& left, std::vector<T>& right)
{
    bool sorted = false;
    size_t left_index = 0;
    size_t right_index = 0;
    size_t index_to_insert = 0;
    while (!sorted) {
        if (left_index == left.size()) {
            // Left array is empty, put the rest of right inside the merged_array
            for (size_t i = right_index; i < right.size(); i++) {
                merged_array[index_to_insert] = right[i];
                index_to_insert++;
            }
            break;
        } else if (right_index == right.size()) {
            // right array is empty, put the rest of right inside the merged_array
            for (size_t i = left_index; i < left.size(); i++) {
                merged_array[index_to_insert] = left[i];
                index_to_insert++;
            }
            break;
        } else if (right[right_index] < left[left_index]) {

            merged_array[index_to_insert] = right[right_index];
            right_index++;
        } else {
            merged_array[index_to_insert] = left[left_index];
            left_index++;
        }

        index_to_insert++;
    }
}

/*
    Separate arrays in three, firt element is a pivot, second element is
    an array at the left of the pivot with all element smaller than the pivot.
    last is an array at the right with all elements higher than the pivot.

    In this implementation, pivot is the first elements.
    BEST = O(n log n)
    AVERAGE = O(n log n)
    WORST = O(n log n)
*/
template<typename T>
void QuickSort(std::vector<T>& array)
{
    if (array.size() <= 1) {
        return;
    }
    // Find pivot and separate in two arrays.
    T pivot = array[0];
    std::vector<T> left;
    std::vector<T> right;

    for (int i = 1; i < array.size(); i++) {
        if (array[i] > pivot) {
            right.push_back(array[i]);
        } else {
            left.push_back(array[i]);
        }
    }

    // Sort the sub arrays.
    QuickSort(left);
    QuickSort(right);

    // Now merge.
    std::copy(left.begin(), left.end(), array.begin());
    array[left.size()] = pivot;
    std::copy(right.begin(), right.end(), array.begin() + left.size() + 1);
}

int main()
{
    int size = 150000;
    std::vector<double> x(size);
    //std::vector<int> x = {3, 2, 5, 4, 9, 7};

    std::generate_n(x.begin(), size, gen_rand());

    QuickSort(x);
}
