#include <stdio.h>

#define Q_MAX 100000

int r, c;
char map[1510][1510];
char copy[1510][1510];
char visit[1510][1510];
int sol;

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

typedef struct point {
	int y;
	int x;
}Point;

Point people[2];

Point queue[Q_MAX];
int front, rear;

int isEmpty() {
	return front == rear;
}

void enQueue(int y,int x) {
	queue[rear].y = y;
	queue[rear++].x = x;
	if (rear == Q_MAX) rear = 0;
}

Point deQueue() {
	Point ret;
	ret.y = queue[front].y;
	ret.x = queue[front++].x;
	if (front == Q_MAX) front = 0;
	return ret;
}

void copyMap() {
	int i, j;
	int cnt = 0;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			copy[i][j] = visit[i][j] = map[i][j];
			if (copy[i][j] == 'L') {
				people[cnt].y = i;
				people[cnt++].x = j;
			}
		}
		printf("\n");
	}
}

void BFS_MAP() {
	front = rear = 0;

}

void DFS_MEET(int y, int x) {
	
}

int BFS_MEET() {
	front = rear = 0;

	return 1;
}

int main(){
	int i, j;
	//int sol=0;
	char str[1510];
	scanf("%d %d", &r, &c);
	gets(str);
	for (i = 1; i <= r;i++) {
		gets(str);
		for (j = 1; j <= c; j++) {
			map[i][j] = str[j-1];
		}
	}

	copyMap();

	while (!sol) {
		BFS_MAP();
		copyMap();
		//sol = BFS_MEET();
		DFS_MEET(people[0].y, people[0].y);
	}

	printf("%d\n", sol);

	/*for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}*/

	
	return 1;
}