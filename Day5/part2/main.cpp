#include <KEUL/Utility.h>

class Page
{
public:
    Page() = default;

    void addPredecessor(int p)
    {
        m_predecessors.emplace(p);
    }

    void addSuccessor(int s)
    {
        m_successors.emplace(s);
    }

    bool isPredecessor(int n) const { return m_predecessors.contains(n); }
    bool isSuccessor(int n) const { return m_successors.contains(n); }

private:
    std::set<int> m_predecessors;
    std::set<int> m_successors;
};

bool isInGoodOrder(const std::vector<int> &queue, std::map<int, Page> &dependencies)
{
    bool status = true;
    for (int i = 0; i < queue.size(); i++)
    {
        // predecessor check
        for (int j = 0; j < i; j++)
        {
            if (dependencies[queue[i]].isSuccessor(queue[j]))
            {
                status = false;
                break;
            }
        }

        // successor check
        for (int j = i + 1; j < queue.size(); j++)
        {
            if (dependencies[queue[i]].isPredecessor(queue[j]))
            {
                status = false;
                break;
            }
        }
    }

    return status;
}


int main(int argc, char** argv)
{
    bool test_input = true;

    if (argc == 2)
    {
        auto arg = ke::fromString<bool>(argv[1]);
        if (arg.has_value())
            test_input = *arg;
    }

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

    std::map<int, Page> dependencies;
    std::random_device rd;
    std::mt19937 g(rd());

    for (const auto &[first, second] : rules)
    {
        dependencies[first].addSuccessor(second);
        dependencies[second].addPredecessor(first);
    }

    uint32_t sum = 0;
    uint32_t count = 0;
    for (auto &queue : queues)
    {
        bool status = isInGoodOrder(queue, dependencies);

        if (!status)
        {
            std::map<int, int> predecessor_count;

            for (int i = 0; i < queue.size(); i++)
            {
                uint32_t pcount = 0;
                for (int j = 0; j < queue.size(); j++)
                {
                    if (queue[i] == queue[j])
                        continue;

                    if (dependencies[queue[j]].isPredecessor(queue[i]))
                    {
                        pcount++;
                    }
                }

                predecessor_count[queue[i]] = pcount;
            }

            std::sort(queue.begin(), queue.end(), [&](const int a, const int b){ return predecessor_count[a] < predecessor_count[b]; });
            sum += queue[queue.size() / 2];
        }
        std::println("iteration: {}", count);
        count++;
    }

    std::println("{}", sum);
}