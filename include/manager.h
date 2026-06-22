#ifndef MANAGER_H
#define MANAGER_H

#define MAX_NAME (30) 
#define MAX_DATA (50) 

//データ構造体
struct sample_0{
	int no;
	char name[MAX_NAME];
	char codename[MAX_NAME];
};

typedef struct sample_0 X;

//データ構造体
struct sample_1{
	void* datas;
	int data_counts;
};

typedef struct sample_1 XData;

extern int manager_initialize();
extern void* getXData();
extern void clear();

#endif //MANAGER_H
