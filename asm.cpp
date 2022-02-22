#include "asm.h"

const int ASM_BASIC_JMP_NUM = 4;
const int ASM_MEMORY_MAX = 66000;
const int ASM_REG_NUM = 16;

asm_error hex_to_dec_reg (char reg, int value){
    value = 0;
    if ('0' <= reg && reg <= '9'){
        value = reg - '0';
        return ASM_OK;
    }
    if ('a' <= reg && reg <= 'f'){
        value = reg - 'a' + 10;
        return ASM_OK;
    }
    if ('A' <= reg && reg <= 'F'){
        value = reg - 'A' + 10;
        return ASM_OK;
    }
    return ASM_WRONG_DIGIT;
}

asm_error hex_to_dec (char* str, int value){
    asm_error asm_error_check = ASM_OK;
    value = 0;
    int deg = 1, reg_val = 0;
    for (int i = strlen(str) - 1; i >= 0; --i){
        if (hex_to_dec_reg (str[i], reg_val) != ASM_OK){
            asm_error_check = hex_to_dec_reg (str[i], reg_val);
        }
        value += reg_val * deg;
        deg *= 16;
    }
    return asm_error_check;
}

asm_error run_asm_code (document* code, char* output_file){
    FILE *out_file = fopen(output_file, "w");
    asm_info info;
    info.line_num = 0;
    info.code = code;
    stack_ctor(info.jmp_adr, ASM_BASIC_JMP_NUM);
    stack_ctor(info.jmp_id,  ASM_BASIC_JMP_NUM);
    info.jmp_num = 0;
    info.memory     = (elemen_t*) (malloc(sizeof(elemen_t) * ASM_MEMORY_MAX));
    info.reg_memory = (elemen_t*) (malloc(sizeof(elemen_t)  *   ASM_REG_NUM));
    if (info.memory == NULL){
        return ASM_NO_MEMORY;
    }
    ///first
    for (info.line_num = 0; info.line_num < code->number_of_strings; ++info.line_num){
        jmp_processing (&info);
    }
    ///second
    for (info.line_num = 0; info.line_num < code->number_of_strings; ++info.line_num){
        line_processing (&info);
    }
    return ASM_OK;
}

void jmp_action (asm_info *info){
    stack_push(info->jmp_adr, info->memory_adress);
    stack_push(info->jmp_id,              0);
    info->jmp_num++;
    for (int i = 0; i < info->jmp_num; ++i){
        if (info->jmp_adr->data[i] == info->memory_adress){
            info->jmp_id->data[i] = info->line_num;
        }
    }
}

asm_error jmp_check (asm_info *info){
    for (int i = 0; i < info->jmp_num; ++i){
        if (info->jmp_adr->data[i] == info->memory_adress){
            info->jmp_id->data[i] = info->line_num;
        }
    }
}

asm_error jmp_processing (asm_info *info){
    char cmd_adress_s[4], cmd_num_s[2], reg1_s[1], reg2_s[1], memory_adress_s[4];
    int cmd_adress = 0, cmd_num = 0, reg1 = 0, reg2 = 0;
    if (sscanf(info->code->string[info->line_num].pointer, "%s %s %s %s %s", cmd_adress_s, cmd_num_s, reg1_s, reg2_s, memory_adress_s) == 5){
        hex_to_dec (cmd_adress_s, cmd_adress);
        hex_to_dec (cmd_num_s, cmd_num);
        hex_to_dec (reg1_s, reg1);
        hex_to_dec (reg2_s, reg2);
        hex_to_dec (memory_adress_s, info->memory_adress);
        if ((128 <= cmd_num && cmd_num <= 134) || (147 <= cmd_num && cmd_num <= 150)){
            jmp_action (info);
        }
        else{
            jmp_check (info);
        }
    }
    else{
        return ASM_WRONG_FORMAT;
    }
}

asm_error line_processing (asm_info *info){
    char cmd_adress_s[4], cmd_num_s[2], reg1_s[1], reg2_s[1], memory_adress_s[4];
    int cmd_adress = 0, cmd_num = 0, reg1 = 0, reg2 = 0;
    info->memory_adress = 0;
    if (sscanf(info->code->string[info->line_num].pointer, "%s %s %s %s %s", cmd_adress_s, cmd_num_s, reg1_s, reg2_s, memory_adress_s) == 5){
        hex_to_dec (cmd_adress_s, cmd_adress);
        hex_to_dec (cmd_num_s, cmd_num);
        hex_to_dec (reg1_s, reg1);
        hex_to_dec (reg2_s, reg2);
        hex_to_dec (memory_adress_s, info->memory_adress);
        switch(cmd_num)
        {
        case 153:
            break;
        case 0:
            jmp_check(info);

            break;

        default:
            break;
        }
    }
    else{
        return ASM_WRONG_FORMAT;
    }
}
