#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
typedef struct {
	char name[60]; //ʳ������
	int time; //����ʱ��
	int capacity; //���洢��
}Food; //����ʳ����
typedef struct {
	char name[60]; //�ײ�����
	int sum; //�ײ���ʳ�����Ŀ
	Food food[10]; //�ײͰ�����ʳ������
}Combo;
typedef struct {
	Food food[110]; //�˵��еĵ�Ʒ
	Combo combo[110];  //�˵��е��ײ�
	int N, M, W1, W2;
}Menu;
static int order; // ��¼δ����Ķ�����Ŀ
static int interval[110]; //��¼ÿ��ʳ���Ѿ�ʹ�õ�����ʱ��
static int remain[110]; //��¼ʳ���ʣ����Ŀ
static int time = 7 * 3600; //����ʱ��
static int waituntil = 7 * 3600 - 1; //ʲôʱ�򿪷�
static int waitTime[110]; //���ڵȴ����Ķ���Ҫ��ú����
static int open = 1; //�ж��Ƿ��ܽ��ܶ���
int cmp(const void* a, const void* b) { //�������õ��ıȽ�׼��,���ڴӴ�С����
	return -*(int*)a + *(int*)b;
}
static Menu InitMenu() {
	Menu menu;
	for (int i = 0; i < 110; i++)
		for (int j = 0; j < 10; j++)strcpy(menu.combo[i].food[j].name, "");
	FILE* fp = fopen("dict.dic", "r");
	if (fp != NULL) {
		fscanf(fp, "%d %d", &menu.N, &menu.M);
		for (int i = 0; i < menu.N; i++)fscanf(fp, "%s", menu.food[i].name);
		for (int i = 0; i < menu.N; i++)fscanf(fp, "%d", &menu.food[i].time);
		for (int i = 0; i < menu.N; i++)fscanf(fp, "%d", &menu.food[i].capacity);
		fscanf(fp, "%d %d", &menu.W1, &menu.W2);
		for (int i = 0; i < menu.M; i++) {
			fscanf(fp, "%s", menu.combo[i].name);
			char ch;
			int cnt = 0;
			while (1) {
				char tmp[60] = "";
				int pos;
				ch = fgetc(fp);
				if (ch == '\r') {
					ch=fgetc(fp);
					if (ch == '\n') {
						menu.combo[i].sum = cnt;
						break;
					}
				}
				if (ch == '\n') {
					menu.combo[i].sum = cnt;
					break;
				}
				if (ch == EOF) {
					menu.combo[i].sum = cnt;
					break;
				}
				fscanf(fp, "%s", tmp);
				for (pos = 0; pos < menu.N; pos++)
					if (strcmp(menu.food[pos].name, tmp) == 0)break;
				menu.combo[i].food[cnt].time = menu.food[pos].time;
				menu.combo[i].food[cnt].capacity = menu.food[pos].capacity;
				strcpy(menu.combo[i].food[cnt].name, menu.food[pos].name);
				cnt++;
			}
		}
		fclose(fp);
		fp = NULL;
		return menu;
	}
}
void ProcessOrder(Menu menu) { //��ȡÿһ�ж���������
	if (order > menu.W1)open = 0;
	int new_time = 0;
	int h, m, s;  scanf("%d", &h); getchar(); scanf("%d", &m); getchar(); scanf("%d", &s);
	new_time = new_time + h * 60 * 60 + m * 60 + s; //��ȡ����ʱ��;
	qsort(waitTime, 110, sizeof(int), cmp);
	int old_order = order;
	int bool_time = waitTime[menu.W2 - 1];
	for (int i = 0; i < old_order; i++)if (new_time >= waitTime[i] && waitTime[i] > 0) {
		waitTime[i] = 0; order--;
	} //����ȴ��Ķ���
	//����һ��ʣ���ʳ��
	for (int i = 0; i < menu.N; i++)interval[i] += new_time - time; //�ۼ�һ������ʱ��
	time = new_time;
	for (int i = 0; i < menu.N; i++) {
		int make = interval[i] / menu.food[i].time;
		if (make + remain[i] >= menu.food[i].capacity) {
			remain[i] = menu.food[i].capacity;
			interval[i] = 0;
		}
		else if (make + remain[i] < menu.food[i].capacity && make > 0) {
			remain[i] = remain[i] + make;
			interval[i] = interval[i] % menu.food[i].time;
		}
	}
	//�ж��Ƿ��ܿ���ϵͳ
	if (order<menu.W2 && time>bool_time)open = 1;
	if (open == 0) {
		char tmp[60]; scanf("%s", tmp); //Ҫ���벻����Ĳ�Ʒ����
		printf("Fail\n");
	}
	else {
		char tmp[60];
		scanf("%s", tmp);
		int pos; for (pos = 0; pos < menu.N; pos++)if (strcmp(tmp, menu.food[pos].name) == 0)break;
		if (pos == menu.N) { //���ڵ������Ŀ��
			int max_time = 0; //�жϸ��ײ��ܲ�����������,����������Ҫ�������
			for (pos = 0; pos < menu.M; pos++)if (strcmp(tmp, menu.combo[pos].name) == 0)break;
			int need_wait = 0;
			for (int i = 0; i < menu.combo[pos].sum; i++) {
				int j;
				for (j = 0; j < menu.N; j++)if (strcmp(menu.combo[pos].food[i].name, menu.food[j].name) == 0)break;
				if (remain[j] > 0) {
					remain[j]--;
				}
				else { //ע��һ���ײ���������������Ҳֻ����һ������������

					need_wait = 1;
					if (max_time < menu.food[j].time - remain[j] * menu.food[j].time - interval[j])max_time = menu.food[j].time - remain[j] * menu.food[j].time - interval[j];
					remain[j]--;
				}
			}
			if (need_wait == 1)waitTime[order++] = time + max_time;
			printf("%02d:%02d:%02d\n", (time + max_time) / 3600, (time + max_time) % 3600 / 60, (time + max_time) % 3600 % 60);
		}
		else { //�����Ʒ�Ĵ���
			if (remain[pos] > 0) {
				remain[pos]--;
				printf("%02d:%02d:%02d\n", time / 3600, time % 3600 / 60, time % 3600 % 60);
			}
			else {
				waitTime[order++] = time + menu.food[pos].time - remain[pos] * menu.food[pos].time - interval[pos];
				printf("%02d:%02d:%02d\n", (time + menu.food[pos].time-remain[pos]*menu.food[pos].time-interval[pos]) / 3600, (time + menu.food[pos].time - remain[pos] * menu.food[pos].time-interval[pos]) % 3600 / 60, (time + menu.food[pos].time - remain[pos] * menu.food[pos].time-interval[pos]) % 3600 % 60);
				remain[pos]--;
			}
		}
	}
}
int main() {
	Menu menu = InitMenu(); //��ȡ�˵�
	int n; scanf("%d", &n);
	while (n--) {
		ProcessOrder(menu); //������
	}
	return 0;
}