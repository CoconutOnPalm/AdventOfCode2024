#include <KEUL/Utility.h>


bool inBounds(int i, int j, const std::vector<std::string>& data)
{
    return i >= 0 && i < data.size() && j >= 0 && j < data[0].size();
}


struct GuardPosition
{
    GuardPosition() : i(0), j(0) {}
    GuardPosition(int i, int j) : i(i), j(j) {}

    int i, j;

    // returns ' ' on "out of bounds"
    char getNext(int direction, const std::vector<std::string>& map)
    {
        switch (direction)
        {
        case 0: // up
            if (!inBounds(i - 1, j, map))
                return ' ';
            return map[i - 1][j];
            break;
        case 1: // right
            if (!inBounds(i, j + 1, map))
                return ' ';
            return map[i][j + 1];
            break;
        case 2: // down
            if (!inBounds(i + 1, j, map))
                return ' ';
            return map[i + 1][j];
            break;
        case 3: // left
            if (!inBounds(i, j - 1, map))
                return ' ';
            return map[i][j - 1];
            break;
        default:
            KE_LOGERROR("Invalid direction value: direction={}", direction);
            KE_ASSERT(false);
            break;
        }
    }
};



void rotate(int& direction)
{
    direction++;
    direction = direction % 4;
}


int main(int argc, char** argv)
{
    bool test_input = true;

    if (argc == 2)
        test_input = ke::fromString<int>(argv[1]).has_value() ? ke::fromString<int>(argv[1]).value() : true;

    ke::FileReader reader(test_input ? "../example.txt" : "../data.txt");

    auto data = reader.readAll();

    KE_ASSERT(data.size() > 0);

    GuardPosition gpos;

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            if (data[i][j] == '^')
            {
                gpos = {i, j};
            }
        }
    }

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left
    int direction = 0;

    while (true)
    {
        char next = gpos.getNext(direction, data);
        data[gpos.i][gpos.j] = 'X';
        
        if (next == ' ')
            break;

        if (next == '#')
        {
            rotate(direction);
        }
        else if (next == '.' || next == 'X')
        {
            switch (direction)
            {
            case 0: // up
                gpos.i--;
                break;
            case 1: // right
                gpos.j++;
                break;
            case 2: // down
                gpos.i++;
                break;
            case 3: // left
                gpos.j--;
                break;
            default:
                KE_LOGERROR("Invalid direction value: direction={}", direction);
                KE_ASSERT(false);
                break;
            }
        }
    }

    size_t count = 0;
    for (int i = 0; i < data.size(); i++)
    {
        count += std::count(data[i].begin(), data[i].end(), 'X');
    }

    std::println("{}", count);
    
}