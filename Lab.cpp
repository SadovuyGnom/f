#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include "test.h"

using namespace std;

void show_histogram_text(vector<size_t> bins) //вывод гистограмы звездочками
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
        // проверить масштабирование(пересчитать height)

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
    //ввод данных

    cerr << "Run test? 0-No 1-Yes\n";
    bool run_test;
    cin >> run_test;

    if (run_test)
    {
        test();
        return 0;
    }

    size_t number_count;
    cerr << "Enter number count: \n";

    cin >> number_count;
    cerr << "Enter numbers: \n";

    const auto numbers = input_numbers(cin, number_count);

    size_t bin_count;
    cerr << "Enter bin count: \n";
    cin >> bin_count;

    //расчет данных

    const auto bins = make_histogram(numbers, bin_count);

    //вывод гистрограмы
    svg hist("hist.svg");
    hist.show_histogram_svg(bins);

    return 0;
}
