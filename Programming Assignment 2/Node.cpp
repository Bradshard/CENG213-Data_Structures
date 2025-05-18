#include "Node.h"

Node::Node(const std::string &name, Node *parent) : name_(name), parent_(parent) {}

Node::~Node() {}

void Node::set_parent(Node *parent) {
    parent_ = parent;
}

void Node::set_name(const std::string &name) {
    name_ = name;
}

const std::string &Node::get_name() const {
    return name_;
}

Node *Node::get_parent() const {
    return parent_;
}
