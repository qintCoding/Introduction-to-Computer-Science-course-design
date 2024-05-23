#pragma once
typedef struct {
	char name[60]; //食物名字
	int time; //制作时间
	int capacity; //最大存储量
}Food; //定义食物类
typedef struct {
	char name[60]; //套餐名称
	int sum; //套餐中食物的数目
	Food food[10]; //套餐包含的食物种类
}Combo;
typedef struct {
	Food food[110]; //菜单中的单品
	Combo combo[110];  //菜单中的套餐
	int N, M, W1, W2;
}Menu;
void PrintMenu();