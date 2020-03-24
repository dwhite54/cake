#include <iostream>
#include <string>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

void reverseWords(string& message)
{
    // decode the message by reversing the words

    //reverse everything
    //reverse each word
    for (size_t i = 0; i < message.size()/2; i++) {
        char tmp = message[i];
        message[i] = message[message.size() - 1 - i];
        message[message.size() - 1 - i] = tmp;
    }

    int start_idx = 0;
    for (size_t i = 1; i < message.size(); i++) {
        if (i == message.size()-1 || message[i+1] == ' ') { //end of word found, do reversal
            for (size_t j = start_idx; j < i - ((i - start_idx) / 2 ); j++) {
                char tmp = message[j];
                message[j] = message[i-(j-start_idx)];
                message[i-(j-start_idx)] = tmp;
            }
            start_idx = i+2;
        }
    }
}

// tests

const lest::test tests[] = {
    {CASE("one word") {
        const string expected = "vault";
        string actual = "vault";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("two words") {
        const string expected = "cake thief";
        string actual = "thief cake";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("three words") {
        const string expected = "get another one";
        string actual = "one another get";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("multiple words same length") {
        const string expected = "the cat ate the rat";
        string actual = "rat the ate cat the";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("multiple words different lengths") {
        const string expected = "chocolate bundt cake is yummy";
        string actual = "yummy is cake bundt chocolate";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("empty string") {
        const string expected;
        string actual;
        reverseWords(actual);
        EXPECT(actual == expected);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}