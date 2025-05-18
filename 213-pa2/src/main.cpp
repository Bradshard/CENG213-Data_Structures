#include "File.h"
#include "FileSystem.h"
#include "Link.h"
#include <iostream>

int manual_test() {
  // Creating folders
  Folder *root = new Folder("/");
  root->add_folder("folder1");
  Folder *folder1 = static_cast<Folder *>(root->find_child("folder1"));
  std::cout << "Folder1 name: " << folder1->get_name() << std::endl;

  folder1->add_folder("folder2");
  Folder *folder2 = static_cast<Folder *>(folder1->find_child("folder2"));
  std::cout << "Folder2 name: " << folder2->get_name() << std::endl;

  // Create files
  folder1->add_file("file1.txt", "Hello World");
  std::cout << "Folder1 first child: " << folder1->list_children()[0]
            << std::endl;
  std::cout << "Folder1 second child: " << folder1->list_children()[1]
            << std::endl;
  File *file1 = static_cast<File *>(folder1->find_child("file1.txt"));
  std::cout << "What is written in file1: " << file1->read_content()
            << std::endl;

  folder2->add_file("file2.txt");
  std::cout << "Folder2 first child: " << folder2->list_children()[0]
            << std::endl;
  File *file2 = static_cast<File *>(folder2->find_child("file2.txt"));
  file2->write_content("I am file2 and I have nothing to do.");
  std::cout << "What is written inside file2: " << file2->read_content()
            << std::endl;

  // Create a link (pointing to file1 in folder1)
  folder2->add_link("link_to_file1", static_cast<Node *>(file1));
  Link *link1 = static_cast<Link *>(folder2->find_child("link_to_file1"));
  std::cout << "Folder2 first second child: " << folder2->list_children()[1]
            << std::endl;
  std::cout << "What is the name of the link: " << link1->get_name()
            << std::endl;
  Node *target_node = link1->get_target();
  std::cout << "Target node name: " << target_node->get_name() << std::endl;
  std::cout << "Target node type: "
            << static_cast<int>(target_node->node_type()) << std::endl;

  // FIXED: Only delete the root - it will handle deleting all children properly
  delete root;

  // DO NOT delete these - they're already deleted by the root's destructor
  // delete folder1;
  // delete folder2;
  // delete file1;
  // delete file2;
  // delete link1;

  return 0;
}
void filesystem_test() {
  FileSystem fs; // this creates root /
  fs.print_tree();
  // Create folders
  fs.create_folder("/folder1");
  fs.create_folder("/folder3");
  fs.print_tree();
  fs.create_folder("/folder1/subfolder1");
  fs.print_tree();
  fs.create_folder("/folder2");
  fs.print_tree();

  // Create files
  fs.create_file("/folder1/file1.txt", "Content of file1");
  fs.print_tree();
  fs.create_file("/folder2/file2.txt", "Content of file2");
  fs.print_tree();

  // Create a link (link in folder1 to file2)
  fs.create_link("/folder1/link_to_file2", "/folder2/file2.txt");
  fs.print_tree();

  // Find and check nodes
  Node *node1 = fs.find_node("/folder1/file1.txt");
  if (node1)
    std::cout << node1->get_name() << " found!" << '\n';
  else
    std::cout << "file1.txt not found!" << '\n';

  Node *node2 = fs.find_node("/folder1/link_to_file2");
  if (node2) {
    std::cout << node2->get_name() << " (link) found!" << '\n';
    Link *link = dynamic_cast<Link *>(node2);
    if (link) {
      std::cout << "Link points to: " << link->get_target()->get_name() << '\n';
    }
  } else {
    std::cout << "link_to_file2 not found!" << '\n';
  }

  Node *node3 = fs.find_node("/folder1/subfolder1");
  if (node3)
    std::cout << node3->get_name() << " found!" << '\n';
  else
    std::cout << "subfolder1 not found!" << '\n';
}

int main() {
  manual_test();
  filesystem_test();
  return 0;
}
