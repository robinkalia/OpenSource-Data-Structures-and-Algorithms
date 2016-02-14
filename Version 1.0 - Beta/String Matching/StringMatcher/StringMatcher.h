

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