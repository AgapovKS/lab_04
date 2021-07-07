#include "svg.h"
#include <string>
#include <sstream>
#include <windows.h>

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" <<baseline<< "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "blue")
{
    cout << "<rect x='" << x << "' y='" <<y<< "' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"'></rect>";
}
void svg_end()
{
    cout << "</svg>\n";
}
double domashnee(int IMAGE_WIDTH, int BLOCK_WIDTH, size_t number_count)
{
    while (IMAGE_WIDTH<70 || IMAGE_WIDTH>800 ||IMAGE_WIDTH<(number_count/3.0*BLOCK_WIDTH))
    {
        if (IMAGE_WIDTH<70)
            cout<<"Vvedite shirinu zanovo, tk ona menshe 70. ";
        if (IMAGE_WIDTH>800)
            cout<<"Vvedite shirinu zanovo, tk ona bolshe 800. ";
        if (IMAGE_WIDTH<(number_count/3.0*BLOCK_WIDTH))
            cout<<"Vvedite shirinu zanovo, tk ona menshe treti kolichestva, umnozhennih na BLOCK_WIDTH. ";
        cout<<"Novoe znachenie shirini: ";
        cin>>IMAGE_WIDTH;
    }
    return IMAGE_WIDTH;
}


void show_histogram_svg(const vector<size_t>& bins, size_t number_count)
{
    const int IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const int BLOCK_WIDTH = 10;
    int IMAGE_WIDTH;
    cerr<<"Shirina stolbca=";
    cin>>IMAGE_WIDTH;
    domashnee(IMAGE_WIDTH, BLOCK_WIDTH, number_count);
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }

    svg_end();
}
