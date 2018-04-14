#include "set.h"

void Set::insert(const T &element) {
    root = insert_node(root, element);
}

Set::Node *Set::insert_node(Set::Node *root, const T &element) {
    if (!root) {
        root = new Node(element, true);
        node_size++;
        return root;
    }

    if (element == root->value) {
        root->value = element;
    } else if (element < root->value) {
        root->left = insert_node(root->left, element);
    } else {
        root->right = insert_node(root->right, element);
    }

    if (!is_red(root->left) && is_red(root->right)) {
        root = rotate_left(root);
    }

    if (is_red(root->left) && is_red(root->left->left))
        root = rotate_right(root);


    if (is_red(root->left) && is_red(root->right)) {
        color_flip(root);
    }

    return root;
}

Set::Node *Set::rotate_left(Set::Node *node) {
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->is_red = temp->left->is_red;
    temp->left->is_red = true;
    return temp;
}

Set::Node *Set::rotate_right(Set::Node *node) {
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->is_red = temp->right->is_red;
    temp->right->is_red = true;
    return temp;
}

Set::Node *Set::color_flip(Set::Node *node) {
    node->is_red = !node->is_red;
    if (node->left != nullptr) {
        node->left->is_red = !node->left->is_red;
    }

    if (node->right != nullptr) {
        node->right->is_red = !node->right->is_red;
    }
    return node;
}

bool Set::is_red(Set::Node *node) {
    return (node != nullptr) && node->is_red;
}

Set::Node *Set::move_red_right(Set::Node *node) {
    color_flip(node);
    if (node->left && is_red(node->left->left)) {
        node = rotate_right(node);
        color_flip(node);
    }

    return node;
}

void Set::erase(const T &element) {
    if (count(element)) {
        if (!is_red(root->left) && !is_red(root->right)) {
            root->is_red = true;
        }
        root = delete_node(root, element);
        if (root) {
            root->is_red = false;
        }
        node_size--;
    }
}

void Set::clear() {
    while (root != nullptr) {
        erase(root->value);
    }
}

int Set::count(const T &element) const {
    Node *node = root;
    while (node) {
        if (node->value == element) {
            return 1;
        }

        if (element < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return 0;
}

bool Set::empty() {
    return node_size == 0;
}

size_t Set::size() {
    return node_size;
}

Set::Node *Set::fix_up(Node *node) {
    if (is_red(node->right)) {
        node = rotate_left(node);
    }

    if (is_red(node->left) && is_red(node->left->left)) {
        node = rotate_right(node);
    }

    if (is_red(node->left) && is_red(node->right)) {
        color_flip(node);
    }
    return node;
}

    Set::Node *Set::delete_max(Set::Node *node) {
    if (is_red(node->left)) {
        node = rotate_right(node);
    }

    if (node->right == nullptr) {
        delete node;
        return nullptr;
    }

    if (!is_red(node->right) && !is_red(node->right->left)) {
        node = move_red_right(node);
    }

    node->right = delete_max(node->right);

    return fix_up(node);
}

void Set::delete_max() {
    root = delete_max(root);
    root->is_red = false;
}

Set::Node *Set::move_red_left(Set::Node *node) {
    color_flip(node);
    if (node->right && is_red(node->right->left)) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
        color_flip(node);
    }

    return node;
}

Set::Node *Set::delete_min(Set::Node *node) {
    if (node->left == nullptr) {
        delete node;
        return nullptr;
    }

    if (!is_red(node->left) && !is_red(node->left->left)) {
        node = move_red_left(node);
    }

    node->left = delete_min(node->left);
    return fix_up(node);
}

void Set::delete_min() {
    root = delete_min(root);
    root->is_red = false;
}

Set::Node *Set::delete_node(Set::Node *node, const T &key) {

    if (key < node->value) {
        if (!is_red(node->left) && !is_red(node->left->left)) {
            node = move_red_left(node);
        }
        node->left = delete_node(node->left, key);
    } else {
        if (is_red(node->left)) {
            node = rotate_right(node);
        }

        if (key == node->value && (node->right == nullptr)) {
            return nullptr;
        }

        if (!is_red(node->right) && !is_red(node->right->left)) {
            node = move_red_right(node);
        }

        if (key == node->value) {
            node->value = min_node(node->right)->value;
            node->right = delete_min(node->right);
        } else {
            node->right = delete_node(node->right, key);
        }
    }

    return fix_up(node);
}

Set::Node *Set::min_node(Set::Node *node) {
    while (node->left) {
        node = node->left;
    }

    return node;
}







