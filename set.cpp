#include "set.h"

void Set::insert(const T &element) {
    insert_node(root, element);
}

Set::Node *Set::insert_node(Set::Node *root, const T &element) {
    if (!root) {
        return new Node(element, true);
    }

    if (is_red(root->left) && is_red(root->right)) {
        color_flip(root);
    }

    if (element == root->value) {
        root->value = element;
    } else if (element < root->value) {
        root->left = insert_node(root->left, element);
    } else {
        root->right = insert_node(root->right, element);
    }

    if (is_red(root->right)) {
        root = rotate_left(root);
    }

    if (is_red(root->left) && is_red(root->left->left))
        root = rotate_right(root);

    return root;
}

Set::Node *Set::rotate_left(Set::Node *node) {
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->is_red = node->is_red;
    node->is_red = true;
    return temp;
}

Set::Node *Set::rotate_right(Set::Node *node) {
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->is_red = node->is_red;
    node->is_red = true;
    return temp;
}

Set::Node *Set::color_flip(Set::Node *node) {
    node->is_red = !node->is_red;
    node->left->is_red = !node->left->is_red;
    node->right->is_red = !node->right->is_red;
    return node;
}

bool Set::is_red(Set::Node *node) {
    return (node != nullptr) && node->is_red;
}

Set::Node *Set::move_red_right(Set::Node *node) {
    color_flip(node);
    if (is_red(node->left->left)) {
        node = rotate_right(node);
        color_flip(node);
    }
    return node;
}

void Set::erase(const T &element) {

}

void Set::clear() {

}

int Set::count(const T &element) const {
    return 0;
}

bool Set::empty() {
    return false;
}

size_t Set::size() {
    return 0;
}





