//
// Created by Eden Bar on 12/04/2022.
//

#ifndef Y1S2PROJECT4_Q4_H
#define Y1S2PROJECT4_Q4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct treeNode{
    int data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

typedef struct tree{
    TreeNode* root;
} Tree;


//required functions
void printByLevels(Tree tr);
Tree BuildTreeFromArray( int  *arr, int  size); //from question 1

//Tree functions
TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode *root);
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);
void checkAllocation(void* ptr);

//Queue functions
TreeNode *removeFromQueue(TreeNode **queue, int *front);
TreeNode **createQueue(int *front, int *rear);
void inputToQueue(TreeNode **queue, int *rear, TreeNode *node);


#endif //Y1S2PROJECT4_Q4_H
