#include<iostream>
#include<time.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
using namespace std;

void creat_square(char **square,int n){
	int i,j;
	for(i=0;i<2*n+1;i++){
		for(j=0;j<6*n+1;j++){
			if(i%2==0){
				if(j%6==0)
				*((char*)square+(6*n+1)*i+j)='+';
				else
				*((char*)square+(6*n+1)*i+j)='-';
			}
			else if(j%6==0)
			*((char*)square+(6*n+1)*i+j)='|';
			else
			*((char*)square+(6*n+1)*i+j)=' ';
		}
	}
}
void add_number(char **square,int *one_number,int i,int j,int k,int n){
	int a;
	for(a=0;a<k;a++){
		if(k<=2)
		*((char*)square+(6*n+1)*(2*i+1)+6*j+3+a)=*(one_number+k-1-a)+'0';
		else if(k=3)
		*((char*)square+(6*n+1)*(2*i+1)+6*j+2+a)=*(one_number+k-1-a)+'0';
		else
	    *((char*)square+(6*n+1)*(2*i+1)+6*j+1+a)=*(one_number+k-1-a)+'0';
	}	
}
void adapt_array(char** square,int** number,int n){
	int a,i,j,k=0;
	int one_number[4];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a=*((int*)number+n*i+j);
			while(a){
				*(one_number+k)=a%10;
				a=a/10;
				k+=1;
			}
			add_number(square,one_number,i,j,k,n);
			k=0;
		}
	}
}
void printf_square(char **square,int **number,int n){
	int i,j;
	creat_square(square,n);
	adapt_array(square,number,n); 
	for(i=0;i<2*n+1;i++){
		for(j=0;j<6*n+1;j++){
			printf("%c",*((char*)square+(6*n+1)*i+j));
		}
		printf("\n");
   }
} 
void creat_number(int **number,int n){
	int a,b;
	int i,j;
	do{
		a=rand()%n;
		b=rand()%n;
      }
	while(*((int*)number+n*a+b)!=0);
	*((int*)number+n*a+b)=2;		
}
void move_up(int** number,int* score,int n,int& judge){
	int i,j,k,l=0;int m;
	int chang_number=0;
	for(j=0;j<n;j++){
		for(k=0;k<n;k++){
			l=0;
			for(i=1;i<n;i++){
			if(*((int*)number+n*(i-1)+j)==0){
				for(m=0;m+i<n;m++){
				    *((int*)number+n*(i+m-1)+j)=*((int*)number+n*(i+m)+j);
				}
				*((int*)number+n*(n-1)+j)=0;
				i--;l++;chang_number++;
			}
			if((k==0)&&(chang_number==n-1)&&(*((int*)number+j))==0) chang_number=0;
			if(l==n-1) break;
     	    }
     	    if((*((int*)number+n*k+j)==*((int*)number+n*(k+1)+j))&&*((int*)number+n*k+j)){
				*((int*)number+n*k+j)=*((int*)number+n*k+j)*2;
				*score=*score+*((int*)number+n*k+j);
			    *((int*)number+n*(k+1)+j)=0;
			    chang_number++;
			}
			if(*((int*)number+n*k+j)==0)  break;
	    }
	}
	if(chang_number==0) judge=0;
	else judge=1; 
}
void move_down(int** number,int* score,int n,int& judge){
	int i,j,k,l=0;int m;
	int chang_number=0;
	for(j=0;j<n;j++){
		for(k=n-1;k>0;k--){
			l=0;
			for(i=n-1;i>0;i--){
			if(*((int*)number+n*i+j)==0){
				for(m=0;i-m>0;m++){
				    *((int*)number+n*(i-m)+j)=*((int*)number+n*(i-m-1)+j);
				}
				*((int*)number+j)=0;
				i++;l++;chang_number++;
			}
			if((k==n-1)&&(chang_number==n-1)&&(*((int*)number+n*(n-1)+j))==0) chang_number=0;
			if(l==n-1) break;
     	    }
     	    if((*((int*)number+n*k+j)==*((int*)number+n*(k-1)+j))&&*((int*)number+n*k+j)){
				*((int*)number+n*k+j)=*((int*)number+n*k+j)*2;
				*score=*score+*((int*)number+n*k+j);
			    *((int*)number+n*(k-1)+j)=0;
			    chang_number++;
			}
			if(*((int*)number+n*k+j)==0)  break;
	    }
	}
	if(chang_number==0) judge=0;
	else judge=1; 
}
void move_left(int** number,int *score,int n,int& judge){
	int i,j,k,l=0;int m;
	int chang_number=0;
	for(i=0;i<n;i++){
		for(k=0;k<n-1;k++){
			l=0;
			for(j=1;j<n;j++){
			if(*((int*)number+n*i+j-1)==0){
				for(m=0;m+j<n;m++){
				    *((int*)number+n*i+j+m-1)=*((int*)number+n*i+j+m);
				}
				*((int*)number+n*i+n-1)=0;
				j--;l++;chang_number++;
			}
			if((k==0)&&(chang_number==n-1)&&(*((int*)number+n*i))==0) chang_number=0;
			if(l==n-1) break;
     	    }
     	    if((*((int*)number+n*i+k)==*((int*)number+n*i+k+1))&&*((int*)number+n*i+k)){
				*((int*)number+n*i+k)=*((int*)number+n*i+k)*2;
				*score=*score+*((int*)number+n*i+k);
			    *((int*)number+n*i+k+1)=0;
			    chang_number++;
			}
			if(*((int*)number+n*i+k)==0)  break;
	    }
	}
	if(chang_number==0) judge=0;
	else judge=1; 
}
void move_right(int** number,int* score,int n,int& judge){
	int i,j,k,l=0;int m;
	int chang_number=0;
	for(i=0;i<n;i++){
		for(k=n-1;k>0;k--){
			l=0;
			for(j=n-1;j>0;j--){
			if(*((int*)number+n*i+j)==0){
				for(m=0;j-m>0;m++){
				    *((int*)number+n*i+j-m)=*((int*)number+n*i+j-m-1);
				}
				*((int*)number+n*i)=0;
				j++;l++;chang_number++;
			}
			if((k==n-1)&&(chang_number==n-1)&&(*((int*)number+n*i+n-1))==0) chang_number=0;
			if(l==n-1) break;
     	    }
     	    if((*((int*)number+n*i+k)==*((int*)number+n*i+k-1))&&*((int*)number+n*i+k)){
				*((int*)number+n*i+k)=*((int*)number+n*i+k)*2;
				*score=*score+*((int*)number+n*i+k);
			    *((int*)number+n*i+k-1)=0;
			    chang_number++;
			}
			if(*((int*)number+n*i+k)==0)  break;
	    }
	}
	if(chang_number==0) judge=0;
	else judge=1; 
}
void move_number(int** number,char *b,int *score,int n,int& judge){
	int i,j;
	char a;
	scanf("%c",&a);
	switch(a)
	{
		case 'w' :move_up(number,score,n,judge);if(judge==1) creat_number(number,n);break;
		case 'z' :move_down(number,score,n,judge);if(judge==1) creat_number(number,n);break;
		case 'a' :move_left(number,score,n,judge);if(judge==1) creat_number(number,n);break;
		case 's' :move_right(number,score,n,judge);if(judge==1) creat_number(number,n);break;
		case 't' :*b='t';break;
	}
}
void game_over(int** number,char check,int*check_1,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(check=='t'){
				if(*((int*)number+n*i+j)>=64){
					*check_1=0;
				}
			}
			else if(*((int*)number+n*i+j)==2048){
				*check_1=0;
			}
		}
	}
}
void choose(int& n){
	cout<<"请选择游戏的维数：（2，3，4，5）"<<endl;
	cin>>n;
	while((n!=3)&&(n!=4)&&(n!=5)&&(n!=2)){
		cout<<"输入不符合规则，请重新输入："<<endl;
		cin>>n;
		fflush(stdin);
	}
}
void copy_1(int** number,int** copy,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			*((int*)copy+n*i+j)=*((int*)number+n*i+j);
		}
	}
}
void prob(int** number,int *score,int n,char& open,int& prob_number,int** copy,int*check_1){
	int i,j,judge_1,judge_2,judge_3,judge_4;
	char a[4]={'0','0','0','0'};int all=0;
	copy_1(number,copy,n);
	move_up(copy,score,n,judge_1);
	if(judge_1!=0) {
	    a[0]='w';all++;
	}
	copy_1(number,copy,n);
	move_down(copy,score,n,judge_2);
	if(judge_2!=0) {
	    a[1]='z';all++;
    }
    copy_1(number,copy,n);
	move_left(copy,score,n,judge_3);
	if(judge_3!=0) {
	    a[2]='a';all++;
    }
    copy_1(number,copy,n);
	move_right(copy,score,n,judge_4);
	if(judge_4!=0){
	   a[3]='s';all++;
    }
    if(all==1){
    	for(i=0;i<4;i++){
    		if ((a[i]>='a')&&(a[i]<='z')) {
			open=a[i];prob_number=0;
		    }
		}
	}
	if(all==0) *check_1=0;
} 
int main(){
	srand(time(NULL));
	int a,b,i,j,check_1=1;
	char check;
	int n=0;
	choose(n);
	char **square;
	square=(char**)malloc(sizeof(char)*(2*n+1));
	for(i=0;i<2*n+1;i++)
	square[2*i+1]=(char*)malloc(sizeof(char)*(6*n+1)); 
	int **number;
	number=(int**)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	number[i]=(int*)malloc(sizeof(int)*n); 
	int** copy;
	copy=(int**)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	copy[i]=(int*)malloc(sizeof(int)*n); 
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	     *((int*)number+n*i+j)=0 ;
      }
    }
	char key;
	cout<<"请进行模式选择："<<endl;
	cout<<"1:单人模式"<<endl;
	cout<<"2:双人模式"<<endl;
	cout<<"请键入对应模式的序号："<<endl;
	int choice;
	cin>>choice;
	if(choice==1){
		int score=0;
		creat_number(number,n);
	    creat_number(number,n);
	    printf_square(square,number,n);
	    while(check_1!=0){
	    fflush(stdin);
	    int judge=0;
	    char open;int prob_number=1;
	    prob(number,&score,n,open,prob_number,copy,&check_1);
		if(check_1==0) break;
	    move_number(number,&check,&score,n,judge); 
	    while(judge==0){
	    	fflush(stdin);
	    	cout<<"输入无效，请重新输入指令:"<<endl; 
	    	move_number(number,&check,&score,n,judge); 
		}
	    printf_square(square,number,n);
	    fflush(stdin);
	    cout<<"用户当前得分为："<<score<<endl;
	    game_over(number,check,&check_1,n);
	    
	    }
	    cout<<"游戏结束！"<<endl;
	}
	else if(choice==2){
		int score=0;
		int judge;
		char people_1[100],people_2[100];
		cout<<"请输入用户1的名称："<<endl;
		cin>>people_1;
		cout<<"请输入用户2的名称："<<endl;
		cin>>people_2;
		int turn=1;
		creat_number(number,n);
	    creat_number(number,n);
	    printf_square(square,number,n);
	    fflush(stdin);
	    char open;int prob_number=1;
	    int score_1=0,score_2=0;
		string order;
	    while(check_1!=0){
	    if(turn%2==1){
	    	cout<<"下轮的操作者为："<<people_1<<endl; 
	    	if(prob_number!=0){
	    		prob(number,&score,n,open,prob_number,copy,&check_1);
	    		if(prob_number==0){
	    		   cout<<"请用户"<<people_2<<"输入指令；"<<endl;
				   cin>>order; 
				   cout<<order<<"同意请按"<<open<<endl;
			    }
			}
			prob(number,&score,n,open,prob_number,copy,&check_1);
			if(check_1==0) break;
	    	move_number(number,&check,&score_1,n,judge); 
	    	while(judge==0){
	    	  fflush(stdin);
	    	  cout<<"输入无效，请重新输入指令:"<<endl; 
	    	  move_number(number,&check,&score,n,judge); 
		    }
	        printf_square(square,number,n); 
	        cout<<people_1<<"用户当前得分为"<<score_1<<endl; 
	        fflush(stdin);
		}
	    else if(turn%2==0){
	    	cout<<"下轮的操作者为："<<people_2<<endl;
			if(prob_number!=0){
	    		prob(number,&score,n,open,prob_number,copy,&check_1);
	    		if(prob_number==0){
	    		   cout<<"请用户"<<people_1<<"输入指令；"<<endl;
				   cin>>order; 
				   fflush(stdin); 
				   cout<<order<<"同意请按"<<open<<endl;
			    }
			}
			prob(number,&score,n,open,prob_number,copy,&check_1);
			if(check_1==0) break;
	    	move_number(number,&check,&score_2,n,judge);
			while(judge==0){
	    	  fflush(stdin);
	    	  cout<<"输入无效，请重新输入指令:"<<endl; 
	    	  move_number(number,&check,&score,n,judge); 
		    } 
	        printf_square(square,number,n);
	        cout<<people_2<<"用户当前得分为"<<score_2<<endl; 
	        fflush(stdin);
		}
		turn+=1;
	    }
	    cout<<"游戏结束！"<<endl; 
	    if(score_1-score_2>0){
	    	cout<<people_1<<"用户获得胜利！"<<endl;
		}
		else if(score_1-score_2==0){
			cout<<"双方平局"<<endl; 
		}
		else
		cout<<people_2<<"用户获得胜利"<<endl;
	}
	return 0;
}

