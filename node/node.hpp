#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

enum Type
{
    FILE_,
    DIRECTORY,
};

class Node
{
public:
    Node(std::string, Type);

    std::string name;
    int size;
    Type type;
    Node *prev_dir;
    std::vector<Node *> nodes;

    void print();
    void process_dir_sizes();
    void smaller_than(int, std::vector<Node *> &);
};

#endif
