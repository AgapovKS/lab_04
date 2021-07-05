#ifndef HISTOGRAM_H_INCLUDED
#include <vector>
#include <iomanip>
#include <iostream>
#define HISTOGRAM_H_INCLUDED
using namespace std;
struct Input {  vector<double> numbers; size_t bin_count;};
void find_minmax(const vector<double>& numbers, double& min, double& max);
void show_histogram_svg(const vector<size_t>& bins, size_t number_count);
void svg_end();
void svg_begin(double width, double height);
void svg_rect(double x, double y, double width, double height,string stroke, string fill);
void domashnee(int IMAGE_WIDTH, int BLOCK_WIDTH, size_t number_count);
void svg_text(double left, double baseline, string text);
#endif // HISTOGRAM_H_INCLUDED

