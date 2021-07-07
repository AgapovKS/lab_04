#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <curl/curl.h>
#include "histogram.h"

#include "svg.h"

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
using namespace std;

vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
Input
read_input(istream& in, bool promt) {
    Input data;
    if(promt)
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if(promt)
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if(promt)
    cerr << "Enter bin count: ";
    in >> data.bin_count;
    return data;
}
vector <size_t> make_histogram(const Input& data)
{
    double min;
    double max;
    vector <size_t> result(data.bin_count);
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
void show_histogram_text(vector <size_t> bins, const size_t MAX_ASTERISK)
{
    size_t bin_count = bins.size();
    size_t  Max = bins[0];
    for (size_t  j=1; j<bin_count; j++)
    {
        if (bins[j]>Max)
            Max = bins[j];
    }
    for (size_t  j=0; j<bin_count; j++)
    {
        if(bins[j]>=100)
            cout<<bins[j];
        if (bins[j]<10)
            cout <<"  "<< bins[j];
        else if (bins[j]<100)
            cout<< " "<< bins[j] ;
        cout << "|";
        if(Max>MAX_ASTERISK)
        {
            size_t  height = MAX_ASTERISK * (static_cast<double>(bins[j]) / Max);
            for (size_t  a=0; a<height; a++)
            {
                cout << "*";
            }
        }
        else
            for(size_t a=0; a<bins[j]; a++)
                cout << "*";
        cout << endl;
    }
}
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
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
                 cerr << "total time spent downloading the file:" << curtime << "\n";
                }
            }
        }

    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{cout<<endl;
const char* name = "Commander Shepard";
int year = 2154;
printf("%s was born in %d.\n", name, year);
cout<<endl;
    Input input;
    size_t  number_count;
    if (argc > 1)
    {
        input = download(argv[1]);
    }
     else
    {
        input = read_input(cin, true);
    }
    size_t  bin_count;
    const auto bins = make_histogram(input);
    string stroke;
    string fill;
    show_histogram_svg(bins, bin_count, number_count,stroke,fill);
    return 0;
}
