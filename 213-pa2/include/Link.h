/**
 * @file Link.h
 * @brief Class representing a symbolic link in the file system.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#ifndef LINK_H_
#define LINK_H_

#include "Node.h"

/**
 * @brief Class representing a symbolic link in the file system.
 *
 * The Link class is a specialized Node that acts as a symbolic reference to
 * another node (file, folder, or another link) in the file system. It does not
 * store its own data but points to another node.
 */
class Link : public Node {
private:
  Node *target_; ///< Pointer to the target node that this link points to

public:
  /**
   * @brief Constructor for Link.
   * @param name The name of the link
   * @param parent Pointer to the parent node
   * @param target Pointer to the target node that this link will point to
   */
  Link(const std::string &name, Node *parent, Node *target);

  /**
   * @brief Destructor for Link.
   */
  ~Link() override;

  /**
   * @brief Gets the type of the node.
   * @return NodeType::Link
   */
  NodeType node_type() const override;

  /**
   * @brief Creates a clone of the link.
   *
   * Creates a new Link object pointing to the same target as this link.
   *
   * @param parent The parent node for the cloned link (nullptr by default)
   * @return Pointer to the newly created Link clone
   */
  Node *clone(Node *parent = nullptr) const override;

  /**
   * @brief Gets the target node that this link points to.
   * @return Pointer to the target node
   */
  Node *get_target() const;
};

#endif
