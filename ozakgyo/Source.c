#include <stdio.h>

#define Q_MAX 1000000

int r, c;
char map[1510][1510];
char visit[1510][1510];
char meet[1510][1510];
int sol;
int push_cnt, people_cnt;

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

typedef struct point {
	int y;
	int x;
}Point;

Point people[2];

Point queue[Q_MAX];
int front, rear;

Point queue_new[Q_MAX];
int front_new, rear_new;

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


int isEmptyNew() {
	return front_new == rear_new;
}

void enQueueNew(int y, int x){ 
	queue_new[rear_new].y = y;
	queue_new[rear_new++].x = x;
	if (rear_new == Q_MAX) rear_new = 0;
}

Point deQueueNew() {
	Point ret;
	ret.y = queue_new[front_new].y;
	ret.x = queue_new[front_new++].x;
	if (front_new == Q_MAX) front_new = 0;
	return ret;
}

void initVisit() {
	int i, j;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			//copy[i][j] = visit[i][j] = map[i][j];
			visit[i][j] = 0;
		}
		//printf("\n");
	}
}

void BFS_MAP() {
	Point p;
	int i,j;
	int next_y, next_x;
	int cnt = push_cnt;
	push_cnt = 0;
	for (i = 0; i < cnt; i++) {
		p = deQueue();
		for (j = 0; j < 4; j++) {
			next_y = p.y + dy[j];
			next_x = p.x + dx[j];
			if (next_y<1 || next_y>r || next_x<1 || next_x>c)
				continue;
			if (map[next_y][next_x] == 'X' && visit[next_y][next_x] == 0) {
				enQueue(next_y, next_x);
				map[next_y][next_x] = '.';
				visit[next_y][next_x] = 1;
				push_cnt++;
			}
		}
	}
}


int BFS_MEET(int num) {
	Point p;
	int i;
	int next_y, next_x;
	front_new = rear_new = 0;
	enQueueNew(people[0].y, people[0].x);

	while (!isEmptyNew()) {
		p = deQueueNew();
		//printf("%d %d\n", p.y, p.x);
		for (i = 0; i < 4; i++) {
			next_y = p.y + dy[i];
			next_x = p.x + dx[i];
			if (next_y<1 || next_y>r || next_x<1 || next_x>c)
				continue;
			if (map[next_y][next_x] != 'X' && meet[next_y][next_x] != num) {
				if (map[next_y][next_x] == 'R') {
					return 1;
				}
				enQueueNew(next_y, next_x);
				//printf("%d %d\n", next_y, next_x);

				map[next_y][next_x] = 'L';
				meet[next_y][next_x] = num;
			}
		}
	}

	return 0;
}

void printMap() {
	int i, j;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(){
	int i, j;
	//int sol=0;
	char str[1510];
	int ans, check;
	/*FILE* fp;
	printf("aaaa\n");
	fp=fopen("input.txt", "r");
	
	fscanf(fp,"%d", &r);
	fscanf(fp,"%d", &c);
	for (i = 1; i <= r; i++) {
		fgets(str, 1510, fp);
		for (j = 1; j <= c; j++) {
			map[i][j] = str[j - 1];
		}
	}

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}*/

	scanf("%d %d", &r, &c);
	gets(str);
	for (i = 1; i <= r;i++) {
		gets(str);
		for (j = 1; j <= c; j++) {
			map[i][j] = str[j-1];
			if (map[i][j] == '.') {
				enQueue(i, j);
				push_cnt++;
			}
			
			else if (map[i][j] == 'L') {
				people[people_cnt].y = i;
				people[people_cnt++].x = j;
			}
		}
	}

	map[people[1].y][people[1].x] = 'R';


	/*initVisit();

	printf("\n");
	printMap();
	initVisit();
	BFS_MEET();
	printMap();*/

	check = 0;
	ans = 0;
	while (!check) {
		BFS_MAP();
		//initVisit();
		check=BFS_MEET(ans);
		ans++;
	}

	printf("%d\n", ans);

	return 1;
}