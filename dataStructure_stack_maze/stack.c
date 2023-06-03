#include "stack.h"
#include "pos.h"

#define INIT_CAPACITY 100

void reallocate(Stack s);

struct stack_type {
	Item *contents; //stack ������ �� �迭
	int top; //contents�� top ����
	int size; //contents�� size
};

static void terminate(const char *message) {//���� ó�� �Լ�
	printf("%s\n", message);
	exit(1);
}

Stack create() { //Stack ��ü ����
	Stack s = (Stack)malloc(sizeof(struct stack_type));

	if (s == NULL)
		terminate("Error in create: stack could not be created");

	s->contents = (Item*)malloc(sizeof(Item) * INIT_CAPACITY);

	if (s->contents == NULL) {
		free(s);
		terminate("Error in create: stack could not be created.");
	}
	s->top = -1;
	s->size = INIT_CAPACITY;

	return s;
}

void destroy(Stack s) { //Stack ��ü ����
	free(s->contents);
	free(s);
}

void make_empty(Stack s) { //Stack �ʱ�ȭ
	s->top = -1;
}

bool is_empty(Stack s) { //empty ���� Ȯ��
	return s->top == -1;
}

int is_full(Stack s) { //is_full
	return s->top == s->size - 1;
}

void push(Stack s, Item i) { //push
	if (is_full(s))
		reallocate(s);
	s->top++;
	s->contents[s->top] = i;
}

Item pop(Stack s) { //pop
	if (is_empty(s))
		terminate("Error in pop: stack is empty.");
	s->top--;

	return s->contents[s->top + 1];
}

Item peek(Stack s) { //peek
	if (is_empty(s))
		terminate("Error in peek: stack is empty.");

	return s->contents[s->top];
}

void reallocate(Stack s) {
	Item *tmp = (Item*)malloc(sizeof(Item) * 2 * s->size);

	if (tmp == NULL)
		terminate("Error in create: stack could not be created.");

	for (int i = 0; i < s->size; i++)
		tmp[i] = s->contents[i];

	free(s->contents);

	s->contents = tmp;
	s->size *= 2;
}

int read_line(FILE *fp, char* str, int limit) { //������ ��� ������ ���ڿ� �Է� �Լ�
	int ch, i = 0;
	char tmp = ' ';

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) //getchar()�� ��ȯ���� int��!! ���
		if (i < limit - 1) {
			if (tmp != ' ' || ch != ' ') {
				str[i++] = tmp = ch;
			}
		}

	if (str[i - 1] == ' ')
		i--;

	str[i] = '\0';
	return i; //���ڿ� ���� ��ȯ
}