#include <KEUL/Utility.h>
#include <queue>


template<typename T>
static constexpr inline T pow(T x, uint32_t p) 
{
    T result = 1;

    while (p) {
        if (p & 0x1) {
            result *= x;
        }
        x *= x;
        p >>= 1;
    }

    return result;
}


std::string base10_to_base3(int n)
{
    if (n == 0)
        return "0";

    std::string result;
    while (n != 0)
    {
        result += (n % 3) + '0';
        n /= 3;
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}



int main(int argc, char** argv)
{
    bool test_input = false;
    if (argc == 2)
    {
        auto res = ke::fromString<bool>(argv[1]);
        if (res.has_value()) test_input = res.value();
    }

    ke::FileReader reader(test_input ? "../example.txt" : "../data.txt");

    auto raw_data = reader.readAll();
    std::vector<std::pair<uint64_t, std::vector<uint64_t>>> data; data.reserve(data.size());
    for (const auto& itr : raw_data)
    {
        uint64_t left;
        std::vector<uint64_t> right;
        std::vector<std::string> right_raw;
        auto p = ke::splitStringToPair<std::pair>(itr, 0, ':');
        
        left = ke::fromString<uint64_t>(p.first).value();
        right_raw = ke::splitString<std::vector>(p.second, ' ');
        right.reserve(right_raw.size());

        for (const auto& str : right_raw)
        {
            right.push_back(ke::fromString<uint64_t>(str).value());
        }
 
        data.push_back({left, right});
    }


    uint64_t sum = 0;

    for (const auto& [expected, values] : data)
    {
        bool correct = false;

        std::string operations;
        uint64_t queue_length = pow(3, values.size() - 1);
        for (uint64_t gen = 0; gen < queue_length; gen++)
        {
            operations = base10_to_base3(gen);
            uint64_t num = values[0];

            // std::println("gen={}", gen);
            // std::println("operations={}", operations);
            // std::println("operations.size()={}", operations.size());
            // std::println("values.size()={}", values.size());

            operations = std::string(values.size() - 1 - operations.size(), '0') + operations;

            KE_ASSERT(values.size() - 1 == operations.size());

            for (int i = 1, opindex = 0; i < values.size(); i++, opindex++)
            {
                if (operations[opindex] == '0') // +
                {
                    num += values[i];
                }
                else if (operations[opindex] == '1') // *
                {
                    num *= values[i];
                }
                else if (operations[opindex] == '2') // ||
                {
                    num = ke::fromString<uint64_t>(ke::toString(num) + ke::toString(values[i])).value();
                }
                else
                {
                    KE_LOGERROR("invalid operation: {}", (int)operations[opindex]);
                    std::abort();
                }
            }

            if (num == expected)
            {
                correct = true;
                break;
            }
        }

        if (correct)
            sum += expected;
    }

    std::println("{}", sum);

}