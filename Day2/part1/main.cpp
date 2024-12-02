#include <KEUL/Utility.h>

int main()
{
    constexpr bool test_input = false;
    ke::FileReader reader(test_input ? "../example.txt" : "../data.txt");

    if (!reader.isOpen())
        return 1;

    auto reports = reader.readAll();

    uint32_t correct_count = 0;
    for (const auto& rep : reports)
    {
        auto raw_row = ke::splitString<std::vector>(rep, ' ');
        std::vector<int> row;
        row.reserve(raw_row.size());

        for (const auto& i : raw_row)
        {
            row.push_back(ke::fromString<int>(i).value());
        }

        KE_ASSERT(row.size() > 1);

        if (row[0] == row[1])
            continue;

        bool asc = true;
        if (row[0] - row[1] > 0)
            asc = false;
        
        bool correct = true;
        for (int i = 0; i < row.size() - 1; i++)
        {
            int diff = row[i] - row[i + 1];
            if (!ke::InRange(ke::ClosedRange(1, 3), std::abs(diff)))
            {
                correct = false;
                break;
            }

            if (!((asc && diff < 0) || (!asc && diff > 0)))
            {
                correct = false;
                break;
            }
        }

        if (correct)
            correct_count++;
    }

    std::println("{}", correct_count);
}