//
// Created by Eden Bar on 04/04/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1
#define SIZE 100


//Tree structs
typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
}TreeNode;

typedef struct tree
{
    TreeNode *root;
}Tree;

//required function
BOOL buildExpressionTree(char* str, Tree *tr);
Tree buildExpressionTreeRec(char *str);
int findOprator(char* str);
double calcExpression(Tree tr);
double calcExpressionRec(TreeNode *root);
double calculate(double left, double right, char operator);
BOOL isValidInteger(char ch);
BOOL isValidOperator(char ch);


//Tree functions
TreeNode* createNewTreeNode(char data, TreeNode* left, TreeNode* right);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode *root);
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);
void checkAllocation(void* ptr);




void main()
{

    char str[SIZE];
    Tree tr;
    double res;
    BOOL expressionOK;
    printf("Please enter the expression: ");
    gets(str);

    expressionOK = buildExpressionTree(str, &tr);

    if(expressionOK == TRUE)
    {
        res = calcExpression(tr);
        printf("%s = %.2f", str, res);
    }
    else
        printf("The input expression is not valid\n");

    freeTree(tr);

}

BOOL buildExpressionTree(char *str, Tree *tr){
    // the pattern : open - ( , int/operator - * , close - ) : ( * * * ) //

    int ind = 0, counter =0;

    while (str[ind] != '\0') { //checking to see if we are not in the end of the string
        if (str[ind] == '(') //how many openings
            counter++;
        if (str[ind] == ')')//how many closings
            counter--;

        if((!isValidInteger(str[ind]) && !isValidOperator(str[ind]) ) && (str[ind] != ')' && str[ind]!='(') )
            return FALSE;

//        if((str[ind] <= '0') || (str[ind] >= '9' ))
//            if ((str[ind] != '+') && (str[ind] != '-') && (str[ind] != '*') && (str[ind] != '%') && (str[ind] != '/'))
//                if(str[ind] != '(' && str[ind]!= ')')
//                    return FALSE;

        ind++;
    }

    if (counter == 0) { // means the string is valid and we can continue building our Tree
        *tr = buildExpressionTreeRec(str);
        return TRUE;

    }
    else{
        return FALSE;
    }
}

Tree buildExpressionTreeRec(char *str){

    Tree left;
    Tree mid;
    Tree right;

    if(str[1] == '\0' )
        mid.root = createNewTreeNode(str[0],NULL,NULL); //Case of a string with 1 char.
    else {
        char data;
        int findOp = findOprator(str);
        mid.root = (TreeNode *) malloc(sizeof(TreeNode));
        checkAllocation(mid.root);
        mid.root->data = str[findOp-1];

        data = str[findOp-1];
        str[findOp-1] = '\0'; //cutting the string to use ( * * *) pattern

        left = buildExpressionTreeRec(str+1); // here the +1 is for removing : (
        mid.root ->left = left.root; //inserting left Tree
        str[findOp-1] = data; //returning the original operator

        data = str[strlen(str) -1]; // here the -1 is for removing : ) - to math the pattern
        str[strlen(str)-1] = '\0';

        //Building right tree , + 1 is to start another ( * * *) pattern
        right = buildExpressionTreeRec(str + findOp);
        mid.root ->right = right.root; //inserting right Tree
        str[strlen(str) + 1] = '\0'; // want to shorten the string
        str[strlen(str)] = data; //returning the original operator


    }

    return mid;

}

double calcExpression(Tree tr){

    return calcExpressionRec(tr.root);
}

double calcExpressionRec(TreeNode *root){

    double right, left ;
    double sum ;
    if(root == NULL)
        return 0;
    else{

        if (root->data >= '0' && root->data <= '9')
                sum = root->data - '0';

        else {
            if (root->left->data >= '0' && root->left->data <= '9')
                left= root->left->data - '0';
            else
                left = calcExpressionRec(root->left);


            if (root->right->data >= '0' && root->left->data <= '9')
                right = root->right->data - '0';
            else
                right = calcExpressionRec(root->right);

            sum = calculate(left, right,root->data);
        }

    }

    return sum;
}

//calculate the sum of left and right trees withe relevant operator
double calculate(double left, double right, char operator)
{

    switch (operator) {
        case '+':
            return (left+right);
        case '*':
            return (left*right);
        case '-':
            return (left-right);
        case '/':
            return (left/right);
        case '%':
            return ((int)left % (int)right);
        default:
            return operator;

    }
}

//Here we will find the operator that will be in the node.
int findOprator(char* str){

    int open = 0, close = 0;
    int ind = 0;
    BOOL found = FALSE;
    while ((str[ind] != '\0') && (!found)) {

        if (str[ind] == '(') //How many opening are for the pattern ( * * * )
            open++;

        //checking to see if the item is an operator
        else if ((str[ind] == '+') || (str[ind] == '-') || (str[ind] == '*') || (str[ind] == '%') || (str[ind] == '/'))
            close++;

        if (close == open) // if we open and find and operator, so it's true;
            found = TRUE;

        ind++;
    }
    return ind;
}

BOOL isValidOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

BOOL isValidInteger(char ch) {
    return (ch >= '0' && ch <= '9');
}

TreeNode* createNewTreeNode(char data, TreeNode* left, TreeNode* right)
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
    //freeTreeRec(tr.root);
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