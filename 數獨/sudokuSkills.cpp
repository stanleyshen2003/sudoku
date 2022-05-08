#include <iostream>
#include <fstream>
using namespace std;
int times=1;
int setsq(int x,int y){
	int sq;
	if(x<=3){
		if(y<=3){
			sq=1;
		}
		else if(y>=7){
			sq=3;
		}
		else{
			sq=2;
		}
	}
	else if(x>=7){
		if(y<=3){
			sq=7;
		}
		else if(y>=7){
			sq=9;
		}
		else{
			sq=8;
		}
	}
	else{
		if(y<=3){
			sq=4;
		}
		else if(y>=7){
			sq=6;
		}
		else{
			sq=5;
		}
	}
	return sq;
}
void readFile(char file[], int q[10][10][10]){
	ifstream f1;
	int x,y;
	f1.open(file);
	for(x=1;x<10;x++){
		for(y=1;y<10;y++){
			f1>>q[x][y][0];
		}
	}
	f1.close();
}
void printans(int num[10][10][10]){
	for(int i=1;i<10;i++){
		for(int q=1;q<10;q++){
			if(num[i][q][0]==0){
				cout<<" ";
			}
			else{
				cout<<num[i][q][0];
			}
			cout<<" | ";
		}
		cout<<endl;
	}
}

void refresh(int x[10][10][10]){
	int amount=0;
	int now=0;
	for(int r=1;r<10;r++){
		for(int c=1;c<10;c++){
			if(x[r][c][0]==0){
				amount=0;
				now=0;
				for(int f=1;f<10;f++){
					if(x[r][c][f]==0){
						amount+=1;
						now=f;
					}
				}
				if(amount==1){
					x[r][c][0]=now;
				}
			}	
		}
	}
}



void bye(int x[10][10][10],int i,int q){
	int sq,r,c,n;
	n=x[i][q][0];
	for(int b=1;b<10;b++){
		x[b][q][n]=1;
	}
	for(int b=1;b<10;b++){
		x[i][b][n]=1;
	}
	sq=setsq(i,q);
	r=(sq-1)/3*3+1;
	q=(sq-1)%3*3+1;
	for(int b=r;b<r+3;b++){
		for(int f=q;f<q+3;f++){
			x[b][f][n]=1;
		}
	}
}
void init(int x[10][10][10]){
	for(int i=0;i<10;i++){
		for(int q=0;q<10;q++){
			for(int f=1;f<10;f++){
				x[i][q][f]=0;
			}
		}
	}
}
void fill(int x[10][10][10],int i,int q){
	int sq,r,c,amount=0;
	int able=1;
	sq=setsq(i,q);
	r=(sq-1)/3*3+1;
	c=(sq-1)%3*3+1;
	for(int tr=1;tr<10;tr++){
		if(x[i][q][tr]==0){
			amount=0;
			able=1;
			for(int b=r;b<r+3;b++){
				for(int f=c;f<c+3;f++){
					if(x[b][f][0]==0 && x[b][f][tr]==0){
						amount++;
					}
					if(x[b][f][0]==tr){
						able=0;
					}
				}
			}
			if(amount==1 && able==1){
				x[i][q][0]=tr;
				break;
			}
		}	
	} 	
}

int main(){
	int numandpos[10][10][10];
	int finish=0;
	readFile("Q1.txt",numandpos);
	init(numandpos);
	while(finish==0){
		refresh(numandpos);
		for(int i=1;i<10;i++){
			for(int q=1;q<10;q++){
				if(numandpos[i][q][0]!=0){
					bye(numandpos,i,q);
				}
			}
		}
		for(int i=1;i<10;i++){
			for(int q=1;q<10;q++){
				if(numandpos[i][q][0]==0){
					fill(numandpos,i,q);
				}
			}
		}
		finish=1;
		for(int i=1;i<10;i++){
			for(int q=1;q<10;q++){
				if(numandpos[i][q][0]==0){
					finish=0;
				}
			}
		}
		times+=1;
	}	
	printans(numandpos);
	return 0;
}

