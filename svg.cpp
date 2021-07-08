#include "svg.h"
#include <string>
#include <sstream>
#include <windows.h>

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height <<"' stroke='"<<stroke<<"' fill='"<< fill<<"'/>";
}
void
svg_end()
{
    cout << "</svg>\n";
}

double domashnee (size_t number_count, double BLOCK_WIDTH,  istream& in)
{
    int IMAGE_WIDTH;
    cerr<<"IMAGE_WIDTH= ";
    in >> IMAGE_WIDTH;
    while (IMAGE_WIDTH<70 || IMAGE_WIDTH>800 ||IMAGE_WIDTH<(number_count/3.0*BLOCK_WIDTH))
    {
        if (IMAGE_WIDTH<70)
            cerr<<"Vvedite shirinu zanovo, tk ona menshe 70. ";
        if (IMAGE_WIDTH>800)
            cerr<<"Vvedite shirinu zanovo, tk ona bolshe 800. ";
        if (IMAGE_WIDTH<(number_count/3.0*BLOCK_WIDTH))
            cerr<<"Vvedite shirinu zanovo, tk ona menshe treti kolichestva, umnozhennih na BLOCK_WIDTH. ";
        cerr<<"Novoe znachenie shirini: ";
        in>>IMAGE_WIDTH;
        return IMAGE_WIDTH;
    }

}
string
make_info_text() {

stringstream buffer;

    DWORD info = GetVersion();
printf("n = %08x\n",info);
    printf("%u \n", info);
DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
DWORD mask1 = 0x0000ffff;
    DWORD platform = info >> 16;
if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask1;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")"<<" \n ";
    }

    DWORD size = MAX_COMPUTERNAME_LENGTH+1;
    char computer_name[size];
    GetComputerNameA(computer_name, &size);
    buffer << "Computer name: " << computer_name;

    return buffer.str();
}

void show_histogram_svg(const vector <size_t>& bins, double bin_count, size_t  number_count, string& stroke, string& fill)
{
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double IMAGE_WIDTH = domashnee(number_count, BLOCK_WIDTH,  cin);
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    size_t  max = 0;
    for (size_t count : bins)
    {
        if (count > max)
            max = count;
    }
    const bool scaling1 = (max*BLOCK_WIDTH) > (IMAGE_WIDTH-TEXT_WIDTH);
    if (scaling1)
    {
        const double scaling2 = (double)(IMAGE_WIDTH-TEXT_WIDTH) / (max*BLOCK_WIDTH);
        cerr << "scaling="<<scaling2;
        //cerr << "MAX_ASTERISK="<<MAX_ASTERISK;
        //cerr << "Max="<<max;
        for (size_t bin : bins)
        {
          //  cerr <<"bin="<<bin<<"\n";
            auto  height = (size_t)(bin * scaling2);
           // cerr << "height=" << height<<"\n";
            const double bin_width = BLOCK_WIDTH * height;
         //   cerr << "bin_width=" << bin_width<<"\n";
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "#blue");
            top += BIN_HEIGHT;
        }
    }
    else
    {
        for (size_t bin : bins)
        {
            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "blue");
            top += BIN_HEIGHT;
        }
    }
    svg_text(0, top + TEXT_BASELINE, make_info_text());
    svg_end();
}
