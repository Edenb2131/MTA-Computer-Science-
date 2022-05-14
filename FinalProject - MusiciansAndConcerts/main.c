#define _CRT_SECURE_NO_WARNINGS
#include "ciList.h"
#include "common.h"
#include "concert.h"
#include "mpiList.h"
#include "musician.h"
#include "tree.h"

#define _DEBUG

void main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Number of program arguments is invalid.\nExiting...");
    exit(1);
  }

  char* instrumentsFileName = argv[1];
  char* musiciansFileName = argv[2];

  int instrumentsNamesArraySize, treeSize, musiciansOutputLinesArraySize, musiciansGroupSize, concertsArrSize;
  InstrumentTree tr;

  char** instrumentsNamesArray = getInstrumentsListByFileName(instrumentsFileName, &instrumentsNamesArraySize);
  tr = buildInstrumentsTreeByArray(instrumentsNamesArray, instrumentsNamesArraySize);
  treeSize = instrumentsNamesArraySize;

  StringsNestedArray** musiciansOutputLinesArray =
      getMusiciansArrayByFileName(musiciansFileName, &musiciansOutputLinesArraySize);
  musiciansGroupSize = musiciansOutputLinesArraySize;

  Musician** musiciansGroup = buildMusiciansGroup(tr, musiciansOutputLinesArray, musiciansGroupSize);

  MusicianNestedArray** musicianCollection = buildMusicianCollection(treeSize, musiciansGroup, musiciansGroupSize);

  Concert** concertsArr = buildConcertsArr(tr, &concertsArrSize);

  printConcertsSummary(concertsArr, concertsArrSize, musicianCollection);

  // Cleanup
  freeConcertsArr(concertsArr, concertsArrSize);
  concertsArr = NULL;
  freeMusicianCollection(musicianCollection, treeSize);
  musicianCollection = NULL;
  freeMusiciansGroup(musiciansGroup, musiciansOutputLinesArraySize);
  musiciansGroup = NULL;
  freeStringsNestedArrayObjArray(musiciansOutputLinesArray, musiciansOutputLinesArraySize);
  musiciansOutputLinesArray = NULL;
  freeTree(tr);
  tr.root = NULL;
  free(instrumentsNamesArray);
  instrumentsNamesArray = NULL;

  return;
}
