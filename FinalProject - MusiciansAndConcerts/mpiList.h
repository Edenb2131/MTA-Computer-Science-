#ifndef _MPI_LIST_H
#define _MPI_LIST_H

#include "common.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned short instrumentId; // Instrument Id
  char* name;                  // Instrument name
  float price;                 // The price the musician is asking for the instrument
} MusicianPriceInstrument;

typedef struct mpiListNode {
  MusicianPriceInstrument data;
  struct mpiListNode* next;
} MPIListNode;

typedef struct mpiList {
  MPIListNode* head;
  MPIListNode* tail;
} MPIList;

MPIListNode* createNewMPIListNode(MusicianPriceInstrument data, MPIListNode* next);
void initEmptyMPIList(MPIList* lst);
bool isEmptyMPIList(MPIList lst);
void insertDataToEndMPIList(MPIList* lst, MusicianPriceInstrument data);
void insertNodeToEndMPIList(MPIList* lst, MPIListNode* newTail);
void printMPIList(MPIList* lst);
void printMPIListWithTree(TreeNode* root, MPIList* lst);
void freeMPIList(MPIList* lst);
int getInstrumentPriceByName(MPIList lst, char* instrumentName);

#endif //_MPI_LIST_H