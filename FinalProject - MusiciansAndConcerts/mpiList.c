#include "mpiList.h"

/**
 * @brief Create a New List Node object
 *
 * @param data Data to be stored in the node
 * @param next Pointer to the next node
 * @return ListNode*
 */
MPIListNode* createNewMPIListNode(MusicianPriceInstrument data, MPIListNode* next) {
  MPIListNode* result;

  result = (MPIListNode*)malloc(sizeof(MPIListNode));
  checkMemoryAllocation(result);

  result->data = data;
  result->next = next;

  return result;
}

/**
 * @brief Initialize an empty list
 *
 * @param lst Pointer to the list to be initialized
 */
void initEmptyMPIList(MPIList* lst) {
  lst->head = lst->tail = NULL;
}

/**
 * @brief Check if the list is empty
 *
 * @param lst Pointer to the list to be checked
 * @return true
 * @return false
 */
bool isEmptyMPIList(MPIList lst) {
  return (lst.head == NULL);
}

/**
 * @brief Insert a new node with custom data to the end of the list
 *
 * @param lst Pointer to the list to be inserted to
 * @param data Data to be stored in the new node
 */
void insertDataToEndMPIList(MPIList* lst, MusicianPriceInstrument data) {
  MPIListNode* result = createNewMPIListNode(data, NULL);
  insertNodeToEndMPIList(lst, result);
}

/**
 * @brief Insert a new node to the end of the list
 *
 * @param lst Pointer to the list to be inserted to
 * @param newTail Pointer to the new node to be inserted
 */
void insertNodeToEndMPIList(MPIList* lst, MPIListNode* newTail) {
  newTail->next = NULL;

  if (isEmptyMPIList(*lst))
    lst->head = lst->tail = newTail;
  else {
    lst->tail->next = newTail;
    lst->tail = newTail;
  }
}

/**
 * @brief Free the memory allocated for a linked list
 *
 * @param lst Pointer to the list to be freed
 */
void freeMPIList(MPIList* lst) {
  MPIListNode *curr = lst->head, *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}

/**
 * @brief Get instrument's price from a musician instrument list, by its name
 *
 * @param lst Pointer to the musician's instrument list
 * @param instrumentName Name of the instrument to be searched
 * @return int Instrument's price
 */
int getInstrumentPriceByName(MPIList lst, char* instrumentName) {
  MPIListNode* currNode = lst.head;

  while (currNode != NULL) {
    if (isStringsEqual(currNode->data.name, instrumentName)) {
      return currNode->data.price;
    }
    currNode = currNode->next;
  }

  return INSTRUMENT_NOT_FOUND_INT;
}