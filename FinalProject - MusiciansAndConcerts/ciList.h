#ifndef _CI_LIST_H
#define _CI_LIST_H

#include "common.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int num;          // Number of instruments
  char* name;       // Instrument name
  int instrumentId; // Instrument Id
  char isImportant; // Is this instrument important? (TRUE_AS_CHAR or FALSE_AS_CHAR)
} ConcertInstrument;

typedef struct ciListNode {
  ConcertInstrument data;
  struct ciListNode* next;
} CIListNode;

typedef struct ciList {
  CIListNode* head;
  CIListNode* tail;
} CIList;

CIListNode* createNewCIListNode(ConcertInstrument data, CIListNode* next);
void initEmptyCIList(CIList* lst);
bool isEmptyCIList(CIList lst);
void insertDataToEndCIList(CIList* lst, ConcertInstrument data);
void insertNodeToEndCIList(CIList* lst, CIListNode* newTail);
void printCIList(CIList* lst);
void printCIListWithTree(TreeNode* root, CIList* lst);
void freeCIList(CIList* lst);

#endif //_CI_LIST_H