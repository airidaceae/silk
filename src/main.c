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
#include "util/util.h"
#include "lex/lex.h"


int main(int argc, char* argv[]) {
    // TODO handle any flags that have been passed to the program
    if (argc != 2) {
        fprintf(stderr, "Please specify one arguement for the source file\n");
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    if (source == NULL) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        return 1;
    }
    ArrayList *program = newArrayList();
    fprintf(stderr, "begin input gathering\n");
    for (char temp = '\0'; !feof(source); fscanf(source, "%c", &temp)) {
        appendArrayList(program, temp);
    }
    fclose(source);
    fprintf(stderr, "input gathering complete\n\n");

    fprintf(stderr, "printing source:\n");
    int len = getArrayListLength(program);
    for (int i = 0; i < len; i++) {
        fprintf(stderr, "%c", getArrayList(program, i));
    }

    TokenContext context = tokenize(program);
    if(context.status != 0) {
        fprintf(stderr, "Errors occured in lexing stage. Cannot continue further\n");
        return context.status;
    }
    ArrayList* tokenList = context.list;
    NameTable* nameTable = context.table;

    for(int i = 0; i < getArrayListLength(tokenList); i++){
        fprintf(stderr, "%d ", getArrayList(tokenList, i));
    }
    

    return 0;
}
