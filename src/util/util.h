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

typedef struct ArrayList_s ArrayList;

/// Creates a new Arraylist
ArrayList* newArrayList();

/// Appends
void appendArrayList(ArrayList* list, int item);

/// gets the value at `index` from the ArrayList
int getArrayList(ArrayList* list, int index);

/// gets the length of the arraylist
int getArrayListLength(ArrayList* list);

/// Frees an ArrayList
void freeArrayList(ArrayList* list);

/// Prints message and exits with 1 if given a null ptr
void checkAlloc(void* ptr, char message[]);
