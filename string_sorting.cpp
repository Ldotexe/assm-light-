#include <stdio.h>
#include "string_sorting.h"
#include "FILE_working.h"

#define CREATE_SWAP(type) \
void swap(type * first, type * second) { \
    type tmp = *first; \
    *first = *second; \
    *second = tmp; \
    \
}

const char* sorter_errors_value[] = {
    "SORTER_ERROR_OK",
    "SORTER_ERROR_NO_POINTER",
    "SORTER_ERROR_NO_MEMORY",
    "SORTER_ERROR_NO_FILE"
};

CREATE_SWAP(int)

CREATE_SWAP(char)

CREATE_SWAP(char*)

int document_ERROR (sorter_error_code code){

    if (code != SORTER_ERROR_OK){
        printf("%s\n", sorter_errors_value[code]);
        return 0;
    }
    return 1;
}

long long symbol_in_string (char *text, char symbol){
    int result = 0;
    for (int i = 0; text[i] != '\0'; i++){
        if (text[i] == symbol){
            result++;
        }
    }
    return result;
}

sorter_error_code allocate_memory_strings (long long number_of_bytes, document *line){

    if (line == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    line->string = (strings*)calloc(number_of_bytes, sizeof(strings));
    if (line->string == nullptr){
        return SORTER_ERROR_NO_MEMORY;
    }
    return SORTER_ERROR_OK;
}


sorter_error_code document_ctor (struct document *line, FILE *readfile, long long filesize){

    sorter_error_code document_ctor_error = SORTER_ERROR_OK;
    if (line == nullptr || readfile == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }

    if (text_read(&line->text, filesize, readfile) == FILE_ERROR_NO_MEMORY){
        return SORTER_ERROR_NO_MEMORY;
    }

    line->number_of_strings = symbol_in_string(line->text, '\n') + 1;

    document_ctor_error = string_pointers_filling(line);
    if (document_ctor_error != SORTER_ERROR_OK){
        return document_ctor_error;
    }
    return SORTER_ERROR_OK;
}

sorter_error_code document_ctor_file (struct document *line, char* filename){

    sorter_error_code document_ctor_error = SORTER_ERROR_OK;

    FILE *readfile = fopen(filename, "r");
    if (readfile == nullptr){
        return SORTER_ERROR_NO_FILE;
    }

    long long filesize = filesizeoftext(readfile);

    document_ctor_error = document_ctor(line, readfile, filesize);
    if (document_ctor_error != SORTER_ERROR_OK){
        fclose(readfile);
        return document_ctor_error;
    }

    fclose(readfile);
    return SORTER_ERROR_OK;
}

sorter_error_code document_dtor (struct document *line){

    if (line == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }

    free(line->text);
    free(line->string);
    return SORTER_ERROR_OK;
}

sorter_error_code string_pointers_filling (struct document *line){

    if (line == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }

    sorter_error_code string_pointers_filling_error = SORTER_ERROR_OK;

    string_pointers_filling_error = allocate_memory_strings(line->number_of_strings, line);
    if (string_pointers_filling_error != SORTER_ERROR_OK){
        return string_pointers_filling_error;
    }

    long long amount_of_strings = 0;
    int beginning = 0;
    for (int i = 0; amount_of_strings < line->number_of_strings; i++){
        if (line->text[i] == '\n' || line->text[i] == '\0'){
            line->text[i] = '\0';
            line->string[amount_of_strings].pointer = &line->text[beginning];
            line->string[amount_of_strings].length = i - beginning;
            amount_of_strings++;
            beginning = i + 1;
        }
    }
    return SORTER_ERROR_OK;
}

sorter_error_code document_output(struct document line)
{
    if(line.string == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    for (int i = 0; i < line.number_of_strings; i++){
        printf("%s\n", line.string[i].pointer);
    }
    return SORTER_ERROR_OK;
}

sorter_error_code document_output_file(struct document line, FILE* file)
{
    if(line.string == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    for (int i = 0; i < line.number_of_strings; i++){
        fprintf(file, "%s\n", line.string[i].pointer);
    }
    return SORTER_ERROR_OK;
}

char* from_alpha_string(char *string)
{
    char *beginning_string = string;
    while((*beginning_string < 'A' || *beginning_string > 'Z') && (*beginning_string < 'a' || *beginning_string > 'z') && *beginning_string != '\0'){
        beginning_string++;
    }
    return beginning_string;
}


char* from_back_alpha_string(struct strings string)
{
    char *back_string = string.pointer + string.length - 1;
    while((*back_string < 'A' || *back_string > 'Z') && (*back_string < 'a' || *back_string > 'z') && *back_string != '\0' && back_string >= string.pointer){
        back_string--;
    }
    return back_string;
}

sorter_error_code document_output_beginning (struct document line)
{
    if(line.string == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    for (int i = 0; i < line.number_of_strings; i++){
        printf("%s\n", from_alpha_string(line.string[i].pointer));
    }
    return SORTER_ERROR_OK;
}

sorter_error_code document_output_beginning_file (struct document line, FILE* file)
{
    if(line.string == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    for (int i = 0; i < line.number_of_strings; i++){
        fprintf(file, "%s\n", from_alpha_string(line.string[i].pointer));
    }
    return SORTER_ERROR_OK;
}

int document_comparator(struct strings string1, struct strings string2,  comparator_mode mode)
{
    char *beginningstring1 = nullptr;
    char *beginningstring2 = nullptr;
    char *end1 = nullptr;
    char *end2 = nullptr;
    int step = 0;
    if (mode == COMPARATOR_STRINGS_POINTERS){
        return string1.pointer - string2.pointer;
    }
    if (mode == COMPARATOR_STRINGS_BIGGER_BEGINNING){
        beginningstring1 = from_alpha_string(string1.pointer);
        beginningstring2 = from_alpha_string(string2.pointer);
        end1 = beginningstring1 + string1.length + 1;
        end2 = beginningstring2 + string2.length + 1;
        step = 1;
    }
    if (mode == COMPARATOR_STRINGS_BACK_BIGGER_BEGINNING){
        beginningstring1 = from_back_alpha_string(string1);
        beginningstring2 = from_back_alpha_string(string2);
        end1 = string1.pointer - 1;
        end2 = string2.pointer - 1;
        step = -1;
    }
    while(beginningstring1 != end1 && beginningstring2 != end2)
    {
        if(*beginningstring1 != *beginningstring2){
            return *beginningstring1 - *beginningstring2;
        }
        beginningstring1 += step;
        beginningstring2 += step;
    }
    if (beginningstring1 == end1)
    {
        return -1;
    }
    else{
        return 1;
    }
}

int document_comparator_bigger_beginning(const void* string1,const void* string2){
    return document_comparator(*(struct strings*)string1, *(struct strings*)string2, COMPARATOR_STRINGS_BIGGER_BEGINNING);
}

int document_comparator_back_bigger_beginning(const void* string1,const void* string2){
    return document_comparator(*(struct strings*)string1, *(struct strings*)string2, COMPARATOR_STRINGS_BACK_BIGGER_BEGINNING);
}

int document_comparator_pointers(const void* string1,const void* string2){
    return document_comparator(*(struct strings*)string1, *(struct strings*)string2, COMPARATOR_STRINGS_POINTERS);
}

sorter_error_code document_quick_sort(struct document *line, long long leftpointer, long long rightpointer, comparator_mode mode){
    if (line == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    long long left = leftpointer;
    long long right = rightpointer;
    struct strings stringcompare = {line->string[leftpointer].pointer, line->string[leftpointer].length};
    while (leftpointer < rightpointer){
        while (leftpointer < rightpointer && document_comparator(stringcompare, line->string[rightpointer], mode) < 0){
            rightpointer--;
        }
        if (leftpointer != rightpointer){
            line->string[leftpointer] = line->string[rightpointer];
            leftpointer++;
        }
        while (leftpointer < rightpointer && document_comparator(line->string[leftpointer], stringcompare, mode) < 0){
            leftpointer++;
        }
        if (leftpointer != rightpointer){
            line->string[rightpointer] = line->string[leftpointer];
            rightpointer--;
        }
    }
    line->string[leftpointer] = stringcompare;
    long long k = leftpointer;
    leftpointer = left;
    rightpointer = right;
    if (left < k){
        document_quick_sort(line, left, k - 1, mode);
    }
    if (right > k){
        document_quick_sort(line, k + 1, right, mode);
    }
    return SORTER_ERROR_OK;
}

sorter_error_code document_qsort(struct document line, int(*comparator)(const void*, const void*)){
    qsort(line.string, line.number_of_strings, sizeof(struct strings), comparator);
    return SORTER_ERROR_OK;
}

sorter_error_code document_quick_sort_no_boulders(struct document *line, comparator_mode mode){
    return document_quick_sort(line, 0, line->number_of_strings - 1, mode);
}

/** This functions are not used in the solution of the "Evgenii Onegin" problem */

sorter_error_code reverse_string(char *string)
{
    if (string == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    char *pointer = string;
    while(*pointer != '\0'){
        pointer++;
    }
    pointer--;
    while (pointer > string){
        swap(pointer, string);
        pointer--;
        string++;
    }
    return SORTER_ERROR_OK;
}

sorter_error_code reverse_text(char *strings[], int stringnumber){
    if (strings == nullptr){
        return SORTER_ERROR_NO_POINTER;
    }
    for (int i = 0; i <= stringnumber; i++){
        sorter_error_code revers_text_error = reverse_string(strings[i]);
        if (revers_text_error != SORTER_ERROR_OK){
            return revers_text_error;
        }
    }
    return SORTER_ERROR_OK;
}
