#include <iostream>
#include <vector>
#include <unordered_set>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

bool canTwoMoviesFillFlight(const vector<int>& movieLengths, int flightLength)
{
    // determine if two movies add up to the flight length
    unordered_set<int> complements;

    for (size_t i = 0; i < movieLengths.size(); ++i) {
        if (complements.find(movieLengths[i]) != complements.end()) {
            return true;
        }
        complements.insert(flightLength-movieLengths[i]);
    }

    return false;
}

// tests

const lest::test tests[] = {
    {CASE("short flight") {
        const vector<int> movieLengths {2, 4};
        EXPECT(canTwoMoviesFillFlight(movieLengths, 1) == false);
    }},
    {CASE("long flight") {
        const vector<int> movieLengths {2, 4};
        EXPECT(canTwoMoviesFillFlight(movieLengths, 6) == true);
    }},
    {CASE("only one movie half flight length") {
        const vector<int> movieLengths {3, 8};
        EXPECT(canTwoMoviesFillFlight(movieLengths, 6) == false);
    }},
    {CASE("two movies half flight length") {
        const vector<int> movieLengths {3, 8, 3};
        EXPECT(canTwoMoviesFillFlight(movieLengths, 6) == true);
    }},
    {CASE("lots of possible pairs") {
        const vector<int> movieLengths {1, 2, 3, 4, 5, 6};
        EXPECT(canTwoMoviesFillFlight(movieLengths, 7) == true);
    }},
    {CASE("not using first movie") {
        const vector<int> movieLengths {4, 3, 2};
        EXPECT(canTwoMoviesFillFlight(movieLengths, 5) == true);
    }},
    {CASE("only one movie") {
        const vector<int> movieLengths {6};
        EXPECT(canTwoMoviesFillFlight(movieLengths, 6) == false);
    }},
    {CASE("no movies") {
        const vector<int> movieLengths;
        EXPECT(canTwoMoviesFillFlight(movieLengths, 6) == false);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}