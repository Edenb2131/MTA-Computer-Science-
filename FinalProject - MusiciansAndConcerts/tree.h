#ifndef _TREE_H
#define _TREE_H

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
  char* instrumentName;        // Instrument name
  unsigned short instrumentId; // Instrument Id
  struct TreeNode* left;
  struct TreeNode* right;
} TreeNode;

typedef struct Tree {
  TreeNode* root;
} InstrumentTree;

TreeNode* createNewTreeNode(char* instrument, unsigned short insld, TreeNode* left, TreeNode* right);
void freeTree(InstrumentTree tr);
void freeTreeRec(TreeNode* root);
int getInstrumentIdByName(InstrumentTree tree, char* instrument);
int getInstrumentIdByNameRec(TreeNode* root, char* instrument);
char* getInstrumentNameById(InstrumentTree tree, int instrumentId);
char* getInstrumentNameByIdRec(TreeNode* root, int instrumentId);
InstrumentTree buildInstrumentsTreeByArray(char** instrumentsNamesArray, int arrSize);
TreeNode* searchSuitableNextNodeByRoot(TreeNode* root, char* instrumentName, int* childPlacement);
char** getInstrumentsListByFileName(char* fileName, int* instrumentsNamesArraySize);

#endif //_TREE_H