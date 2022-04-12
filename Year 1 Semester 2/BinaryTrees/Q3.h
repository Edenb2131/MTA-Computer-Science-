//
// Created by Eden Bar on 12/04/2022.
//

#ifndef Y1S2PROJECT4_Q3_H
#define Y1S2PROJECT4_Q3_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct listNode  {
    int data;
    struct listNode* next;
} ListNode;

typedef struct list  {
    ListNode* head;
    ListNode* tail;
} List;

typedef struct  treeNode {
    int data;
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

typedef struct tree{
    TreeNode* root;
    List leafList;   /*רשימה מקושרת של כל העלים בעץ*/
} Tree;



#define LEFT  0
#define RIGHT 1

//Required function
Tree AddLeaf (Tree tr, TreeNode *p, int branchSelect, int data);
Tree BuildTreeFromArrayWithLeafList(int *arr, int size);
Tree BuildTreeFromArray(int* arr, int size);
List buildList(Tree tr);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
TreeNode* findParentRec(TreeNode *root, int parentData, int branchSelect);


//Tree functions
TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode *root);
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);
void checkAllocation(void* ptr);
void printLeafList(Tree tr);
//void updateListOfLeaves(ListNode *head, int pData, int data, int branchSelect);
Tree updateListOfLeaves(Tree tr);

//List functions
void buildTheListWithLeaves(TreeNode *root, List *list);
List buildList(Tree tr);
void checkAllocationList(void* ptr); //Allocation
void makeEmptyList(List* lst); //Making new list
int isEmptyList(List lst);//Checking if the list is empty
void freeList(List* lst); // free allocation of list
void printList(List* lst); //Printing lists
ListNode* createNewListNode(int data, ListNode* next); // create new list with given data
void insertDataToEndList(List* lst, int data); // Insert data to end
void insertNodeToEndList(List* lst, ListNode* newTail); // Insert Node to end





#endif //Y1S2PROJECT4_Q3_H
