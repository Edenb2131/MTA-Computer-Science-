#include "common.h"

/**
 * @brief Check for successful memory allocation. Exits the program if not successful.
 *
 * @param ptr Pointer to the memory to check.
 */
void checkMemoryAllocation(void* ptr) {
  if (ptr == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }
}

/**
 * @brief Checks if the file was opened successfuly
 *
 * @param f Pointer to a file object
 * @return true
 * @return false
 */
bool isFileOpened(FILE* f) {
  if (f == NULL) {
    return false;
  }

  return true;
}

/**
 * @brief Trims the new line character from the end of the string
 *
 * @param str String to trim
 */
void trimNewLineChar(char* str) {
  char* newString = strtok(str, "\n\r");

  if (newString != str) {
    strcpy(str, newString);
  }

  return;
}

/**
 * @brief Increases the size of the array, if it is full
 *
 * @param arr The array to be resized
 * @param logSize The logical size of the array
 * @param phySize The physical size of the array
 * @return void* The resized array, before casting to the original type
 */
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType) {
  if (*logSize == *phySize) {
    (*phySize) *= 2;
    arr = realloc(arr, (*phySize) * sizeOfType);
    checkMemoryAllocation(arr);
  }

  return arr;
}

/**
 * @brief Frees the memory allocated for an array of StringsArray objects
 *
 * @param strArr Array of StringsArray objects
 * @param strArrSize Size of the array
 */
void freeStringsNestedArrayObjArray(StringsNestedArray* strArr[], int strArrSize) {
  int i, j;

  for (i = 0; i < strArrSize; i++) {
    for (j = 0; j < strArr[i]->logSize; j++) {
      free(strArr[i]->arr[j]);
      strArr[i]->arr[j] = NULL;
    }
    free(strArr[i]->arr);
    strArr[i]->arr = NULL;
    free(strArr[i]);
    strArr[i] = NULL;
  }

  free(strArr);
  strArr = NULL;

  return;
}

/**
 * @brief Checks if str1 and str2 are equal
 *
 * @param str1 First string
 * @param str2 Second string
 * @return true
 * @return false
 */
bool isStringsEqual(char* str1, char* str2) {
  if (strcmp(str1, str2) == 0) {
    return true;
  }

  return false;
}

/**
 * @brief Checks if str1 is lexiographically smaller than str2
 *
 * @param str1 First string
 * @param str2 Second string
 * @return true
 * @return false
 */
bool isLexicographicallySmaller(char* str1, char* str2) {
  if (strcmp(str1, str2) < 0) {
    return true;
  }

  return false;
}

/**
 * @brief Scan a string from input and stop at the first new line character
 *
 * @return char* String read from input
 */
char* scanInputWithUnknownSize() {
  char c = (char)0;

  int inputStringLogSize = 0;
  int inputStringPhySize = 1;
  char* inputString = (char*)malloc(sizeof(char) * inputStringPhySize + 1); // +1 for the null terminator
  checkMemoryAllocation(inputString);

  c = getchar();
  while (c != '\n') {
    inputString = (char*)increaseArraySizeIfFull(inputString, &inputStringLogSize, &inputStringPhySize, sizeof(char));

    inputString[inputStringLogSize] = c;

    inputStringLogSize++;
    c = getchar();
  }

  inputString = (char*)realloc(inputString, sizeof(char) * inputStringLogSize + 1);
  inputString[inputStringLogSize] = '\0';

  if (isStringsEqual(inputString, EMPTY_STRING)) {
    free(inputString);
    inputString = NULL;
  }

  return inputString;
}

/**
 * @brief Convert a string with a format of "HH:MM" to a float
 *
 * @param str String to convert
 * @return float Float representing the time
 */
float convertStringHourToFloat(char* str) {
  const int minNumOfDigitsFormat = 2;
  const int maxStrSize = minNumOfDigitsFormat + 1; // +1 for the null terminator
  char* hoursStr = (char*)malloc(sizeof(char) * maxStrSize);
  char* minutesStr = (char*)malloc(sizeof(char) * maxStrSize);
  int i = 0;

  while (i < 2 * minNumOfDigitsFormat + 1) {
    if (i < minNumOfDigitsFormat) {
      hoursStr[i] = str[i];
    } else if (i > minNumOfDigitsFormat) {               // Skip the ':'
      minutesStr[i - minNumOfDigitsFormat - 1] = str[i]; // -1 to compensate for the ':'
    }
    i++;
  }
  hoursStr[minNumOfDigitsFormat] = '\0';
  minutesStr[minNumOfDigitsFormat] = '\0';

  int hour = atoi(hoursStr);
  int minute = atoi(minutesStr);

  free(hoursStr);
  free(minutesStr);
  hoursStr = NULL;
  minutesStr = NULL;

  return (float)hour + (float)minute / NUM_OF_MINUTES_IN_AN_HOUR;
}

/**
 * @brief Convert a float to a string with a format of "HH:MM"
 *
 * @param hour Float representing the time
 * @return char* String representing the time
 */
char* convertFloatHourToString(float hour) {
  int hourInt = (int)hour;
  int minuteInt = (int)((hour - (float)hourInt) * NUM_OF_MINUTES_IN_AN_HOUR);

  int hourStringLogSize = getNumberOfDigits(hourInt);
  int minuteStringLogSize = getNumberOfDigits(minuteInt);

  char* hourString = integerToString(hourInt, hourStringLogSize);
  char* minuteString = integerToString(minuteInt, minuteStringLogSize);

  int hourStringPhySize = hourStringLogSize + 1;
  int minuteStringPhySize = minuteStringLogSize + 1;

  char* timeString = (char*)malloc(sizeof(char) * hourStringPhySize + minuteStringPhySize +
                                   2); // +2 for the ":" and the null terminator
  checkMemoryAllocation(timeString);

  strcpy(timeString, hourString);
  strcat(timeString, ":");
  strcat(timeString, minuteString);

  free(hourString);
  free(minuteString);
  hourString = NULL;
  minuteString = NULL;

  return timeString;
}

/**
 * @brief Convert a float to a string with a format of "HH:MM"
 *
 * @param hour
 */
void printHourAsString(float hour) {
  char* timeString = convertFloatHourToString(hour);
  printf("%s", timeString);
  free(timeString);

  return;
}

/**
 * @brief Converts an integer to a string
 *
 * @param integer Integer to convert
 * @param integerLength Length of the integer
 * @return char* String representing the integer
 */
char* integerToString(int integer, int integerLength) {
  if (integer == 0) {
    integerLength = 2;
  }

  char* integerAsString = (char*)malloc(sizeof(char) * integerLength + 1);
  checkMemoryAllocation(integerAsString);

  sprintf(integerAsString, "%02d", integer);

  return integerAsString;
}

/**
 * @brief Gets the number of digits of an integer
 *
 * @param integer Integer to get the number of digits of
 * @return int Number of digits of the integer
 */
int getNumberOfDigits(int integer) {
  int numberOfDigits = 0;

  while (integer != 0) {
    integer /= 10;
    numberOfDigits++;
  }

  return numberOfDigits;
}