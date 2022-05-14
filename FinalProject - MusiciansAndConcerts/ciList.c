#include "ciList.h"

/**
 * @brief Create a New List Node object
 *
 * @param data Data to be stored in the node
 * @param next Pointer to the next node
 * @return ListNode*
 */
CIListNode* createNewCIListNode(ConcertInstrument data, CIListNode* next) {
  CIListNode* result;

  result = (CIListNode*)malloc(sizeof(CIListNode));
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
void initEmptyCIList(CIList* lst) {
  lst->head = lst->tail = NULL;
}

/**
 * @brief Check if the list is empty
 *
 * @param lst Pointer to the list to be checked
 * @return true
 * @return false
 */
bool isEmptyCIList(CIList lst) {
  return (lst.head == NULL);
}

/**
 * @brief Insert a new node with custom data to the end of the list
 *
 * @param lst Pointer to the list to be inserted to
 * @param data Data to be stored in the new node
 */
void insertDataToEndCIList(CIList* lst, ConcertInstrument data) {
  CIListNode* result = createNewCIListNode(data, NULL);
  insertNodeToEndCIList(lst, result);
}

/**
 * @brief Insert a new node to the end of the list
 *
 * @param lst Pointer to the list to be inserted to
 * @param newTail Pointer to the new node to be inserted
 */
void insertNodeToEndCIList(CIList* lst, CIListNode* newTail) {
  newTail->next = NULL;

  if (isEmptyCIList(*lst))
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
void freeCIList(CIList* lst) {
  CIListNode *curr = lst->head, *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}