#include <iostream>
#include <vector>

using namespace std;

class node {
  public:
    int data;
    vector <node*> children;

    node (int data) {
      this->data = data;
    }
};

class tree {
  public:
    node* root;

    tree () {
      root = nullptr;
    } 

    node* find_node (node* current_node, int data) {
      if (current_node == nullptr) {
        return nullptr;
      }

      else if (current_node->data == data) {
        return current_node;
      }

      else {
        for (int i = 0; i < current_node->children.size (); i++) {
          node* found_node = find_node (current_node->children [i], data);

          if (found_node != nullptr) {
            return found_node;
          }
        }

        return nullptr;
      }
    }

    void add_node (int parent_data, int child_data) {
      node* new_node = new node (child_data);

      if (root == nullptr) {
        root = new_node;
      }

      else {
        node* parent_node = find_node (root, parent_data);
        parent_node->children.push_back (new_node);
      }
    }
};

int method1(node* root){
  if(root == nullptr){
    return 0;
  }
  else {
    int valid = 1;
    for(int i = 0; i < root->children.size ();i++){
      valid += method1 (root->children[i]);
    }
    return valid;
  }
}

int method2(node*root){
  if(root == nullptr){
    return 0;
  }
  else{
    int max_height = 0;
    for(int i = 0; i < root->children.size(); i++){
      int current_height = method2(root->children[i]);
      if(current_height > max_height){
        max_height = current_height;
      }
    }
    return max_height + 1;
  }
}

int method3(node*root){
  if(root == nullptr){
    return 0;
  }
  else{
    int total = 0;
    for(int i = 0; i < root->children.size(); i++){
      if(root->children.size() == 2){
        total += root->children[i]->data; 
      }
      total += method3(root->children[i]);
    }
    return total;
  }
}

int method4(node*root, node* child){
  if(root == nullptr || child == nullptr){
    return 0;
  }
  else{
    for(int i = 0; i < root->children.size(); i++){
      if(root->children[i] == child){
        return root->data;
      }
      else{
        int parent = method4(root->children[i], child);
        if(parent != 0){
          return parent;
        }
      }
    }
    return 0;
  }
}





int main () {
  tree t1;
  t1.add_node (0, 1);
  t1.add_node (1, 2);
  t1.add_node (1, 3);
  t1.add_node (2, 4);
  t1.add_node (2, 5);
  t1.add_node (5, 6);
  t1.add_node (5, 7);
  t1.add_node (5, 8);

  tree t2;
  t2.add_node (0, 1);
  t2.add_node (1, 2);
  t2.add_node (1, 3);
  t2.add_node (2, 4);
  t2.add_node (2, 5);
  t2.add_node (2, 6);
  t2.add_node (3, 7);
  t2.add_node (3, 8);
  t2.add_node (5, 9);
  t2.add_node (5, 10);
  
  /*
  Question # 1:

  Given the root of a tree, create a method that calulates its size (i.e. how many nodes it has). Examples:

  tree # 1 -> 8
  tree # 2 -> 10
  */
  
  cout << "\nQuestion # 1:\n";
  cout << method1 (t1.root) << "\n";
  cout << method1 (t2.root) << "\n";

  /*
  Question # 2:

  Given the root of a tree, create a method that calculates the height of a tree (i.e. the length of the longest path from the root to any node). Examples:

  tree # 1 -> 4
  tree # 2 -> 4
  */

  cout << "\nQuestion # 2:\n";
  cout << method2 (t1.root) << "\n";
  cout << method2 (t2.root) << "\n";

  /*
  Question # 3:

  Given the root of a tree, create a method that calculates the sum of all the nodes with exactly 1 other sibling. Examples:

  tree # 1 -> 14 because 2 + 3 + 4 + 5 = 14
  tree # 2 -> 39 because 2 + 3 + 7 + 8 + 9 + 10 = 39
  */

  cout << "\nQuestion # 3:\n";
  cout << method3 (t1.root) << "\n";
  cout << method3 (t2.root) << "\n";

  /*
  Question # 4:

  Given a the root of a tree and a node, create a method that returns its parent node. Examples:

  tree # 1 node 2 -> 1
  tree # 2 node 9 -> 5
  */

  cout << "\nQuestion # 4:\n";
  cout << method4 (t1.root, t1.root->children [0]) << "\n";
  cout << method4 (t2.root, t2.root->children [0]->children [1]->children [0]) << "\n";

}
