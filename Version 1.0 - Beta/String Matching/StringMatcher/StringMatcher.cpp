// Robin Kalia
// robinkalia@berkeley.edu
// Project: String Matching
// 
// StringMatcher.h: Contains the definition of different methods declared in the "StringMatcher" class

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


#include "StringMatcher.h"

StringMatcher::StringMatcher()
{
	

}


StringMatcher::~StringMatcher()
{


}


bool StringMatcher::CheckStringsSanity(const std::string &pattern, const std::string &text)
{
	if ((text.size() == 0) | (pattern.size() == 0) | (text.size() < pattern.size()))	return false;

	return true;
}


void StringMatcher::KnuthMorrisPrattStringMatchingAlgorithm(const std::string &text, const std::string &pattern, std::vector<int32_t> &matching_indices)
{
	matching_indices.clear();

	if (CheckStringsSanity(pattern, text) == false) {
		std::cout << "\nError in the passed strings:\n\ttext = " << text << "\n\tpattern = " << pattern << "\n\n";
		return;
	}

	std::vector<int32_t> prefix(pattern.size(), 0);

	GeneratePrefix(pattern, prefix);

	MatchPatternInTextWithPrefix(text, pattern, prefix, matching_indices);
}

void StringMatcher::GeneratePrefix(const std::string &pattern, std::vector<int32_t> &prefix)
{
	int32_t i = 1;
	int32_t j = 0;

	while (i < pattern.size()) {
		while ((j>0) && (pattern[i] != pattern[j]))
			prefix[i] = prefix[--j];

		if (pattern[i] == pattern[j])	++j;

		prefix[i++] = j;
	}
}


void StringMatcher::MatchPatternInTextWithPrefix(const std::string &text, const std::string &pattern, const std::vector<int32_t> &prefix, std::vector<int32_t> &matching_indices)
{
	int32_t matching_chars = 0;
	int32_t pattern_index = 0;
	
	for (int32_t i = 0; i < text.size(); i++) {
		while ((text[i] == pattern[pattern_index]) && (matching_chars < pattern.size()) && (i < text.size()))	{
			++i;
			++pattern_index;
			matching_chars = pattern_index;
		}

		if (matching_chars == pattern.size())	{
			matching_indices.push_back(i-pattern_index + 1);
			i = (i != text.size()) ? i - pattern_index : i;
			pattern_index = 0;
			matching_chars = 0;
		}

		if (i==text.size())	continue;

		if (pattern_index > 0) {
			pattern_index = prefix[pattern_index-1];
			--i;
		}
	}
}