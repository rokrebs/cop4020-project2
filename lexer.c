/***************************************************************
  Student Name:Rocio Krebs
  File Name:lexer.c
  Assignment number 2

  This file impllement the required funcions needed to run the lexic analyzer
and inserting IDs into the symbol table
***************************************************************/
#include "lexer.h"

// This function open a file for reading
// and starts reading the contect
void initLexer(char *name) {
  file = fopen(name, "r");
  lineNr = 1;
  lookahead = lexan();
}

// This function reads char by char the file
// and depending of the char it will store them
// in an array to store in the table symbol.
// This function will return the value of a char or
// the type of lexema.
int lexan() {
  memset(idLexeme, 0, MAX);
  idLen = 0;
  while (1) {
    ch = fgetc(file);
    if (ch == ' ' || ch == '\t' || ch == ',') {
      ; // do nothing
    } else if (ch == '\n') {
      lineNr++;
    } else if (ch == '~') {
      while (ch != '\n') {
        // read the comment until finding \n
        ch = fgetc(file);
      }
      ungetc(ch, file);
    } else if (isdigit(ch)) {
      while (isdigit(ch)) {
        // inserr digit to lexem
        strncat(idLexeme, &ch, 1);
        ch = fgetc(file);
      }
      ungetc(ch, file);
      return NUM;
    } else if (isalpha(ch)) {
      while (isalpha(ch) || isdigit(ch) || ch == '.' || ch == '_') {
        // insert into idLExeme
        strncat(idLexeme, &ch, 1);
        idLen++;
        ch = fgetc(file);
      }
      type = getTyp(idLexeme, idLen);
      ungetc(ch, file);
      return type;
    } else if (ch == EOF) {
      return DONE;
    } else {
      strncat(idLexeme, &ch, 1);
      return ch;
    }
  }
}

// this is a help function that identifies the type of the lexema
// and it will return its correct type.
int getTyp(char *lexema, int size) {
  if (strcmp(lexema, start) == 0) {
    return BEGIN;
  } else if (strcmp(lexema, end) == 0) {
    return END;
  } else if (lexema[0] == '_') {
    return START_U;
  } else if (lexema[size - 1] == '_') {
    return END_U;
  } else if (strcmp(lexema, "int") == 0) {
    return INT;
  } else {
    for (int i = 0; i < MAX - 1; i++) {
      if (lexema[i] == '_' && lexema[i + 1] == '_') {
        return TWO_U;
      }
    }
  }
  return ID;
}