#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

class svg
{
public:
    svg(string path)
    {
        out.open(path);
    }

    void svg_rect(double x, double y, double width, double height, string stroke = "blue", string fill = "#aaffaa");
    void svg_text(double left, double baseline, string text);
    void svg_begin(double width, double height);
    void svg_end();

    void show_histogram_svg(const vector<size_t>& bins);

private:
    ofstream out;
};

#endif // SVG_H_INCLUDED
