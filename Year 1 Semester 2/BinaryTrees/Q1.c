//
// Created by Eden Bar on 31/03/2022.
//

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

//Tree structs
typedef struct treeNode {
    unsigned int data;
    struct treeNode *left;
    struct treeNode *right;
}TreeNode;

typedef struct tree
{
    TreeNode *root;
}Tree;

//required function
Tree BuildTreeFromArray( int  *arr, int  size);

//Tree functions
TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode *root);
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);
void checkAllocation(void* ptr);


void main()
{
    int size, i;
    int arr[SIZE];
    Tree tr;

    printf("Please enter the number of items: ");
    scanf("%d", &size);
    for(i=0; i<size; i++)
        scanf("%d", &arr[i]);


    tr = BuildTreeFromArray(arr, size);
    printf("The tree in inorder (LDR) format:\n");
    printTreeInorder(tr); //Print the tree in-order (LDR)
    freeTree(tr);

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