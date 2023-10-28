#include "pseudo-codegen.h"

#include "symbol_table.h"

Attributes* generate_label() {
    int next_label = generate_next_int();
    return create_attributes(TYPE_VOID, next_label, "LABEL", 0, CLASS_LABEL);
}

int actual_label = 0;
int generate_next_int() {
    actual_label++;
    return actual_label;
}

void generate_pseudo_assembly(ASTNode* node, InstructionList* list) {
    if (node == NULL) return;

    switch (node->info->class_type) {
        case CLASS_PROGRAM:
        case CLASS_DECL_LIST:
        case CLASS_SENTENCE_LIST:
        case CLASS_METHODS_DECL_LIST:
            generate_pseudo_assembly(node->left, list);
            generate_pseudo_assembly(node->right, list);
            break;

        case CLASS_DECL_FUNCTION:
            Instruction* init_func_instr = create_instruction(DECL_FUNC_INIT, NULL, NULL, node->info);
            append_instruction(list, init_func_instr);

            //SymbolTable* st_temp = node->info->parameter_list;


            generate_pseudo_assembly(node->left, list);
            Instruction* end_func_instr = create_instruction(DECL_FUNC_END, NULL, NULL, node->info);
            append_instruction(list, end_func_instr);
            break;

        case CLASS_DECL:
        case CLASS_ASSIGN:
            generate_pseudo_assembly(node->right, list);
            CodOp op_code = node->right->info->class_type == CLASS_CONSTANT ? MOV_C : MOV_V;
            Instruction* movInstr = create_instruction(op_code, node->right->info, NULL, node->left->info);
            append_instruction(list, movInstr);
            break;

        case CLASS_ADD:
            generate_binary_operator(node, ADD, list);
            break;

        case CLASS_SUB:
            generate_binary_operator(node, SUB, list);
            break;

        case CLASS_DIV:
            generate_binary_operator(node, DIV, list);
            break;

        case CLASS_MOD:
            generate_binary_operator(node, MOD, list);
            break;

        case CLASS_GREATER:
            generate_binary_operator(node, GREATER, list);
            break;

        case CLASS_LESS:
            generate_binary_operator(node, LESS, list);
            break;

        case CLASS_EQUALS:
            generate_binary_operator(node, EQUALS, list);
            break;

        case CLASS_AND:
            generate_binary_operator(node, AND, list);
            break;

        case CLASS_OR:
            generate_binary_operator(node, OR, list);
            break;

        case CLASS_MUL:
            generate_binary_operator(node, MUL, list);
            break;

        case CLASS_RETURN_EXPR:
            generate_pseudo_assembly(node->left, list);
            Instruction* ret_expr_instr = create_instruction(RETURN_EXPR, NULL, NULL, node->left->info);
            append_instruction(list, ret_expr_instr);
            break;

        case CLASS_RETURN:
            Instruction* ret_instr = create_instruction(RETURN_A, NULL, NULL, NULL);
            append_instruction(list, ret_instr);
            break;

        case CLASS_WHILE:
            Attributes* label = generate_label();
            Instruction* label_first = create_instruction(LABEL, NULL, NULL, label);
            append_instruction(list, label_first);

            generate_pseudo_assembly(node->left, list);
            Attributes* label_two = generate_label();
            Instruction* iff = create_instruction(JMP_F, NULL, node->left->info, label_two);
            append_instruction(list, iff);

            generate_pseudo_assembly(node->right, list);
            Instruction* jmp = create_instruction(JMP, NULL, NULL, label);
            Instruction* label_snd = create_instruction(LABEL, NULL, NULL, label_two);
            append_instruction(list, jmp);
            append_instruction(list, label_snd);
            break;

        case CLASS_IF:
            generate_pseudo_assembly(node->left, list);
            Attributes* label_iff = generate_label();
            Instruction* iff_jmp_instr = create_instruction(JMP_F, NULL, node->left->info, label_iff);
            append_instruction(list, iff_jmp_instr);
            generate_pseudo_assembly(node->middle, list);
            append_instruction(list, create_instruction(LABEL, NULL, NULL, label_iff));
            break;

        case CLASS_IF_THEN_ELSE:
            generate_pseudo_assembly(node->left, list);
            Attributes* l_else = generate_label();
            Attributes* l_final = generate_label();

            append_instruction(list, create_instruction(JMP_F, NULL, node->left->info, l_else));
            generate_pseudo_assembly(node->middle, list);
            append_instruction(list, create_instruction(JMP, NULL, NULL, l_final));
            append_instruction(list, create_instruction(LABEL, NULL, NULL, l_else));
            // LABEL ELSE
            generate_pseudo_assembly(node->right, list);
            append_instruction(list, create_instruction(LABEL, NULL, NULL, l_final));
            // LABEL FINAL

            /*CONDICION
            JMPF t2 l2
            -----
            jmp l_final

            label l_else 12
            ----
            label l_final*/

            break;

        case CLASS_CALL_FUNCTION:
            Instruction* call_instr = create_instruction(CALL, NULL, NULL, node->info);
            append_instruction(list, call_instr);
            break;

        case CLASS_VAR:
        case CLASS_EMPTY:
        case CLASS_CONSTANT:
            break;

        default:
            generate_pseudo_assembly(node->left, list);
            generate_pseudo_assembly(node->right, list);
            break;
    }
}

InstructionList* generate_tac(ASTNode* node) {
    InstructionList* list = (InstructionList*)malloc(sizeof(InstructionList));
    list->head = NULL;
    generate_pseudo_assembly(node, list);
    return list;
}

void generate_binary_operator(ASTNode* node, CodOp op, InstructionList* list) {
    generate_pseudo_assembly(node->left, list);
    generate_pseudo_assembly(node->right, list);
    Instruction* instr = create_instruction(op, node->left->info, node->right->info, node->info);
    append_instruction(list, instr);
}
