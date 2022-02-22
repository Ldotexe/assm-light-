#include "asm.h"

void arg_processing (int argc, const char** argv, char* input_file, char* output_file);

//*************************************************************************************************

int main (int argc, const char** argv)
{
    char *input_file = NULL, *output_file = NULL;
    arg_processing(argc, argv, input_file, output_file);
    document asm_code = {};
    document_ctor_file(&asm_code, input_file);

    return 0;
}

//*************************************************************************************************

void arg_processing (int argc, const char** argv, char* input_file, char* output_file){
    if (!argc){
        char *input_file = (char*) malloc(sizeof(char) * 10);
        char *output_file = (char*) malloc(sizeof(char) * 11);
        input_file  = "input.txt";
        output_file = "output.txt";
    }
    if (argc == 1){
        input_file = (char*) argv[0];
        char *output_file = (char*) malloc(sizeof(char) * 11);
        output_file = "output.txt";
    }
    if (argc == 2){
        input_file  = (char*) argv[0];
        output_file = (char*) argv[1];
    }
}
