#ifndef GUARD_93231FD3_9D6A_4531_9B89_F28DCAA3AD8D
#define GUARD_93231FD3_9D6A_4531_9B89_F28DCAA3AD8D

#include <stdlib.h>
#include <stdbool.h>

enum ArrayFileType { INT_ARRAY, FLOAT_ARRAY };
typedef enum ArrayFileType ArrayFileType;

typedef struct ArrayFileInfo ArrayFileInfo;
struct ArrayFileInfo {
  ArrayFileType array_type;
  size_t num_of_elems;
  size_t size_of_elems;
};

ArrayFileInfo get_int_file_info(size_t num_of_elems);
ArrayFileInfo get_float_file_info(size_t num_of_elems);

bool is_int_array(ArrayFileInfo info);
bool is_float_array(ArrayFileInfo info);

bool is_compatible(ArrayFileInfo info);

#endif // GUARD_93231FD3_9D6A_4531_9B89_F28DCAA3AD8D
