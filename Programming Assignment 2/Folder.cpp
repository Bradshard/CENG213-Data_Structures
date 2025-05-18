
/**
 * @file Folder.cpp
 * @brief Implementation of the Folder class methods.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#include "Folder.h"
#include "File.h"
#include "Link.h"
 
#include <cstddef>
#include <iostream>
 
/**
* @brief Constructor for Folder.
*
* Initializes a new Folder object with the specified name and parent.
*
* @param name The name of the folder
* @param parent Pointer to the parent node (nullptr by default)
*/
Folder::Folder(const std::string &name, Node *parent) : Node(name, parent) {}
 
/**
* @brief Destructor for Folder.
*
* Deletes all child nodes recursively.
*/
Folder::~Folder() {
  while (!(children_.empty())) {
    Node* child = children_.back();
    children_.pop_back();
    delete child;
  }
}
 
/**
* @brief Gets the type of the node.
*
* @return NodeType::Folder
*/
NodeType Folder::node_type() const {
    return NodeType::Folder;
}
 
/**
* @brief Creates a deep copy of the folder and all its contents.
*
* Recursively clones all child nodes.
*
* @param parent The parent node for the cloned folder (nullptr by default)
* @return Pointer to the newly created Folder clone
*/
Node *Folder::clone(Node *parent) const {
    Folder *clone_folder = new Folder(this->name_, parent);
    for (Node *child : children_) {
        Node *clone_child = child->clone(clone_folder);
        clone_folder->add_child(clone_child);
    }
    return clone_folder;
}
 
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
Node *Folder::add_file(const std::string &name, const std::string &content) {
    if (name.empty()){
        throw std::invalid_argument("no file named as such.");
    }
    // memory allocation here
    File *file = new File(name, this, content);
    try {
        // after allocation push to vector children_
        children_.push_back(file);
    } catch (...) {
        delete file;
        throw; // here we check every possible error.
    }
    return file;
}
/**
* @brief Adds a subfolder as a child to this folder.
*
* Creates a new Folder object and adds it to the children of this folder.
*
* @param name The name of the subfolder to add
* @return Pointer to the newly created Folder node
* @throws std::invalid_argument if the name is present or empty
  */
Node *Folder::add_folder(const std::string &name) {
    Node *if_exist = find_child(name);
    if (name.empty() || (if_exist && if_exist->node_type() == NodeType::Folder)) {
        throw std::invalid_argument("Duplicate folder name.");
    }
    Node *folder = new Folder(name, this);
    children_.push_back(folder);
    return folder;
}
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
Node *Folder::add_link(const std::string &name, Node *target) {
    // Similar to add_file
    if (name.empty() || !(target)){
        throw std::invalid_argument("Inv link_name or null.");
    }
    if (find_child(name)){
        throw std::invalid_argument("Duplicate node name.");
    }

    Link *link = new Link(name, this, target);
    try {
        children_.push_back(link);
    } catch (...) {
        delete link;
        throw;
    }
    return link;
}


/**
* @brief Adds a child node by Node.
*
* If the given node is not null, it is added to the children of this folder.
*
* @param child Pointer to the child node to add
* @return
* @throws
*/
void Folder::add_child(Node *child) {
    if (child) {
        child->set_parent(this);
        children_.push_back(child);
    }
}
 
/**
* @brief Removes a child node by name.
*
* Searches for a child node with the given name and removes it if found.
*
* @param name The name of the child node to remove
* @return Pointer to the removed node
* @throws std::invalid_argument if the name is empty or not present
*/
Node *Folder::remove_child(const std::string &name) {
    if (name.empty()){
        throw std::invalid_argument("Don't exist, must exist for removal.");
    }

    for (auto iterated = children_.begin(); iterated != children_.end(); ++iterated) {
        if ((*iterated)->get_name() == name) {
            Node *removes = *iterated;
            children_.erase(iterated);
            return removes;
        }
    }
    throw std::invalid_argument("No child exists with such name.");
}
 
/**
* @brief Finds a child node by name.
*
* Searches for a child node with the given name.
*
* @param name The name of the child node to find
* @return Pointer to the found node, or nullptr if no matching child exists
*/
Node *Folder::find_child(const std::string &name) const {
    for (Node *child : children_) {
        if (child->get_name() == name){
            return child;  
        } 
    }
    return nullptr;
}

/**
* @brief Lists the names of all child nodes.
*
* @return Vector of strings containing the names of all children
*/
std::vector<std::string> Folder::list_children() const {
    std::vector<std::string> names;
    for (const Node *child : children_) {
        names.push_back(child->get_name());
    }
    return names;
}
