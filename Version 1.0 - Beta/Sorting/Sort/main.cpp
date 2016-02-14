// Robin Kalia
// robinkalia@berkeley.edu
// Sort: Contains the various algorithms that can be used for sorting: HeapSort, MergeSort, QuickSort, Shellsort, RadixSort
// 
// main.cpp: Illustration of the various algorithms used for Sorting 

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


#include "Sort.hpp"

#include <string>

enum ERRORS { FUNCTION_ERROR = -2, ARGUMENT_ERROR = -1, SUCCESS = 0 };

const int32_t DEBUG = 1;

int32_t main(int32_t argc, char* argv[])
{
	std::vector<int32_t> init_data_list, sorted_data_list;

	if (DEBUG) {
		init_data_list = { 35, 40, 2, 8, 1, 100, 3, 70, 41, 11, 6, 94, 97, 91, 88, 106, 170 };
	} 	else {
		if (argc < 3)	{
			std::cout << "\nUsage:\n\tWindows: Sort.exe <integer data stream>\n\tLinux/Unix: ./Sort <data integer stream>";
			return ARGUMENT_ERROR;
		}

		for (int32_t i = 1; i < argc; i++)		init_data_list.push_back(std::stoi(std::string(argv[i])));	
	}


	std::cout << "\n\nInitial Data: { ";
	for (int32_t i = 0; i < init_data_list.size(); i++)
		std::cout << init_data_list[i] << ((i != init_data_list.size() - 1) ? ", " : " }");

	Sort<int32_t> sorter;

	try {
		std::cout << "\n\nQuicksort Algorithm:-\nSorted Data: { ";
		sorter.QuickSort(init_data_list, sorted_data_list);
		for (int32_t i = 0; i < sorted_data_list.size(); i++)
			std::cout << sorted_data_list[i] << ((i != sorted_data_list.size() - 1) ? ", " : " }");

		sorted_data_list.clear();
		std::cout << "\n\nHeapsort Algorithm:-\nSorted Data: { ";
		sorter.HeapSort(init_data_list, sorted_data_list);
		for (int32_t i = 0; i < sorted_data_list.size(); i++)
			std::cout << sorted_data_list[i] << ((i != sorted_data_list.size() - 1) ? ", " : " }");

		sorted_data_list.clear();
		std::cout << "\n\nHeapsort2 Algorithm:-\nSorted Data: { ";
		sorter.HeapSort2(init_data_list, sorted_data_list);
		for (int32_t i = 0; i < sorted_data_list.size(); i++)
			std::cout << sorted_data_list[i] << ((i != sorted_data_list.size() - 1) ? ", " : " }");

		sorted_data_list.clear();
		std::cout << "\n\nMergesort Algorithm:-\nSorted Data: { ";
		sorter.MergeSort(init_data_list, sorted_data_list);
		for (int32_t i = 0; i < sorted_data_list.size(); i++)
			std::cout << sorted_data_list[i] << ((i != sorted_data_list.size() - 1) ? ", " : " }");

		std::cout << std::endl;
	}
	catch (const std::exception& err) {
		std::cout << "\nCaught Error: " << std::string(err.what()) << std::endl;
		return FUNCTION_ERROR;
	}

	return SUCCESS;
}