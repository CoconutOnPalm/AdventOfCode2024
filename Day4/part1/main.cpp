#include <KEUL/Utility.h>


bool isXMAS(std::string_view str)
{
    return str == "XMAS" || str == "SAMX";
}


int main()
{
    constexpr bool test_input = false;
    constexpr int XMAS_size = 4;

    ke::FileReader reader(test_input ? "../example.txt" : "../data.txt");

    if (!reader.isOpen())
        return 1;

    auto data = reader.readAll();
    auto data_cpy = data;

    KE_ASSERT(data.size() > 0);

    size_t count = 0;

    // --
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j <= data[i].size() - XMAS_size; j++)
        {
            if (isXMAS(data[i].substr(j, XMAS_size)))
            {
                data_cpy[i + 0][j + 0] = '#';
                data_cpy[i + 0][j + 1] = '#';
                data_cpy[i + 0][j + 2] = '#';
                data_cpy[i + 0][j + 3] = '#';
                count++;
            }
        }
    }

    // |
    for (int i = 0; i <= data.size() - XMAS_size; i++)
    {
        for (int j = 0; j < data[0].size(); j++)
        {
            if (isXMAS(std::string{data[i + 0][j], data[i + 1][j], data[i + 2][j], data[i + 3][j]}))
            {
                data_cpy[i + 0][j + 0] = '#';
                data_cpy[i + 1][j + 0] = '#';
                data_cpy[i + 2][j + 0] = '#';
                data_cpy[i + 3][j + 0] = '#';
                count++;
            }
        }
    }

    // /
    for (int i = 3; i < data.size(); i++)
    {
        for (int j = 0; j <= data[i].size() - XMAS_size; j++)
        {
            if (isXMAS(std::string{data[i - 0][j + 0], data[i - 1][j + 1], data[i - 2][j + 2], data[i - 3][j + 3]}))
            {
                data_cpy[i - 0][j + 0] = '#';
                data_cpy[i - 1][j + 1] = '#';
                data_cpy[i - 2][j + 2] = '#';
                data_cpy[i - 3][j + 3] = '#';
                count++;
            }
        }
    }

    // '\'
    for (int i = 0; i <= data.size() - XMAS_size; i++)
    {
        for (int j = 0; j <= data[i].size() - XMAS_size; j++)
        {
            if (isXMAS(std::string{data[i + 0][j + 0], data[i + 1][j + 1], data[i + 2][j + 2], data[i + 3][j + 3]}))
            {
                data_cpy[i + 0][j + 0] = '#';
                data_cpy[i + 1][j + 1] = '#';
                data_cpy[i + 2][j + 2] = '#';
                data_cpy[i + 3][j + 3] = '#';
                count++;
            }
        }
    }

    // for (const auto& itr : data_cpy)
    // {
    //     std::println("{}", itr);
    // }
    std::println("{}", count);
}