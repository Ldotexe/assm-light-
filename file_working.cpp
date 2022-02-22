#include "FILE_working.h"

const char* file_errors_value[] = {
    "FILE_ERROR_OK",
    "FILE_ERROR_NO_MEMORY"
};

long long filesizeoftext (FILE* readfile){
    fseek(readfile, 0, SEEK_END);
    long long filesize = ftell(readfile);
    fseek(readfile, 0, SEEK_SET);
    return filesize;
}

file_working_code allocate_memory (long long number_of_bytes, char** buffer){
    *buffer = (char*) calloc(number_of_bytes, sizeof(char));
    if (*buffer == nullptr){
        return FILE_ERROR_NO_MEMORY;
    }
    return FILE_ERROR_OK;
}

file_working_code text_read (char** text, long long filesize, FILE* readfile){
    if (allocate_memory(filesize + 1, text) != FILE_ERROR_OK){
        return FILE_ERROR_NO_MEMORY;
    }
    fread(*text, filesize, sizeof(char), readfile);
    (*text)[filesize] = '\0';
    return FILE_ERROR_OK;
}
