// Robin Kalia
// robinkalia@berkeley.edu
// Project: String Matching
// 
// main.cpp: Contains the illustrations of various String Matching algorithms


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
