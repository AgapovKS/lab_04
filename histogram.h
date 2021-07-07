#ifndef HISTOGRAM_H_INCLUDED
#include <vector>
#include <iomanip>
#include <iostream>
#define HISTOGRAM_H_INCLUDED
using namespace std;
struct Input
{
    vector<double> numbers;
    size_t bin_count;
};
void find_minmax(const vector<double>& numbers, double& min, double& max);

#endif // HISTOGRAM_H_INCLUDED

