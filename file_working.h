#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#ifndef FILE_WORKING_H_INCLUDED
#define FILE_WORKING_H_INCLUDED

enum file_working_code{
    FILE_ERROR_OK,
    FILE_ERROR_NO_MEMORY
};

extern const char* file_errors_value[];

long long filesizeoftext (FILE*);

/** *****************************************************************************************************
 * @brief reads text from file
 * @param text - pointer, where text will be
 * @param filesize - size of file in bytes
 * @param readfile - file with text
 *
 * Reading text from file and putting it to the array of char with the memory from calloc from allocate_memory
 * Using allocate_memory function
*/

file_working_code text_read (char **text, long long filesize, FILE* readfile);

/** *****************************************************************************************************
 * @param number_of_bytes for memory
 * @param buffer - pointer on buffer
 *
 * Allocates memory using the calloc
*/

file_working_code allocate_memory (long long number_of_bytes, char** buffer);

/** *****************************************************************************************************
 * @param number of bytes for memory
 * @param buffer - pointer on buffer
 *
 * Same as allocate_memory, but for more complex struct, for example array of pointers
 * Using the calloc
*/

file_working_code allocate_memory_mas (long long number_of_bytes, char*** buffer);

#endif// FILE_WORKING_H_INCLUDE
