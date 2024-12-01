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

    std::map<int, int> numcount;

    int max_elem = *std::max_element(rdata.begin(), rdata.end());
    for (int i = 0; i < max_elem; i++)
    {
        int count = std::count(rdata.begin(), rdata.end(), i);
        if (count > 0)
            numcount[i] = count;
    }

    uint32_t similarity_score = 0;
    for (const auto itr : ldata)
    {
        similarity_score += itr * numcount[itr];
    }

    std::println("{}", similarity_score);

}