// Robin Kalia
// robinkalia@berkeley.edu
// BSTree: Implementation of various algorithms in Binary Search Tree
// 
// main.cpp: Illustration of various operations on a Binary Search Tree

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


#include <string>
#include <exception>

#include "BSTree.hpp"


int32_t main(int32_t argc, char* argv[]) {
	try {
		BSTree<int32_t> tree;

		int32_t max_h = 3;
		int32_t max_elems = (1 << max_h) - 1;
		std::vector<int32_t> elem_list;
		for (int32_t i = 0; i < max_elems; i++)     elem_list.push_back(i);

		std::cout << "\nCreating a Dummy BSTree" << std::endl;
		tree.CreateDummyTree(elem_list);

		std::string inorder_dfs_str, preorder_dfs_str, postorder_dfs_str;
		if (max_h == 3) {
			inorder_dfs_str = "Correct InOrder DFS for Height = 3 [LVR]: 3, 1, 4, 0, 5, 2, 6";
			preorder_dfs_str = "Correct PreOrder DFS for Height = 3 [VLR]: 0, 1, 3, 4, 2, 5, 6";
			postorder_dfs_str = "Correct PostOrder DFS for Height = 3 [LRV]: 3, 4, 1, 5, 6, 2, 0";
		}
		else if (max_h == 4) {
			inorder_dfs_str = "InOrder DFS for Height = 4 [LVR]: 7, 3, 8, 1, 9, 4, 10, 0, 11, 5, 12, 2, 13, 6, 14";
			preorder_dfs_str = "Correct PreOrder DFS for Height = 4 [VLR]: 0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 12, 6, 13, 14";
			postorder_dfs_str = "Correct PostOrder DFS for Height = 4 [LRV]: 7, 8, 3, 9, 10, 4, 1, 11, 12, 5, 13, 14, 6, 2, 0";
		}
		std::cout << "\n\n" << inorder_dfs_str; 
		std::cout << "\nTesting InOrder DFS: ";
		tree.InorderDFS();
		std::cout << "\n\n" << preorder_dfs_str;
		std::cout << "\nTesting PreOrder DFS: ";
		tree.PreorderDFS();
		std::cout << "\n\n" << postorder_dfs_str;
		std::cout << "\nTesting PostOrder DFS: ";
		tree.PostorderDFS();

		std::cout << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Encountered Error: " << e.what() << std::endl;
	}

	return 0;
}