#include <KEUL/Utility.h>
#include <cmath>
#include <print>

int main()
{
    constexpr bool test_input = false;

    ke::FileReader inputReader;

    if (test_input)
    {
        if (!inputReader.open("../example.txt"))
            KE_LOGERROR("Failed to open input");
    }
    else
    {
        if (!inputReader.open("../data.txt"))
            KE_LOGERROR("Failed to open input");    
    }

    auto raw_data = inputReader.readAll();

    std::vector<int> ldata, rdata;
    ldata.reserve(raw_data.size());
    rdata.reserve(raw_data.size());

    for (const auto& itr : raw_data)
    {
        auto pair = ke::splitString<std::vector>(itr, ' ');
        KE_ASSERT(pair.size() == 2);

        ldata.push_back(ke::fromString<uint32_t>(pair[0]).value());
        rdata.push_back(ke::fromString<uint32_t>(pair[1]).value());
    }

    std::sort(ldata.begin(), ldata.end());
    std::sort(rdata.begin(), rdata.end());

    size_t total_distance = 0;
    for (size_t i = 0; i < ldata.size(); i++)
    {
        total_distance += std::abs(ldata[i] - rdata[i]);
    }

    std::println("{}", total_distance);
}