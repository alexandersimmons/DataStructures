#include <iostream>
#include <memory>

using namespace std;

class BinaryTree{
  public:
  BinaryTree() : root(nullptr){}
  
  void Insert(int newData){
    InsertHelper(root, root, newData);
  }
  
  void Delete(int deleteData){
    DeleteHelper(root, root, deleteData);
  }

  void Search(int searchData){
    SearchHelper(root.get(), searchData);
  }
  
  void PreOrderTraversal(){
    PreOrderTravHelper(root.get());
  }
  
  void InOrderTraversal(){
    InOrderTravHelper(root.get());
  }
  
  void PostOrderTraversal(){
    PostOrderTravHelper(root.get());
  }

  private:
  struct Node{
    int data;
    int height;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
  };  

  unique_ptr<Node> root;
  
  void InsertHelper(unique_ptr<Node>& rootRef, unique_ptr<Node>& parentNode, int newData){
    if(rootRef == nullptr){
      rootRef = make_unique<Node>();
      rootRef->data = newData;
      rootRef->height = 1;
      parentNode->height = 1 + max((parentNode->left ? parentNode->left->height : -1),
                                      (parentNode->right ? parentNode->right->height : -1));
      BalanceHelper(parentNode);
      return;
    }else if(newData < rootRef->data){
      InsertHelper(rootRef->left, rootRef, newData);
    }else if(newData > rootRef->data){
      InsertHelper(rootRef->right, rootRef, newData);
    }else{
      cout<<"repeat entry"<<endl;
      return;
    }
    rootRef->height = 1 + max((rootRef->left ? rootRef->left->height : -1),
                                (rootRef->right ? rootRef->right->height : -1));
    BalanceHelper(rootRef);
  }
  
  void DeleteHelper(unique_ptr<Node>&rootRef, unique_ptr<Node>& parentNode, int deleteData){
    if(rootRef == nullptr){
      cout<<"data not found"<<endl;
    }else if(deleteData < rootRef->data){
      DeleteHelper(rootRef->left, rootRef, deleteData);
    }else if(deleteData > rootRef->data){
      DeleteHelper(rootRef->right, rootRef, deleteData);
    }else{
      if(rootRef->left == nullptr && rootRef->right == nullptr){
        rootRef.reset();
      }else if(rootRef->left == nullptr){
        rootRef = move(rootRef->right);
      }else if(rootRef->right == nullptr){
        rootRef = move(rootRef->left);
      }else{
        Node* replace = rootRef->right.get();
        while(replace->left != nullptr){
          replace = replace->left.get();
        }
        rootRef->data = replace->data;
        DeleteHelper(rootRef->right, rootRef, replace->data);
      }
    }
    if(rootRef != nullptr){
      rootRef->height = 1 + max((rootRef->left ? rootRef->left->height : -1),
                                  (rootRef->right ? rootRef->right->height : -1));
    }
    if(parentNode != nullptr){
      BalanceHelper(parentNode);
    }
  } 

  int CheckBalance(Node* rootRef){
    if(rootRef == nullptr){
      return 0;
    }
    int leftHeight = CheckBalance(rootRef->left.get());
    int rightHeight = CheckBalance(rootRef->right.get());
    if(leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1){
      return -1;
    }
    return max(leftHeight, rightHeight) + 1;
  }

  void RightRotation(unique_ptr<Node>&rootRef){
    unique_ptr<Node> leftChild = move(rootRef->left);
    unique_ptr<Node> rightLeftChild = move(leftChild->right);

    leftChild->right = move(rootRef);
    rootRef = move(leftChild);
    rootRef->left = move(rightLeftChild);

    rootRef->height = 1 + max((rootRef->left ? rootRef->left->height : -1), 
                                rootRef->right ? rootRef->right->height : -1);
    if(rootRef->right != nullptr){
      rootRef->right->height = 1 + max((rootRef->right->left ? rootRef->right->left->height : -1), 
                                        (rootRef->right->right ? rootRef->right->right->height : -1));
    }
  }

  void LeftRotation(unique_ptr<Node>&rootRef){
    unique_ptr<Node> rightChild = move(rootRef->right);
    unique_ptr<Node> leftRightChild = move(rightChild->left);

    rightChild->left = move(rootRef);
    rootRef = move(rightChild);
    rootRef->left = move(leftRightChild);

    rootRef->height = 1 + max((rootRef->left ? rootRef->left->height : -1),
                                (rootRef->right ? rootRef->right->height : -1));
    if(rootRef->left != nullptr){
      rootRef->left->height = 1 + max((rootRef->left->left ? rootRef->left->left->height : -1), 
                                        (rootRef->left->right ? rootRef->left->right->height : -1));
    }
  }

  int GetBalanceValue(Node* balNode){
    if(balNode == nullptr){
      return 0;
    }
    return (balNode->left->height) - (balNode->right->height);
  }

  void BalanceHelper(unique_ptr<Node>&rootRef){
    if(CheckBalance(rootRef.get()) != -1){
      cout<<"already balanced"<<endl;
      return;
    }
    int balanceValue = GetBalanceValue(rootRef.get());
    if(balanceValue > 1 && rootRef->data < rootRef->left->data){
      RightRotation(rootRef);
    }else if(balanceValue < -1 && rootRef->data > rootRef->left->data){
      LeftRotation(rootRef);
    }else if(balanceValue > 1 && rootRef->data > rootRef->left->data){
      LeftRotation(rootRef->left);
      RightRotation(rootRef);
    }else if(balanceValue < -1 && rootRef->data < rootRef->left->data){
      RightRotation(rootRef->right);
      LeftRotation(rootRef);
    }
    if(rootRef->left != nullptr){
      BalanceHelper(rootRef->left);
    }
    if(rootRef->right != nullptr){
      BalanceHelper(rootRef->right);
    }
  }
  
  void SearchHelper(Node* rootRef, int searchData)const{
    if(rootRef == nullptr){
      cout<<"failure"<<endl;
      return;
    }else if(searchData < rootRef->data){
      SearchHelper(rootRef->left.get(), searchData);
    }else if(searchData > rootRef->data){
      SearchHelper(rootRef->right.get(), searchData);
    }else{
      cout<<"found "<<searchData<<endl;
    }
  }
  
  void PreOrderTravHelper(Node* rootRef)const{
    if(rootRef == nullptr){
      return;
    }
    cout<<"Node: "<<rootRef->data<<endl;
    PreOrderTravHelper(rootRef->left.get());
    PreOrderTravHelper(rootRef->right.get());
  }
  
  void InOrderTravHelper(Node* rootRef)const{
    if(rootRef == nullptr){
      return;
    }
    InOrderTravHelper(rootRef->left.get());
    cout<<"Node: "<<rootRef->data<<endl;
    InOrderTravHelper(rootRef->right.get());
  }
  
  void PostOrderTravHelper(Node* rootRef)const{
    if(rootRef == nullptr){
      return;
    }
    PostOrderTravHelper(rootRef->left.get());
    PostOrderTravHelper(rootRef->right.get());
    cout<<"Node: "<<rootRef->data<<endl;
  }
};

int main(){}