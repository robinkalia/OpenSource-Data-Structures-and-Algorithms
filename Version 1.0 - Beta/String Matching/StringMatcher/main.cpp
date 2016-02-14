// Robin Kalia
// robinkalia@berkeley.edu
// Project: String Matching
// 
// main.cpp: Contains the illustrations of various String Matching algorithms


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

enum ERRORS { FUNCTION_ERROR = -2, ARGUMENT_ERROR = -1, SUCCESS = 0 };

const int32_t DEBUG = 1;

int32_t main(int32_t argc, char *argv[])
{
	std::string text, pattern;

	if (DEBUG) {
		text = "ascasfcascafascafscascasfcasfscasfafscfasfcascascscsfascasfcas";
		pattern = "asfc";

		//text = "abxabcabcaby";
		//pattern = "abcaby";

		//text = "cozacocacolacococacola";
		//pattern = "cocacola";
	}
	else {
		if (argc != 3)	{
			std::cout << "\nUsage:\n\tWindows: Stringmatcher.exe <text string> <pattern string>\n\tLinux/Unix: ./StringMatcher <text string> <pattern string>";
			return ARGUMENT_ERROR;
		}

		text = std::string(argv[1]);
		pattern = std::string(argv[2]);
	}

	StringMatcher string_matcher;
	
	std::vector<int32_t> matching_indices;

	try {
		std::cout << "\n\tTEXT    = " << text << "\n\tPATTERN = " << pattern << "\n\n";
		string_matcher.KnuthMorrisPrattStringMatchingAlgorithm(text, pattern, matching_indices);
		std::cout << "Knuth-Morris-Pratt String Matching Algorithm:\n\tMatching Indices = { ";
		for (int32_t i = 0; i < matching_indices.size(); i++)
			std::cout << matching_indices[i] << ((i == matching_indices.size() - 1) ? " }\n" : ", ");


	}
	catch (const std::exception& err) {
		std::cout << "\nCaught Error: " << std::string(err.what()) << std::endl;
		return FUNCTION_ERROR;
	}
	
	return SUCCESS;
}
