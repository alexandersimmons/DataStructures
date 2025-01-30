#include <iostream>
#include <memory>

template <typename T> class BinaryTree{
  public:
  BinaryTree() : root(nullptr){}
  
  void Insert(T newData){
    std::unique_ptr<Node> temp;
    InsertHelper(root, temp, newData);
  }
  
  void Delete(T deleteData){
    std::unique_ptr<Node> temp;
    DeleteHelper(root, temp, deleteData);
  }

  void Search(T searchData){
    SearchHelper(root.get(), searchData);
  }
  
  void PreOrderTraversal(){
    std::cout<<"PreOrder: ";
    PreOrderTravHelper(root.get());
    std::cout<<std::endl;
  }
  
  void InOrderTraversal(){
    std::cout<<"InOrder: ";
    InOrderTravHelper(root.get());
    std::cout<<std::endl;
  }
  
  void PostOrderTraversal(){
    std::cout<<"PostOrder: ";
    PostOrderTravHelper(root.get());
    std::cout<<std::endl;
  }

  private:
  struct Node{
    T data;
    int height;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };  

  std::unique_ptr<Node> root;
  
  void InsertHelper(std::unique_ptr<Node>& rootRef, std::unique_ptr<Node>& parentNode, T newData){  
    if(rootRef == nullptr){
      //cout<<"Inserting "<<newData<<endl;
      rootRef = std::make_unique<Node>();
      rootRef->data = newData;
      rootRef->height = 1;
      return;
    }else if(newData < rootRef->data){
      InsertHelper(rootRef->left, rootRef, newData);
    }else if(newData > rootRef->data){
      InsertHelper(rootRef->right, rootRef, newData);
    }else{
      std::cout<<"repeat entry"<<std::endl;
      return;
    }
    rootRef->height = 1 + std::max((rootRef->left ? rootRef->left->height : -1),
                                     (rootRef->right ? rootRef->right->height : -1));
    BalanceHelper(rootRef);
  }
  
  void DeleteHelper(std::unique_ptr<Node>&rootRef, std::unique_ptr<Node>& parentNode, T deleteData){
    if(rootRef == nullptr){
      std::cout<<"data not found"<<std::endl;
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
      rootRef->height = 1 + std::max((rootRef->left ? rootRef->left->height : -1),
                                       (rootRef->right ? rootRef->right->height : -1));
    }
    if(parentNode != nullptr){
      BalanceHelper(parentNode);
    }
  }

  void RightRotation(std::unique_ptr<Node>&rootRef){
    std::unique_ptr<Node> leftChild = move(rootRef->left);
    rootRef->left = move(leftChild->right);
    leftChild->right = move(rootRef);
    rootRef = move(leftChild);
    rootRef->height = 1 + std::max((rootRef->left ? rootRef->left->height : -1), 
                                     (rootRef->right ? rootRef->right->height : -1));
    if(rootRef->right != nullptr){
      rootRef->right->height = 1 + std::max((rootRef->right->left ? rootRef->right->left->height : -1), 
                                              (rootRef->right->right ? rootRef->right->right->height : -1));
    }
  }

  void LeftRotation(std::unique_ptr<Node>&rootRef){
    std::unique_ptr<Node> rightChild = move(rootRef->right);
    rootRef->right = move(rightChild->left);
    rightChild->left = move(rootRef);
    rootRef = move(rightChild);
    rootRef->height = 1 + std::max((rootRef->left ? rootRef->left->height : -1),
                                    (rootRef->right ? rootRef->right->height : -1));
    if(rootRef->left != nullptr){
      rootRef->left->height = 1 + std::max((rootRef->left->left ? rootRef->left->left->height : -1), 
                                            (rootRef->left->right ? rootRef->left->right->height : -1));
    }
  }

  int GetBalanceValue(Node* balNode){
    if(balNode == nullptr){
      return 0;
    }
    return (balNode->left ? balNode->left->height : 0) - (balNode->right ? balNode->right->height : 0);
  }

  void BalanceHelper(std::unique_ptr<Node>&rootRef){
    if(rootRef == nullptr){
      return;
    }
    int balanceValue = GetBalanceValue(rootRef.get());
    if(balanceValue > 1){
      if(GetBalanceValue(rootRef->left.get()) >= 0){
        RightRotation(rootRef);
      }else{
        LeftRotation(rootRef->left);
        RightRotation(rootRef);
      }
    }else if(balanceValue < -1){
      if(GetBalanceValue(rootRef->right.get()) <= 0){
        LeftRotation(rootRef);
      }else{
        RightRotation(rootRef->right);
        LeftRotation(rootRef);
      }
    }
    rootRef->height = 1 + std::max((rootRef->left ? rootRef->left->height : -1),
                                    (rootRef->right ? rootRef->right->height : -1));
  }
  
  void SearchHelper(Node* rootRef, T searchData)const{
    if(rootRef == nullptr){
      std::cout<<"failure"<<std::endl;
      return;
    }else if(searchData < rootRef->data){
      SearchHelper(rootRef->left.get(), searchData);
    }else if(searchData > rootRef->data){
      SearchHelper(rootRef->right.get(), searchData);
    }else{
      std::cout<<"found "<<searchData<<std::endl;
    }
  }
  
  void PreOrderTravHelper(Node* rootRef)const{
    if(rootRef == nullptr){
      return;
    }
    std::cout<<rootRef->data<<" ";
    PreOrderTravHelper(rootRef->left.get());
    PreOrderTravHelper(rootRef->right.get());
  }
  
  void InOrderTravHelper(Node* rootRef)const{
    if(rootRef == nullptr){
      return;
    }
    InOrderTravHelper(rootRef->left.get());
    std::cout<<rootRef->data<<" ";
    InOrderTravHelper(rootRef->right.get());
  }
  
  void PostOrderTravHelper(Node* rootRef)const{
    if(rootRef == nullptr){
      return;
    }
    PostOrderTravHelper(rootRef->left.get());
    PostOrderTravHelper(rootRef->right.get());
    std::cout<<rootRef->data<<" ";
  }
};