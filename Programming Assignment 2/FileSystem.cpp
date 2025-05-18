/**
 * @file FileSystem.cpp
 * @brief Implementation of the FileSystem class methods.
 * @author Adnan Harun Dogan
 * @date April 2025
 */

#include "FileSystem.h"
#include "File.h"
#include "Link.h"
#include <iostream>
//static stores path_collection helper function.
static void split_path(const std::string& path, std::vector<std::string>& out) {
    out.clear();
    //size_t for to safely assign any value, unsigned_int but has no limits.
    size_t length = path.size();
    size_t idx = 0;
    if (idx < length && path[0] == '/') {
        ++idx; // leading '/' skipped.
    }
    while (idx < length) {
        size_t k = path.find('/', idx);
        if (k == std::string::npos){
            k = length; //npos is the end of string special size_t operator.
        }
        if (k > idx) {
            out.emplace_back(path.substr(idx, k - idx));// higher efficiency push_back()
        }
        idx = k + 1;
    }
}

/**
 * @brief Default constructor.
 *
 * Creates a new FileSystem object with a root folder named "/".
 */
FileSystem::FileSystem() {
    root_ = new Folder("/", nullptr); // constructior
}

/**
 * @brief Copy constructor.
 *
 * Creates a deep copy of another FileSystem object.
 *
 * @param obj The FileSystem object to copy
 */
FileSystem::FileSystem(const FileSystem &obj) {
    Node* clones = obj.root_->clone(nullptr);
    Folder* clone_fold = dynamic_cast<Folder*>(clones);
    if (!(clone_fold)) {
        delete clones;
        throw std::runtime_error("Clone is not a folder.");
    }
    root_ = clone_fold;
}

/**
 * @brief Assignment operator.
 *
 * Creates a deep copy of another FileSystem object and assigns it to this
 * object.
 *
 * @param other The FileSystem object to copy
 * @return Reference to this FileSystem object
 */
FileSystem &FileSystem::operator=(const FileSystem &other) {
    if (this != &other) {
        recursive_delete(root_);
        Node* cloned_root = other.root_->clone(nullptr);
        Folder* if_run = dynamic_cast<Folder*>(cloned_root); //for safe cast, rather than static.
        if (!(if_run)) {
            delete cloned_root;
            throw std::runtime_error("Clone is not a folder.");
        }
        root_ = if_run;
    }
    return *this;
}

/**
 * @brief Resolves a path to a node in the file system.
 *
 * Traverses the file system tree following the given path and returns the node
 * at that path. Supports absolute paths with '/' as the separator. Handles
 * navigation through symbolic links.
 *
 * @param path The path to resolve
 * @return Pointer to the node at the given path, or nullptr if the path is
 * invalid
 */
Node *FileSystem::resolve_path(const std::string &path) const {
    if (path.empty() || path[0] != '/'){
        return nullptr;
    }
    if (path == "/"){
        return root_;
    }

    Node* current_node = root_;
    std::vector<std::string> path_parts;
    split_path(path, path_parts);

    for (const auto& val_child : path_parts) {
        if (current_node->node_type() != NodeType::Folder){ return nullptr;}
        Folder* folder = static_cast<Folder*>(current_node);
        Node* child = folder->find_child(val_child);
        if (!(child)){ return nullptr;}
        // follow links
        while (child && child->node_type() == NodeType::Link) {
            child = static_cast<Link*>(child)->get_target();
        }
        if (!(child)){ return nullptr;}
        current_node = child;
    }
    return current_node;
}

/**
 * @brief Recursively deletes a node and all its children.
 *
 * Frees memory allocated for the node and its children.
 *
 * @param node Pointer to the node to delete
 */
void FileSystem::recursive_delete(Node *node) {
    if (!(node)){ return;}
    if (node->node_type() == NodeType::Folder) {
        Folder* folder = static_cast<Folder*>(node);
        auto children = folder->list_children();
        for (const auto& name : children) {
            Node* child = folder->remove_child(name);
            recursive_delete(child);
        }
    }
    delete node;
}

/**
 * @brief Destructor.
 *
 * Deletes all nodes in the file system and frees their memory.
 */
FileSystem::~FileSystem() {
    recursive_delete(root_);
}

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
void FileSystem::create_file(const std::string &path, const std::string &content) {
    
    std::vector<std::string> path_parts;
    // parent path is constructed.
    std::string parent_path = "/";
    if (path.empty() || path[0] != '/'){
        throw std::runtime_error("No such file or directory."); // standart error
    }

    split_path(path, path_parts);
    if (path_parts.empty()){
        throw std::runtime_error("No such file or directory.");
    }

    const std::string file_name = path_parts.back();
    if (file_name.empty()){
        throw std::runtime_error("No such file or directory.");
    }

    if (path_parts.size() > 1) {
        for (size_t idx = 0; idx + 1 < path_parts.size(); ++idx) {
            parent_path += path_parts[idx];
            if (idx + 2 < path_parts.size())
                parent_path += "/";
        }
    }

    Node* parent_node = resolve_path(parent_path);
    if (!(parent_node) || parent_node->node_type() != NodeType::Folder){
        throw std::runtime_error("No such file or directory.");
    }

    Folder* parent = static_cast<Folder*>(parent_node);
    if (parent->find_child(file_name)){
        throw std::runtime_error("A file with this name already exists.");
    }

    parent->add_file(file_name, content);
}

/**
 * @brief Creates a folder at the specified path.
 *
 * Creates a new folder at the specified path.
 * If intermediate directories in the path don't exist, they will be created.
 *
 * @param path The path where the folder should be created
 * @throws std::runtime_error If a folder with the same name already exists
 */
void FileSystem::create_folder(const std::string& path) {
    // same as create_file with tiny changes.
    // parent path creation
    std::string parent_path = "/";
    std::vector<std::string> path_parts;
    if (path.empty() || path[0] != '/'){
        throw std::runtime_error("No such file or directory.");
    }

    split_path(path, path_parts);
    if (path_parts.empty()){
        throw std::runtime_error("No such file or directory.");
    }

    const std::string folder_name = path_parts.back();
    if (folder_name.empty()){
        throw std::runtime_error("No such file or directory.");
    }


    if (path_parts.size() > 1) {
        for (size_t idx = 0; idx + 1 < path_parts.size(); ++idx) {
            parent_path += path_parts[idx];
            if (idx + 2 < path_parts.size())
                parent_path += "/";
        }
    }

    Node* parent_node = resolve_path(parent_path);
    if (!(parent_node) || parent_node->node_type() != NodeType::Folder){
        throw std::runtime_error("No such file or directory.");
    }

    Folder* parent = static_cast<Folder*>(parent_node);
    if (parent->find_child(folder_name)){
        throw std::runtime_error("A folder with this name already exists.");
    }

    parent->add_folder(folder_name);
}

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
void FileSystem::create_link(const std::string& path, const std::string& target_path) {
    // again create_file-folder and link nearly identical.
    if (path.empty() || path[0] != '/'){
        throw std::runtime_error("No such file or directory.");
    }

    if (target_path.empty() || target_path[0] != '/'){
        throw std::runtime_error("Target node not found.");
    }

    std::vector<std::string> path_parts;
    split_path(path, path_parts);
    if (path_parts.empty()){
        throw std::runtime_error("No such file or directory.");
    }

    // traversal of parent folders and auto-creation of them
    Folder* current = root_; // directly get from root_.
    for (size_t idx = 0; idx + 1 < path_parts.size(); ++idx) {
        Node* cur_path = current->find_child(path_parts[idx]);
        if (!(cur_path)){
            cur_path = current->add_folder(path_parts[idx]);
        }
        if (cur_path->node_type() != NodeType::Folder){
            throw std::runtime_error("No such file or directory.");
        }
        current = static_cast<Folder*>(cur_path);
    }

    const std::string& linker_name = path_parts.back();
    Node* target = resolve_path(target_path);
    if (!(target)){
        throw std::runtime_error("Target node not found.");
    }

    if (current->find_child(linker_name)){
        throw std::runtime_error("A link with this name already exists.");
    }

    current->add_link(linker_name, target);
}

/**
 * @brief Removes a node from the file system.
 *
 * Removes the node at the specified path and all its children (if it's a
 * folder). Root node cannot be removed.
 *
 * @param path The path to the node to be removed
 * @return true if the node was successfully removed, false otherwise
 */
bool FileSystem::remove_node(const std::string& path) {
    if (path == "/"){
        return false;
    }
    Node* node = resolve_path(path);
    if (!(node)){
        return false;
    }

    Folder* parent = static_cast<Folder*>(node->get_parent());
    parent->remove_child(node->get_name());
    recursive_delete(node);
    return true;
}

/**
 * @brief Moves a node from one path to another.
 *
 * Moves the node at the source path to the destination path.
 * If the destination exists and is of the same type, it will be overwritten.
 *
 * @param src_path The source path
 * @param dest_path The destination path
 */
void FileSystem::move_node(const std::string& src_path, const std::string& dest_path) {
    Node* src = resolve_path(src_path);
    if (!(src)) {
        throw std::invalid_argument("No such file or directory.");
    }

    std::vector<std::string> path_parts;
    split_path(dest_path, path_parts);
    if (path_parts.empty()){
        throw std::invalid_argument("No such file or directory.");
    }

    Folder* dest_folder = root_;
    for (size_t idx = 0; idx + 1 < path_parts.size(); ++idx) {
        Node* cur = dest_folder->find_child(path_parts[idx]);
        if (!(cur) || cur->node_type() != NodeType::Folder){
            throw std::invalid_argument("No such file or directory.");
        }
        dest_folder = static_cast<Folder*>(cur);
    }

    // old_parent_removal for move
    Folder* old_parent = static_cast<Folder*>(src->get_parent());
    old_parent->remove_child(src->get_name());

    // collision check
    const std::string& new_name = path_parts.back();
    if (Node* ex_path = dest_folder->find_child(new_name)) {
        dest_folder->remove_child(new_name);
        recursive_delete(ex_path);
    }

    src->set_parent(dest_folder);
    src->set_name(new_name);
    dest_folder->add_child(src);
}

/**
 * @brief Copies a node from one path to another.
 *
 * Creates a deep copy of the node at the source path and places it at the
 * destination path. If the destination exists and is of the same type, it will
 * be overwritten.
 *
 * @param src_path The source path
 * @param dest_path The destination path
 */
void FileSystem::copy_node(const std::string& src_path, const std::string& dest_path) {
    // similar to move_node
    std::vector<std::string> path_parts;
    Node* src = resolve_path(src_path);
    if (!(src)){
        throw std::invalid_argument("No such file or directory.");
    }


    split_path(dest_path, path_parts);
    if (path_parts.empty()) {
        throw std::invalid_argument("No such file or directory.");
    }
    Folder* dest_folder = root_;
    for (size_t idx = 0; idx + 1 < path_parts.size(); ++idx) {
        Node* cur = dest_folder->find_child(path_parts[idx]);
        if (!(cur) || cur->node_type() != NodeType::Folder){
            throw std::invalid_argument("No such file or directory.");
        }
        dest_folder = static_cast<Folder*>(cur);
    }

    const std::string& new_name = path_parts.back();
    if (Node* ex_path = dest_folder->find_child(new_name)) {
        dest_folder->remove_child(new_name);
        recursive_delete(ex_path);
    }

    Node* cloned = src->clone(dest_folder);
    cloned->set_name(new_name);
    dest_folder->add_child(cloned);
}

/**
 * @brief Finds a node at the specified path.
 *
 * @param path The path to the node
 * @return Pointer to the node, or nullptr if the path is invalid
 */
Node *FileSystem::find_node(const std::string &path) const {
    if (path.empty() || path[0] != '/'){
        return nullptr;
    }
    if (path == "/"){
        return root_;
    }

    std::vector<std::string> path_parts;
    split_path(path, path_parts);
    if (path_parts.empty()){
        return nullptr;
    }

    Node* cur_node = root_;
    for (size_t idx = 0; idx < path_parts.size(); ++idx) {
        if (cur_node->node_type() != NodeType::Folder){
            return nullptr;
        }
        Folder* folder = static_cast<Folder*>(cur_node);
        Node* child = folder->find_child(path_parts[idx]);
        if (!(child)){
            return nullptr;
        }

        // interim comp link following
        if (idx + 1 < path_parts.size()) {
            while (child && child->node_type() == NodeType::Link) {
                child = static_cast<Link*>(child)->get_target();
            }
            if (!(child)) {
                return nullptr;
            }
        }
        cur_node = child;
    }
    return cur_node;
}



/**
 * @brief Prints the file system tree starting from the specified path.
 *
 * Recursively prints the tree structure of the file system with indentation.
 *
 * @param path The path to start printing from (defaults to root "/")
 * @param indent The initial indentation level (defaults to 0)
 */
void FileSystem::print_tree(const std::string &path, int indent) const {
    Node* node = resolve_path(path);
    if (!node){
        return;
    }

    // intendation part for tree structure
    for (int k = 0; k < indent; ++k){
        std::cout << ' ';
    }
    std::cout << node->get_name() << "\n";

    if (node->node_type() == NodeType::Folder) {
        Folder* folder = static_cast<Folder*>(node);
        for (const auto& name : folder->list_children()) {
            std::string child_path = (path == "/") ? "/" + name : path + "/" + name;
            print_tree(child_path, indent + 2);
        }
    }
}

std::vector<std::string> FileSystem::list_directory(const std::string& path) const {
    Node* node = resolve_path(path);
    if (!node || node->node_type() != NodeType::Folder)
        return {};
    return static_cast<Folder*>(node)->list_children();
}


