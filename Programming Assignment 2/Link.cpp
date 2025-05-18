/**
 * @file Link.cpp
 * @brief Implementation of the Link class methods.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#include "Link.h"

/**
 * @brief Constructor for Link.
 *
 * Initializes a new Link object with the specified name, parent, and target.
 *
 * @param name The name of the link
 * @param parent Pointer to the parent node
 * @param target Pointer to the target node that this link will point to
 */
Link::Link(const std::string &name, Node *parent, Node *target) : Node(name, parent), target_(target) {}

/**
 * @brief Destructor for Link.
 *
 * Virtual destructor to ensure proper cleanup through base pointer.
 * Note: The link does not own the target node, so it does not delete it.
 */
Link::~Link() {
    target_ = nullptr; //doesn't delete only assigns null.
}

/**
 * @brief Gets the type of the node.
 *
 * @return NodeType::Link
 */
NodeType Link::node_type() const {
    return NodeType::Link;
}

/**
 * @brief Creates a clone of the link.
 *
 * Creates a new Link object pointing to the same target as this link.
 *
 * @param parent The parent node for the cloned link (nullptr by default)
 * @return Pointer to the newly created Link clone
 */
Node *Link::clone(Node *parent) const {
    return new Link(this->get_name(), parent, this->target_); 
}

/**
 * @brief Gets the target node that this link points to.
 *
 * @return Pointer to the target node
 */
Node *Link::get_target() const {
    return target_ ? target_ : nullptr;
}
