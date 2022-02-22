#include <cstdlib> // calloc
#include <iostream>
#ifndef STRING_SORTING_H_INCLUDED
#define STRING_SORTING_H_INCLUDED

enum sorter_error_code{
    SORTER_ERROR_OK,
    SORTER_ERROR_NO_POINTER,
    SORTER_ERROR_NO_MEMORY,
    SORTER_ERROR_NO_FILE
};

enum comparator_mode{
    COMPARATOR_STRINGS_BIGGER_BEGINNING,
    COMPARATOR_STRINGS_BACK_BIGGER_BEGINNING,
    COMPARATOR_STRINGS_POINTERS
};

extern const char* sorter_errors_value[];

struct strings{
    char *pointer;
    int length;
};

struct document{
    char* text;
    long long number_of_strings;
    struct strings* string;
};

#define CREATE_SWAP_DECLARATION(type) void swap (type * first, type * second)


int document_ERROR (sorter_error_code code);

/** *****************************************************************************************************
 * @param text char*
 * @param symbol char '%c' symbol
 * counts the number of includes of this symbol in string
*/

long long symbol_in_string (char *text, char symbol);

/** *****************************************************************************************************
 * @param number of bytes and pointer on struct strings in line
 * allocates memory with calloc for number of bytes / sizeof (struct strings) elements
*/

sorter_error_code allocate_memory_strings (long long number_of_bytes, document *line);

/** *****************************************************************************************************
 * fills number of strings and pointers on strings
 * @param pointer on struct document, file with text to work with, size of file, to allocate memory with calloc
 *
 *
*/

sorter_error_code document_ctor (struct document *line, FILE *readfile, long long filesize);

/** *****************************************************************************************************
 * Present paper for document_ctor (struct document *line, FILE *readfile, long long filesize);
 * opens file with name filename
*/

sorter_error_code document_ctor_file (struct document *line, char* filename);

/** *****************************************************************************************************
 * Frees memory for line which is document
*/

sorter_error_code document_dtor (struct document *line);

/** *****************************************************************************************************
 * Fills the pointers on strings in text
*/

sorter_error_code string_pointers_filling (struct document *line);

/** *****************************************************************************************************
 * Outputs the text pointer by pointer
*/

sorter_error_code document_output (struct document line);

/** *****************************************************************************************************
 * Outputs the text pointer by pointer into opened file
*/

sorter_error_code document_output_file (struct document line, FILE* file);

/** *****************************************************************************************************
 * Returns the pointer on first symbol after beginning of string which is a letter
*/

char* from_alpha_string (char *string);

/** *****************************************************************************************************
 * Returns the pointer on first symbol before end of string which is a letter
*/

char* from_back_alpha_string (struct strings string);

/** *****************************************************************************************************
 * Outputs the text using from_alpha_string () for each string
*/

sorter_error_code document_output_beginning (struct document line);

/** *****************************************************************************************************
 * Outputs the text using from_alpha_string () for each string but into opened file
*/

sorter_error_code document_output_beginning_file (struct document line, FILE* file);

/** *****************************************************************************************************
 * @param strings that we are going to compare and mode of comparing (for example from beginning or from the end or from the first letter)
 * comparator with many modes, which compares strings from struct strings
*/

int document_comparator (struct strings string1, struct strings string2, comparator_mode mode);

/** *****************************************************************************************************
 * returns the result of work of document_comparator with "Bigger from letter" mode
*/

int document_comparator_bigger_beginning (const void* string1, const void* string2);

/** *****************************************************************************************************
 * returns the result of work of document_comparator with "Bigger from end from letter" mode
*/

int document_comparator_back_bigger_beginning (const void* string1, const void* string2);

/** *****************************************************************************************************
 * returns the result of work of document_comparator with "Pointers bigger" mode
*/

int document_comparator_pointers (const void* string1, const void* string2);

/** *****************************************************************************************************
 * @param struct with array of strings to compare and range from left to right and mode of comparator
 * Standard quick sort algorithm with document_comparator in it
*/

sorter_error_code document_quick_sort (struct document *line, long long leftpointer, long long rightpointer, comparator_mode mode);

/** *****************************************************************************************************
 * Function that starts the standart "qsort" with required accepted values
*/

sorter_error_code document_qsort (struct document line, int (*comparator) (const void*, const void*));

/** *****************************************************************************************************
 * Function that starts the "document_quick_sort" with required accepted values
*/

sorter_error_code document_quick_sort_no_boulders (struct document *line, comparator_mode mode);

/** This functions are not used in the solution of the "Evgenii Onegin" problem */

/**
 * Reverses string
*/

sorter_error_code reverse_string (char *string);

/**
 * Algorithm for reversing text string by string
 * Uses the reverse_string algorithm for each string
*/

sorter_error_code reverse_text (char *strings[], int stringnumber);

/**
 * Swap using the tmp
*/

CREATE_SWAP_DECLARATION (int);
CREATE_SWAP_DECLARATION (char);
CREATE_SWAP_DECLARATION (char*);

#undef CREATE_SWAP_DECLARATION

#endif // ONEGIN_H_INCLUDED
