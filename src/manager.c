#include "manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME ("./file/XMENFILE")
#define MAX_BUF (128)
#define STR_SPL (",")

//データ変数宣言
X info[MAX_DATA];

//管理データ宣言
XData xmenData;

//プロトタイプ宣言
extern int read_file(XData* xp);

int manager_initialize(){
	int ref = 0;
	
	//データの初期化
	memset(info, '\0', sizeof(info));
	memset(&xmenData, '\0', sizeof(xmenData));

	//管理データのデータに実体のデータのアドレスを入れる
	xmenData.datas = info;

	//ファイルのデータを配列に入れる
	ref =  read_file(&xmenData);
	
	return (ref);
}

int read_file(XData* xp){
	FILE* fp;
	char inBuf[MAX_BUF];
	char wkBuf[MAX_BUF];
	char *strPt;

	memset(inBuf, '\0', sizeof(inBuf));
	memset(wkBuf, '\0', sizeof(wkBuf));
	
	fp = fopen(FILE_NAME, "r");

	if(fp == NULL){
		return (-1);
	}

	while(fgets(inBuf, MAX_BUF, fp)){
		X tmp;
		size_t len;

		memset(&tmp, '\0', sizeof(tmp));
		len = strlen(inBuf);
		if(len > 0 && inBuf[len - 1] == '\n'){
			inBuf[len - 1] = '\0';
		}

		if(xp->data_counts >= MAX_DATA){
			// 最大件数を超えた分は無視する
			break;
		}

		strncpy(wkBuf, inBuf, MAX_BUF - 1);
		wkBuf[MAX_BUF - 1] = '\0';

		strPt = strtok(wkBuf, STR_SPL);
		if(strPt == NULL){
			continue;
		}
		tmp.no = atoi(strPt);

		strPt = strtok(NULL, STR_SPL);
		if(strPt == NULL){
			continue;
		}
		strncpy(tmp.name, strPt, MAX_NAME - 1);
		tmp.name[MAX_NAME - 1] = '\0';

		strPt = strtok(NULL, STR_SPL);
		if(strPt == NULL){
			continue;
		}
		strncpy(tmp.codename, strPt, MAX_NAME - 1);
		tmp.codename[MAX_NAME - 1] = '\0';

		//入れたいデータの位置を相対的に変数化
		X* inData = (X*)xp->datas;
		int inCount = xp->data_counts;

		memcpy(inData + inCount, &tmp, sizeof(X));

		//入れたデータの数をふやす
		xp->data_counts++;
	}
	
	fclose(fp);

	return (0);
}

void*  getXData(){
	return ((void*)&xmenData);
}

void clear(){
	system("clear");
}
