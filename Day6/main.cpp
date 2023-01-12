#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

int uniq_pos(std::ifstream &file, const int uniques)
{
    char ch;
    std::vector<char> char_tracker;
    int index = 0;
    std::map<char, int> char_counter;
    while (file.peek() != EOF && file.peek() != '\n')
    {
        file.get(ch);
        char_counter[ch] += 1;
        char_tracker.push_back(ch);
        if (index >= uniques)
        {
            bool unique = true;
            char_counter[char_tracker[0]] -= 1;
            char_tracker.erase(char_tracker.begin());
            for (const auto &c : char_tracker)
            {
                if (char_counter[c] != 1)
                {
                    unique = false;
                    break;
                }
            }
            if (unique)
            {
                return index + 1;
            }
        }
        index += 1;
    }

    return -1;
}

int main()
{
    std::ifstream input;
    input.open("input", std::ios::in);

    if (input.is_open())
    {
        std::cout << "Part 1: " << uniq_pos(input, 4) << std::endl;
        input.seekg(0);
        std::cout << "Part 2: " << uniq_pos(input, 14) << std::endl;
    }
    input.close();

    return 0;
}
