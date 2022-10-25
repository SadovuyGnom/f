#include "svg.h"

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

string svg::make_info_text()
{
    DWORD WINAPI GetVersion(void);
    stringstream buffer;
    const auto R = GetVersion();

    printf("n = %lu\n", R);
    printf("n = %lx\n", R);

    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = R & mask;
    printf("ver = %lu\n", version);

    DWORD platform = R >> 16;
    printf("ver2 = %lu\n", platform);

    DWORD mask2 = 0b00000000'11111111;
    DWORD version_major = version & mask2;
    printf("version_major = %lu\n", version_major);

    DWORD version_minor = version >> 8;
    printf("version_minor = %lu\n", version_minor);

    DWORD build = 0;

    if ((R & 0x80000000) == 0)
    {
        build = platform;
        printf("build = %lu\n", build);

    }
    buffer << "Windows" << " " << "v" << " " << version_major << "." << version_minor << " " << "(build" << " " << build << ")" << endl;
    char storage[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD  bufCharCount = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(storage, &bufCharCount);
    buffer << "Computer name:" << " " << storage;
    return buffer.str();
}

void svg::save_histogram_svg(const vector<size_t>& bins)
{
    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    size_t max_bin = bins[0];
    for (size_t bin : bins)
        if (bin > max_bin)
            max_bin = bin;

    for (size_t bin : bins)
    {
        size_t height = bin * BLOCK_WIDTH;
        if (max_bin * BLOCK_WIDTH > (size_t)IMAGE_WIDTH - TEXT_WIDTH)
            height = ((size_t)IMAGE_WIDTH - TEXT_WIDTH) * bin / max_bin;

        const double bin_width = (double)height;
        svg_text(TEXT_LEFT + top, TEXT_BASELINE, to_string(bin));
        svg_rect(top + BLOCK_WIDTH, TEXT_WIDTH, BIN_HEIGHT, bin_width, "red", "#aaffaa");
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, IMAGE_HEIGHT, make_info_text());
    svg_end();
}
