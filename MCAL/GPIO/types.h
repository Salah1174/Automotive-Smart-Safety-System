#ifndef TYPES_H
#define TYPES_H

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef int *int32_ptr;

typedef uint32 *uint32_ptr;

typedef float float32;
typedef double float64;

typedef float32 *float32_ptr;
typedef float64 *float64_ptr;

// typedef in compiling stage , #define in preprocessing
// so errors can be detected by compiler in typedef , but hard to detect in preprocessor stage
//  for #define
//  typedef is the actual definition of a new type , #define will just copy-paste the definition values.

#endif