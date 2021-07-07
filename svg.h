#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

void show_histogram_svg(const vector<size_t>& bins, size_t number_count);
void svg_end();
void svg_begin(double width, double height);
void svg_rect(double x, double y, double width, double height,string stroke, string fill);
void domashnee(int IMAGE_WIDTH, int BLOCK_WIDTH, size_t number_count);
void svg_text(double left, double baseline, string text);
#endif // SVG_H_INCLUDED
