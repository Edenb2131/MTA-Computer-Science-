//
// Created by Eden Bar on 12/04/2022.
//

#include "Q4.h"
//#include "Q4main.c"


void printByLevels(Tree tr){
//This function will use a Queue as a way for as to know what TreeNode to print
//The Queue will use the FIFO system - First In First Out
//That means, we will enter the first TreeNode of the level, after that the second.... and we print/
//The way we will use Queue system is by binary tree - that means
//We will build a Tree and each "root" we will put his children in (Left and then Right) in the system
// For example tree:
//              M
//             / \
//			  B   Q
//           / \   \
//			A   C   Z
//the newRoot will get the "M", then the Queue will be filled with "B" and "Q"" and then printing them
//Then newRoot will get the "B", then the Queue will be filled with "A" and "C"" and then printing them
//And so on .........
//As for efficiency : it will be O(N) as required :
//For each "root" we are doing no more then "if" and printing and then calling functions:
//(InputTo Queue and removeFromQueue are ordinary tasks and will be const.)
//There for, efficiency :  O(N + const) = ~O(n) as needed.

    int front;
    int rear;
    TreeNode **queue; // This will be out Queue
    TreeNode *newRoot; //this will be the root that will put his children in the Queue

    queue = createQueue(&front, &rear);
    newRoot = tr.root; // root of the tree
    while (newRoot != NULL){
        printf("%d ", newRoot->data);
        if (newRoot->left != NULL)
            inputToQueue(queue, &rear, newRoot->left); // Adding the left child to the Queue

        if (newRoot->right != NULL)
            inputToQueue(queue, &rear, newRoot->right);// Adding the right child to the Queue

        newRoot = removeFromQueue(queue, &front); //removing the node from Queue so we can continue
    }
}

Tree BuildTreeFromArray( int  *arr, int  size)
{
    Tree tr ;

//    if(size == 0){ // Does not have any roots
//        return tr;
//    }
    if(size == 1){ // Only have 1 item, it's the root
        tr.root= createNewTreeNode(arr[size-1], NULL, NULL);
        return tr;
    }
    else{
        int half = size/2;
        int halfHalf = (size/2)/2;
        tr.root= createNewTreeNode(arr[half], NULL, NULL);
        // tr.root->data = arr[(size/2)];

        //// [ - half/2 - - - half - - half+half/2 - -] ////
        if(arr[halfHalf + half + 1] != -1){
            Tree rightTree = BuildTreeFromArray(arr + half + 1,half); //Making new tree
            TreeNode *right = rightTree.root;
            tr.root->right =  right; // Connecting the new tree with the main tree

        }
        else{
            tr.root->right = NULL;
        }

        if(arr[halfHalf] != -1){
            Tree leftTree = BuildTreeFromArray(arr,half); //Making new tree
            TreeNode *left = leftTree.root;
            tr.root->left =  left; // Connecting the new tree with the main tree

        }
        else{
            tr.root->left = NULL;
        }
    }
    return tr;
}

TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right)
{
    TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));

    checkAllocation(res);
    res->data = data;
    res->left = left;
    res->right = right;

    return res;
}

void printTreeInorder(Tree tr)
{
    printTreeInorderRec(tr.root);
}

void printTreeInorderRec(TreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        printTreeInorderRec(root->left);
        printf("%d ", root->data);
        printTreeInorderRec(root->right);
    }
}

void freeTree(Tree tr)
{
    freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        freeTreeRec(root->left);
        freeTreeRec(root->right);
        free(root);
    }
}

void checkAllocation(void* ptr)
{
    if (ptr == NULL)
    {
        printf("Allocation error\n");
        exit(-1);
    }
}


//Queue functions
TreeNode **createQueue(int *front, int *rear){
    TreeNode **queue;
    queue = (TreeNode **)malloc(SIZE*sizeof(TreeNode *));
    checkAllocation(queue);
    *front = 0;
    *rear = 0;
    return queue;
}

void inputToQueue(TreeNode **queue, int *rear, TreeNode *node){
    queue[*rear] = node;
    (*rear)++;
    queue[*rear] = NULL;
}

TreeNode* removeFromQueue(TreeNode **queue, int *front){
    (*front)++;
    return queue[*front - 1];
}