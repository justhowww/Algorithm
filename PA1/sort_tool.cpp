// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data)
{
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++)
    {
        int j = i - 1;
        int target = data[i];
        while (j >= 0)
        {
            if (target < data[j])
            {
                swap(data[j + 1], data[j]);
            }
            else
            {
                break;
            }
            j--;
        }
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data)
{
    srand(time(NULL));
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (high > low)
    {
        int pivot = Partition(data, low, high);
        QuickSortSubVector(data, low, pivot - 1);
        QuickSortSubVector(data, pivot + 1, high);
    }
}

int SortTool::Partition(vector<int> &data, int low, int high)
{
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171
    // int pi = high;
    int pi = rand() % (high - low + 1) + low;
    int left_idx = low;
    for (int i = low; i < high; i++)
    {
        if (data[i] < data[pi])
        {
            swap(data[left_idx], data[i]);
            left_idx++;
        }
    }
    swap(data[left_idx], data[pi]);
    return left_idx;
}

// Merge sort method
void SortTool::MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (high > low)
    {
        MergeSortSubVector(data, (high + low) / 2 + 1, high);
        MergeSortSubVector(data, low, (high + low) / 2);
        Merge(data, low, (high + low) / 2, (high + low) / 2 + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int middle1, int middle2, int high)
{
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int small_idx = low;
    int big_idx = middle2;
    vector<int> temp;
    while (small_idx <= middle1 && big_idx <= high)
    {
        if (data[small_idx] <= data[big_idx])
        {
            temp.push_back(data[small_idx]);
            small_idx++;
        }
        else if (data[small_idx] > data[big_idx])
        {
            temp.push_back(data[big_idx]);
            big_idx++;
        }
    }
    if (small_idx <= middle1)
    {
        while (small_idx <= middle1)
        {
            temp.push_back(data[small_idx]);
            small_idx++;
        }
    }
    else
    {
        while (big_idx <= high)
        {
            temp.push_back(data[big_idx]);
            big_idx++;
        }
    }
    for (int i = 0; i < high - low + 1; i++)
    {
        data[low + i] = temp[i];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data)
{
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data, 0);
    }
}

// Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
}

// Build max heap
void SortTool::BuildMaxHeap(vector<int> &data)
{
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
}
