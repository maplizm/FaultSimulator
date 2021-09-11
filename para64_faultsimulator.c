#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define OR 1
#define AND 2
#define BRANCH 3
#define PO 4
#define XOR 5
#define NAND -1
#define NOR -2
#define NOT -3

typedef struct DATA{
	int data;
	struct DATA *next;
}DATA_T;

typedef struct QUEUE{
	DATA_T *head;
	DATA_T *tail;
}QUEUE_T;

/* 関数のプロトタイプ宣言 */
void initQueue(QUEUE_T*);
void finishQueue(QUEUE_T*);
void printQueue(QUEUE_T*);
void enqueue(QUEUE_T*, int);
int deqeueue(QUEUE_T*);



/* キューを初期化する関数 */
void initQueue(QUEUE_T *queue){
	queue->head = NULL;
	queue->tail = NULL;
}

/* キューの終了処理をする関数 */
void finishQueue(QUEUE_T *queue){
	DATA_T *p, *next;
	p = queue->head;
	while(p != NULL){
		next = p->next;
		free(p);
		p = next;
	}
}

/* エンキューする関数 */
void enqueue(QUEUE_T *queue, int input){

  	DATA_T *add;

  	/* エンキューするデータを保持するメモリを確保 */
  	add = (DATA_T*)malloc(sizeof(DATA_T));

  	/* メモリが足りなければ何もせず関数終了 */
  	if(add == NULL){
    		printf("メモリが取得ないためエンキューできません\n");
    		return ;
  	}

  	add->data = input;
  	add->next = NULL;

  	/* キューが空の場合は先頭に追加するのみ */
  	if(queue->head == NULL){
    		queue->head = add;
    		queue->tail = add;
    		return ;
  	}

  	/* キューの最後尾に追加したデータを追加 */
  	/* キューの最後尾のデータのnextを追加データのアドレスにセット */
  	queue->tail->next = add;

  	/* キューの最後尾を指すtailを追加したデータのアドレスにセット */
  	queue->tail = add;
}

/* デキューする関数 */
int dequeue(QUEUE_T *queue){
  	int i = 0;
  	int ret = 0;
  	DATA_T *tmpNext;

  	/* キューが空なら何もせずに関数終了 */
  	if(queue->head == NULL){
    		printf("キューが空です\n");
    		return -1;
  	}

  	/* デキューする数（先頭データ）を取得 */
  	ret = queue->head->data;

  	/* デキューするデータのnextポインタの指すアドレスを退避 */
  	tmpNext = queue->head->next;

  	/* デキューしたデータ（先頭データ）を削除 */
  	free(queue->head);

  	/* 先頭を指すheadポインタを先頭の次のデータのアドレス（退避したアドレス）にセット */
  	queue->head = tmpNext;

  	return ret;
}

/* キューの中身を表示 */
void printQueue(QUEUE_T *queue){
  	int i = 0;
  	DATA_T *p;

  	p = queue->head;
  	while(p != NULL){
    		printf("%d,", p->data);
    		p = p->next;
  	}
  	printf("\n");
}


int logic_calc_AND(int line,int signal_line[][7],int pointer[]){
	int result;
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{
		j=signal_line[line][2];
		if(signal_line[line][1]==1){
			if(signal_line[j-1][5]==-1){
				return -1;
			}
			else{
				signal_line[line][5]=signal_line[j-1][5];
			}
		}
		else{
			if(signal_line[pointer[j-1]-1][5]==-1){
				return -1;
			}
			else{
				result=signal_line[pointer[j-1]-1][5];
				for(i=1; i<signal_line[line][1]; i++){
					if(signal_line[pointer[j+i-1]-1][5]==-1){
						return -1;
					}
					else{
						result&=signal_line[pointer[j+i-1]-1][5];
					}
				}
				signal_line[line][5]=result;
			}
		}
	}
	return 0;
}

int logic_calc_OR(int line,int signal_line[][7],int pointer[]){
	int result;
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{
		j=signal_line[line][2];
		if(signal_line[line][1]==1){
			if(signal_line[j-1][5]==-1){
				return -1;
			}
			else{
				signal_line[line][5]=signal_line[j-1][5];
			}
		}
		else{
			if(signal_line[pointer[j-1]-1][5]==-1){
				return -1;
			}
			else{
				result=signal_line[pointer[j-1]-1][5];
				for(i=1; i<signal_line[line][1]; i++){
					if(signal_line[pointer[j+i-1]-1][5]==-1){
						return -1;
					}
					else{
						result|=signal_line[pointer[j+i-1]-1][5];
					}
				}
				signal_line[line][5]=result;
			}
		}
	}
	return 0;
}

int logic_calc_NAND(int line,int signal_line[][7],int pointer[]){
	int result=-1;
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{
		j=signal_line[line][2];
		if(signal_line[line][1]==1){
			if(signal_line[j-1][5]==-1){
				return -1;
			}
			else{
				signal_line[line][5]=signal_line[j-1][5];
			}
		}
		else{
			if(signal_line[pointer[j-1]-1][5]==-1){
				return -1;
			}
			else{
				result=signal_line[pointer[j-1]-1][5];
				for(i=1; i<signal_line[line][1]; i++){
					if(signal_line[pointer[j+i-1]-1][5]==-1){
						return -1;
					}
					else{
						result&=signal_line[pointer[j+i-1]-1][5];
					}
				}
				signal_line[line][5]=!result;
			}
		}
	}
	return 0;
}

int logic_calc_NOR(int line,int signal_line[][7],int pointer[]){
	int result;
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{
		j=signal_line[line][2];
		if(signal_line[line][1]==1){
			if(signal_line[j-1][5]==-1){
				return -1;
			}
			else{
				signal_line[line][5]=signal_line[j-1][5];
			}
		}
		else{
			if(signal_line[pointer[j-1]-1][5]==-1){
				return -1;
			}
			else{
				result=signal_line[pointer[j-1]-1][5];
				for(i=1; i<signal_line[line][1]; i++){
					if(signal_line[pointer[j+i-1]-1][5]==-1){
						return -1;
					}
					else{
						result|=signal_line[pointer[j+i-1]-1][5];
					}
				}
				signal_line[line][5]=!result;
			}
		}
	}
	return 0;
}

int logic_calc_XOR(int line,int signal_line[][7],int pointer[]){
	int result;
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{
		j=signal_line[line][2];
		if(signal_line[line][1]==1){
			if(signal_line[j-1][5]==-1){
				return -1;
			}
			else{
				signal_line[line][5]=signal_line[j-1][5];
			}
		}
		else{
			if(signal_line[pointer[j-1]-1][5]==-1){
				return -1;
			}
			else{
				result=signal_line[pointer[j-1]-1][5];
				for(i=1; i<signal_line[line][1]; i++){
					if(signal_line[pointer[j+i-1]-1][5]==-1){
						return -1;
					}
					else{
						result^=signal_line[pointer[j+i-1]-1][5];
					}
				}
				signal_line[line][5]=result;
			}
		}
	}
	return 0;
}

int logic_calc_NOT(int line,int signal_line[][7]){
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{	
		j=signal_line[line][2];
		if(signal_line[j-1][5]==-1){
			return -1;
		}
		else{
			signal_line[line][5]=!signal_line[j-1][5];
		}
	}
	return 0;
}

int logic_calc_BRANCH(int line,int signal_line[][7]){
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{
		j=signal_line[line][2];
		if(signal_line[j-1][5]==-1){
			return -1;
		}
		else{
			signal_line[line][5]=signal_line[j-1][5];
		}
	}
	return 0;
}

int logic_calc_PO(int line,int signal_line[][7]){
	int i,j;
	if(signal_line[line][1]<1){
		printf("input_num error\n");
		return -1;
	}
	else{
		j=signal_line[line][2];
		if(signal_line[j-1][5]==-1){
			return -1;
		}
		else{
			signal_line[line][5]=signal_line[j-1][5];
		}
	}
	return 0;
}

int seri_logic_calc(int line,int signal_line[][7],int pointer[]){//1bitの論理演算用	
	int logic_out;

	switch(signal_line[line][0]){
		case AND:
			logic_out=logic_calc_AND(line,signal_line,pointer);break;
		case OR:
			logic_out=logic_calc_OR(line,signal_line,pointer);break;
		case NAND:
			logic_out=logic_calc_NAND(line,signal_line,pointer);break;
		case NOR:
			logic_out=logic_calc_NOR(line,signal_line,pointer);break;
		case XOR:
			logic_out=logic_calc_XOR(line,signal_line,pointer);break;
		case NOT:
			logic_out=logic_calc_NOT(line,signal_line);break;
		case BRANCH:
			logic_out=logic_calc_BRANCH(line,signal_line);break;
		case PO:
			logic_out=logic_calc_PO(line,signal_line);break;
	}
	return logic_out;
}

void para_logic_calc(int line, unsigned long long int signal_bit[],int signal_line[][7],int pointer[]){//64bitの論理演算用
	unsigned long long int result;
	int i,j;
	switch(signal_line[line][0]){
		case AND:
			j=signal_line[line][2];
			if(signal_line[line][1]==1){
				signal_bit[line]=signal_bit[j-1];
			}
			else{
				result=signal_bit[pointer[j-1]-1];
				for(i=1; i<signal_line[line][1]; i++){
					result&=signal_bit[pointer[j+i-1]-1];
				}
				signal_bit[line]=result;
			}
			break;
		case OR:
			j=signal_line[line][2];
			if(signal_line[line][1]==1){
				signal_bit[line]=signal_bit[j-1];
			}
			else{
				result=signal_bit[pointer[j-1]-1];
				for(i=1; i<signal_line[line][1]; i++){
					result|=signal_bit[pointer[j+i-1]-1];
				}
				signal_bit[line]=result;
			}
			break;
		case NAND:
			j=signal_line[line][2];
			if(signal_line[line][1]==1){
				signal_bit[line]=signal_bit[j-1];
			}
			else{
				result=signal_bit[pointer[j-1]-1];
				for(i=1; i<signal_line[line][1]; i++){
					result&=signal_bit[pointer[j+i-1]-1];
				}
				signal_bit[line]=~(result);
			}
			break;
		case NOR:
			j=signal_line[line][2];
			if(signal_line[line][1]==1){
				signal_bit[line]=signal_bit[j-1];
			}
			else{
				result=signal_bit[pointer[j-1]-1];
				for(i=1; i<signal_line[line][1]; i++){
					result|=signal_bit[pointer[j+i-1]-1];
				}
				signal_bit[line]=~(result);
			}
			break;
		case XOR:
			j=signal_line[line][2];
			if(signal_line[line][1]==1){
				signal_bit[line]=signal_bit[j-1];
			}
			else{
				result=signal_bit[pointer[j-1]-1];
				for(i=1; i<signal_line[line][1]; i++){
					result^=signal_bit[pointer[j+i-1]-1];
				}
				signal_bit[line]=result;
			}
			break;
		case NOT:
			j=signal_line[line][2];
			signal_bit[line]=~(signal_bit[j-1]);
			break;
		case BRANCH:
			j=signal_line[line][2];
			signal_bit[line]=signal_bit[j-1];
			break;
	}
}

unsigned long long int pow2(int times){
	unsigned long long int result=1;
	for(int i=0; i<times; i++){
		result*=2;
	}
	return result;
}

void main(int argc, char *argv[]){
	char tbl_fname[60],pat_fname[60],fault_fname[60];
	FILE *fp;
	int i,j,k,l;
	int signal_lines,pat_lists,fault_lists,pointer_lists,PI_lists,PO_lists;
	QUEUE_T queue;//計算待ちキュー

	initQueue(&queue);

	//テーブルファイル読み取り
	strcpy(tbl_fname,argv[1]);
	strcat(tbl_fname,".tbl");
	if((fp=fopen(tbl_fname,"r"))==NULL){
		printf("Can't open %s.\n",argv[1]);
		exit(1);
	}
	fscanf(fp,"%d",&signal_lines);

	int signal_line[signal_lines][7];
	//0:type,1:in_num,2:in_signal,3:out_num,4:out_signal,5:output


	for(i=0; i<signal_lines; i++){
		for(j=0; j<5; j++){
			fscanf(fp,"%d",&signal_line[i][j]);
		}
	}
	
	//ポインタリスト読み取り
	fscanf(fp,"%d",&pointer_lists);
	int pointer[pointer_lists];
	for(i=0; i<pointer_lists; i++){
		fscanf(fp,"%d",&pointer[i]);
	}

	//外部入力リスト読み取り
	fscanf(fp,"%d",&PI_lists);
	int PI_signal[PI_lists];
	for(i=0; i<PI_lists; i++){
		fscanf(fp,"%d",&PI_signal[i]);
	}

	//外部出力リスト読み取り
	fscanf(fp,"%d",&PO_lists);
	int PO_signal[PO_lists];
	for(i=0; i<PO_lists; i++){
		fscanf(fp,"%d",&PO_signal[i]);
	}

	fclose(fp);

	//パターンファイル読み取り
	strcpy(pat_fname,argv[1]);
	strcat(pat_fname,".txt");
    	fp=fopen(pat_fname, "r");
	fscanf(fp,"%d",&pat_lists);

	int pat_list[pat_lists][PI_lists];

	for(i=0; i<pat_lists; i++){
		for(j=0; j<PI_lists; j++){
			fscanf(fp,"%d",&pat_list[i][j]);
		}
	}
	fclose(fp);

	//故障リストファイル読み取り
	strcpy(fault_fname,argv[1]);
	strcat(fault_fname,"f.rep");
	fp=fopen(fault_fname,"r");
	fscanf(fp,"%d",&fault_lists);
	int faultData[fault_lists][3];

	for(i=0; i<fault_lists; i++){
		fscanf(fp,"%d",&faultData[i][0]);
		fscanf(fp,"%d",&faultData[i][1]);
		faultData[i][2]=-1;
	}

	fclose(fp);
	
	//効率の良い演算順を調べる
	for(i=0; i<signal_lines; i++){//各信号線の値を-1で初期化	
		signal_line[i][5]=-1;
	}

	int sort[signal_lines]; //演算順を格納する配列	
	int sort_cnt=0;
	for(i=0; i<signal_lines; i++){
		if(signal_line[i][0]==0){
			signal_line[i][5]=0;//ALL0
			sort[sort_cnt]=i;
			sort_cnt++;
		}
		else{
			if(seri_logic_calc(i,signal_line,pointer)==-1){//論理演算が不可ならエンキュー
				enqueue(&queue,i);
			}
			else{//論理演算が可能なら演算順を記録
				sort[sort_cnt]=i;
				sort_cnt++;
			}
		}
	}


	while((i=dequeue(&queue))!=-1){
		if(seri_logic_calc(i,signal_line,pointer)==-1){
			enqueue(&queue,i);
		}
		else{
			sort[sort_cnt]=i;
			sort_cnt++;
		}
	}

	//故障シミュレーション
	unsigned long long int signal_bit[signal_lines];//unsigned int(32)>unsigned long long int(64)
	unsigned long long int mask_bit; //故障追加のためのマスク
	int PI_signal_cnt;
	int test_cnt,rep_cnt;
	int rep_sum=0; //検出した故障の合計数
	int return_num; //int型論理演算関数の返り値の行き先(バグ回避用)
	int fault_remain=fault_lists; //故障リストの残り数
	int tmp; //故障リストのエントリ入れ替え用
	int par; //故障並列の数

	for(test_cnt=0; test_cnt<pat_lists; test_cnt++){
		//正常出力演算
		for(i=0; i<signal_lines; i++){//各信号線の値を-1で初期化
			signal_line[i][5]=-1;
		}
		PI_signal_cnt=0;
		for(i=0; i<sort_cnt; i++){
			j=sort[i];
			if(signal_line[j][0]==0){
				signal_line[j][5]=pat_list[test_cnt][PI_signal_cnt];
				PI_signal_cnt++;
			}
			else if(signal_line[j][0]==4){
				signal_line[j][5]=signal_line[signal_line[j][2]-1][5];
			}
			else{
				return_num=seri_logic_calc(j,signal_line,pointer);
			}
		}
		
		rep_cnt=0;
		//故障リストの故障数が64個未満なら並列数を調整
		if(rep_cnt+64>fault_remain){
			par=fault_remain;
		}
		else{
			par=64;
		}

		while(rep_cnt<fault_remain){
			
			//故障追加、故障が追加された信号線にはフラグを立てておく
			for(i=0; i<signal_lines; i++){
				signal_line[i][6]=-1;
				signal_bit[i]=0b0;
			}
			for(i=0; i<PI_lists; i++){
				if(signal_line[PI_signal[i]-1][5]==0||signal_line[PI_signal[i]-1][5]==1){
					if(signal_line[PI_signal[i]-1][5]==1){//外部入力が1(ALL1のビット列)
						signal_bit[PI_signal[i]-1]=~signal_bit[PI_signal[i]-1];
					}
				}
				else{
					printf("input error\n");
					exit(1);
				}
			}
			for(k=0; k<par; k++){
				signal_line[faultData[rep_cnt+k][0]-1][6]=1;
			}
			
			for(i=0; i<signal_lines; i++){
				j=sort[i];

				if(signal_line[j][0]==0){
					if(signal_line[j][6]!=-1){
						for(k=0; k<par; k++){
							if(faultData[rep_cnt+k][0]-1==j){
								if(faultData[rep_cnt+k][1]==0){//0縮退故障
									mask_bit=pow2(k);
									mask_bit=~mask_bit;
									signal_bit[j]&=mask_bit;
								}
								else if(faultData[rep_cnt+k][1]==1){//1縮退故障
									mask_bit=pow2(k);
									signal_bit[j]|=mask_bit;
								}
							}
						}
					}
				}
				
				else if(signal_line[j][0]==4){
					//正常出力と比較
					if(signal_line[j][5]==1){
						mask_bit=0b0;
						mask_bit=~(mask_bit);
						signal_bit[j]=signal_bit[signal_line[j][2]-1]^mask_bit;
					}
					else if(signal_line[j][5]==0){
						mask_bit=0b0;
						signal_bit[j]=signal_bit[signal_line[j][2]-1]^mask_bit;
					}
					else{
						printf("output error\n");
					}
					for(k=0; k<par; k++){//右にシフトしながら故障を検出
						if((signal_bit[j]>>k)&1==1){
							if(faultData[rep_cnt+k][2]==-1){
								rep_sum++;
								faultData[rep_cnt+k][2]=1;
							}
						}
					}
				}
				else{
					para_logic_calc(j,signal_bit,signal_line,pointer);
					if(signal_line[j][6]!=-1){
						for(k=0; k<par; k++){
							if(faultData[rep_cnt+k][0]-1==j){
								if(faultData[rep_cnt+k][1]==0){//0縮退故障
									mask_bit=pow2(k);
									mask_bit=~mask_bit;
									signal_bit[j]&=mask_bit;
								}
								else if(faultData[rep_cnt+k][1]==1){//1縮退故障
									mask_bit=pow2(k);
									signal_bit[j]|=mask_bit;
								}
							}
						}
					}
				}
			}
			//次の故障セット(64個)、次の故障セットが64個未満なら調整			
			rep_cnt+=64;
			if(rep_cnt+64>fault_remain){
				par=fault_remain-rep_cnt;
			}
		}
	
		//検出済の故障をリストのエントリから削除
		for(i=0; i<fault_remain; i++){
			if(faultData[i][2]==1){
				if(i!=fault_remain-1){
					for(l=0; l<3; l++){
						tmp=faultData[i][l];
						faultData[i][l]=faultData[fault_remain-1][l];
						faultData[fault_remain-1][l]=tmp;
					}
					i--;
				}
				fault_remain--;
			}
		}
	}

	//出力内容:全体の故障数、検出故障数、検出故障率、処理時間	
	printf("fault sum:%d　find fault sum:%d　find fault rate:%.2f%\n",fault_lists,rep_sum,(double)rep_sum*100/fault_lists);
	printf("process time:%.2fs\n",(double)clock()/CLOCKS_PER_SEC);
	
}

