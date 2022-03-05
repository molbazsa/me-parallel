#include <stdio.h>

#include "array_export.h"

ArrayFileInfo get_int_file_info(size_t num_of_elems) {
  ArrayFileInfo info = {.array_type = INT_ARRAY,
                        .num_of_elems = num_of_elems,
                        .size_of_elems = sizeof(int)};
  return info;
}

ArrayFileInfo get_float_file_info(size_t num_of_elems) {
  ArrayFileInfo info = {.array_type = FLOAT_ARRAY,
                        .num_of_elems = num_of_elems,
                        .size_of_elems = sizeof(float)};
  return info;
}

bool is_int_array(ArrayFileInfo info) {
  return info.array_type == INT_ARRAY;
}

bool is_float_array(ArrayFileInfo info) {
  return info.array_type == FLOAT_ARRAY;
}

bool is_compatible(ArrayFileInfo info) {
  switch (info.array_type) {
    case INT_ARRAY:
      return info.size_of_elems == sizeof(int);
    case FLOAT_ARRAY:
      return info.size_of_elems == sizeof(float);
    default:
      return false;
  }
}
