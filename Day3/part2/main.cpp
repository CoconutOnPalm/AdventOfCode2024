#include <KEUL/Utility.h>
#include <regex>


int main()
{
    constexpr bool test_input = false;
    ke::FileReader reader(test_input ? "../example.txt" : "../data.txt");

    if (!reader.isOpen())
        return 1;

    auto raw_data = reader.readAll();

    std::regex word_regex("(mul\\([0-9]+\\,[0-9]+\\))|(don't\\(\\))|(do\\(\\))");

    bool enabled = true;
    uint64_t sum = 0;
    for (const auto& str : raw_data)
    {
        auto match_begin = std::sregex_iterator(str.begin(), str.end(), word_regex);
        auto match_end = std::sregex_iterator();

        for (std::sregex_iterator i = match_begin; i != match_end; ++i)
        {
            std::smatch match = *i;
            std::string bracket(match.str().substr(3, match.str().size() - 3));

            std::regex do_regex("do\\(\\)");
            std::regex dont_regex("don\'t\\(\\)");

            if (std::regex_search(match.str(), do_regex))
            {
                enabled = true;
                continue;
            }
            else if (std::regex_search(match.str(), dont_regex))
            {
                enabled = false;
                continue;
            }
            
            if (!enabled)
                continue;

            auto split = ke::splitString<std::vector>(bracket, "(", ")", ",");

            int a = ke::fromString<int>(split[0]).value();
            int b = ke::fromString<int>(split[1]).value();
            
            sum += a * b;
        }
    }

    std::println("{}", sum);
}