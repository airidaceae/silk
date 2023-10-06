// Silk, Compiler for the Silk Programming language
// Copyright (C) 2023  Roux (aridaceae)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/util.h"
#include "lex.h"

// constants
#define START_SIZE 16
#define IDENTIFIER_LENGTH 64
#define NUM_LENGTH 12
#define KEYWORD_LENGTH 10

// macros
#define isLetter(c) ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
#define isDecimal(c) (c <= '9' && c >= '0')

struct NameTable_s {
    int length;
    int capacity;
    char **array;
};

NameTable *newNameTable() {
    NameTable *temp = calloc(1, sizeof(NameTable));
    temp->array = calloc(START_SIZE, sizeof(char));
    for (int i = 0; i < START_SIZE; i++) {
        temp->array[i] = calloc(IDENTIFIER_LENGTH + 1, sizeof(char));
    }
    temp->length = 0;
    temp->capacity = START_SIZE;

    return temp;
}


int getNameTable(NameTable* table, char* name ){
    for (int i = 0; i < table->length; i++) {
        if (strcmp(table->array[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

/// gets a value from the nametable or adds it. returns the index
int getOrAppend(NameTable* table, char* name) {
    int res = getNameTable(table, name);
    if(res != -1) {
      return res;
    }

    if (table->length >= table->capacity) {
        table->capacity *= 2;
        table->array = realloc(table->array, table->capacity * sizeof(char*));
        for (int i = table->capacity / 2; i < table->capacity; i++) {
            table->array[i] = calloc(IDENTIFIER_LENGTH + 1, sizeof(char));
        }
    }
    strcpy(table->array[table->length], name);

    return table->length++;
}


void freeNameTable(NameTable *table) {
    for (int i = 0; i < table->length; i++) {
        free(table->array[i]);
    }
    free(table->array);
    free(table);
}


TokenContext tokenize(ArrayList* program) {
    // KEYWORDS allows us to check if a string is a keyword easily and get its
    // proper symbol without
    fprintf(stderr, "begin keyword setup\n");
    char KEYWORDS[TOKEN_COUNT + 1][KEYWORD_LENGTH + 1];
    for (int i = 0; i < TOKEN_COUNT; i++) {
        strcpy(KEYWORDS[i], "\0");
    }
    strcpy(KEYWORDS[fnsym], "fn");
    strcpy(KEYWORDS[letsym], "let");
    strcpy(KEYWORDS[mutsym], "mut");
    strcpy(KEYWORDS[ifsym], "if");
    strcpy(KEYWORDS[elsesym], "else");
    strcpy(KEYWORDS[whilesym], "while");
    strcpy(KEYWORDS[returnsym], "return");
    fprintf(stderr, "keyword setup complete\n");

    fprintf(stderr, "\n");
    
    NameTable*  nameTable = newNameTable();
    ArrayList* tokenList = newArrayList();
    for (int i = 0, line = 1, column = 1; i < getArrayListLength(program); i++) {
        column++;
        char c = getArrayList(program, i);
        fprintf(stderr, "root level char is %c\n", c);

        if (isDecimal(c)) {
            char curNum[NUM_LENGTH + 1];
            
            
        } else if (isLetter(c)) {
            // scan until `isDecimal(c) == 0 && isLetter(c) == 0`
            // int t;
            // char curIden[IDENTIFIER_LENGTH + 1];
            // for(t = i; isDecimal(c) || isLetter(c); t++, c = getArrayList(program, t))
        } else {
            switch (c) {
            case '+':
                // appendArrayList(tokenList, plussym);
                break;
            case '*':
                // appendArrayList(tokenList, starsym);
                break;
            case '/':
                // appendArrayList(tokenList, slashsym);
                break;
            case ',':
                // appendArrayList(tokenList, commasym);
                break;
            case '.':
                // appendArrayList(tokenList, dotsym);
                break;
            case ';':
                // appendArrayList(tokenList, semisym);
                break;
            case '{':
                // appendArrayList(tokenList, lbracesym);
                break;
            case '}':
                // appendArrayList(tokenList, rbracesym);
                break;
            case '(':
                // appendArrayList(tokenList, lparensym);
                break;
            case ')':
                // appendArrayList(tokenList, rparensym);
                break;
            case ':':
                // check next character
                // if '='
                //    add assign sym
                // else
                // add colon sym
                break;
            case '-':
                // check next character
                // if '>'
                //    add arrow sym
                // else
                //    add minus sym
            case '!':
                // check next character
                // if '='
                // add neq sym
                // else throw an error with line # and char #
                break;
            case '=':
                // check next character
                // if '='
                // add eq sym
                // else throw an error with line # and char #
                break;
            case '>':
                // check next character
                // if '='
                // add gt sym
                // else
                // add gte sym
                break;
            case '<':
                // check next character
                // if '='
                // add lt sym
                // else
                // add lte sym
                break;
            case '\n':
                line++;
                column = 1;

                break;
            }
        }
    }

    fprintf(stderr, "Finished Tokenizing\n");

    TokenContext context;
    context.list = tokenList;
    context.table = nameTable;
    return context;
}
