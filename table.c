/***************************************************************
  Student Name:Rocio Krebs
  File Name: table.c
  Assignment number 2

  This file contains the symbol table and the functionality
  of adding and seraching the contenct of the table.
***************************************************************/
#include "table.h"

// this functuons iniztialize the table.
void initSymbolTable() {
  strcpy(end, "end.");
  strcpy(start, "begin");
}

// this function checks if the lexema is in the table
bool lookupVar(char *lexema) {
  struct Entry *current = head;
  if (current == NULL) {
    return false;
  }
  while (strcmp(current->value, lexema) != 0) {
    if (current->next == NULL) {
      return false;
    } else {
      current = current->next;
    }
  }
  return true;
}

// this function insert lexemas at the end table
void insertEntry(char *lexema, int line, int t) {
  newEntry = (struct Entry *)malloc(sizeof(struct Entry));
  strncpy(newEntry->value, lexema, sizeof(newEntry->value) - 1);
  newEntry->typ = t;
  newEntry->next = NULL;
  newEntry->line = line;

  if (head == NULL) {
    head = newEntry;
  } else {
    struct Entry *lastEntry = head;
    while (lastEntry->next != NULL) {
      lastEntry = lastEntry->next;
    }
    lastEntry->next = newEntry;
  }
}

// this funcion is to free the space allocate each time
// a new element was added to the table
void free_table() {
  struct Entry *pNode = head, *pNext;

  while (NULL != pNode) {
    pNext = pNode->next;
    free(pNode);
    pNode = pNext;
  }
}
