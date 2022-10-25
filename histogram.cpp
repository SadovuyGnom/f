#include "histogram.h"

void find_minmax(const vector<double>& numbers, double& min, double& max) //поиск минимального и макс чисел
{
    if (numbers.size() == 0)
        return;

    min = numbers[0];
    max = numbers[0];
    for (double number : numbers)
    {
        if (number < min)
            min = number;

        if (number > max)
            max = number;
    }
}

vector<double> input_numbers(istream& in, size_t cnt)
{
    vector<double> result(cnt);
    for (size_t i = 0; i < cnt; i++)
        in >> result[i];

    return result;
}

vector<size_t> make_histogram(Input input) //создание гистограмы
{
    double min, max;
    find_minmax(input.numbers, min, max);
    vector<size_t> bins(input.bin_count, 0);
    double bin_size = (max - min) / input.bin_count;

    for (auto number : input.numbers)
    {
        bool found = false;
        for (size_t j = 0; j < (input.bin_count - 1) && !found; j++)
        {
            auto low = min + j * bin_size;
            auto hight = min + (j + 1) * bin_size;

            if ((low <= number) && (number < hight))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
            bins[input.bin_count - 1]++;
    }
    return bins;
}

void show_histogram_text(vector<size_t> bins) //вывод гистограмы звездочками
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4;
    size_t max_bin = bins[0];
    for (size_t bin : bins)
        if (bin > max_bin)
            max_bin = bin;

    for (size_t bin : bins)
    {
        size_t height = bin;
        // проверить масштабирование(пересчитать height)

        if (max_bin > MAX_ASTERISK)
            height = MAX_ASTERISK * (bin / max_bin);

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