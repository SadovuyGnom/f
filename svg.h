#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class svg
{
public:
    svg(string path) { out.open(path); }

    void svg_rect(double x, double y, double width, double height, string stroke = "blue", string fill = "#aaffaa");
    void svg_text(double left, double baseline, string text);
    void svg_begin(double width, double height);
    void svg_end();
    string make_info_text();

    void save_histogram_svg(const vector<size_t>& bins);

private:
    ofstream out;
    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = 300;
    const int TEXT_LEFT = 22;
    const int TEXT_BASELINE = 30;
    const int TEXT_WIDTH = 50;
    const int BIN_HEIGHT = 30;
    const int BLOCK_WIDTH = 10;
};

#endif // SVG_H_INCLUDED
