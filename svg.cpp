#include <math.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include "svg.h"

using namespace std;

void svg::svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    out << " <rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}

void svg::svg_text(double left, double baseline, string text)
{
    out << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg::svg_begin(double width, double height)
{
    out << "<?xml version='1.0' encoding='UTF-8'?>\n";
    out << "<svg ";
    out << "width='" << width << "' ";
    out << "height='" << height << "' ";
    out << "viewBox='0 0 " << width << " " << height << "' ";
    out << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg::svg_end() { out << "</svg>\n"; }

void svg::show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 22;
    const auto TEXT_BASELINE = 30;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double max_bin = bins[0];
    for (double bin : bins)
        if (bin > max_bin)
            max_bin = bin;

    for (size_t bin : bins)
    {
        size_t height = bin * BLOCK_WIDTH;
        if (max_bin * BLOCK_WIDTH > IMAGE_WIDTH - TEXT_WIDTH)
            height = (IMAGE_WIDTH - TEXT_WIDTH) * bin / max_bin;

        const double bin_width = height;
        svg_text(TEXT_LEFT + top, TEXT_BASELINE, to_string(bin));
        svg_rect(top + BLOCK_WIDTH, TEXT_WIDTH, BIN_HEIGHT, bin_width, "red", "#aaffaa");
        top += BIN_HEIGHT;
    }
    svg_end();
}
