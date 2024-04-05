#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "List.h"
#include "Stack.h"
#include <vector>

#include <iostream>

template <typename K, typename V>

class BinaryTree{
public:

  struct Node{
    K key;
    List<V> values;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* up = nullptr;
  };

  BinaryTree(){}

  BinaryTree(const BinaryTree& other){
    Stack<Node*> stack;
    Node* current = other.root;
    while (!stack.empty() || current){
      if(current){
        stack.push(current);
        insertElements(current->key, current->values);
        current = current->left;
      } else {
        current = stack.top()->right;
        stack.pop();
      }
    }
  }

  BinaryTree(BinaryTree&& other){
    root = other.root;
    other.root = nullptr;
  }

  BinaryTree& operator=(const BinaryTree& other){
    if(&other = this){
      return *this;
    }
    BinaryTree tmp(other);
    std::swap(tmp.root, root);
    return *this;
  }

  BinaryTree& operator=(BinaryTree&& other){
    if(&other = this){
      return *this;
    }
    BinaryTree tmp(other);
    std::swap(tmp.root, root);
    return *this;
  }

  V& getElement(const K& key, int num = -1){
    Node* node = findOrCreateNode(key);
    if(!node){
      throw std::out_of_range("");
    } else {
      if(num > node->values.size() || num < -1){
        throw std::out_of_range("");
      }
      if(num == -1){
        return node->values.back();
      }
      auto listNode = node->values.GetHead();
      for (int i = 0; i < num; ++i){
        listNode = listNode->next;
      }
      return listNode->value;
    }
  }

  // for tests
  List<V> getAllElements(const K& key){
    Node* node = findOrCreateNode(key);
    if(!node){
      throw std::out_of_range("");
    } 
    return node->values;
  }

  const V& getElement(const K& key, int num = -1) const {
    Node* node = findOrCreateNode(key);
    if(!node){
      throw std::out_of_range("");
    } else {
      if(num > node->values.size() || num < -1){
        throw std::out_of_range("");
      }
      if(num == -1){
        return node->values.back();
      }
      auto listNode = node->values.GetHead();
      for (int i = 0; i < num; ++i){
        listNode = listNode->next;
      }
      return listNode->value;
    }
  }

  void insertElement(const K& key, const V& value){
    Node* node = findOrCreateNode(key, true);
    node->values.pushBack(value);
  }

  void removeElement(const K& key){
    Node* node = findOrCreateNode(key);
    if (!node){
      return;
    }
    node->values.popFront();
    if (node->values.size() == 0){
      removeNode(node);
    }
  }

  const K& findFirstGreater(const K& key){
    Node* ans = nullptr;  
    Node* current = root;
    while(current){
      if(key < current->key){
        if (!ans || current->key < ans->key){
          ans = current;
        }
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (ans){
      return ans->key;
    } else {
      throw std::out_of_range("");
    }
    
  }

  void printTree(){
    Stack<Node*> stack;
    Node* current = root;
    while (!stack.empty() || current){
      if(current){
        stack.push(current);
        current = current->left;
      } else {
        std::cout << "key: " << stack.top()->key << std::endl;
        auto listNode = stack.top()->values.GetHead();
        for (int i = 0; i < stack.top()->values.size(); ++i){
          std::cout << "element #" << i << ": " << listNode->value << std::endl;
          listNode = listNode->next;
        }
        std::cout << std::endl;
        current = stack.top()->right;
        stack.pop();
      }
    }
  }

  void printTree(const K& key){
    Stack<Node*> stack;
    Node* current = root;
    while (!stack.empty() || current){
      if(current){
        stack.push(current);
        current = current->left;
      } else {
        if(stack.top()->key > key){
          break;
        }
        std::cout << "key: " << stack.top()->key << std::endl;
        auto listNode = stack.top()->values.GetHead();
        for (int i = 0; i < stack.top()->values.size(); ++i){
          std::cout << "element #" << i << ": " << listNode->value << std::endl;
          listNode = listNode->next;
        }
        std::cout << std::endl;
        current = stack.top()->right;
        stack.pop();
      }
    }
  }

  // begin for test 
  std::vector<K> toVectorLNR(){
    std::vector<K> ans;
    Stack<Node*> stack;
    Node* current = root;
    while (!stack.empty() || current){
      if(current){
        stack.push(current);
        current = current->left;
      } else {
        ans.push_back(stack.top()->key);
        current = stack.top()->right;
        stack.pop();
      }
    }
    return ans;
  }

  std::vector<K> toVectorNLR(){
    std::vector<K> ans;
    Stack<Node*> stack;
    Node* current = root;
    while (!stack.empty() || current){
      if(current){
        ans.push_back(current->key);
        if(current->right){
          stack.push(current->right);
        }
        current = current->left;
      } else {
        current = stack.top();
        stack.pop();
      }
    }
    return ans;
  }

  // end for tests

  ~BinaryTree(){
    Stack<Node*> stack;
    Node* current = root;
    while (!stack.empty() || current){
      if(current){
        stack.push(current);
        current = current->left;
      } else {
        current = stack.top()->right;
        delete stack.top();
        stack.pop();
      }
    }
  }

private:
  void insertElements(const K& key, const List<V>& values){
    Node* node = findOrCreateNode(key, true);
    node->values = values;
  }

  void removeNode(Node* node){
    if(!node){
      return;
    }
    // leaf case
    if (node->left == nullptr && node->right == nullptr){
      Node* parentNode = node->up;
      if(parentNode){
        if (parentNode->left == node){
          parentNode->left = nullptr;
        } else {
          parentNode->right = nullptr;
        }
        delete node;
      } else {
        delete root;
        root = nullptr;
      }

    } else if(node->left == nullptr || node->right == nullptr) { // one child case
      Node* childNode = (node->left != nullptr) ? node->left : node->right;
      Node* parentNode = node->up;
      if(parentNode){
        if (parentNode->left == node){
          parentNode->left = childNode;
        } else {
          parentNode->right = childNode;
        }
        childNode->up = parentNode;
        delete node;
      } else {
        delete root;
        root = childNode;
        root->up = nullptr;
      }
      
    } else { // 2 children case
      Node* inorderNode  = node->right;
      while (inorderNode->left){
        inorderNode = inorderNode->left;
      }
      std::swap(node->values, inorderNode->values);
      std::swap(node->key, inorderNode->key);
      removeNode(inorderNode);
    }
  }

  Node* findOrCreateNode(const K& key, bool create = false){
    if (!root){
      if(create){
        root = new Node;
        root->key = key;
      } 
      return root;
    }
    Node* current = root;
    while (current->key != key){
      if (key < current->key) {
        if (current->left){
          current = current->left;
        } else {
          if (create){
            Node* new_node = new Node;
            new_node->up = current;
            new_node->key = key;
            current->left = new_node;
            return new_node;
          } else {
            return nullptr;
          }
        }
      } else {
        if (current->right){
          current = current->right;
        } else {
          if (create){
            Node* new_node = new Node;
            new_node->up = current;
            new_node->key = key;
            current->right = new_node;
            return new_node;
          } else {
            return nullptr;
          }
        }
      }
    }
    return current;
  }

  Node* root = nullptr;
};

// todo: nodes to vector convertor for easier testing

#endif
