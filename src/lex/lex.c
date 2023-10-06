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
#define NUM_LENGTH 10
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
    checkAlloc(temp, "Calloc error in newNameTable()\0");
    temp->array = calloc(START_SIZE, sizeof(char));
    checkAlloc(temp->array, "Calloc error in newNameTable()\0");
    for (int i = 0; i < START_SIZE; i++) {
        temp->array[i] = calloc(IDENTIFIER_LENGTH + 1, sizeof(char));
        checkAlloc(temp->array[i], "Calloc error in newNameTable()\0");
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
        checkAlloc(table->array, "Realloc error in getOrAppend()\0");
        for (int i = table->capacity / 2; i < table->capacity; i++) {
            table->array[i] = calloc(IDENTIFIER_LENGTH + 1, sizeof(char));
            checkAlloc(table->array[i], "Calloc error in getOrAppend()\0");
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
    int status = 0;
    
    // KEYWORDS allows us to check if a string is a keyword easily and get its
    // proper symbol without
    fprintf(stderr, "\nbegin keyword setup\n");
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
    int err = 0;
    
    NameTable*  nameTable = newNameTable();
    ArrayList* tokenList = newArrayList();
    for (int i = 0, line = 1, column = -1; i < getArrayListLength(program); i++) {
        column++;
        char c = getArrayList(program, i);
        // fprintf(stderr, "root level char is %c\n", c);

        if (isDecimal(c)) {
            char curNum[NUM_LENGTH + 1];
            int t;
            for(t = i; isDecimal(c);++t, c = getArrayList(program, t)){

                // start building our num and make sure that our nums are always
                //null terminated
                curNum[t - i] = c;
                curNum[t - i + 1] = '\0'; 
                
                if(t - i >= NUM_LENGTH) {
                    //print our error message
                    fprintf(stderr, "line %2d, column %2d: Number too long\n", line, column);

                    //set error code to one
                    err = 1;
                    status = 1;

                    // continue scanning until we hit the end of the number so 
                    // that we can also check for an unexpected identifier.
                    for(;isDecimal(c);t++, c = getArrayList(program, t));
                    break;
                }
            }

            if(isLetter(getArrayList(program, t))) {
                fprintf(stderr, "line %2d, column %2d: Unexpected Identifier\n", line, column + (t-i));
                err = 1;
                status = 1;
            }
            if(!err) {
                // fprintf(stderr, "Built number %s\n", curNum);
                appendArrayList(tokenList, numsym);
                appendArrayList(tokenList, atoi(curNum));
            } else {
                // finish to scanning to get past the malformed token
                for(;isLetter(c) || isDecimal(c);t++, c = getArrayList(program, t));
            }

            //reset the error variable and increment our indecies 
            err = 0;
            t--;
            column += (t-i);
            i = t;
            // fprintf(stderr,"upcoming char is at index %d and is (%c, %d)",i, getArrayList(program, i), getArrayList(program, i));
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
                column = 0;
                break;
            default:
                break;
            }
        }
    }

    fprintf(stderr, "Finished Tokenizing\n");

    TokenContext context;
    context.status = status;
    context.list = tokenList;
    context.table = nameTable;
    return context;
}
