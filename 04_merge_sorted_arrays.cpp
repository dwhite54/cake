#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

vector<int> mergeVectors(const vector<int>& myVector, const vector<int>& alicesVector)
{
    // combine the sorted vectors into one large sorted vector
    size_t i = 0, j = 0;
    vector<int> rv(myVector.size() + alicesVector.size());
    while (i < myVector.size() && j < alicesVector.size()) {
        if (myVector[i] <= alicesVector[j]) {
            rv[i+j] = myVector[i];
            i++;
        } else {
            rv[i+j] = alicesVector[j];
            j++;
        }
    }
    if (i == myVector.size()) { // this is implied by following for loop conditions, but nice for readability
        for (; j < alicesVector.size(); j++) {
            rv[i+j] = alicesVector[j];
        }
    } else {
        for (; i < myVector.size(); i++) {
            rv[i+j] = myVector[i];
        }
    }

    return rv;
}


















// tests

const lest::test tests[] = {
    {CASE("both vectors are empty") {
        const vector<int> myVector;
        const vector<int> alicesVector;
        const vector<int> expected;
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("first vector is empty") {
        const vector<int> myVector;
        const vector<int> alicesVector {1, 2, 3};
        const vector<int> expected {1, 2, 3};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("second vector is empty") {
        const vector<int> myVector {5, 6, 7};
        const vector<int> alicesVector;
        const vector<int> expected {5, 6, 7};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("both vectors have some numbers") {
        const vector<int> myVector {2, 4, 6};
        const vector<int> alicesVector {1, 3, 7};
        const vector<int> expected {1, 2, 3, 4, 6, 7};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("vectors are different lengths") {
        const vector<int> myVector {2, 4, 6, 8};
        const vector<int> alicesVector {1, 7};
        const vector<int> expected {1, 2, 4, 6, 7, 8};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}