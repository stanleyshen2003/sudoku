#include <iostream>
#include <fstream>
using namespace std;

int top=-1;
struct step{
	int x;
	int y;
	int num;
};
step stack[80];
void push(step x){
	stack[++top]=x;
}
step pop(){
	return stack[top--];
}


void readFile(int q[9][9][10]){
	ifstream f1;
	int x,y;
	f1.open("Q1.txt");
	for(x=0;x<9;x++){
		for(y=0;y<9;y++){
			f1>>q[x][y][0];
		}
	}
	f1.close();
}

void init(int x[9][9][10]){
	for(int i=0;i<9;i++){
		for(int q=0;q<9;q++){
			for(int f=1;f<10;f++){
				x[i][q][f]=0;
			}
		}
	}
}

bool canGo(int x,int y,int num, int array[9][9][10]){
	for(int i=0;i<9;i++){
		if(array[x][i][0]==num || array[i][y][0]==num){
			return false;
		}
	}
	int dimX,dimY;
	dimX = x/3;
	dimY = y/3;
	for(int i=dimX*3;i<dimX+3;i++){
		for(int q = dimY*3;q<dimY+3;q++){
			if(array[i][q][0]==num)
				return false;
		}
	}
	return true;
}

void printans(int num[9][9][10]){
	for(int i=0;i<9;i++){
		for(int q=0;q<9;q++){
			cout<<num[i][q][0];
			
			cout<<" | ";
		}
		cout<<endl;
	}
}
int path(int num[9][9][10]){
	int trynum,i,j,number;
	step first;
	int firstx=0,firsty=0;
	while(num[firstx][firsty][0]!=0){
		firsty = firsty+1;
		if(firsty == 9){
			firsty = 0;
			firstx+=1;
		}
		if(firstx==9)return 0;
	}
	first.x = firstx;first.y = firsty;first.num = 0;
	push(first);
	while(top!=-1){
		step now = pop();
		i = now.x; j = now.y; number = now.num+1;
		num[i][j][0]=0;
		while(number<=9){
			if(canGo(i,j,number,num)){
				now.x = i; now.y = j;now.num = number;
				push(now);
				//cout<<i<<" "<<j<<endl;
				if(i==8 && j==8){
					cout<<"succeed!"<<endl;
					printans(num);
					return 0;
				}
				num[i][j][0]=number;
				while(num[i][j][0]!=0){
					j++;
					if(j==9){
						j=0;
						i+=1;
					}
					if(i==9){
						cout<<"succeed!"<<endl;
						printans(num);
						return 0;
					}
				}
				number=0;
			}
			number+=1;
		}	
	}
	return -1;
} 
int main(){
	int numandpos[9][9][10];
	int a;
	init(numandpos);
	readFile(numandpos);
	a=path(numandpos);
	if(a==-1) cout<<"no answer!";
	return 0;
}

