#include <KEUL/Utility.h>

int main()
{
    constexpr bool test_input = false;
    ke::FileReader rulesReader(test_input ? "../example_rules.txt" : "../data_rules.txt");
    ke::FileReader queueReader(test_input ? "../example_queue.txt" : "../data_queue.txt");

    auto raw_rules = rulesReader.readAll();
    auto raw_queue = queueReader.readAll();

    std::vector<std::pair<int, int>> rules;
    rules.reserve(raw_rules.size());
    std::vector<std::vector<int>> queues;
    queues.reserve(raw_queue.size());

    for (const auto &itr : raw_rules)
    {
        auto p = ke::splitStringToPair<std::pair>(itr, 0, '|');
        rules.push_back(std::make_pair(ke::fromString<int>(p.first).value(), ke::fromString<int>(p.second).value()));
    }

    for (const auto &itr : raw_queue)
    {
        auto q = ke::splitString<std::vector>(itr, ',');
        std::vector<int> vec;
        vec.reserve(q.size());
        for (const auto &snum : q)
        {
            vec.push_back(ke::fromString<int>(snum).value());
        }
        queues.push_back(vec);
    }

    std::set<int> present_numbers;
    std::list<int> order;

    ke::Random rnd;

    size_t changes_count = 1; // not 0 value
    while (changes_count != 0)
    {
        changes_count = 0;

        for (const auto &[first, second] : rules)
        {
            bool first_in = present_numbers.contains(first);
            bool second_in = present_numbers.contains(second);

            if (!first_in && !second_in)
            {
                present_numbers.emplace(second);
                present_numbers.emplace(second);

                order.push_back(first);
                order.push_back(second);

                changes_count += 2;
            }
            else if (first_in && !second_in)
            {
                present_numbers.emplace(second);

                for (auto itr = order.begin(); itr != order.end(); ++itr)
                {
                    if ((*itr) == first)
                    {
                        ++itr;
                        if (itr == order.end())
                            order.emplace_back(second);
                        else
                            order.emplace(itr, second);

                        changes_count++;
                        break;
                    }
                }
            }
            else if (!first_in && second_in)
            {
                present_numbers.emplace(first);

                for (auto itr = order.begin(); itr != order.end(); ++itr)
                {
                    if ((*itr) == second)
                    {
                        order.emplace(itr, first);
                        changes_count++;
                        break;
                    }
                }
            }
            else if (first_in && second_in)
            {
                std::list<int>::iterator first_pos = order.end();
                size_t first_index = 0;
                std::list<int>::iterator second_pos = order.end();
                size_t second_index = 0;

                for (auto itr = order.begin(); itr != order.end(); ++itr, first_index++)
                {
                    if ((*itr) == first)
                    {
                        first_pos = itr;
                        break;
                    }
                }
                for (auto itr = order.begin(); itr != order.end(); ++itr, second_index++)
                {
                    if ((*itr) == second)
                    {
                        second_pos = itr;
                        break;
                    }
                }

                KE_ASSERT(first_pos != order.end() && second_pos != order.end());

                if (first_index > second_index)
                {
                    order.erase(first_pos);
                    order.emplace(second_pos, first);
                    changes_count++;
                }
            }
        }

        std::println("Changes count = {}", changes_count);
    }

    order.unique();

    KE_LOGDEBUG("{}", queues.size());

    uint32_t sum = 0;
    for (const auto &qvec : queues)
    {
        bool status = true;

        auto oitr = order.begin();

        for (const auto i : qvec)
        {
            if (status)
            {
                while (*oitr != i)
                {
                    ++oitr;
                    if (oitr == order.end())
                    {
                        status = false;
                        break;
                    }
                }
            }
        }

        if (status)
        {
            KE_LOGDEBUG("{}", qvec);
            sum += qvec[qvec.size() / 2];
        }
    }

    std::println("{}", sum);

    for (const auto &itr : order)
    {
        std::print("{} ", itr);
    }
}