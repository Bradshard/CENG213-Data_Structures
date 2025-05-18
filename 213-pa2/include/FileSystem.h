/**
 * @file FileSystem.h
 * @brief Class representing an in-memory file system.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_
#include "Folder.h"

#include <map>
#include <string>
#include <vector>

/**
 * @brief Class representing an in-memory file system.
 *
 * The FileSystem class provides a complete interface for managing an in-memory
 * file system, including operations like creating, moving, copying, and
 * removing nodes, as well as mounting and unmounting external file systems.
 */
class FileSystem {
private:
  Folder *root_; ///< Pointer to the root folder of the file system
  std::map<std::string, Folder *>
      mounts_; ///< Map of mount points to external root folders

  /**
   * @brief Resolves a path to a node in the file system.
   *
   * Traverses the file system tree following the given path and returns the
   * node at that path. Supports absolute paths with '/' as the separator.
   * Handles navigation through symbolic links.
   *
   * @param path The path to resolve
   * @return Pointer to the node at the given path, or nullptr if the path is
   * invalid
   */
  Node *resolve_path(const std::string &path) const;

  /**
   * @brief Recursively deletes a node and all its children.
   *
   * Frees memory allocated for the node and its children.
   *
   * @param node Pointer to the node to delete
   */
  void recursive_delete(Node *node);

public:
  /**
   * @brief Default constructor.
   *
   * Creates a new FileSystem object with an empty root folder.
   */
  FileSystem();

  /**
   * @brief Copy constructor.
   *
   * Creates a deep copy of another FileSystem object.
   *
   * @param other The FileSystem object to copy
   */
  FileSystem(const FileSystem &other);

  /**
   * @brief Assignment operator.
   *
   * Creates a deep copy of another FileSystem object and assigns it to this
   * object.
   *
   * @param other The FileSystem object to copy
   * @return Reference to this FileSystem object
   */
  FileSystem &operator=(const FileSystem &other);

  /**
   * @brief Destructor.
   *
   * Deletes all nodes in the file system and frees their memory.
   */
  ~FileSystem();

  /**
   * @brief Creates a file at the specified path.
   *
   * Creates a new file with the given content at the specified path.
   * If intermediate directories in the path don't exist, they will be created.
   *
   * @param path The path where the file should be created
   * @param content The initial content of the file (empty string by default)
   * @throws std::runtime_error If a file with the same name already exists
   */
  void create_file(const std::string &path, const std::string &content = "");

  /**
   * @brief Creates a folder at the specified path.
   *
   * Creates a new folder at the specified path.
   * If intermediate directories in the path don't exist, they will be created.
   *
   * @param path The path where the folder should be created
   * @throws std::runtime_error If a folder with the same name already exists
   */
  void create_folder(const std::string &path);

  /**
   * @brief Creates a symbolic link at the specified path.
   *
   * Creates a new symbolic link at the specified path, pointing to the target
   * path.
   *
   * @param path The path where the link should be created
   * @param target_path The path to the target node that the link will point to
   * @throws std::runtime_error If a link with the same name already exists
   */
  void create_link(const std::string &path, const std::string &target_path);

  /**
   * @brief Removes a node from the file system.
   *
   * Removes the node at the specified path and all its children (if it's a
   * folder).
   *
   * @param path The path to the node to be removed
   * @return true if the node was successfully removed, false otherwise
   */
  bool remove_node(const std::string &path);

  /**
   * @brief Moves a node from one path to another.
   *
   * Moves the node at the source path to the destination path.
   * If the destination exists and is of the same type, it will be overwritten.
   *
   * @param src_path The source path
   * @param dest_path The destination path
   */
  void move_node(const std::string &src_path, const std::string &dest_path);

  /**
   * @brief Copies a node from one path to another.
   *
   * Creates a deep copy of the node at the source path and places it at the
   * destination path. If the destination exists and is of the same type, it
   * will be overwritten.
   *
   * @param src_path The source path
   * @param dest_path The destination path
   */
  void copy_node(const std::string &src_path, const std::string &dest_path);

  /**
   * @brief Finds a node at the specified path.
   *
   * @param path The path to the node
   * @return Pointer to the node, or nullptr if the path is invalid
   */
  Node *find_node(const std::string &path) const;

  /**
   * @brief Lists the contents of a directory.
   *
   * @param path The path to the directory
   * @return Vector of strings containing the names of all items in the
   * directory
   */
  std::vector<std::string> list_directory(const std::string &path) const;

  /**
   * @brief Prints the file system tree starting from the specified path.
   *
   * Recursively prints the tree structure of the file system with indentation.
   *
   * @param path The path to start printing from (defaults to root "/")
   * @param indent The initial indentation level (defaults to 0)
   */
  void print_tree(const std::string &path = "/", int indent = 0) const;

};

#endif
