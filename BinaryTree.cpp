/*
Binary Tree in C++
In need of:
Min, Max, Floor and Ceil Finder
Balancing
*/

#include <iostream>

using namespace std;

struct Node{
  int data;
  Node* left;
  Node* right;
};

class BinaryTree{
    Node* root;
  
    void StoreInOrder(Node*& rootRef, vector<int>& nodes){
      if(rootRef == NULL){
        return;
      }
      StoreInOrder(rootRef->left, nodes);
      nodes.push_back(rootRef->data);
      StoreInOrder(rootRef->right, nodes);
    }

    void InsertHelper(struct Node*& rootRef, int newData){
      if(rootRef == NULL){
        rootRef = new Node();
        rootRef->data = newData;
        rootRef->left = NULL;
        rootRef->right = NULL;
        return;
      }
      
      if(rootRef->data > newData){
        InsertHelper(rootRef->left, newData);
      }else if(rootRef->data < newData){
        InsertHelper(rootRef->right, newData);
      }else{
        cout << "repeat entry" << endl;
      }
    }
    
    void DeleteHelper(struct Node*& rootRef, int deleteData){
      if(rootRef == NULL){
        cout<<"Nothing to delete"<<endl;
        return;
      }

      if(deleteData < rootRef->data){
        DeleteHelper(rootRef->left, deleteData);
      }else if(deleteData > rootRef->data){
        DeleteHelper(rootRef->right, deleteData);
      }else if(deleteData == rootRef->data){
        Node* temp = rootRef;
        if(rootRef->left == NULL && rootRef->right == NULL){
          delete rootRef;
          rootRef = NULL;
        }else if(rootRef->left == NULL){
          rootRef = rootRef->right;
          delete temp;
        }else if(rootRef->right == NULL){
          rootRef = rootRef->left;
          delete temp;
        }else if(rootRef->left != NULL && rootRef->right != NULL){
          Node* replace = rootRef->right;
          while(replace->left != NULL){
            replace = replace->left;
          }
          rootRef->data = replace->data;
          DeleteHelper(rootRef->right, replace->data);
        }
      }
    }

    void BalanceHelper(struct Node*& rootRef){
      vector<int> nodes;
      StoreInOrder(rootRef, nodes);
    }

    void SearchHelper(struct Node* rootRef, int findData){
      if(rootRef == NULL){
        cout<< "failure" << endl;
        return;
      }
      
      if(findData < rootRef->data){
        SearchHelper(rootRef->left, findData);
      }else if(findData > rootRef->data){
        SearchHelper(rootRef->right, findData);
      }else if(findData == rootRef->data){
        cout << "found data" << endl;
        return;
      }
    }

    void PreOrderTraversalHelper(struct Node* rootRef){
      if(rootRef == NULL){
        return;
      }
      cout << "Node: " << rootRef->data << endl;
      PreOrderTraversalHelper(rootRef->left);
      PreOrderTraversalHelper(rootRef->right);
    }

    void InOrderTraversalHelper(struct Node* rootRef){
      if(rootRef == NULL){
        return;
      }
      InOrderTraversalHelper(rootRef->left);
      cout << "Node: " << rootRef->data << endl;
      InOrderTraversalHelper(rootRef->right);
    } 

    void PostOrderTraversalHelper(struct Node* rootRef){
      if(rootRef == NULL){
        return;
      }
      PostOrderTraversalHelper(rootRef->left);
      PostOrderTraversalHelper(rootRef->right);
      cout << "Node: " << rootRef->data << endl;
    } 

  public:
    BinaryTree() : root(NULL){}
    
    void Insert(int newData){
      InsertHelper(root, newData);
    }
    
    void Delete(int delData){
      DeleteHelper(root, delData);
    }

    void Balance(){
      BalanceHelper(root);
    }

    void Search(int findData){
      SearchHelper(root, findData);
    }
    
    void PreOrderTraversal(){
      PreOrderTraversalHelper(root);
    }

    void InOrderTraversal(){
      InOrderTraversalHelper(root);
    }

    void PostOrderTraversal(){
      PostOrderTraversalHelper(root);
    }
};


int main(){
  BinaryTree bTree;
  bTree.Insert(5);
  bTree.Insert(10);
  bTree.Insert(4);
  bTree.Insert(2);
  bTree.Insert(13);
  bTree.Insert(31);
  bTree.Insert(1);
  bTree.Insert(3);
  bTree.Insert(18);
  bTree.InOrderTraversal();
  bTree.Search(13);
  bTree.Search(55);
  return 0;
}
