#include "tree.h"

/**
 * @brief Create a New TreeNode object
 *
 * @param instrumentName Instrument name
 * @param instrumentId Instrument Id
 * @param left Pointer to the left node
 * @param right Pointer to the right node
 * @return TreeNode* Created TreeNode
 */
TreeNode* createNewTreeNode(char* instrumentName, unsigned short instrumentId, TreeNode* left, TreeNode* right) {
  TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
  checkMemoryAllocation(res);

  res->instrumentName = instrumentName;
  res->instrumentId = instrumentId;
  res->left = left;
  res->right = right;

  return res;
}

/**
 * @brief Finds an instrument id by name
 *
 * @param tree Tree to be searched
 * @param instrumentName Instrument name to be found
 * @return int Instrument id
 */
int getInstrumentIdByName(InstrumentTree tree, char* instrumentName) {
  return getInstrumentIdByNameRec(tree.root, instrumentName);
}

/**
 * @brief Recursive implementation of findInstrumentIdByName
 *
 * @param tree Tree to be searched
 * @param instrumentName Instrument name to be found
 * @return int Instrument id
 */
int getInstrumentIdByNameRec(TreeNode* root, char* instrumentName) { //// This functions in Q2 - findInsID
  if (root == NULL) {
    return INSTRUMENT_NOT_FOUND_INT;
  }

  int leftNodeResult, rightNodeResult;

  if (isStringsEqual(root->instrumentName, instrumentName)) {
    return root->instrumentId;
  }

  leftNodeResult = getInstrumentIdByNameRec(root->left, instrumentName);
  rightNodeResult = getInstrumentIdByNameRec(root->right, instrumentName);

  if (leftNodeResult != INSTRUMENT_NOT_FOUND_INT) {
    return leftNodeResult;
  } else if (rightNodeResult != INSTRUMENT_NOT_FOUND_INT) {
    return rightNodeResult;
  } else {
    return INSTRUMENT_NOT_FOUND_INT;
  }
}

/**
 * @brief Finds an instrument name by id
 *
 * @param tree Tree to be searched
 * @param instrumentId Instrument id to be found
 * @return char* Instrument name
 */
char* getInstrumentNameById(InstrumentTree tree, int instrumentId) {
  return getInstrumentNameByIdRec(tree.root, instrumentId);
}

/**
 * @brief Recursive implementation of findInstrumentNameByIdRec
 *
 * @param tree Tree to be searched
 * @param instrumentId Instrument id to be found
 * @return char* Instrument name
 */
char* getInstrumentNameByIdRec(TreeNode* root, int instrumentId) {

  if (root == NULL) {
    return INSTRUMENT_NOT_FOUND;
  }

  char *leftNodeResult, *rightNodeResult;

  if (root->instrumentId == instrumentId) {
    return root->instrumentName;
  }

  leftNodeResult = getInstrumentNameByIdRec(root->left, instrumentId);
  rightNodeResult = getInstrumentNameByIdRec(root->right, instrumentId);

  if (leftNodeResult != INSTRUMENT_NOT_FOUND) {
    return leftNodeResult;
  } else if (rightNodeResult != INSTRUMENT_NOT_FOUND) {
    return rightNodeResult;
  } else {
    return INSTRUMENT_NOT_FOUND;
  }
}

/**
 * @brief Frees the tree
 *
 * @param tr Tree to be freed
 */
void freeTree(InstrumentTree tr) {
  freeTreeRec(tr.root);
}

/**
 * @brief Recursive implementation of freeTree
 *
 * @param root Root of the tree to be freed
 */
void freeTreeRec(TreeNode* root) {
  if (root == NULL) {
    return;
  }

  freeTreeRec(root->left);
  freeTreeRec(root->right);

  free(root->instrumentName);
  free(root);
  root = NULL;

  return;
}

/**
 * @brief Makes a new tree from an array of instrument names
 *
 * @param instruments Array of instrument names
 * @param size Size of the array
 * @return InstrumentTree Tree made from the array
 */
InstrumentTree buildInstrumentsTreeByArray(char** instrumentsNamesArray, int arrSize) {
  int i;
  int childPlacement;
  InstrumentTree tr;
  TreeNode* suitableNode;

  TreeNode* root = createNewTreeNode(instrumentsNamesArray[0], 0, NULL, NULL);

  // Placing each item in his place in the tree
  for (i = 1; i < arrSize; i++) {
    suitableNode = searchSuitableNextNodeByRoot(root, instrumentsNamesArray[i], &childPlacement);

    if (childPlacement == LEFT) {
      suitableNode->left = createNewTreeNode(instrumentsNamesArray[i], i, NULL, NULL);
    } else if (childPlacement == RIGHT) {
      suitableNode->right = createNewTreeNode(instrumentsNamesArray[i], i, NULL, NULL);
    }
  }

  tr.root = root;

  return tr;
}

/**
 * @brief Search for a suitable node to insert a new node.
 * A suitable node is a node that has no children in the childPlacement side, based on lexiographic order.
 *
 * @param root Root of the tree
 * @param instrumentName Instrument name to be inserted
 * @param childPlacement (Output argument) Pointer to the placement of the new node (LEFT or RIGHT)
 * @return TreeNode* Suitable node
 */
TreeNode* searchSuitableNextNodeByRoot(TreeNode* root, char* instrumentName, int* childPlacement) {
  if (root == NULL) {
    return NULL;
  }

  if (isLexicographicallySmaller(instrumentName, root->instrumentName)) {
    if (root->left == NULL) {
      *childPlacement = LEFT;
      return root;
    } else {
      return searchSuitableNextNodeByRoot(root->left, instrumentName, childPlacement);
    }
  } else {
    if (root->right == NULL) {
      *childPlacement = RIGHT;
      return root;
    } else {
      return searchSuitableNextNodeByRoot(root->right, instrumentName, childPlacement);
    }
  }
}

/**
 * @brief Extracts instrument names from the file and puts them in an of instrument names
 *
 * @param fileName File name
 * @param resultArraySize (Output argument) Size of the array
 * @return char** Array of instrument names
 */
char** getInstrumentsListByFileName(char* fileName, int* resultArraySize) {
  FILE* pFile;
  char currentInstrumentName[INPUT_FILE_MAX_LINE_LENGTH];
  pFile = fopen(fileName, "r");

  int namesArrayLogSize = 0;
  int namesArrayPhySize = 1;
  char** instrumentNamesArray = (char**)malloc(namesArrayPhySize * sizeof(char*));
  checkMemoryAllocation(instrumentNamesArray);

  if (!isFileOpened(pFile)) {
    printf("File: '%s' not found.\n", fileName);
    exit(1);
  }

  while (fgets(currentInstrumentName, INPUT_FILE_MAX_LINE_LENGTH, pFile) != NULL) {
    instrumentNamesArray =
        (char**)increaseArraySizeIfFull(instrumentNamesArray, &namesArrayLogSize, &namesArrayPhySize, sizeof(char*));

    trimNewLineChar(currentInstrumentName);

    instrumentNamesArray[namesArrayLogSize] =
        (char*)malloc(strlen(currentInstrumentName) * sizeof(char) + 1); // +1 for "\0" at the end
    checkMemoryAllocation(instrumentNamesArray[namesArrayLogSize]);

    strcpy(instrumentNamesArray[namesArrayLogSize], currentInstrumentName);
    namesArrayLogSize++;
  }

  fclose(pFile);

  *resultArraySize = namesArrayLogSize;
  instrumentNamesArray = (char**)realloc(instrumentNamesArray, (*resultArraySize) * sizeof(char*));
  return instrumentNamesArray;
}