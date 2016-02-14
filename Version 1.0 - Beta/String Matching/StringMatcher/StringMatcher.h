// Robin Kalia
// robinkalia@berkeley.edu
// Project: String Matching
// 
// StringMatcher.h: Contains the declaration of different methods and data members used in the "StringMatcher" class that
//                  provides access to different efficient string matching algorithms.    


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

#include <string>
#include <stdint.h>
#include <vector>


class StringMatcher {
private:
	bool CheckStringsSanity(const std::string &pattern, const std::string &text);

	void GeneratePrefix(const std::string &pattern, std::vector<int32_t> &prefix);
	void MatchPatternInTextWithPrefix(const std::string &text, const std::string &pattern, const std::vector<int32_t> &prefix, std::vector<int32_t> &matching_indices);

public:
	StringMatcher();
	~StringMatcher();

	void KnuthMorrisPrattStringMatchingAlgorithm(const std::string &text, const std::string &pattern, std::vector<int32_t> &matching_indices);
};