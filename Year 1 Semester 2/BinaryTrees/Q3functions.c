//
// Created by Eden Bar on 12/04/2022.
//

#include "Q3.h"


Tree BuildTreeFromArrayWithLeafList(int *arr, int size)
{
    Tree tr;
    List leafList;
    tr = BuildTreeFromArray(arr, size);
    leafList = buildList(tr);
    tr.leafList = leafList;
    return tr;
}

TreeNode* findParent(Tree tr, int parentData, int branchSelect){

    TreeNode* p = findParentRec(tr.root,parentData, branchSelect);
    return p;
}

TreeNode* findParentRec(TreeNode *root, int parentData, int branchSelect){

    if(root == NULL){
        //printf("Didnt find");
        return NULL;
    }
    else{
        //Maybe it's the root
         if ((root->data == parentData) && ((root->left == NULL && branchSelect == LEFT) || (root->right == NULL && branchSelect == RIGHT)))
            return root;

         //else we check Left and Right
         TreeNode* res;
         res = findParentRec(root->left, parentData, branchSelect); //searching left
         if (res == NULL)
             res = findParentRec(root->right, parentData, branchSelect); //searching right
         return res;
    }

}

Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data){

    //creating new TreeNode
    TreeNode* new = createNewTreeNode(data, NULL, NULL);
    new->parent = p;
    //Connecting the new TreeNode to the right location
    if(branchSelect == LEFT)
         p->left = new;
    else if(branchSelect == RIGHT)
        p->right = new;
    else{
        printf("Wrong Branch-select!");
        exit(1);
    }

    //updating List of leaves
    tr = updateListOfLeaves(tr);

    return tr;

}

Tree updateListOfLeaves(Tree tr){

//    while(head!= NULL){
//
//        if(head->data == pData)
//            head->data = data;
//            //Swap successfully
//
//        head = head->next;
//    }

    freeList(&tr.leafList);
    tr.leafList = buildList(tr);
    return tr;
}

void printLeafList(Tree tr){
    printList(&(tr.leafList));
}

Tree BuildTreeFromArray(int* arr, int size){
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

List buildList(Tree tr)
{
    List list;
    makeEmptyList(&list);
    buildTheListWithLeaves(tr.root, &list);
    return list;
}

void buildTheListWithLeaves(TreeNode *root, List *list){

    if ((root->left == NULL) && (root->right == NULL)){
        insertDataToEndList(list, root->data);
    }
    else{
        if (root->left != NULL)
            buildTheListWithLeaves(root->left, list);

        if (root->right != NULL)
            buildTheListWithLeaves(root->right, list);
    }

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
    printf("\n");
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

    freeList(&tr.leafList);
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

ListNode* createNewListNode(int data, ListNode* next){
    ListNode *result;

    result = (ListNode*)malloc(sizeof(ListNode));
    checkAllocation(result);

    result->data = (int*)malloc(sizeof(int));
    checkAllocation(&result->data);

    result->data = data;
    result->next = next;

    return result;
}

void makeEmptyList(List* lst){
    lst->head = lst->tail = NULL;
}

int isEmptyList(List lst){
    return (lst.head == NULL);
}

void printList(List *lst)
{
    ListNode* curr = lst->head;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void insertDataToEndList(List* lst, int data){
    ListNode *result = createNewListNode(data, NULL);

    insertNodeToEndList(lst, result);

}

void insertNodeToEndList(List* lst, ListNode* newTail){
    newTail->next = NULL;

    if (isEmptyList(*lst))
        lst->head = lst->tail = newTail;
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void freeList(List* lst){
    ListNode* curr = lst->head, *next;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void checkAllocationList(void* ptr){
    if (ptr == NULL)
    {
        printf("Allocation error\n");
        exit(-1);
    }
}