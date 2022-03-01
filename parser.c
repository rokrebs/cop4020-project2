/***************************************************************
  Student Name: Rocio Krebs
  File Name: parser.c
  Assignment number 2

  This file contains all the required functions to parse the statements, keeping
track of where you are in the string, and report whether or not the input
program is legal
***************************************************************/
#include "parser.h"

// this function will run until we finish succesfully
// or we have to finish because an error happened.
void parse() {
  registers = 0;
  varsNr = 0;
  while (lookahead != BEGIN) {
    match(lookahead);
    if (lookahead == DONE) {
      printf("Never found start of program\n");
      free_table();
      fclose(file);
      exit(1);
    }
  }
  match(BEGIN);
  while (lookahead != END) {
    if (lookahead == DONE) {
      printf("Never found end of program\n");
      free_table();
      fclose(file);
      exit(1);
    }
    process();
  }
  printf("legal\n");
  free_table();
  fclose(file);
}

// function to check if the term or operation needed
// is on the file.
void match(int t) {
  if (lookahead == t) {
    lookahead = lexan();
  } else {
    printError(t);
  }
}

void process() {
  while (lookahead == INT) {
    declaration();
  }
  while (lookahead == ID) {
    AssignStmt();
  }
}

// This function start checking for variables declarations
void declaration() {
  match(INT);
  variable(type);
  match(';');
}

// this function will add each variable to my symboltable
void variable(int type) {
  while (lookahead == ID) {
    if (lookupVar(idLexeme)) {
      printf("Line: %d variable '%s' already defined \n", lineNr, idLexeme);
      free_table();
      fclose(file);
      exit(1);
    }
    insertEntry(idLexeme, lineNr, ID);
    match(ID);
  }
}

// funcion to check if the assigment operation
// is right and keep track of register
void AssignStmt() {
  char a[30];
  strcpy(a, idLexeme);

  if (lookahead == INT) {
    match(INT);
    if (lookupVar(idLexeme)) {
      printf("Line: %d Redeclaration of %s\n", lineNr, idLexeme);
      free_table();
      fclose(file);
      exit(1);
    }
  }
  if (lookahead == ID && !lookupVar(idLexeme)) {
    printf("Line: %d Variable %s is undefined\n", lineNr, idLexeme);
    free_table();
    fclose(file);
    exit(1);
  }

  match(ID);
  if (lookahead != '=') {
    printf("Line: %d syntax error expected '='\n", lineNr);
    free_table();
    fclose(file);
    exit(1);
  }

  match('=');
  term();
  match(';');

  registers -= 1;
  sprintf(output + strlen(output), "%s = R%d\n", a, registers);
  printStatmt();
}

// this function is the definition for each term
void term() {
  factor();
  while (lookahead == '+' || lookahead == '-' || lookahead == '*' ||
         lookahead == '/') {
    char looker = lookahead + 0;
    match(lookahead);
    factor();
    sprintf(output + strlen(output), "R%d = R%d %s R%d\n", registers - 2,
            registers - 2, &looker, registers - 1);
    registers -= 1;
    strcpy(vars[varsNr], &looker);
    varsNr++;
  }
}

// funcion to check if the factor contains the right
// experssion and if ( ) were missed.
void factor() {
  if (lookahead == '(') {
    match('(');
    if (lookahead == ')') {
      printf("Line %d - Expected identifier got ')'\n", lineNr);
      free_table();
      fclose(file);
      exit(1);
    }
    term();
    match(')');
  } else if (lookahead == ID) {
    if (!lookupVar(idLexeme)) {
      printf("Line %d - Variable %s not declared\n", lineNr, idLexeme);
      free_table();
      fclose(file);
      exit(1);
    }
    sprintf(output + strlen(output), "R%d = %s\n", registers++, idLexeme);
    strcpy(vars[varsNr], idLexeme);
    varsNr++;
    match(lookahead);
  } else if (lookahead == NUM) {
    sprintf(output + strlen(output), "R%d = %s\n", registers++, idLexeme);
    strcpy(vars[varsNr], idLexeme);
    varsNr++;
    match(lookahead);
  }
}

// print list of variables and operators
void printStatmt() {
  int i;
  sprintf(output + strlen(output), "*****[");
  for (i = 0; i < varsNr - 1; i++) {
    sprintf(output + strlen(output), "%s", vars[i]);
    sprintf(output + strlen(output), ",");
  }
  sprintf(output + strlen(output), "%s", vars[i]);

  sprintf(output + strlen(output), "]*****\n");
  varsNr = 0;
}

void printError(char c) {
  if (lookahead == START_U) {
    printf("Line: %d Identifier cannot start with underscore\n", lineNr);
  } else if (lookahead == END_U) {
    printf("Line: %d Identifier cannot end with underscore\n", lineNr);
  } else if (lookahead == TWO_U) {
    printf("Line: %d Identifier has underscore followed by other underscore\n",
           lineNr);
  } else if (c == '(') {
    printf("Line: %d syntax error expected '%c'\n", lineNr, c);
  } else if (c == ')') {
    printf("Line: %d syntax error expected '%c'\n", lineNr, c);
  } else if (c == ';') {
    printf("Line: %d syntax error expected '%c'\n", lineNr, c);
  }
  free_table();
  fclose(file);
  exit(1);
}