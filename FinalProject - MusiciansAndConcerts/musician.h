#ifndef _MUSICIAN_C
#define _MUSICIAN_C

#include "ciList.h"
#include "common.h"
#include "mpiList.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char** name;         // Array of strings that are built from the musician's name
  int nameLength;      // Length of the musician's name
  MPIList instruments; // Linked list of MusicianPriceInstuments
} Musician;

typedef struct {
  Musician** arr;
  int logSize;
  int phySize;
} MusicianNestedArray;

StringsNestedArray* normalizeMusicianStringToArray(char* originalStr);
StringsNestedArray** getMusiciansArrayByFileName(char* fileName, int* resultArraySize);
Musician** buildMusiciansGroup(InstrumentTree tr, StringsNestedArray** normalizedMusicianStringsObj, int arrSize);
Musician* buildMusicianByOutputLine(InstrumentTree tr, StringsNestedArray* normalizedMusicianStringsObj);
void freeMusician(Musician* musician);
void freeMusiciansGroup(Musician** musiciansGroup, int arrSize);
int countNumberOfWordsInMusicianName(InstrumentTree tr, StringsNestedArray* normalizedMusicianStringsObj);
void fillMusicianName(Musician* musician, StringsNestedArray* normalizedMusicianStringsObj, int numOfWords);
void fillMusicianInstruments(Musician* musician, InstrumentTree tr, StringsNestedArray* normalizedMusicianStringsObj,
                             int firstInstrumentIndex);
void initMusicianNestedArray(MusicianNestedArray* musiciansNestedArray);
MusicianNestedArray** buildMusicianCollection(int numOfInstruments, Musician** musiciansGroup, int musicianGroupSize);
void freeMusicianCollection(MusicianNestedArray** musicianCollection, int arrSize);
int getMusicianInstrumentPriceByName(Musician* musician, char* instrumentName);
void sortMusicianCollectionByInstrumentImportance(MusicianNestedArray** musicianCollection, CIListNode* instrument);
void sortMusicianGroupByPriceAsc(Musician** musicianGroup, int musicianGroupSize, char* instrumentName);
void sortMusicianGroupByPriceDesc(Musician** musicianGroup, int musicianGroupSize, char* instrumentName);
void printMusicianName(Musician* musician);
void printMusicianGroupWithInstruments(Musician** musicianGroup, int musicianGroupSize, char* instrumentName,
                                       int requiredUniqueMusicians, MusicianNestedArray* alreadyPlayingMusicians,
                                       int* totalCost, bool* isSkipPrecedingComma);
int getMusicianGroupTotalCost(Musician** musicianGroup, int musicianGroupSize, char* instrumentName,
                              MusicianNestedArray* alreadyPlayingMusicians);
bool isMusicianAlreadyPlaying(MusicianNestedArray* alreadyPlayingMusicians, Musician* musician);
MusicianNestedArray* addMusicianToNestedArray(MusicianNestedArray* musicianNestedArray, Musician* musician);
void copyArr(Musician* src[], Musician* dest[], int size);
void mergeAsc(Musician* arr1[], int size1, Musician* arr2[], int size2, Musician* tmpArr[], char* instrumentName);
void mergeDesc(Musician* arr1[], int size1, Musician* arr2[], int size2, Musician* tmpArr[], char* instrumentName);
void mergeSort(Musician** arr, int size, bool isAscending, char* instrumentName);

#endif //_MUSICIAN_C