#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <node.hpp>

int main(int argc, char **argv)
{
    std::ifstream input;
    std::string line;
    input.open("input", std::ios::in);
    if (input.is_open())
    {
        Filesystem::Node *root = new Filesystem::Node("/", Filesystem::Type::DIRECTORY);
        Filesystem::Node *open_node = root;

        while (getline(input, line))
        {
            bool is_command = line.find("$ ") != std::string::npos;
            if (is_command)
            {
                line.erase(0, 2);
                std::stringstream linestream = std::stringstream(line);
                std::vector<std::string> command_vector;
                std::string value;
                while (getline(linestream, value, ' '))
                {
                    command_vector.push_back(value);
                }

                if (command_vector[0] == "cd")
                {
                    if (command_vector[1] == ".." && open_node->prev_dir != nullptr)
                    {
                        open_node = open_node->prev_dir;
                        continue;
                    }
                    for (auto &file : open_node->nodes)
                    {
                        if (file->name == command_vector[1])
                        {
                            open_node = file;
                            break;
                        }
                    }
                }
                else if (command_vector[0] == "ls")
                {
                    continue;
                }
            }
            else
            {
                bool is_dir = line.substr(0, 3) == "dir";
                if (is_dir)
                {
                    line.erase(0, 4);
                    Filesystem::Node *new_node = new Filesystem::Node(line, Filesystem::Type::DIRECTORY);
                    new_node->prev_dir = open_node;
                    open_node->nodes.push_back(new_node);
                }
                else
                {
                    size_t split_index = line.find(" ");
                    int size = std::stoi(line.substr(0, split_index));
                    line.erase(0, split_index + 1);
                    Filesystem::Node *file = new Filesystem::Node(line, Filesystem::Type::FILE);
                    file->size = size;
                    file->prev_dir = open_node;
                    open_node->nodes.push_back(file);
                }
            }
        }

        root->process_dir_sizes();
        // root->print();
        std::vector<Filesystem::Node *> smol;
        root->smaller_than(100000, smol);
        int sum = 0;
        for (auto &node : smol)
        {
            sum += node->size;
        }
        std::cout << sum << std::endl;
        delete root;
        input.close();
    }

    return 0;
}
