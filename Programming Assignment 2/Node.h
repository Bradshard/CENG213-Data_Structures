/**
 * @file Node.h
 * @brief Abstract base class representing a node in the file system.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <cstdint>

/**
 * @brief Enumeration of node types in the file system.
 */
enum class NodeType : std::uint8_t {
  File,         ///< Represents a file node
  Folder,      ///< Represents a folder/directory node
  Link,       ///< Represents a symbolic link node
  FileSystem ///< Represents a file system node
};

/**
 * @brief Abstract base class for all file system nodes.
 *
 * The Node class represents a generic node in the file system hierarchy.
 * It serves as the base class for specialized node types (File, Folder, Link).
 * Each node has a name and a parent pointer.
 */
class Node {
protected:
  std::string name_; ///< Name of the node
  Node *parent_;     ///< Pointer to parent node (nullptr if it's the root)

public:
  /**
   * @brief Constructor for Node.
   * @param name The name of the node
   * @param parent Pointer to the parent node (nullptr by default)
   */
  Node(const std::string &name, Node *parent = nullptr);

  /**
   * @brief Virtual destructor to ensure proper cleanup through base pointer.
   */
  virtual ~Node();

  /**
   * @brief Gets the name of the node.
   * @return A constant reference to the node's name
   */
  const std::string &get_name() const;

  /**
   * @brief Gets the parent of the node.
   * @return Pointer to the parent node, or nullptr if it has no parent
   */
  Node *get_parent() const;

  /**
   * @brief Sets the parent of this node.
   * @param parent Pointer to the parent node
   */
  void set_parent(Node *parent);

  /**
   * @brief Sets the name of this node.
   * @param name The new name for the node
   */
  void set_name(const std::string &name);

  /**
   * @brief Pure virtual method to get the type of the node.
   * @return The type of the node (File, Folder, or Link)
   */
  virtual NodeType node_type() const = 0;

  /**
   * @brief Pure virtual method to create a clone of the node.
   * @param parent The parent node for the cloned node (nullptr by default)
   * @return Pointer to the newly created clone
   */
  virtual Node *clone(Node *parent = nullptr) const = 0;
};

#endif
