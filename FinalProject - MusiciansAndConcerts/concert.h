#ifndef _CONCERT_C
#define _CONCERT_C

#define NUMBER_OF_FIELDS_PER_INSTRUMENT 3
#define REMAINDER_OF_INSTRUMENT_NAME_INDEX 2
#define REMAINDER_OF_INSTRUMENT_COUNT 0
#define REMAINDER_OF_INSTRUMENT_IMPORTANCE 1

#include "ciList.h"
#include "common.h"
#include "musician.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  Date date;          // Date of the concert
  char* name;         // Concert name
  CIList instruments; // Linked list of ConcertInstruments
} Concert;

Concert** buildConcertsArr(InstrumentTree tr, int* concertsArrSize);
Concert* buildConcertByString(InstrumentTree tr, char* performanceString);
void initEmptyConcertInstrument(ConcertInstrument* concertInstrument);
void printConcertSummary(Concert* concert, MusicianNestedArray** musicianCollection);
void freeConcert(Concert* concert);
void freeConcertsArr(Concert** concerts, int logSize);
void printConcertsSummary(Concert** concertsArr, int concertsArrSize, MusicianNestedArray** musicianCollection);
bool isAllInstrumentsAvailable(Concert* concert, MusicianNestedArray** musicianCollection);
void printConcertMusicians(Concert* concert, MusicianNestedArray** musicianCollection, int* totalCost);
int getConcertTotalCost(Concert* concert, MusicianNestedArray** musicianCollection,
                        MusicianNestedArray* alreadyPlayingMusicians);

#endif //_CONCERT_C