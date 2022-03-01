/***************************************************************
  Student Name:Rocio Krebs
  File Name:lexer.h
  Assignment number 2

  This is the header file with the required funcions needed to run the lexic
analyzer and inserting IDs into the symbol table
***************************************************************/
#ifndef LEXER
#define LEXER
#include "table.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 250
#define ID 300
#define NUM 301
#define BEGIN 400
#define END 401
#define NOT_FOUND -1
#define DONE 800
#define START_U 801
#define END_U 802
#define TWO_U 803
#define INT 200

FILE *file, *o_fp;
int lineNr;
char ch;
int type;
int lookahead;
int idLen;

// functions
int lexan(void);
void initLexer(char *name);
char idLexeme[MAX];
int getTyp(char *lexema, int size);

#endif
