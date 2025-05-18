/**
 * @file File.h
 * @brief Class representing a file in the file system.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#ifndef FILE_H_
#define FILE_H_
#include "Node.h"

/**
 * @brief Class representing a file in the file system.
 *
 * The File class is a specialized Node that represents a file in the file
 * system. It contains text content that can be read from or written to.
 */
class File : public Node {
private:
std::string content_; ///< The text content of the file

public:
/**
 * @brief Constructor for File.
 * @param name The name of the file
 * @param parent Pointer to the parent node (nullptr by default)
 * @param content The initial content of the file (empty string by default)
 */
File(const std::string &name, Node *parent = nullptr,
      const std::string &content = "");

/**
 * @brief Destructor for File.
 */
~File() override;

/**
 * @brief Gets the type of the node.
 * @return NodeType::File
 */
NodeType node_type() const override;

/**
 * @brief Creates a deep copy of the file.
 * @param parent The parent node for the cloned file (nullptr by default)
 * @return Pointer to the newly created File clone
 */
Node *clone(Node *parent = nullptr) const override;

/**
 * @brief Reads the content of the file.
 * @return A constant reference to the file's content
 */
const std::string &read_content() const;

/**
 * @brief Writes new content to the file.
 * @param data The new content to write to the file
 */
void write_content(const std::string &data);
};

#endif
