#include <stdio.h>
#include <stdlib.h>

struct Node{
    double *point;
    struct Node *left;
    struct Node *right;
};

struct CompareAxis{
    int axis;
};

struct Node* CreateNode(double *newData, int k){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->point = (double*)malloc(k * sizeof(double));
    for(int i = 0; i < k; i++){
        newNode->point[i] = newData[i];
    }
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void InOrderTrav(struct Node *rootRef, int k){
    if(rootRef != NULL){
        InOrderTrav(rootRef->left, k);
        printf("Node : ");
        for(int i = 0; i < k; i++){
            if(i == k - 1){
                printf("%lf", rootRef->point[i]);
            }else{
                printf("%lf, ", rootRef->point[i]);
            }
            
        }
        printf("\n");
        InOrderTrav(rootRef->right, k);
    }
}

void DestroyTree(struct Node *rootRef, int k){
    if(rootRef == NULL){
        return;
    }
    DestroyTree(rootRef->left, k);
    DestroyTree(rootRef->right, k);
    free(rootRef->point);
    free(rootRef);
}

int GetHeight(struct Node* curNode){
    int leftHeight;
    int rightHeight;
    if(curNode == NULL){
        return 0;
    }
    leftHeight = GetHeight(curNode->left);
    rightHeight = GetHeight(curNode->right);
    if(leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1){
        return -1;
    }
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void FillArrayNodes(struct Node* rootRef, struct Node** arr, int* index){
    if(rootRef == NULL){
        return;
    }
    FillArrayNodes(rootRef->left, arr, index);
    arr[*index] = rootRef;
    (*index)++;
    FillArrayNodes(rootRef->right, arr, index);
}

int PreOrderCounter(struct Node *rootRef, int k, int counter){
    if(rootRef == NULL){
        return counter;
    }
    counter += 1;
    counter = PreOrderCounter(rootRef->left, k, counter);
    counter = PreOrderCounter(rootRef->right, k, counter);
    return counter;
}

int CompareNodes(const void* a, const void* b){
    struct Node* nodeA = *(struct Node**)a;
    struct Node* nodeB = *(struct Node**)b; 
    struct CompareAxis* compAxis = (struct CompareAxis*)a;
    int axis = compAxis->axis;
    return nodeA->point[axis] - nodeB->point[axis];
}

void BuildTree(struct Node* rootRef, struct Node** contNodes, int treeNodeCounter, int k, int depth){
    if(treeNodeCounter == 0){
        return;
    }
    struct CompareAxis compAxis;
    int axis = depth % k;
    compAxis.axis = axis;
    qsort(contNodes, treeNodeCounter, sizeof(*contNodes), CompareNodes);
    rootRef = NULL;
    rootRef = contNodes[treeNodeCounter / 2];
    //set root to medean of contNodes
    //split the array at the median
    //repeat until out of nodes
}

struct Node* DoBalance(struct Node* rootRef, int k){
    int index = 0;
    int treeNodeCounter = PreOrderCounter(rootRef, k, 0);
    struct Node** contNodes = (struct Node**)malloc(treeNodeCounter * sizeof(struct Node*));
    FillArrayNodes(rootRef, contNodes, &index);
    BuildTree(rootRef, contNodes, treeNodeCounter, k, 0);
    return rootRef;
}

void CheckBalance(struct Node* rootRef, int k){
    printf("checking balance\n");
    if(GetHeight(rootRef) == -1){
        printf("no bal\n");
        //rootRef = DoBalance(rootRef, k);
    }else{
        printf("is balanced\n");
    }
}

struct Node* Insert(struct Node** rootRef, double newData[], int depth, int k){
    int axis = depth % k;
    if(*rootRef == NULL){
        return CreateNode(newData, k);
    }else if(((*rootRef)->point[axis]) > newData[axis]){
        (*rootRef)->left = Insert(&((*rootRef)->left), newData, depth + 1, k);
    }else if(((*rootRef)->point[axis]) < newData[axis]){
        (*rootRef)->right = Insert(&((*rootRef)->right), newData, depth + 1, k);
    }else{
        int i;
        for(i = 0; i < k; i++){
            if((*rootRef)->point[i] != newData[i]){
                (*rootRef)->right = Insert(&((*rootRef)->right), newData, depth + 1, k);
                return *rootRef;
            }
        }
        printf("Repeat entry\n");
        return *rootRef;
    }
    CheckBalance(*rootRef, k);
    return *rootRef;
}

int main(){
    int k = 3;
    struct Node *root = NULL;
    double point1[3] = {12.1, 20.0, 30.0};
    double point2[3] = {10.5, 30.0, 40.0};
    double point3[3] = {15.7, 25.0, 35.0};
    double point4[3] = {7.9, 18.0, 33.0};
    double point5[3] = {13.4, 22.0, 31.0};
    double point6[3] = {57.2, -34.8, 12.6};
    double point7[3] = {-78.4, 90.1, -55.2};
    double point8[3] = {23.3, -6.9, 41.8};
    double point9[3] = {-17.5, 68.2, -19.0};
    double point10[3] = {5.6, -3.4, 30.7};
    double point11[3] = {-80.9, 14.1, -42.6};
    
    root = Insert(&root, point1, 0, k);
    root = Insert(&root, point2, 0, k);
    root = Insert(&root, point3, 0, k);
    root = Insert(&root, point4, 0, k);
    root = Insert(&root, point5, 0, k);
    root = Insert(&root, point6, 0, k);
    root = Insert(&root, point7, 0, k);
    root = Insert(&root, point8, 0, k);
    root = Insert(&root, point9, 0, k);
    root = Insert(&root, point10, 0, k);
    root = Insert(&root, point11, 0, k);
    
    InOrderTrav(root, k);
    DestroyTree(root, k);
    return 0;
}