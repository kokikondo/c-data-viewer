#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input.h"
#include "manager.h"

#define MAX_PRINTDATA (5)

//プロトタイプ宣言
extern void update_displayData(X* p1, XData* p2, int page);

int main(){
	int c;
	int endFlag;
	int prev_c;

	X printData[MAX_PRINTDATA];
	XData* xmenData;

	int counts;
	int page;
	int page_max;
	int i;
	int targetIndex;

	char msg[128];

	//初期化
	endFlag = 1;
	prev_c = 0;

	if(manager_initialize() == -1){
			printf("file not found:/\n");
			return(-1);
	}

	memset(printData, '\0', sizeof(printData));
	xmenData = (XData*)getXData();

	page = 0;
	page_max = xmenData->data_counts == 0 ? 1 : (int)ceil((double)xmenData->data_counts / (double)MAX_PRINTDATA);
	i = 0;
	targetIndex = 0;

	memset(msg, '\0', sizeof(msg));
	
	clear();

	initialize_input();
	
	//表示データを作成
	update_displayData(printData, xmenData, page);

	//表示
	while(endFlag ==  1){
		
		printf("----------------X-men-member-----------------\n");
		printf("----No.--------Name------------CodeName------\n");
		for(i = 0; i  < MAX_PRINTDATA; i++){

			X tmp = printData[i];

			if(i == targetIndex){
				printf("\e[30m \e[47m");
			}

			if(tmp.name[0] != '\0'){
				printf("    %04d       %-16s%s\n", tmp.no, tmp.name, tmp.codename);
			}
			else{
				printf("    ----           -             -           \n");
			}


			if(i == targetIndex){
				printf("\e[0m");
			}
								
		}
		printf("---------------------------------------------\n");
		printf("'a':page-'d':next page -----------------%d/%d\n", page + 1, page_max);
		printf("%s\n", msg);

		//キー入力待ち
		c = getch();
		clear();
		memset(msg, '\0', sizeof(msg));

		switch((char)c){

		case 'e':
			printf("end of system.\nthaks you tester:)\n"
							);
			endFlag = 0;
			break;

		case 'w':
			//カーソルを上へ
			if(targetIndex <= 0){
				targetIndex = MAX_PRINTDATA -1;
			}
			else{
				targetIndex--;
			}
			break;


		case 's':
			//カーソルを下へ
			if(targetIndex >= MAX_PRINTDATA - 1){
				targetIndex = 0;
			}
			else{
				targetIndex++;
			}
			break;


	
		case 'a':
			//前のページに戻る
			if(page <= 0){
				page = 0;
				strcpy(msg, "[msg]最初のページです。");
			}
			else{
				page--;
			}

			//ページ更新
			update_displayData(printData, xmenData, page);
			break;


		case 'd':
			//次のページへ
			if(page >= page_max - 1){
				page = page_max  - 1;
				strcpy(msg, "[msg]page is max.");
			}
			else{
				page++;
			}

			//ページ更新
			update_displayData(printData, xmenData, page);
			break;
		}

	}

	finalize_input();
	return (0);
}


void update_displayData(X* p1, XData* p2, int page){
	//宣言
	int data_max;
	int index;
	int i;

	//初期化
	data_max = p2->data_counts;
	index = page * MAX_PRINTDATA;

	memset(p1, '\0',sizeof(X) * MAX_PRINTDATA);

	for(i = 0; i < MAX_PRINTDATA; i++){
			//避難用変数を宣言、初期化
			X tmp;
			memset(&tmp, '\0', sizeof(tmp));

			//構造体のデータの変数を宣言、初期化
			X *wkData = ((X*)p2->datas) + index;

			if(index >= data_max){
				//今のページにはデータがあるがすべて埋まらないのでそのデータはからデータとしてスキップする
				continue;
			}
			else if(wkData->name[0] != '\0'){
				//名前の最初のデータが終了文字でなければデータあり
				tmp.no =(wkData->no);
				strcpy(tmp.name, wkData->name);
				strcpy(tmp.codename, wkData->codename);
				memcpy(&p1[i], &tmp, sizeof(X));
			}
			else{
				//もし虫食いのデータなしならデータを詰めるためいったんループをすすめさせない
				i--;
			}

			//次回のループの取得するアドレスを取得する
			index++;
	}
}
