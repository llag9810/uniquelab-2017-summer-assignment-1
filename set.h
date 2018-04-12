#include <algorithm>

using T = double;

class Set {
public:
    void insert(const T &element);

    void erase(const T &element);

    void clear();

    int count(const T &element) const;

    bool empty();

    size_t size();

private:
    class Node {
    public:
        Node(const T &value, bool is_red) : value(value), is_red(is_red) {}

        T value;
        Node *left;
        Node *right;
        bool is_red;
    };

    Node *insert_node(Set::Node *root, const T &element);

    Node *rotate_left(Node *node);

    Node *rotate_right(Node *node);

    Node *color_flip(Node *node);

    bool is_red(Node *node);

    Node *move_red_right(Node *node);

    Node *root;
};