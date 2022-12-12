#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::ifstream input;
    input.open("input", std::ios::in);

    if (input.is_open())
    {
        char ch;
        std::vector<char> last_4;
        int index = 0;
        std::map<char, int> char_counter;
        while (input.peek() != EOF && input.peek() != '\n')
        {
            input.get(ch);
            char_counter[ch] += 1;
            last_4.push_back(ch);
            if (index >= 4)
            {
                bool unique = true;
                char_counter[last_4[0]] -= 1;
                last_4.erase(last_4.begin());
                for (const auto &c : last_4)
                {
                    if (char_counter[c] != 1)
                    {
                        unique = false;
                        break;
                    }
                }
                if (unique)
                {
                    std::cout << "Part 1: " << index + 1 << std::endl;
                    break;
                }
            }
            index += 1;
        }
        input.close();
    }
    return 0;
}
