// Robin Kalia
// robinkalia@berkeley.edu
// Graphs: Class that contains implementation of various Graph Algorithms
// 
// Node.hpp: Contains the declaration and definition of different data members and methods of the Node class

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


#include <iostream>
#include <stdio.h>

#include <stdint.h>

template<typename T1, typename T2 = int64_t>
class Node {
public:
	T1 data_;
	T2 uuid_;

	Node();
	Node(const T1& data_val, const T2& index);
	~Node();
};


template<typename T1, typename T2>
Node<T1, T2>::Node()
{
	
}


template<typename T1, typename T2>
Node<T1, T2>::Node(const T1& data_val, const T2& index)
{
	data_ = data_val;
	uuid_ = index;
}


template<typename T1, typename T2>
Node<T1, T2>::~Node()
{
	
}
