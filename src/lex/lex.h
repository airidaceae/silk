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

// for ArrayList
#include "../util/util.h"

//enum definition of all token types
typedef enum TokenType {
    identsym,  // identifiers 'a' 'i'
    numsym,    // numbers '123' '999
    plussym,   // +
    minussym,  // -
    starsym,   // *
    slashsym,  // /
    arrowsym,  // ->
    assignsym, // :=
    colonsym,  // :
    commasym,  // ,
    dotsym,    // .
    neqsym,    // !=
    eqsym,     // ==
    gtsym,     // >
    ltsym,     // <
    gtesym,    // >=
    ltesym,    // <=
    semisym,   // ;
    lbracesym, // {
    rbracesym, // }
    lparensym, // (
    rparensym, // )
    fnsym,     // fn
    letsym,    // let
    mutsym,    // mut
    ifsym,     // if
    elsesym,   // else
    whilesym,  // while
    returnsym, // return
} TokenType;
// this constant should always be the last item in the list. this constant 
// exists to make the code more legible.

#define TOKEN_COUNT returnsym

typedef struct NameTable_s NameTable;

NameTable* newNameTable();

int getOrAppend(NameTable* table, char* name);

int getNameTable(NameTable* table, char* name);

void freeNametable(NameTable* table);

typedef struct TokenContext TokenContext;
struct TokenContext {
    ArrayList* list;
    NameTable* table;
};


TokenContext tokenize(ArrayList* program);

