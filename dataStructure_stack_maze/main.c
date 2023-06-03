#include <stdio.h>
#include "Stack.h"
#include "pos.h"

#define MAX 5
#define PATH 0 //������ �� �ִ� ��ġ
#define WALL 1 //������ �� ���� ��ġ
#define VISITED 2 //�̹� �湮�� ��ġ : c
#define BACKTRACKED 3 //�ǵ��� ���� ��ġ

int maze[MAX][MAX];

int offset_main[4][2] = { {-1, 0},
						  {0, 1},
						  {1, 0},
						  {0, -1} }; //��, ��, ��, �� 

bool movable(Position pos, int dir);
void read_maze();
void print_maze();

int main() {
	read_maze(); //maze.txt ���Ͽ��� �̷� ����� �迭 maze�� �Է¹޴´�.

	Stack s = create();
	Position cur;
	cur.x = 0;
	cur.y = 0;

	while (1) {
		maze[cur.x][cur.y] = VISITED;

		if (maze[MAX-1][MAX-1] == VISITED) { //�ⱸ ����
			printf("Found the path.\n");
			break;
		}

		bool forwarded = false; //4���� �� �� ���̶� �����ϴµ� �����ߴ��� ǥ��

		for (int dir = 0; dir < 4; dir++) {
			if (movable(cur, dir)) { //dir �������� ������ �� �ִ��� �˻�
				push(s, cur); //������ġ push
				cur = move_to(cur, dir); //�̵��� ��ġ cur�� ����
				forwarded = true;
				break;
			}
		}

		if (!forwarded) {
			maze[cur.x][cur.y] = BACKTRACKED; //�Դٰ� �ǵ��ư� ��ġ��� ǥ��

			if (is_empty(s)) { //�ǵ��ư� ���� ���ٸ� ���� ���� �̷�
				printf("No path exists.\n");
				exit(1);
			}
			cur = pop(s);
		}
		print_maze();
		printf("\n\n");
	}

	print_maze();
}

bool movable(Position pos, int dir) {
	if(pos.x + offset_main[dir][0] < 0 || pos.y + offset_main[dir][1] < 0)
		return false;
	else if(pos.x + offset_main[dir][0] >= MAX || pos.y + offset_main[dir][1] >= MAX)
		return false;

	if (maze[pos.x + offset_main[dir][0]][pos.y + offset_main[dir][1]] == 0)
		return true;
	else
		return false;
}

void read_maze() {
	FILE *fp;
	int num;
	char ch;
	char file_name[30];

	if (!read_line(stdin, file_name, 30)) 
		terminate("can't read file name");
	else if (fp = fopen(file_name, "r")) {
		for (int x = 0; x < MAX; x++) {
			for (int y = 0; y < MAX; y++) {
				ch = fgetc(fp);
				maze[x][y] = (int)(ch - '0');
			}
			ch = fgetc(fp);
		}

		fclose(fp);
	}
	else
		terminate("No such file exists");
}

void print_maze() {
	for (int x = 0; x < MAX; x++) {
		for (int y = 0; y < MAX; y++) {
			if (maze[x][y] == PATH)
				printf("��\t");
			else if (maze[x][y] == WALL)
				printf("��\t");
			else if (maze[x][y] == VISITED)
				printf("O\t");
			else if (maze[x][y] == BACKTRACKED)
				printf("X\t");
		}
		printf("\n");
	}
}