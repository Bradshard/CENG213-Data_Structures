/**
 * @file File.cpp
 * @brief Implementation of the File class methods.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#include "File.h"

/**
 * @brief Constructor for File.
 *
 * Initializes a new File object with the specified name, parent, and content.
 *
 * @param name The name of the file
 * @param parent Pointer to the parent node (nullptr by default)
 * @param content The initial content of the file (empty string by default)
 */
File::File(const std::string &name, Node *parent,  const std::string &content) : Node(name, parent), content_(content) {}

/**
 * @brief Destructor for File.
 *
 * Virtual destructor to ensure proper cleanup through base pointer.
 */
File::~File() {}

/**
 * @brief Gets the type of the node.
 *
 * @return NodeType::File
 */
NodeType File::node_type() const {
    return NodeType::File;
}

/**
 * @brief Creates a deep copy of the file.
 *
 * Creates a new File object with the same name and content as this file.
 *
 * @param parent The parent node for the cloned file (nullptr by default)
 * @return Pointer to the newly created File clone
 */
Node *File::clone(Node *parent) const {
    return new File(this->name_, parent, this->content_);
}

/**
 * @brief Reads the content of the file.
 *
 * @return A constant reference to the file's content
 */
const std::string &File::read_content() const {
    return content_;
}

/**
 * @brief Writes new content to the file.
 *
 * Replaces the existing content with the new data provided.
 *
 * @param data The new content to write to the file
 */
void File::write_content(const std::string &data) {
    content_ = data;
}
