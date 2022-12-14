#include <node.hpp>
#include <iostream>

namespace Filesystem
{

    Node::Node(std::string name, Type type) : name(name), size(0), type(type), prev_dir(nullptr)
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
    void Node::find_removal_candidates(int available, int desired, std::vector<Node *> &candidates)
    {
        for (auto &node : this->nodes)
        {
            if (node->type == Type::DIRECTORY && available + node->size >= desired)
            {
                candidates.push_back(node);
            }
            node->find_removal_candidates(available, desired, candidates);
        }
    }

    bool Node::compare_size(Node *a, Node *b)
    {
        return a->size < b->size;
    }
}
