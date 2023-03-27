#ifndef INDEX_PARSER_H
#define INDEX_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser_types.h"

int allocate_indexes_memory(Indexes* indexes);
int obj_processing_by_indexes(Indexes* indexes, FILE* fptr);

#endif  //  INDEX_PARSER_H