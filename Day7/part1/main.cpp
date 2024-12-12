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

        std::queue<bool> operations;
        uint64_t queue_length = pow(2, values.size() - 1);
        for (uint64_t gen = 0; gen < queue_length; gen++)
        {
            for (uint64_t i = 0; i < values.size() - 1; i++)
            {
                operations.push(gen & (pow(2, i)));
            }

            uint64_t var = values[0];
            for (int i = 1; i < values.size(); i++)
            {
                bool op = operations.front();
                operations.pop();

                if (op)
                    var += values[i];
                else
                    var *= values[i];
            }

            KE_ASSERT(operations.empty());

            if (var == expected)
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