#include <node.hpp>
#include <iostream>

Node::Node(std::string name, Type type) : name(name), type(type), prev_dir(nullptr), size(0)
{
}

void Node::print()
{
    std::cout << this->name;
    if (this->prev_dir != nullptr)
    {
        std::cout << " lives inside of " << this->prev_dir->name;
    }
    std::cout << " and is of size " << this->size << std::endl;

    for (auto &node : this->nodes)
    {
        node->print();
    }
}

void Node::process_dir_sizes()
{
    for (auto &node : this->nodes)
    {
        node->process_dir_sizes();
    }
    for (auto &node : this->nodes)
    {
        this->size += node->size;
    }
}

void Node::smaller_than(int max, std::vector<Node *> &collected)
{
    for (auto &node : this->nodes)
    {
        if (node->type == Type::DIRECTORY && node->size <= max)
        {
            collected.push_back(node);
        }
        node->smaller_than(max, collected);
    }
}
