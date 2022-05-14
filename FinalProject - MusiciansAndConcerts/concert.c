#include "concert.h"

/**
 * @brief Builds an array of Concerts from user input
 *
 * @param tr Instruments tree, used to find the instrument ID
 * @param concertsArrSize Pointer to the size of the array
 * @return Concert** Array of Concerts
 */
Concert** buildConcertsArr(InstrumentTree tr, int* concertsArrSize) {
  int concertArrLogSize = 0;
  int concertArrPhySize = 1;
  Concert** concertsArr = (Concert**)malloc(concertArrPhySize * sizeof(Concert*));
  checkMemoryAllocation(concertsArr);

  printf("Please enter concerts, separated by newline:\n");
  char* concertString = scanInputWithUnknownSize();

  while (concertString != NULL) {
    concertsArr =
        (Concert**)increaseArraySizeIfFull(concertsArr, &concertArrLogSize, &concertArrPhySize, sizeof(Concert*));

    concertsArr[concertArrLogSize] = buildConcertByString(tr, concertString);

    concertArrLogSize++;
    concertString = scanInputWithUnknownSize();
  }

  concertsArr = (Concert**)realloc(concertsArr, concertArrLogSize * sizeof(Concert*));

  concertArrPhySize = concertArrLogSize;
  *concertsArrSize = concertArrLogSize;
  return concertsArr;
}

/**
 * @brief Builds a Concert from a string
 *
 * @param tr Instruments tree, used to find the instrument ID
 * @param concertString String containing the concert details
 * @return Concert* Pointer to the built concert
 */
Concert* buildConcertByString(InstrumentTree tr, char* concertString) {
  int i = 0;
  ConcertInstrument concertInstrument;
  Concert* concert = (Concert*)malloc(sizeof(Concert));
  checkMemoryAllocation(concert);

  initEmptyCIList(&concert->instruments);
  initEmptyConcertInstrument(&concertInstrument);

  while ((concertString = strtok(concertString, SPACE_STRING)) != NULL) {
    if (i == 0) { // Fill concert's name
      concert->name = concertString;
    } else if (i == 1) { // Fill concert's date & hour
      concert->date.day = atoi(concertString);
    } else if (i == 2) {
      concert->date.month = atoi(concertString);
    } else if (i == 3) {
      concert->date.year = atoi(concertString);
    } else if (i == 4) {
      concert->date.hour = convertStringHourToFloat(concertString);
    } else { // Fill concert instruments
      // Fill concertInstrument instrument id by its name
      if (i % NUMBER_OF_FIELDS_PER_INSTRUMENT == REMAINDER_OF_INSTRUMENT_NAME_INDEX) {
        concertInstrument.instrumentId = getInstrumentIdByName(tr, concertString);
        concertInstrument.name = getInstrumentNameById(tr, concertInstrument.instrumentId);
        // Fill concertInstrument number of instruments
      } else if (i % NUMBER_OF_FIELDS_PER_INSTRUMENT == REMAINDER_OF_INSTRUMENT_COUNT) {
        concertInstrument.num = atoi(concertString);
        // Fill concertInstrument importance of the instrument
      } else if (i % NUMBER_OF_FIELDS_PER_INSTRUMENT == REMAINDER_OF_INSTRUMENT_IMPORTANCE) {
        concertInstrument.isImportant = concertString[0];
        // Add built concertInstrument to concert instruments list
        insertDataToEndCIList(&concert->instruments, concertInstrument);
        initEmptyConcertInstrument(&concertInstrument);
      }
    }

    concertString = NULL;
    i++;
  }

  return concert;
}

/**
 * @brief Initializes a ConcertInstrument to default values
 *
 * @param concertInstrument Pointer to ConcertInstrument to initialize
 */
void initEmptyConcertInstrument(ConcertInstrument* concertInstrument) {
  concertInstrument->instrumentId = INSTRUMENT_NOT_FOUND_INT;
  concertInstrument->num = 0;
  concertInstrument->isImportant = FALSE_AS_CHAR;
}

/**
 * @brief Prints a summary for a single concert object
 *
 * @param concert Pointer to a concert
 * @param musicianCollection Collection of musicians
 */
void printConcertSummary(Concert* concert, MusicianNestedArray** musicianCollection) {
  int totalCost = 0;

  if (!isAllInstrumentsAvailable(concert, musicianCollection)) {
    printf("Could not find musicians for the concert %s\n", concert->name);
    return;
  }

  printf("%s ", concert->name);
  printf("%02d %02d %02d ", concert->date.day, concert->date.month, concert->date.year);
  printHourAsString(concert->date.hour);
  printf(": ");
  printConcertMusicians(concert, musicianCollection, &totalCost);
  printf(". Total cost: %d.", totalCost);

  printf("\n");

  totalCost = 0;
}

/**
 * @brief Free Concerts array
 *
 * @param concerts Concerts array
 * @param logSize Logical size of the array
 */
void freeConcertsArr(Concert** concerts, int logSize) {
  int i;
  for (i = 0; i < logSize; i++) {
    freeConcert(concerts[i]);
  }

  free(concerts);
  concerts = NULL;

  return;
}

/**
 * @brief Free a single Concert
 *
 * @param concert Pointer to a Concert
 */
void freeConcert(Concert* concert) {
  if (concert != NULL) {
    free(concert->name);
    freeCIList(&concert->instruments);
    free(concert);
    concert = NULL;
  }

  return;
}

/**
 * @brief Sort the musician collection per concert by instrument importance
 *
 * @param concertsArr Concerts array
 * @param concertsArrSize Logical size of the array
 * @param musicianCollection Musician collection
 */
void printConcertsSummary(Concert** concertsArr, int concertsArrSize, MusicianNestedArray** musicianCollection) {
  int i;

  for (i = 0; i < concertsArrSize; i++) {
    CIListNode* currentInstrument = concertsArr[i]->instruments.head;

    sortMusicianCollectionByInstrumentImportance(musicianCollection, currentInstrument);

    printConcertSummary(concertsArr[i], musicianCollection);
  }
}

/**
 * @brief Checks if all instruments are available for a given concert
 *
 * @param concert Pointer to a Concert
 * @param musicianCollection Musician collection
 * @return true
 * @return false
 */
bool isAllInstrumentsAvailable(Concert* concert, MusicianNestedArray** musicianCollection) {
  bool isValidConcert = true;
  int requiredUniqueMusicians, foundUniqueMusicians;
  CIListNode* currentInstrument = concert->instruments.head;
  MusicianNestedArray* currentCollection;
  Musician* currentMusician;
  MusicianNestedArray* alreadyPlayingMusicians = (MusicianNestedArray*)malloc(sizeof(MusicianNestedArray));
  checkMemoryAllocation(alreadyPlayingMusicians);
  initMusicianNestedArray(alreadyPlayingMusicians);

  while (currentInstrument != NULL && isValidConcert == true) {
    foundUniqueMusicians = 0;
    requiredUniqueMusicians = currentInstrument->data.num;
    currentCollection = musicianCollection[currentInstrument->data.instrumentId];

    if (currentCollection->logSize == 0 || currentInstrument->data.num > currentCollection->logSize) {
      isValidConcert = false;
    }

    for (int i = 0; i < currentCollection->logSize && foundUniqueMusicians < requiredUniqueMusicians; i++) {
      currentMusician = currentCollection->arr[i];

      if (!isMusicianAlreadyPlaying(alreadyPlayingMusicians, currentMusician)) {
        foundUniqueMusicians++;
        alreadyPlayingMusicians = addMusicianToNestedArray(alreadyPlayingMusicians, currentMusician);
      }
    }

    if (foundUniqueMusicians < requiredUniqueMusicians) {
      isValidConcert = false;
    }

    currentInstrument = currentInstrument->next;
  }

  free(alreadyPlayingMusicians->arr);
  free(alreadyPlayingMusicians);
  alreadyPlayingMusicians = NULL;

  return isValidConcert;
}

/**
 * @brief Prints the musicians for a given concert
 *
 * @param concert Pointer to a Concert
 * @param musicianCollection Musician collection
 * @param totalCost Pointer to a total cost integer
 */
void printConcertMusicians(Concert* concert, MusicianNestedArray** musicianCollection, int* totalCost) {
  CIListNode* currentInstrument = concert->instruments.head;
  MusicianNestedArray* currentCollection;
  bool isSkipPrecedingComma = true;

  MusicianNestedArray* alreadyPlayingMusicians = (MusicianNestedArray*)malloc(sizeof(MusicianNestedArray));
  checkMemoryAllocation(alreadyPlayingMusicians);
  initMusicianNestedArray(alreadyPlayingMusicians);

  while (currentInstrument != NULL) {
    currentCollection = musicianCollection[currentInstrument->data.instrumentId];
    printMusicianGroupWithInstruments(currentCollection->arr, currentCollection->logSize, currentInstrument->data.name,
                                      currentInstrument->data.num, alreadyPlayingMusicians, totalCost,
                                      &isSkipPrecedingComma);

    currentInstrument = currentInstrument->next;
  }

  free(alreadyPlayingMusicians->arr);
  free(alreadyPlayingMusicians);
  alreadyPlayingMusicians = NULL;
}