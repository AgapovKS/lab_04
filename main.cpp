#include <iostream>
#include <vector>
#include <iomanip>
#include "histogram.h"
#include "svg.h"
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
    if (prompt)
        cerr << "Enter bin count: ";
    in >> data.bin_count;
    return data;

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
vector<size_t> make_histogram(const Input& data)
{
    size_t number_count=data.numbers.size();
    vector<size_t> result(data.bin_count);

    double min, max;
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        result[bin]++;
    }
    return result;
}
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{


    auto data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

    buffer->write(reinterpret_cast<const char*>(items), data_size);

    return data_size;
}

Input
download(const string& address) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if(res)
            {
                cout << curl_easy_strerror(res);
                exit(1);
            }
            else
            {
                double curtime = 0;
                curtime= curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &curtime);
                if(!res)
                {
                 cout << "total time spent downloading the file:" << curtime << "\n";
                }
            }
        }

    return read_input(buffer, false);
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
size_t number_count;
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, number_count);
    return 0;
}

