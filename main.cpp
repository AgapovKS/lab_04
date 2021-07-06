#include <iostream>
#include <vector>
#include <iomanip>
#include "histogram.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <math.h>

using namespace std;
vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
Input
read_input(istream& in, bool prompt)
{
    Input data;

    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    return data;
    if (prompt)
        cerr << "Enter bin count: ";
    in >> data.bin_count;

}
void show_histogram_text(const vector<size_t>& bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


    size_t bin_count=bins.size();
    for (size_t i=0; i<bin_count; i++)
    {
        if (bins[i]<100)
            cout<<" ";
        if (bins[i]<10)
            cout<<" ";
        cout<<bins[i]<<"|";
        for (size_t j=0; j<bins[i]; j++)
            cout<<"*";
        cout<<endl;
    }
}
vector<size_t> make_histogram(Input data)
{
    size_t number_count=data.numbers.size();
    vector<size_t> bins(data.bin_count);
    cerr<< "cerr "<<data.bin_count;

    double min, max;
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
}
int main(int argc, char* argv[])
{
    Input input;
    if(argc>1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin,true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins, number_count);
    return 0;
}

