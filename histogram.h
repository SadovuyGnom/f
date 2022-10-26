#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>
#include <iostream>

using namespace std;


void find_minmax(const vector<double>& numbers, double& min, double& max);

vector<double> input_numbers(istream& in, size_t cnt);
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count);

#endif // HISTOGRAM_H_INCLUDED
