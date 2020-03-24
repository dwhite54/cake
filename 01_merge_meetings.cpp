#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

class Meeting
{
private:
    // number of 30 min blocks past 9:00 am
    unsigned int startTime_;
    unsigned int endTime_;

public:
    Meeting() :
        startTime_(0),
        endTime_(0)
    {
    }

    Meeting(unsigned int startTime, unsigned int endTime) :
        startTime_(startTime),
        endTime_(endTime)
    {
    }

    unsigned int getStartTime() const
    {
        return startTime_;
    }

    void setStartTime(unsigned int startTime)
    {
        startTime_ = startTime;
    }

    unsigned int getEndTime() const
    {
        return endTime_;
    }

    void setEndTime(unsigned int endTime)
    {
        endTime_ = endTime;
    }

    bool operator == (const Meeting& other) const
    {
        return
            startTime_ == other.startTime_
            && endTime_ == other.endTime_;
    }
};

vector<Meeting> mergeRanges(const vector<Meeting>& meetings)
{
    vector<Meeting> rv(meetings.size());
    vector<Meeting> merged;
    for (unsigned long i = 0; i < meetings.size(); i++) {
        rv[i] = meetings[i];
    }
    
    // merge meeting ranges
    std::sort(rv.begin(), rv.end(), [ ]( const auto& a, const auto& b)
        {
           return a.getStartTime() == b.getStartTime() ? 
                     a.getEndTime() <= b.getEndTime(): 
                     a.getStartTime() < b.getStartTime();
        });
        
    unsigned int best_start = 0;
    unsigned int best_end = 0;
    bool merging = false;
    for (unsigned long i = 0; i < rv.size() - 1; i++) {
        printf("found (%u,%u)\n", rv[i].getStartTime(), rv[i].getEndTime());
        best_end = max(rv[i].getEndTime(), best_end);
        if (best_end >= rv[i+1].getStartTime()) { // overlapping
            if (!merging) { // beginning a new merge
                best_start = rv[i].getStartTime();
                merging = true;
            } // else, continuing previous merge (do nothing)
        } else { // non-overlapping
            if (merging) { // ending previous
                merged.emplace_back(best_start, best_end);
            } else { // no overlaps at all, just pass through
                merged.emplace_back(rv[i].getStartTime(), rv[i].getEndTime());
            }
            //printf("added (%u,%u)\n", merged[i].getStartTime(), merged[i].getEndTime());
            merging = false;
            best_end = 0;
        }
    }
    
    //check for final meeting
    if (merging) {
        best_end = max(rv[rv.size()-1].getEndTime(), best_end);
        merged.emplace_back(best_start, best_end);
    } else { // didn't overlap, pass through
        merged.emplace_back(rv[rv.size()-1].getStartTime(), rv[rv.size()-1].getEndTime());
    }
    //printf("(last) added (%u,%u)\n", merged[merged.size()-1].getStartTime(), merged[merged.size()-1].getEndTime());

    return merged;
}

// tests

const lest::test tests[] = {
    {CASE("meetings overlap") {
        const auto meetings = vector<Meeting> {Meeting(1, 3), Meeting(2, 4)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 4)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings touch") {
        const auto meetings = vector<Meeting> {Meeting(5, 6), Meeting(6, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(5, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meeting contains other meeting") {
        const auto meetings = vector<Meeting> {Meeting(1, 8), Meeting(2, 5)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings stay separate") {
        const auto meetings = vector<Meeting> {Meeting(1, 3), Meeting(4, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 3), Meeting(4, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("multiple merged meetings") {
        const auto meetings = vector<Meeting> {Meeting(1, 4), Meeting(2, 5), Meeting(5, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings not sorted") {
        const auto meetings = vector<Meeting> {Meeting(5, 8), Meeting(1, 4), Meeting(6, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 4), Meeting(5, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("one long meeting contains smaller meetings") {
        const auto meetings = vector<Meeting> {Meeting(1, 10), Meeting(2, 5), Meeting(6, 8),
            Meeting(9, 10), Meeting(10, 12)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 12)};
        EXPECT(actual == expected);
    }},

    {CASE("sample input") {
        const auto meetings = vector<Meeting> {Meeting(0, 1), Meeting(3, 5), Meeting(4, 8),
            Meeting(10, 12), Meeting(9, 10)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(0, 1), Meeting(3, 8), Meeting(9, 12)};
        EXPECT(actual == expected);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}