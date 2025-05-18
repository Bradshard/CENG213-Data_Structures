#include "../include/File.h"
#include "../include/FileSystem.h"
#include "../include/Folder.h"
#include "../include/Link.h"
#include <algorithm>
#include <gtest/gtest.h>

// Basic Node Tests
TEST(NodeTest, BasicNodeOperations) {
  File file("test.txt", nullptr, "Hello World");

  EXPECT_EQ(file.get_name(), "test.txt");
  EXPECT_EQ(file.get_parent(), nullptr);
  EXPECT_EQ(file.node_type(), NodeType::File);
  EXPECT_EQ(file.read_content(), "Hello World");

  file.write_content("Updated content");
  EXPECT_EQ(file.read_content(), "Updated content");
}

class DummyNode : public Node {
public:
  DummyNode(const std::string &name, Node *parent = nullptr)
      : Node(name, parent) {}

  NodeType node_type() const override {
    return NodeType::File; // Arbitrary choice
  }

  Node *clone(Node *parent = nullptr) const override {
    return new DummyNode(name_, parent);
  }
  void test_set_parent(Node *new_parent) { set_parent(new_parent); }
};

TEST(NodeTest, ParentChildRelationship) {
  DummyNode root("root");
  DummyNode child("child", &root);

  EXPECT_EQ(root.get_name(), "root");
  EXPECT_EQ(root.get_parent(), nullptr);

  EXPECT_EQ(child.get_name(), "child");
  EXPECT_EQ(child.get_parent(), &root);
}

TEST(NodeTest, CloneCreatesCopyWithParent) {
  DummyNode parent("parent");
  DummyNode original("child", &parent);

  Node *copy = original.clone(&parent);

  EXPECT_NE(copy, &original);
  EXPECT_EQ(copy->get_name(), "child");
  EXPECT_EQ(copy->get_parent(), &parent);
  EXPECT_EQ(copy->node_type(), NodeType::File);

  delete copy; // cleanup
}

// --- DummyNode Clone Tests (using your DummyNode) ---
TEST(NodeTest, DummyNodeClone) {
  DummyNode proto("proto");
  // clone detaches by default
  Node *c1 = proto.clone();
  EXPECT_EQ(c1->get_name(), "proto");
  EXPECT_EQ(c1->get_parent(), nullptr);
  delete c1;
  // clone with parent
  Folder bar("bar");
  Node *c2 = proto.clone(&bar);
  EXPECT_EQ(c2->get_parent(), &bar);
  delete c2;
}
// File Tests
TEST(FileTest, FileOperations) {
  // Create file with content
  File file("document.txt", nullptr, "Initial content");
  EXPECT_EQ(file.read_content(), "Initial content");

  // Modify content
  file.write_content("Modified content");
  EXPECT_EQ(file.read_content(), "Modified content");

  // Clone file
  Node *cloned = file.clone();
  File *cloned_file = static_cast<File *>(cloned);

  EXPECT_EQ(cloned_file->get_name(), "document.txt");
  EXPECT_EQ(cloned_file->read_content(), "Modified content");
  EXPECT_EQ(cloned_file->get_parent(), nullptr);

  delete cloned;
}

// --- File Clone Tests ---
TEST(FileTest, CloneWithoutParent) {
  File orig("orig.txt", nullptr, "Some content");
  Node *cloned = orig.clone();
  ASSERT_NE(cloned, nullptr);
  auto *f = static_cast<File *>(cloned);
  EXPECT_EQ(f->get_name(), "orig.txt");
  EXPECT_EQ(f->get_parent(), nullptr);
  EXPECT_EQ(f->read_content(), "Some content");
  delete cloned;
}

TEST(FileTest, CloneWithParent) {
  Folder parent("parent");
  File orig("file.txt", nullptr, "Data");
  Node *cloned = orig.clone(&parent);
  ASSERT_NE(cloned, nullptr);
  auto *f = static_cast<File *>(cloned);
  EXPECT_EQ(f->get_parent(), &parent);
  delete cloned;
}

// Folder Tests
TEST(FolderTest, FolderOperations) {
  Folder root("root");

  // Add files and folders
  root.add_file("file1.txt", "Content 1");
  root.add_file("file2.txt", "Content 2");
  root.add_folder("subfolder");

  // Verify children
  auto children = root.list_children();
  EXPECT_EQ(children.size(), 3);
  EXPECT_TRUE(std::find(children.begin(), children.end(), "file1.txt") !=
              children.end());
  EXPECT_TRUE(std::find(children.begin(), children.end(), "file2.txt") !=
              children.end());
  EXPECT_TRUE(std::find(children.begin(), children.end(), "subfolder") !=
              children.end());

  // Find child
  Node *file1 = root.find_child("file1.txt");
  ASSERT_NE(file1, nullptr);
  EXPECT_EQ(file1->get_name(), "file1.txt");
  EXPECT_EQ(file1->node_type(), NodeType::File);

  Node *subfolder = root.find_child("subfolder");
  ASSERT_NE(subfolder, nullptr);
  EXPECT_EQ(subfolder->get_name(), "subfolder");
  EXPECT_EQ(subfolder->node_type(), NodeType::Folder);

  // Verify parent links
  EXPECT_EQ(file1->get_parent(), &root);
  EXPECT_EQ(subfolder->get_parent(), &root);

  // Remove child
  EXPECT_TRUE(root.remove_child("file2.txt"));
  children = root.list_children();
  EXPECT_EQ(children.size(), 2);
  EXPECT_TRUE(std::find(children.begin(), children.end(), "file2.txt") ==
              children.end());

  // Test clone
  Node *cloned = root.clone();
  Folder *cloned_folder = static_cast<Folder *>(cloned);

  children = cloned_folder->list_children();
  EXPECT_EQ(children.size(), 2);

  delete cloned;
}

// Link Tests
TEST(LinkTest, LinkOperations) {
  Folder root("root");
  root.add_file("target.txt", "Target content");

  Node *target = root.find_child("target.txt");
  ASSERT_NE(target, nullptr);

  // Create link
  root.add_link("link_to_target", target);

  // Find link
  Node *link_node = root.find_child("link_to_target");
  ASSERT_NE(link_node, nullptr);
  EXPECT_EQ(link_node->node_type(), NodeType::Link);

  Link *link = static_cast<Link *>(link_node);
  EXPECT_EQ(link->get_target(), target);

  // Clone link
  Node *cloned = link->clone();
  Link *cloned_link = static_cast<Link *>(cloned);

  EXPECT_EQ(cloned_link->get_name(), "link_to_target");
  EXPECT_EQ(cloned_link->get_target(), target);

  delete cloned;
}
// --- Link Clone Tests ---
TEST(LinkTest, CloneOperations) {
  Folder root("root");
  root.add_file("target.txt", "XYZ");
  Node *target = root.find_child("target.txt");
  ASSERT_NE(target, nullptr);

  Link link("mylink", &root, target);
  // clone without parent
  Node *c1 = link.clone();
  ASSERT_NE(c1, nullptr);
  auto *l1 = static_cast<Link *>(c1);
  EXPECT_EQ(l1->get_name(), "mylink");
  EXPECT_EQ(l1->get_parent(), nullptr);
  EXPECT_EQ(l1->get_target(), target);
  delete c1;

  // clone with parent
  Folder foo("foo");
  Node *c2 = link.clone(&foo);
  ASSERT_NE(c2, nullptr);
  auto *l2 = static_cast<Link *>(c2);
  EXPECT_EQ(l2->get_parent(), &foo);
  delete c2;
}
// FileSystem Basic Tests
TEST(FileSystemTest, BasicOperations) {
  FileSystem fs;

  // Create folders
  fs.create_folder("/folder1");
  fs.create_folder("/folder1/subfolder1");
  fs.create_folder("/folder2");

  // Create files
  fs.create_file("/folder1/file1.txt", "Content of file1");
  fs.create_file("/folder2/file2.txt", "Content of file2");

  // Verify nodes
  Node *folder1 = fs.find_node("/folder1");
  ASSERT_NE(folder1, nullptr);
  EXPECT_EQ(folder1->get_name(), "folder1");
  EXPECT_EQ(folder1->node_type(), NodeType::Folder);

  Node *file1 = fs.find_node("/folder1/file1.txt");
  ASSERT_NE(file1, nullptr);
  EXPECT_EQ(file1->get_name(), "file1.txt");
  EXPECT_EQ(file1->node_type(), NodeType::File);
  EXPECT_EQ(static_cast<File *>(file1)->read_content(), "Content of file1");

  // List directory
  auto contents = fs.list_directory("/folder1");
  EXPECT_EQ(contents.size(), 2);
  EXPECT_TRUE(std::find(contents.begin(), contents.end(), "file1.txt") !=
              contents.end());
  EXPECT_TRUE(std::find(contents.begin(), contents.end(), "subfolder1") !=
              contents.end());
}

// FileSystem Link Tests
TEST(FileSystemTest, LinkOperations) {
  FileSystem fs;

  fs.create_folder("/folder1");
  fs.create_file("/folder1/target.txt", "Target content");
  fs.create_link("/folder1/link_to_target", "/folder1/target.txt");

  // Verify link
  Node *link = fs.find_node("/folder1/link_to_target");
  ASSERT_NE(link, nullptr);
  EXPECT_EQ(link->node_type(), NodeType::Link);

  Link *link_ptr = static_cast<Link *>(link);
  Node *target = link_ptr->get_target();
  ASSERT_NE(target, nullptr);
  EXPECT_EQ(target->get_name(), "target.txt");
}

// FileSystem Copy/Move Tests
TEST(FileSystemTest, CopyMoveOperations) {
  FileSystem fs;

  // Setup
  fs.create_folder("/source");
  fs.create_folder("/dest");
  fs.create_file("/source/file.txt", "Original content");

  // Copy operation
  fs.copy_node("/source/file.txt", "/dest/file_copy.txt");

  Node *original = fs.find_node("/source/file.txt");
  Node *copy = fs.find_node("/dest/file_copy.txt");

  ASSERT_NE(original, nullptr);
  ASSERT_NE(copy, nullptr);
  EXPECT_EQ(static_cast<File *>(original)->read_content(), "Original content");
  EXPECT_EQ(static_cast<File *>(copy)->read_content(), "Original content");

  // Move operation
  fs.move_node("/source/file.txt", "/dest/file_moved.txt");

  Node *moved = fs.find_node("/dest/file_moved.txt");
  ASSERT_NE(moved, nullptr);
  EXPECT_EQ(static_cast<File *>(moved)->read_content(), "Original content");

  // Original should no longer exist
  EXPECT_EQ(fs.find_node("/source/file.txt"), nullptr);
}

// FileSystem Remove Tests
TEST(FileSystemTest, RemoveOperations) {
  FileSystem fs;

  fs.create_folder("/folder");
  fs.create_file("/folder/file.txt", "Content");

  // Remove the file
  EXPECT_TRUE(fs.remove_node("/folder/file.txt"));
  EXPECT_EQ(fs.find_node("/folder/file.txt"), nullptr);

  // Check folder still exists
  EXPECT_NE(fs.find_node("/folder"), nullptr);

  // Remove folder
  EXPECT_TRUE(fs.remove_node("/folder"));
  EXPECT_EQ(fs.find_node("/folder"), nullptr);

  // Can't remove root
  EXPECT_FALSE(fs.remove_node("/"));
}

// FileSystem Deep Paths Tests
TEST(FileSystemTest, DeepPaths) {
  FileSystem fs;

  fs.create_folder("/a");
  fs.create_folder("/a/b");
  fs.create_folder("/a/b/c");
  fs.create_folder("/a/b/c/d");
  fs.create_folder("/a/b/c/d/e");

  fs.create_file("/a/b/c/d/e/deep_file.txt", "Deep content");

  Node *deep_file = fs.find_node("/a/b/c/d/e/deep_file.txt");
  ASSERT_NE(deep_file, nullptr);
  EXPECT_EQ(deep_file->get_name(), "deep_file.txt");
  EXPECT_EQ(static_cast<File *>(deep_file)->read_content(), "Deep content");
}

// FileSystem Edge Cases
TEST(FileSystemTest, EdgeCases) {
  FileSystem fs;

  // Empty paths
  EXPECT_EQ(fs.find_node(""), nullptr);

  // Create file/folder in non-existent parent
  // This should be handled gracefully in your implementation
  EXPECT_THROW(fs.create_file("/nonexistent/file.txt", "Content"), std::runtime_error);
  EXPECT_EQ(fs.find_node("/nonexistent/file.txt"), nullptr);

  // Remove non-existent node
  EXPECT_FALSE(fs.remove_node("/nonexistent"));

  // Duplicate folders
  fs.create_folder("/duplicate");
  EXPECT_THROW(fs.create_folder("/duplicate"), std::runtime_error);

  auto contents = fs.list_directory("/");
  int count = std::count(contents.begin(), contents.end(), "duplicate");
  EXPECT_EQ(count, 1); // Should only have one "duplicate" folder
}

// FileSystem Copy Constructor/Assignment Tests
TEST(FileSystemTest, CopyConstructorAssignment) {
  FileSystem fs1;
  fs1.create_folder("/folder1");
  fs1.create_file("/folder1/file1.txt", "Original content");

  // Test copy constructor
  FileSystem fs2(fs1);

  // Modify original
  fs1.create_file("/folder1/file2.txt", "New file in original");

  // Check copy
  Node *file1_in_copy = fs2.find_node("/folder1/file1.txt");
  ASSERT_NE(file1_in_copy, nullptr);
  EXPECT_EQ(static_cast<File *>(file1_in_copy)->read_content(),
            "Original content");

  // New file should not exist in copy
  EXPECT_EQ(fs2.find_node("/folder1/file2.txt"), nullptr);

  // Test assignment operator
  FileSystem fs3;
  fs3 = fs1;

  // Modify original again
  fs1.create_folder("/folder2");

  // Check assigned copy
  Node *file2_in_copy = fs3.find_node("/folder1/file2.txt");
  ASSERT_NE(file2_in_copy, nullptr);

  // New folder should not exist in assigned copy
  EXPECT_EQ(fs3.find_node("/folder2"), nullptr);
}

// --- FileSystem Deep Copy (copy_node) Tests ---
TEST(FileSystemTest, CopyNodeOperations) {
  FileSystem fs;
  fs.create_folder("/a");
  fs.create_folder("/a/b");
  fs.create_file("/a/b/data.txt", "hello");
  // deep copy /a/b → /b_copy
  fs.copy_node("/a/b", "/b_copy");
  Node *n = fs.find_node("/b_copy/data.txt");
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(n->node_type(), NodeType::File);
  EXPECT_EQ(static_cast<File *>(n)->read_content(), "hello");
  // original still exists
  EXPECT_NE(fs.find_node("/a/b/data.txt"), nullptr);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
