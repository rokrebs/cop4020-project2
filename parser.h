/***************************************************************
  Student Name: Rocio Krebs
  File Name: parser.h
  Assignment number 2

  This the heard for parser.c
***************************************************************/
#ifndef PARSER
#define PARSER

#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

char vars[MAX][MAX];
char output[SIZE];
int registers;
unsigned int varsNr;

void process();
void declaration();
void variable(int);
void AssignStmt();
void term();
void factor();
void match(int);
void printStatmt();
void parse();
void printError(char);
char* setOperator(int);
#endif
