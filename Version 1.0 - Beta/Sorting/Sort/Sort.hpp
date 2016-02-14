// Robin Kalia
// robinkalia@berkeley.edu
// Sort: Contains the various algorithms that can be used for sorting: HeapSort, MergeSort, QuickSort, Shellsort, RadixSort
// 
// Sort.hpp: Class that contains various types of algorithms used for Sorting 

/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_SORT_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_SORT_H

#include <iostream>
#include <stdint.h>

#include <vector>
#include <algorithm>

template<typename T>
class Sort {
private:
	void QSort(std::vector<T> &arr, int32_t start_index, int32_t last_index);

	void MSort(std::vector<T> &arr, int32_t start_index, int32_t last_index);
	void Merge(std::vector<T> &arr, int32_t start_index, int32_t last_index);

	void RestoreHeap(std::vector<T> &arr, int32_t start_index, int32_t last_index);

	// William's Method with a complexity of O(lg(n!)) really seems like an overkill when compared to 
	// Floyd's Method with a complexity of O(n)
	void RestoreHeapWithWilliamAlgorithm(std::vector<T>& heap_data_list, int32_t last_index);
	void MoveUp(std::vector<T>& data_list, int32_t last_index); //Top-Down Approach
	void RestoreHeapWithFloydAlgorithm(std::vector<T>& heap_data_list, int32_t last_index);
	void MoveDown(std::vector<T>& data_list, int32_t first_index, int32_t last_index); //Bottom-Up Approach

public:
	void QuickSort(const std::vector<T> &init_data_list, std::vector<T>& output_data_list);
	
	void MergeSort(const std::vector<T> &init_data_list, std::vector<T>& output_data_list);

	void HeapSort(const std::vector<T> &init_data_list, std::vector<T>& output_data_list);
	void HeapSort2(const std::vector<T> &init_data_list, std::vector<T>& output_data_list);
};


template<typename T>
void Sort<T>::HeapSort(const std::vector<T> &init_data_list, std::vector<T>& output_data_list)
{
	output_data_list = init_data_list;
	int32_t last_index;

	RestoreHeapWithFloydAlgorithm(output_data_list, output_data_list.size()-1);
	for (int32_t i = 0; i < output_data_list.size(); i++) {
		last_index = output_data_list.size() - 1 - i;
		std::swap(output_data_list[0], output_data_list[last_index]);
		RestoreHeapWithFloydAlgorithm(output_data_list, last_index-1);	// For efficiency purposes since it is O(n) in efficiency
	}
}


template<typename T>
void Sort<T>::RestoreHeapWithWilliamAlgorithm(std::vector<T>& heap_data_list, int32_t last_index)
{
	std::vector<T> new_heap_data_list;
	for (const auto& elem : heap_data_list)	{
		new_heap_data_list.push_back(elem);
		MoveUp(new_heap_data_list, last_index);
	}
	heap_data_list = new_heap_data_list;
}


template<typename T>
void Sort<T>::MoveUp(std::vector<T>& data_list, int32_t last_index)
{
	int32_t curr_index = last_index - 1;
	int32_t par_index = (curr_index-1)/2;
	while (par_index >= 0) {
		if (data_list[par_index] < data_list[curr_index])	std::swap(data_list[par_index], data_list[curr_index]);

		curr_index = par_index;
		par_index = (curr_index - 1) / 2;
	}
}


template<typename T>
void Sort<T>::RestoreHeapWithFloydAlgorithm(std::vector<T>& heap_data_list, int32_t last_index)
{
	int32_t start_index = last_index / 2 - 1;
	for (int32_t index = start_index; index >= 0; --index)		MoveDown(heap_data_list, index, last_index);
}


template<typename T>
void Sort<T>::MoveDown(std::vector<T>& data_list, int32_t first_index, int32_t last_index)
{
	int32_t largest_child_index = 2 * first_index + 1;
	while (largest_child_index < last_index) {
		if (data_list[largest_child_index] < data_list[largest_child_index+1])	++largest_child_index;

		if (data_list[first_index] < data_list[largest_child_index])	{
			std::swap(data_list[first_index], data_list[largest_child_index]);
			first_index = largest_child_index; 
			largest_child_index = 2*first_index + 1;
		}
		else largest_child_index = last_index + 1;
	}
}


// Heapsort Code

template<typename T>
void Sort<T>::HeapSort2(const std::vector<T> &init_data_list, std::vector<T> &sorted_data_list)
{
	sorted_data_list.clear();
	sorted_data_list = init_data_list;
	int32_t size = sorted_data_list.size();
	RestoreHeap(sorted_data_list, 0, size);

	// Since we want the sorted_arr in ascending order we will create a Max Heap	
	for (int32_t i = 0; i < sorted_data_list.size() - 1; i++) {
		std::iter_swap(sorted_data_list.begin(), sorted_data_list.end() - 1 - i);
		RestoreHeap(sorted_data_list, 0, size - 1 - i);
	}
}

template<typename T>
void Sort<T>::RestoreHeap(std::vector<T> &arr, int32_t start_index, int32_t last_index)
{
	int32_t size = last_index - start_index;
	int32_t bigger_elem_index = last_index - 1;
	for (int32_t i = size / 2 - 1; i >= start_index; i--) {
		bigger_elem_index = ((size % 2) != 0) ? ((arr[2*i + 1] > arr[2*i + 2]) ? (2*i + 1) : (2*i + 2)) : (2*i + 1);
		if (arr[i] < arr[bigger_elem_index])
			std::iter_swap(arr.begin() + i, arr.begin() + bigger_elem_index);
	}
}


template<typename T>
void Sort<T>::MergeSort(const std::vector<T> &init_data_list, std::vector<T> &sorted_data_list)
{
	sorted_data_list.clear();
	int32_t size = init_data_list.size();
	sorted_data_list = init_data_list;

	int start_index = 0;
	int32_t mid_index = size / 2;
	int32_t last_index = size;
	if (mid_index >= 1) {
		MSort(sorted_data_list, start_index, last_index); // [start_index, last_index);
	}
}

template<typename T>
void Sort<T>::MSort(std::vector<T> &arr, int32_t start_index, int32_t last_index)
{
	int32_t mid_index = (start_index + last_index) / 2;

	if (mid_index > start_index) {
		MSort(arr, start_index, mid_index);   // [start_index, mid_index);
		MSort(arr, mid_index, last_index);    // [mid_index, last_index);
		Merge(arr, start_index, last_index);
	}
}

template<typename T>
void Sort<T>::Merge(std::vector<T>& arr, int32_t start_index, int32_t last_index)
{

	int32_t size = last_index - start_index;
	int32_t mid_index = (start_index + last_index) / 2;

	std::vector<T> inter_arr(size);

	int32_t i = start_index;
	int32_t j = 0;
	int32_t count = 0;
	while (count < size) {
		if ((i < mid_index) && (j + mid_index < last_index)) {
			if (arr[i] < arr[j + mid_index])	 {
				inter_arr[count] = arr[i];
				++i;
				++count;
			}
			else {
				inter_arr[count] = arr[j + mid_index];
				++j;
				++count;
			}
		}
		else if ((i >= mid_index) && (j + mid_index < last_index)) {
			inter_arr[count] = arr[j + mid_index];
			++j;
			++count;
		}
		else if ((i < mid_index) && (j + mid_index >= last_index)) {
			inter_arr[count] = arr[i];
			++i;
			++count;
		}
	}

	for (int32_t u = start_index; u < last_index; i++) {
		arr[u] = inter_arr[u - start_index];
	}
}




// Quicksort Code 

template<typename T>
void Sort<T>::QuickSort(const std::vector<T> &init_data_list, std::vector<T> &sorted_data_list)
{
	sorted_data_list.clear();
	int32_t size = init_data_list.size();
	sorted_data_list = init_data_list;

	std::vector<T>::iterator max_elem_iter = std::max_element(sorted_data_list.begin(), sorted_data_list.end());
	int32_t max_elem_index = std::distance(sorted_data_list.begin(), max_elem_iter);

	std::iter_swap(sorted_data_list.begin() + max_elem_index, sorted_data_list.end() - 1);
	QSort(sorted_data_list, 0, size - 2);
}


template<typename T>
void Sort<T>::QSort(std::vector<T> &arr, int32_t start_index, int32_t last_index)
{
	int32_t lower_id = start_index + 1;
	int32_t upper_id = last_index;
	int32_t mid_id = (start_index + last_index) / 2;
	T bound = arr[mid_id];

	std::iter_swap(arr.begin() + start_index, arr.begin() + mid_id);
	while (lower_id <= upper_id) {
		while (arr[lower_id] < bound)
			++lower_id;
		while (bound < arr[upper_id])
			--upper_id;

		if (lower_id < upper_id)
			std::iter_swap(arr.begin() + lower_id, arr.begin() + upper_id);
		else ++lower_id; // mainly to escape from the while loop
	}

	std::iter_swap(arr.begin() + start_index, arr.begin() + upper_id);

	if (start_index < upper_id - 1)
		QSort(arr, start_index, upper_id - 1);
	if (upper_id + 1 < last_index)
		QSort(arr, upper_id + 1, last_index);
}



#endif		// _OPENSOURCE_DATASTRUCTS_ALGOS_SORT_H