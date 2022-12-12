#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <node.hpp>

bool handle_cd(Filesystem::Node *&open_node, std::vector<std::string> &command_vector)
{
    if (command_vector[1] == ".." && open_node->prev_dir != nullptr)
    {
        open_node = open_node->prev_dir;
        return true;
    }
    for (auto &file : open_node->nodes)
    {
        if (file->name == command_vector[1])
        {
            open_node = file;
            return false;
        }
    }
    return false;
}

void handle_dir(Filesystem::Node *&open_node, std::string &line)
{
    line.erase(0, 4);
    Filesystem::Node *new_node = new Filesystem::Node(line, Filesystem::Type::DIRECTORY);
    new_node->prev_dir = open_node;
    open_node->nodes.push_back(new_node);
}

void register_file(Filesystem::Node *&open_node, std::string &line)
{
    size_t split_index = line.find(" ");
    int size = std::stoi(line.substr(0, split_index));
    line.erase(0, split_index + 1);
    Filesystem::Node *file = new Filesystem::Node(line, Filesystem::Type::FILE);
    file->size = size;
    file->prev_dir = open_node;
    open_node->nodes.push_back(file);
}

void part_1(Filesystem::Node *&root)
{
    std::vector<Filesystem::Node *> smol;
    root->smaller_than(100000, smol);
    int sum = 0;
    for (auto &node : smol)
    {
        sum += node->size;
    }
    std::cout << sum << std::endl;
}

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
                    if (handle_cd(open_node, command_vector))
                    {
                        continue;
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
                    handle_dir(open_node, line);
                }
                else
                {
                    register_file(open_node, line);
                }
            }
        }

        root->process_dir_sizes();
        part_1(root);
        delete root;
        input.close();
    }

    return 0;
}
