#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;
using namespace std;
void svg_begin(double width, double height);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,string stroke, string fill);
void
svg_end();
double domashnee (size_t number_count, double BLOCK_WIDTH, istream& in);
void show_histogram_svg(const vector <size_t>& bins, double bin_count, size_t  number_count, string& stroke, string& fill);
#endif // SVG_H_INCLUDED
