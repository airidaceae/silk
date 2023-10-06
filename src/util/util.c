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

#include "util.h"

#include <stdlib.h>

struct ArrayList_s {
    int length;
    int capacity;
    int* array;
};

ArrayList* newArrayList() {
    ArrayList* temp = calloc(1, sizeof(ArrayList));
    temp->array = calloc(1, sizeof(int));
    temp->length = 0;
    temp->capacity = 1;
    return temp;
}

// Appends an item to the ArrayList. Zeros out new indexes.
void appendArrayList(ArrayList* list, int item) {
    if( list->length >= list->capacity) {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(int));
        for(int i = list->capacity/2; i < list->capacity - 1; i++) {
            list->array[i] = 0;
        }
    }
    list->array[list->length++] = item;
}

int getArrayList(ArrayList* list, int index) {
    return list->array[index];
}

int getArrayListLength(ArrayList* list) {
    return list->length;
}

void freeArrayList(ArrayList* list) {
    free(list->array);
    free(list);
}


