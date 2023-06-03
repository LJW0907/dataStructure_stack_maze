#include <stdio.h>
#include "Stack.h"
#include "pos.h"

#define MAX 5
#define PATH 0 //지나갈 수 있는 위치
#define WALL 1 //지나갈 수 없는 위치
#define VISITED 2 //이미 방문한 위치 : c
#define BACKTRACKED 3 //되돌아 나온 위치

int maze[MAX][MAX];

int offset_main[4][2] = { {-1, 0},
						  {0, 1},
						  {1, 0},
						  {0, -1} }; //북, 동, 남, 서 

bool movable(Position pos, int dir);
void read_maze();
void print_maze();

int main() {
	read_maze(); //maze.txt 파일에서 미로 모양을 배열 maze로 입력받는다.

	Stack s = create();
	Position cur;
	cur.x = 0;
	cur.y = 0;

	while (1) {
		maze[cur.x][cur.y] = VISITED;

		if (maze[MAX-1][MAX-1] == VISITED) { //출구 도착
			printf("Found the path.\n");
			break;
		}

		bool forwarded = false; //4방향 중 한 곳이라도 전진하는데 성공했는지 표시

		for (int dir = 0; dir < 4; dir++) {
			if (movable(cur, dir)) { //dir 방향으로 움직일 수 있는지 검사
				push(s, cur); //현재위치 push
				cur = move_to(cur, dir); //이동한 위치 cur에 저장
				forwarded = true;
				break;
			}
		}

		if (!forwarded) {
			maze[cur.x][cur.y] = BACKTRACKED; //왔다가 되돌아간 위치라고 표시

			if (is_empty(s)) { //되돌아갈 곳이 없다면 길이 없는 미로
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
				printf("□\t");
			else if (maze[x][y] == WALL)
				printf("■\t");
			else if (maze[x][y] == VISITED)
				printf("O\t");
			else if (maze[x][y] == BACKTRACKED)
				printf("X\t");
		}
		printf("\n");
	}
}