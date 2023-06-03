#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pos.h"

typedef Position Item; //�� �̷��� ��? : �̷��� �ϸ� �ٸ� �ڷ������� �� ���� ���ܵ� 'int'�� 'float'�� �ٲٸ� ��!
typedef struct stack_type *Stack;

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);
void terminate(const char *message);
int read_line(FILE *fp, char* str, int limit);