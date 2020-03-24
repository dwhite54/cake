#include <iostream>
#include <string>
#include <unordered_map>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

bool hasPalindromePermutation(const string& str)
{
    // check if any permutation of the input is a palindrome
    unordered_map<char, int> counts;

    //count all characters in string
    for (auto s : str) {
        if (counts.find(s) != counts.end()) {
            counts[s]++;
        } else {
            counts[s] = 1;
        }
    }

    //look for odd counts. if it's an odd-length string, one is required, otherwise none are allowed
    bool isOdd = str.size() % 2 == 1;
    bool foundOdd = false;
    for (auto char_count : counts) {
        if (char_count.second % 2 != 0) {
            if (isOdd && foundOdd) { //already found an odd count, can't have two
                return false;
            } else if (!isOdd) { //even length string can have no odd counts
                return false;
            }
            foundOdd = true;
        }
    }
    if (isOdd && !foundOdd) {
        return false;
    } //don't need to check even, that's in the loop

    return true;
}


















// tests

const lest::test tests[] = {
    {CASE("permutation with odd number of chars") {
        const auto result = hasPalindromePermutation("aabcbcd");
        EXPECT(result == true);
    }},
    {CASE("permutation with even number of chars") {
        const auto result = hasPalindromePermutation("aabccbdd");
        EXPECT(result == true);
    }},
    {CASE("no permutation with odd number of chars") {
        const auto result = hasPalindromePermutation("aabcd");
        EXPECT(result == false);
    }},
    {CASE("no permutation with even number of chars") {
        const auto result = hasPalindromePermutation("aabbcd");
        EXPECT(result == false);
    }},
    {CASE("empty string") {
        const auto result = hasPalindromePermutation("");
        EXPECT(result == true);
    }},
    {CASE("one character string") {
        const auto result = hasPalindromePermutation("a");
        EXPECT(result == true);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}