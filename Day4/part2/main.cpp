#include <KEUL/Utility.h>



class XMASMatrix
{
public:

    XMASMatrix(const std::array<std::string, 3>& rows)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                mat[3 * i + j] = rows[i][j];
            }
        }
    }

    void rotate()
    {
        std::array<char, 3> buffer;
        buffer[0] = mat[0]; buffer[1] = mat[1]; buffer[2] = mat[2];

        mat[0] = mat[2]; mat[1] = mat[5]; mat[2] = mat[8];
        mat[5] = mat[7]; mat[8] = mat[6];
        mat[7] = mat[3];
        mat[6] = buffer[0]; mat[3] = buffer[1];
    }


    bool isXMAS()
    {
        std::string diag1{mat[0], mat[4], mat[8]}; // '\'
        std::string diag2{mat[2], mat[4], mat[6]}; // '/'

        return line_XMAS(diag1) && line_XMAS(diag2);
    }


private:

    bool line_XMAS(const std::string& line)
    {
        return line == "MAS" || line == "SAM";
    }

    std::array<char, 9> mat;
    // | 0 1 2 |
    // | 3 4 5 |
    // | 6 7 8 |
};



bool isXMAS(const std::string& row1, const std::string& row2, const std::string& row3)
{
    XMASMatrix mat({row1, row2, row3});

    bool status = false;
    for (int i = 0; i < 4; i++)
    {
        if (mat.isXMAS())
        {
            status = true;
            break;
        }

        mat.rotate();
    }

    return status;
}


int main()
{
    constexpr bool test_input = false;
    constexpr int XMAS_size = 3; // 3 width and 3 height

    ke::FileReader reader(test_input ? "../example.txt" : "../data.txt");

    if (!reader.isOpen())
        return 1;

    auto data = reader.readAll();
    auto data_cpy = data;

    KE_ASSERT(data.size() > 0);

    size_t count = 0;


    for (int i = 0; i < data.size() - XMAS_size + 1; i++)
    {
        for (int j = 0; j < data[0].size() - XMAS_size + 1; j++)
        {
            count += isXMAS(data[i].substr(j, XMAS_size), data[i + 1].substr(j, XMAS_size), data[i + 2].substr(j, XMAS_size));
        }
    }
    

    // for (const auto& itr : data_cpy)
    // {
    //     std::println("{}", itr);
    // }
    std::println("{}", count);
}