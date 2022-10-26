#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"
#include "svg.h"


using namespace std;

void show_histogram_text(vector<size_t> bins) //����� ���������� �����������
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    size_t max_bin = bins[0];
    for (double bin : bins)
        if (bin > max_bin)
            max_bin = bin;

    for (double bin : bins)
    {
        size_t height = bin;
        // ��������� ���������������(����������� height)

        if (max_bin > MAX_ASTERISK)
            height = MAX_ASTERISK * (static_cast<double> (bin) / max_bin);

        if (bin < 100)
            cout << " ";

        if (bin < 10)
            cout << " ";

        cout << bin << "|";
        for (size_t i = 0; i < height; i++)
            cout << "*";

        cout << endl;
    }
}

int main()
{
    //���� ������

    size_t number_count;
    cerr << "Enter number count: \n";

    cin >> number_count;
    cerr << "Enter numbers: \n";

    const auto numbers = input_numbers(cin, number_count);

    size_t bin_count;
    cerr << "Enter bin count: \n";
    cin >> bin_count;

    //������ ������

    const auto bins = make_histogram(numbers, bin_count);

    //����� �����������
    svg hist("hist.svg");
    hist.show_histogram_svg(bins);

    return 0;
}
