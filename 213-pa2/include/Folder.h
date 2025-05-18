/**
 * @file Folder.h
 * @brief Class representing a folder in the file system.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#ifndef FOLDER_H_
#define FOLDER_H_
#include "Node.h"
#include <vector>

/**
 * @brief Class representing a folder/directory in the file system.
 *
 * The Folder class is a specialized Node that represents a directory in the
 * file system. It can contain other nodes (files, folders, or links) as its
 * children.
 */
class Folder : public Node {
private:
  std::vector<Node *> children_; ///< Vector of pointers to child nodes

public:
  /**
   * @brief Constructor for Folder.
   * @param name The name of the folder
   * @param parent Pointer to the parent node (nullptr by default)
   */
  Folder(const std::string &name, Node *parent = nullptr);

  /**
   * @brief Destructor for Folder.
   *
   * Deletes all child nodes recursively.
   */
  ~Folder() override;

  /**
   * @brief Gets the type of the node.
   * @return NodeType::Folder
   */
  NodeType node_type() const override;

  /**
   * @brief Creates a deep copy of the folder and all its contents.
   *
   * Recursively clones all child nodes.
   *
   * @param parent The parent node for the cloned folder (nullptr by default)
   * @return Pointer to the newly created Folder clone
   */
  Node *clone(Node *parent = nullptr) const override;

  /**
   * @brief Adds a file as a child to this folder.
   *
   * Creates a new File object and adds it to the children of this folder.
   *
   * @param name The name of the file to add
   * @param content The initial content of the file (empty string by default)
   * @return Pointer to the newly created File node
   * @throws std::invalid_argument if the name is present or empty
   */
  Node *add_file(const std::string &name, const std::string &content = "");

  /**
   * @brief Adds a subfolder as a child to this folder.
   *
   * Creates a new Folder object and adds it to the children of this folder.
   *
   * @param name The name of the subfolder to add
   * @return Pointer to the newly created Folder node
   * @throws std::invalid_argument if the name is present or empty
   */
  Node *add_folder(const std::string &name);

  /**
   * @brief Adds a symbolic link as a child to this folder.
   *
   * Creates a new Link object pointing to the target node and adds it to the
   * children of this folder.
   *
   * @param name The name of the link to add
   * @param target Pointer to the node that the link will point to
   * @return Pointer to the newly created Link node
   * @throws std::invalid_argument if the name is present or empty or target is
   * nullptr
   */
  Node *add_link(const std::string &name, Node *target);

  /**
   * @brief Adds the Node as a child to the parent node.
   *
   * @return
   */
  void add_child(Node *child);

  /**
   * @brief Removes a child node by name.
   *
   * Searches for a child node with the given name and removes it if found.
   *
   * @param name The name of the child node to remove
   * @return Pointer to the removed node
   * @throws std::invalid_argument if the name is empty or not present
   */
  Node *remove_child(const std::string &name);

  /**
   * @brief Finds a child node by name.
   *
   * Searches for a child node with the given name.
   *
   * @param name The name of the child node to find
   * @return Pointer to the found node, or nullptr if no matching child exists
   */
  Node *find_child(const std::string &name) const;

  /**
   * @brief Lists the names of all child nodes.
   *
   * @return Vector of strings containing the names of all children
   */
  std::vector<std::string> list_children() const;

};

#endif
