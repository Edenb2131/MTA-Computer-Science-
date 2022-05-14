#include "musician.h"

/**
 * @brief Takes a scrambled "musician line" and normalizes it to an array of sanitized strings
 *
 * @param originalStr The "musician line" string to be normalized
 * @return StringsArray* The array of sanitized strings, as a custom object including the size of the array
 */
StringsNestedArray* normalizeMusicianStringToArray(char* originalStr) {
  StringsNestedArray* musician = (StringsNestedArray*)malloc(sizeof(StringsNestedArray));
  musician->logSize = 0;
  musician->phySize = 1;
  musician->arr = (char**)malloc(musician->phySize * sizeof(char*));
  checkMemoryAllocation(musician->arr);

  while ((originalStr = strtok(originalStr, DISALLOWED_CHARS)) != NULL) {
    musician->arr =
        (char**)increaseArraySizeIfFull(musician->arr, &musician->logSize, &musician->phySize, sizeof(char*));

    char* newString = (char*)malloc(strlen(originalStr) * sizeof(char) + 1); // +1 for "\0"
    checkMemoryAllocation(newString);

    strcpy(newString, originalStr);
    musician->arr[musician->logSize] = newString;

    musician->logSize++;
    originalStr = NULL;
  }

  musician->arr = (char**)realloc(musician->arr, musician->logSize * sizeof(char*));
  musician->phySize = musician->logSize;

  return musician;
}

/**
 * @brief Reads a musician file and returns an array of musicians
 *
 * @param fileName The name of the file to be read
 * @param resultArraySize The size of the array that will be returned
 * @return StringsArray** The array of pointers to musicians, as a custom object including the size of the array
 */
StringsNestedArray** getMusiciansArrayByFileName(char* fileName, int* resultArraySize) {
  FILE* pFile;
  char currentMusicianRow[INPUT_FILE_MAX_LINE_LENGTH];

  int musiciansArrayLogSize = 0;
  int musiciansArrayPhySize = 1;
  StringsNestedArray** musiciansArray =
      (StringsNestedArray**)malloc(musiciansArrayPhySize * sizeof(StringsNestedArray*));
  checkMemoryAllocation(musiciansArray);

  pFile = fopen(fileName, "r");
  if (!isFileOpened(pFile)) {
    printf("File: '%s' not found.\n", fileName);
    exit(1);
  }

  while (fgets(currentMusicianRow, INPUT_FILE_MAX_LINE_LENGTH, pFile) != NULL) {
    musiciansArray = (StringsNestedArray**)increaseArraySizeIfFull(musiciansArray, &musiciansArrayLogSize,
                                                                   &musiciansArrayPhySize, sizeof(StringsNestedArray*));

    musiciansArray[musiciansArrayLogSize] = normalizeMusicianStringToArray(currentMusicianRow);

    musiciansArrayLogSize++;
  }

  fclose(pFile);

  *resultArraySize = musiciansArrayLogSize;
  musiciansArray = (StringsNestedArray**)realloc(musiciansArray, (*resultArraySize) * sizeof(char*));

  return musiciansArray;
}

/**
 * @brief Builds an array of musicians from an array of strings, including the musician instruments
 *
 * @param tr The tree of the instruments
 * @param normalizedMusicianStringsObj Musician as an array of normalized strings
 * @return Musician* Pointer to a musician object
 */
Musician* buildMusicianByOutputLine(InstrumentTree tr, StringsNestedArray* normalizedMusicianStringsObj) {
  Musician* newMusician = (Musician*)malloc(sizeof(Musician));
  checkMemoryAllocation(newMusician);

  newMusician->nameLength = countNumberOfWordsInMusicianName(tr, normalizedMusicianStringsObj);
  newMusician->name = (char**)malloc(newMusician->nameLength * sizeof(char*));
  checkMemoryAllocation(newMusician->name);

  fillMusicianName(newMusician, normalizedMusicianStringsObj, newMusician->nameLength);

  fillMusicianInstruments(newMusician, tr, normalizedMusicianStringsObj, newMusician->nameLength);

  return newMusician;
}

/**
 * @brief Build a musician group from an array of normalized musicians, including the musician instruments
 *
 * @param tr The tree of the instruments
 * @param normalizedMusicianStringsObj Musician as an array of normalized strings
 * @param arrSize The size of the array of normalized musicians
 * @return Musician** Array of pointers to musicians
 */
Musician** buildMusiciansGroup(InstrumentTree tr, StringsNestedArray** normalizedMusicianStringsObj, int arrSize) {
  int i;
  Musician** musiciansGroup = (Musician**)malloc(arrSize * sizeof(Musician*));
  checkMemoryAllocation(musiciansGroup);

  for (i = 0; i < arrSize; i++) {
    musiciansGroup[i] = buildMusicianByOutputLine(tr, normalizedMusicianStringsObj[i]);
  }

  return musiciansGroup;
}

/**
 * @brief Free memory allocated for a musician
 *
 * @param musician Pointer to a musician object
 */
void freeMusician(Musician* musician) {
  free(musician->name);
  freeMPIList(&(musician->instruments));
  free(musician);
}

/**
 * @brief Free memory allocated for a musician group
 *
 * @param musiciansGroup Array of pointers to musicians
 * @param arrSize The size of the array of musicians
 */
void freeMusiciansGroup(Musician** musiciansGroup, int arrSize) {
  int i;

  for (i = 0; i < arrSize; i++) {
    freeMusician(musiciansGroup[i]);
  }

  free(musiciansGroup);
  musiciansGroup = NULL;
}

/**
 * @brief Counts the number of words in a musician name
 *
 * @param tr The tree of the instruments
 * @param normalizedMusicianStringsObj Musician as an array of normalized strings
 * @return int The number of words in the musician name
 */
int countNumberOfWordsInMusicianName(InstrumentTree tr, StringsNestedArray* normalizedMusicianStringsObj) {
  int i = 0;

  while (getInstrumentIdByName(tr, normalizedMusicianStringsObj->arr[i]) == INSTRUMENT_NOT_FOUND_INT &&
         i < normalizedMusicianStringsObj->logSize) {
    i++;
  }

  return i;
}

/**
 * @brief Fills the musician name from a normalized musician string
 *
 * @param musician Pointer to a musician object
 * @param normalizedMusicianStringsObj Musician as an array of normalized strings
 * @param numOfWords The number of words in the musician name
 */
void fillMusicianName(Musician* musician, StringsNestedArray* normalizedMusicianStringsObj, int numOfWords) {
  int i;

  for (i = 0; i < numOfWords; i++) {
    musician->name[i] = normalizedMusicianStringsObj->arr[i];
  }

  return;
}

/**
 * @brief Fills the musician instruments from a normalized musician string
 *
 * @param musician Pointer to a musician object
 * @param tr The tree of the instruments
 * @param normalizedMusicianStringsObj Musician as an array of normalized strings
 * @param firstInstrumentIndex The index of the first instrument in the musician string
 */
void fillMusicianInstruments(Musician* musician, InstrumentTree tr, StringsNestedArray* normalizedMusicianStringsObj,
                             int firstInstrumentIndex) {
  int i;

  initEmptyMPIList(&(musician->instruments));
  for (i = firstInstrumentIndex; i < normalizedMusicianStringsObj->logSize - 1; i += 2) {
    MusicianPriceInstrument newMusicianPriceInstrument;
    newMusicianPriceInstrument.instrumentId = getInstrumentIdByName(tr, normalizedMusicianStringsObj->arr[i]);
    newMusicianPriceInstrument.name = getInstrumentNameById(tr, newMusicianPriceInstrument.instrumentId);
    newMusicianPriceInstrument.price = atoi(normalizedMusicianStringsObj->arr[i + 1]);

    insertDataToEndMPIList(&(musician->instruments), newMusicianPriceInstrument);
  }
}

/**
 * @brief Initializes an empty MusicianNestedArray to default values
 *
 * @param musiciansNestedArray Pointer to a MusicianNestedArray object
 */
void initMusicianNestedArray(MusicianNestedArray* musiciansNestedArray) {
  musiciansNestedArray->logSize = 0;
  musiciansNestedArray->phySize = 1;
  musiciansNestedArray->arr = (Musician**)malloc(musiciansNestedArray->phySize * sizeof(Musician*));
  checkMemoryAllocation(musiciansNestedArray->arr);

  return;
}

/**
 * @brief Builds a Musician collection
 *
 * @param numOfInstruments The total number of instruments, to build the collection by
 * @param musiciansGroup The array of musicians
 * @param musicianGroupSize The size of the array of musicians
 * @return MusicianNestedArray** The collection of musicians
 */
MusicianNestedArray** buildMusicianCollection(int numOfInstruments, Musician** musiciansGroup, int musicianGroupSize) {
  int i;
  int currInstrumentId;
  MusicianNestedArray* currMusicanNestedArr;

  MusicianNestedArray** musiciansNestedArrayObjArray =
      (MusicianNestedArray**)malloc(sizeof(MusicianNestedArray*) * numOfInstruments);
  checkMemoryAllocation(musiciansNestedArrayObjArray);

  for (i = 0; i < numOfInstruments; i++) {
    musiciansNestedArrayObjArray[i] = (MusicianNestedArray*)malloc(sizeof(MusicianNestedArray));
    checkMemoryAllocation(musiciansNestedArrayObjArray[i]);

    initMusicianNestedArray(musiciansNestedArrayObjArray[i]);
  }

  for (i = 0; i < musicianGroupSize; i++) {
    MPIListNode* currInstrument = musiciansGroup[i]->instruments.head;
    while (currInstrument != NULL) { // inserting every instrument to the array
      currInstrumentId = currInstrument->data.instrumentId;
      currMusicanNestedArr = musiciansNestedArrayObjArray[currInstrumentId];

      currMusicanNestedArr->arr = (Musician**)increaseArraySizeIfFull(
          currMusicanNestedArr->arr, &currMusicanNestedArr->logSize, &currMusicanNestedArr->phySize, sizeof(Musician*));

      currMusicanNestedArr->arr[currMusicanNestedArr->logSize] = musiciansGroup[i];
      currMusicanNestedArr->logSize += 1;

      currInstrument = currInstrument->next;
    }
  }

  for (i = 0; i < numOfInstruments; i++) {
    musiciansNestedArrayObjArray[i]->phySize = musiciansNestedArrayObjArray[i]->logSize;
    musiciansNestedArrayObjArray[i]->arr = (Musician**)realloc(
        musiciansNestedArrayObjArray[i]->arr, sizeof(Musician*) * musiciansNestedArrayObjArray[i]->logSize);
  }

  return musiciansNestedArrayObjArray;
}

/**
 * @brief Frees memory allocated for a musician collection
 *
 * @param musiciansNestedArrayObjArray The collection of musicians
 * @param arrSize The size of the collection of musicians
 */
void freeMusicianCollection(MusicianNestedArray** musicianCollection, int arrSize) {
  int i;

  for (i = 0; i < arrSize; i++) {
    // Not free-ing sub-arrays contents, because they are freed in freeMusiciansGroup
    free(musicianCollection[i]->arr);
    musicianCollection[i]->arr = NULL;

    free(musicianCollection[i]);
    musicianCollection[i] = NULL;
  }

  free(musicianCollection);
  musicianCollection = NULL;

  return;
}

void sortMusicianCollectionByInstrumentImportance(MusicianNestedArray** musicianCollection, CIListNode* instrument) {
  MusicianNestedArray* currentCollection;

  while (instrument != NULL) {
    currentCollection = musicianCollection[instrument->data.instrumentId];
    if (instrument->data.isImportant == TRUE_AS_CHAR) {
      sortMusicianGroupByPriceDesc(currentCollection->arr, currentCollection->logSize, instrument->data.name);
    } else {
      sortMusicianGroupByPriceAsc(currentCollection->arr, currentCollection->logSize, instrument->data.name);
    }
    instrument = instrument->next;
  }
}

/**
 * @brief Get an instrument's price from a specific musician, by its name
 *
 * @param musician Pointer to a musician object
 * @param instrumentName The name of the instrument
 * @return int The price of the instrument
 */
int getMusicianInstrumentPriceByName(Musician* musician, char* instrumentName) {
  return getInstrumentPriceByName(musician->instruments, instrumentName);
}

// TODO: Refactor to a better sorting algorithem
/**
 * @brief Sorts a musician group by instrument's price, using its name, in ascending order
 *
 * @param musicianGroup The array of musicians
 * @param musicianGroupSize The size of the array of musicians
 * @param instrumentName The name of the instrument
 */
void sortMusicianGroupByPriceAsc(Musician** musicianGroup, int musicianGroupSize, char* instrumentName) {
  mergeSort(musicianGroup, musicianGroupSize, true, instrumentName);
  return;
}

/**
 * @brief Sorts a musician group by instrument's price, using its name, in descending order
 *
 * @param musicianGroup The array of musicians
 * @param musicianGroupSize The size of the array of musicians
 * @param instrumentName The name of the instrument
 */
void sortMusicianGroupByPriceDesc(Musician** musicianGroup, int musicianGroupSize, char* instrumentName) {
  mergeSort(musicianGroup, musicianGroupSize, false, instrumentName);
}

/**
 * @brief Prints a musician name
 *
 * @param musician Pointer to a musician object
 */
void printMusicianName(Musician* musician) {
  int i;

  for (i = 0; i < musician->nameLength; i++) {
    printf("%s", musician->name[i]);

    if (i != musician->nameLength - 1) {
      printf(" ");
    }
  }
}

/**
 * @brief Prints musician group with its instruments
 *
 * @param musicianGroup The array of musicians
 * @param musicianGroupSize The size of the array of musicians
 * @param instrumentName The name of the instrument to search in the musician's instruments list
 */
void printMusicianGroupWithInstruments(Musician** musicianGroup, int musicianGroupSize, char* instrumentName,
                                       int requiredUniqueMusicians, MusicianNestedArray* alreadyPlayingMusicians,
                                       int* totalCost, bool* isSkipPrecedingComma) {
  int i, musicianInstrumentPrice;
  int foundUniqueMusicians = 0;
  Musician* currentMusician;
  bool isMusiciansGroupPrinted = false;

  for (i = 0; i < musicianGroupSize && foundUniqueMusicians < requiredUniqueMusicians; i++) {
    currentMusician = musicianGroup[i];

    if (!isMusicianAlreadyPlaying(alreadyPlayingMusicians, currentMusician)) {
      musicianInstrumentPrice = getMusicianInstrumentPriceByName(currentMusician, instrumentName);
      *totalCost += musicianInstrumentPrice;

      if (*isSkipPrecedingComma) {
        *isSkipPrecedingComma = false;
      } else {
        printf(", ");
      }
      printMusicianName(currentMusician);
      printf(" - %s (%d)", instrumentName, musicianInstrumentPrice);
      isMusiciansGroupPrinted = true;

      foundUniqueMusicians++;
      alreadyPlayingMusicians = addMusicianToNestedArray(alreadyPlayingMusicians, currentMusician);
    }
  }

  return;
}

MusicianNestedArray* addMusicianToNestedArray(MusicianNestedArray* musicianNestedArray, Musician* musician) {
  musicianNestedArray->arr = (Musician**)increaseArraySizeIfFull(
      musicianNestedArray->arr, &musicianNestedArray->logSize, &musicianNestedArray->phySize, sizeof(Musician*));

  musicianNestedArray->arr[musicianNestedArray->logSize] = musician;
  musicianNestedArray->logSize++;

  return musicianNestedArray;
}

/**
 * @brief Check if a musician is already playing in a musician group
 *
 * @param alreadyPlayingMusicians The array of already playing musicians
 * @param musician The musician to check
 * @return true
 * @return false
 */
bool isMusicianAlreadyPlaying(MusicianNestedArray* alreadyPlayingMusicians, Musician* musician) {
  int i;

  for (i = 0; i < alreadyPlayingMusicians->logSize; i++) {
    if (alreadyPlayingMusicians->arr[i] == musician) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Get the total cost of all instrument prices asked by musicians, in a musician group
 *
 * @param musicianGroup The array of musicians
 * @param musicianGroupSize The size of the array of musicians
 * @param instrumentName The name of the instrument to search in the musician's instruments list
 * @return int Total cost
 */
int getMusicianGroupTotalCost(Musician** musicianGroup, int musicianGroupSize, char* instrumentName,
                              MusicianNestedArray* alreadyPlayingMusicians) {
  int i;
  int totalCost = 0;

  Musician* currMusician;
  int musicianInstrumentPrice;

  for (i = 0; i < musicianGroupSize; i++) {
    currMusician = musicianGroup[i];

    if (!isMusicianAlreadyPlaying(alreadyPlayingMusicians, currMusician)) {
      musicianInstrumentPrice = getMusicianInstrumentPriceByName(currMusician, instrumentName);

      totalCost += musicianInstrumentPrice;
    }
  }

  return totalCost;
}

void copyArr(Musician* src[], Musician* dest[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    dest[i] = src[i];
  }

  return;
}

void mergeAsc(Musician* arr1[], int size1, Musician* arr2[], int size2, Musician* tmpArr[], char* instrumentName) {
  int index1, index2, writeIndex;
  int musicianOneInstrumentPrice, musicianTwoInstrumentPrice;
  index1 = index2 = writeIndex = 0;

  while (index1 < size1 && index2 < size2) {
    musicianOneInstrumentPrice = getMusicianInstrumentPriceByName(arr1[index1], instrumentName);
    musicianTwoInstrumentPrice = getMusicianInstrumentPriceByName(arr2[index2], instrumentName);
    if (musicianOneInstrumentPrice <= musicianTwoInstrumentPrice) {
      tmpArr[writeIndex] = arr1[index1];
      index1++;
    } else {
      tmpArr[writeIndex] = arr2[index2];
      index2++;
    }
    writeIndex++;
  }

  while (index1 < size1) {
    tmpArr[writeIndex] = arr1[index1];
    index1++;
    writeIndex++;
  }

  while (index2 < size2) {
    tmpArr[writeIndex] = arr2[index2];
    index2++;
    writeIndex++;
  }
}

void mergeDesc(Musician* arr1[], int size1, Musician* arr2[], int size2, Musician* tmpArr[], char* instrumentName) {
  int index1, index2, writeIndex;
  int musicianOneInstrumentPrice, musicianTwoInstrumentPrice;
  index1 = index2 = writeIndex = 0;

  while (index1 < size1 && index2 < size2) {
    musicianOneInstrumentPrice = getMusicianInstrumentPriceByName(arr1[index1], instrumentName);
    musicianTwoInstrumentPrice = getMusicianInstrumentPriceByName(arr2[index2], instrumentName);
    if (musicianOneInstrumentPrice >= musicianTwoInstrumentPrice) {
      tmpArr[writeIndex] = arr1[index1];
      index1++;
    } else {
      tmpArr[writeIndex] = arr2[index2];
      index2++;
    }
    writeIndex++;
  }

  while (index1 < size1) {
    tmpArr[writeIndex] = arr1[index1];
    index1++;
    writeIndex++;
  }

  while (index2 < size2) {
    tmpArr[writeIndex] = arr2[index2];
    index2++;
    writeIndex++;
  }
}

void mergeSort(Musician** arr, int size, bool isAscending, char* instrumentName) {
  int halfSize = size / 2;
  Musician** tmpArr;

  if (size < 2) {
    return;
  }

  mergeSort(arr, halfSize, isAscending, instrumentName);
  mergeSort(arr + halfSize, size - halfSize, isAscending, instrumentName);

  tmpArr = (Musician**)malloc(size * sizeof(Musician*));
  checkMemoryAllocation(tmpArr);

  if (isAscending) {
    mergeAsc(arr, halfSize, arr + halfSize, size - halfSize, tmpArr, instrumentName);
  } else {
    mergeDesc(arr, halfSize, arr + halfSize, size - halfSize, tmpArr, instrumentName);
  }
  copyArr(tmpArr, arr, size);
  free(tmpArr);
}