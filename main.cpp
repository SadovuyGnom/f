#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
using namespace std;


Input read_input(istream& in, bool prompt)
{
    Input data;

    if (prompt)
        cerr << "Enter number count: \n";
    size_t number_count;
    in >> number_count;

    if (prompt)
        cerr << "Enter numbers: \n";
    data.numbers = input_numbers(in, number_count);

    if (prompt)
        cerr << "Enter bin count: \n";
    in >> data.bin_count;

    return data;
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    size_t data_size = item_size * item_count;
    buffer->write((char*)items, data_size);
    return data_size;
}

Input download(const string& address, bool flag)
{
    long L = 0;
    stringstream buffer;
    CURL* curl = curl_easy_init();
    if (curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        if (flag)
            curl_easy_setopt(curl, CURLOPT_VERBOSE, L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cerr << curl_easy_strerror(res) << endl;
            exit(1);
        }
        curl_easy_cleanup(curl);
    }

    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);

    //ввод данных
    Input input;

    bool flag = false;
    int adress = 0;
    string file("hist.svg");

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-verbose"))
            flag = true;
        else
            if (!strncmp(argv[i], "-", 1))
            {
                cerr << "-verbose in work" << endl;
               // cin >> adress;
                return 0;
            }
        if (!strncmp(argv[i], "http", 4))
            adress = i;
        if (strstr(argv[i], ".svg") != NULL)
            file = string(argv[i]);
    }

    if (!adress)
        input = read_input(cin, true);
    else
        input = download(argv[adress], flag);

    //расчет данных
    const auto bins = make_histogram(input);

    //вывод гистрограмы в файл
    svg hist(file);
    hist.save_histogram_svg(bins);

   // cin >> adress;

    return 0;
}
