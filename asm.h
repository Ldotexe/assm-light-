#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED
#include "string_sorting.h"
#include "stack_functions.h"
#include <string.h>

extern const int ASM_BASIC_JMP_NUM;
extern const int ASM_MEMORY_MAX;
extern const int ASM_REG_NUM;

enum asm_error{
    ASM_OK,
    ASM_WRONG_FORMAT,
    ASM_WRONG_DIGIT,
    ASM_NO_MEMORY
};

typedef struct asm_info{
    document* code;
    int line_num;
    stack_t* jmp_adr;
    stack_t* jmp_id;
    int jmp_num;
    elemen_t *memory;
    elemen_t *reg_memory;
    int memory_adress;

}asm_info;

asm_error hex_to_dec_reg (char reg, int value);
asm_error hex_to_dec (char* str, int value);
asm_error run_asm_code (document* code, char* output_file);
void jmp_action (asm_info *info);
asm_error jmp_check (asm_info *info);
asm_error jmp_processing (asm_info *info);
asm_error line_processing (asm_info *info);

#endif // ASM_H_INCLUDED
