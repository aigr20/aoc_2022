#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

namespace Filesystem
{
    const int TOTAL_SPACE = 70000000;

    enum Type
    {
        FILE,
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
        void find_removal_candidates(int, int, std::vector<Node *> &);

        static bool compare_size(Node *a, Node *b);
    };
}
#endif
