#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

enum direction {UP=0, DOWN, LEFT, RIGHT};
string dirCharacter[4] = {"w", "z", "a", "s"};

class gameGrid{
    private:
        int value;//���ӵ�ֵ
    public:
        gameGrid();//��ʼ�� ��0ֵ
        void setValue(int value);//����value
        int getValue();//ȡ��value
        int calculateGrid(gameGrid& target, int calcMode = 1);//��target���㵽���øú����Ķ���
        void printGrid();//��ӡ����
};

struct gameUser{
    int score = 0;//�洢�÷�
    char username[100];//�洢�û���
    bool isCheated = false;//�洢�Ƿ��Ѿ�����cheatָ��
    bool isPerformed = false;
    char cheat[100];//�洢�û����׵�����
};

class game2048{
    private:
        int size;//�洢��ͼ�ߴ�
        gameGrid** gameMap;//�洢2048�ַ�
        bool moveTemp;//�����洢Ԥ������Ƿ�������ƶ�
        int goal;//�洢��Ϸ����Ŀ��
        int mode = 1;//�洢��Ϸģʽ��1Ϊ����2Ϊ˫�ˣ�Ĭ�ϵ���
        unsigned char order = 0;//�洢˫��ģʽ��˳��
        gameUser user[2];//�洢�û���Ϣ
        bool cheatTool = false;
    public:
    	bool isStop;//�洢�Ƿ����
        char dir = 0;
        game2048();//��ʼ��
        void setSize(int initSize);//��ʼ���ߴ�
        void gameStart();//��ʼ��Ϸ
        void setGoal(int goal);//����Ŀ��
        void generateTwo();//����2
        void printMap();//��ӡ��ͼ
        bool isStopped();//�ж��Ƿ����
        void mapMove(direction dir, int moveMode = 1);//�ƶ�ĳһ��/��
        void mapCalculate(direction dir, int calcMode = 1);//�����ƶ�����
        void gamePlay();//������Ϸ
        string dirJudge();//�ж���Щ�����ܹ��ƶ�
        void gameOver();//��Ϸ��������
};

int main(int argc, char* argv[]){
    game2048 gm;
    if(argc>2 && !strcmp(argv[1], "-s")) {
        int initSize = (int)argv[2][0]-'0';
        if(initSize>=2&&initSize<=5) gm.setSize(initSize);
        else {
            do{
                cout<<"����ߴ�����Ƿ������������룺";
                cin>>initSize;
            }while(initSize<2||initSize>5);
            gm.setSize(initSize);
        }
    }
    else {
        gm.setSize(4);
    }
    if(!strcmp(argv[3],"-t")){
        gm.setGoal(64);
    }

    gm.gameStart();
    gm.gamePlay();
    gm.gameOver();

    return 0;
}

gameGrid::gameGrid(){
    value = 0;
}

void gameGrid::setValue(int value){
    this->value = value;
}

int gameGrid::getValue(){
    return value;
}

void gameGrid::printGrid(){
    if(value)
        printf("|%-4d ", value);
    else
        printf("|     ");
}

int gameGrid::calculateGrid(gameGrid& target, int calcMode){
    if(target.getValue() && this->getValue()==target.getValue()){
        if(calcMode){
            this->setValue(2*this->getValue());
            target.setValue(0);
        }
        return this->getValue();
    }//���������ֵ����Ҳ�Ϊ0����������

    return 0;
}

game2048::game2048(){
    size = 4;
    isStop = false;
    goal = 2048;
}

void game2048::setSize(int initSize = 4){
    size = initSize;
    gameMap = new gameGrid*[4];
    for(int i=0;i<4;++i){
        gameMap[i] = new gameGrid[4];
    }
}

void game2048::gameStart(){
    cout<<"-----��Ϸ��ʼ-----"<<endl;
    cout<<"�����ģʽѡ��"<<endl;
    cout<<"1������ģʽ"<<endl;
    cout<<"2��˫��ģʽ"<<endl;
    cout<<"���������Ӧģʽ����ţ�";
    cin>>mode;
    if(mode%2){
    	cout<<"������P1�������";
        cin>>user[0].username;
        generateTwo();
        printMap();
        cout<<'['<<user[0].username<<']'<<"��ǰ�÷֣�"<<user[0].score+user[1].score<<endl;
        cout<<"������ָ�";
        cin>>dir;
    }//����ģʽ
    else{
        cout<<"������P1�������";
        cin>>user[0].username;
        cout<<"������P2�������";
        cin>>user[1].username;
        generateTwo();
        printMap();
        cout<<"������"<<'['<<user[order%2].username<<']'<<"���в�����"<<endl;
        cout<<"������ָ�";
        cin>>dir; 
    }//˫��ģʽ
}

void game2048::setGoal(int goal){
    this->goal = goal;
}

void game2048::generateTwo(){
    srand(time(NULL));
    int generator = rand()%(size*size);
    while(gameMap[generator/size][generator%size].getValue()){
        generator = rand()%(size*size);
    }
    gameMap[generator/size][generator%size].setValue(2);
}

void game2048::mapMove(direction dir, int moveMode){
    //����ָ�룬pt1�洢��������λ�ã�pt2�洢��ӽ���ͷ��0λ��
    int pt1, pt2;
    switch(dir){
        case UP:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = 0;
                while(pt1<size&&gameMap[pt1][i].getValue()!=0){ pt1++; pt2++; }//Ѱ����ʼλ��
                while(pt1<size){
                    if(gameMap[pt1][i].getValue()==0){ pt1++; }
                    else{
                        if(moveMode){
                            gameMap[pt2++][i].setValue(gameMap[pt1][i].getValue());
                            gameMap[pt1++][i].setValue(0);
                        }
                        else { pt1++; this->moveTemp = true; }
                    }
                }//�����е����ֻ����涨��ͬһ��
            }
            break;
        }
        case DOWN:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = size-1;
                while(pt1>=0&&gameMap[pt1][i].getValue()!=0){ pt1--; pt2--; }//Ѱ����ʼλ��
                while(pt1>=0){
                    if(gameMap[pt1][i].getValue()==0){ pt1--; }
                    else{
                        if(moveMode){
                            gameMap[pt2--][i].setValue(gameMap[pt1][i].getValue());
                            gameMap[pt1--][i].setValue(0);
                        }
                        else { pt1--; this->moveTemp = true; }
                    }
                }//�����е����ֻ����涨��ͬһ��
            }
            break;
        }
        case LEFT:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = 0;
                while(pt1<size&&gameMap[i][pt1].getValue()!=0){ pt1++; pt2++; }//Ѱ����ʼλ��
                while(pt1<size){
                    if(gameMap[i][pt1].getValue()==0){ pt1++; }
                    else{
                        if(moveMode){
                            gameMap[i][pt2++].setValue(gameMap[i][pt1].getValue());
                            gameMap[i][pt1++].setValue(0);
                        }
                        else { pt1++; this->moveTemp = true; }
                    }
                }//�����е����ֻ����涨��ͬһ��
            }
            break;
        }
        case RIGHT:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = size-1;
                while(pt1>=0&&gameMap[i][pt1].getValue()!=0){ pt1--; pt2--; }//Ѱ����ʼλ��
                while(pt1>=0){
                    if(gameMap[i][pt1].getValue()==0){ pt1--; }
                    else{
                        if(moveMode){
                            gameMap[i][pt2--].setValue(gameMap[i][pt1].getValue());
                            gameMap[i][pt1--].setValue(0);
                        }
                        else { pt1--; this->moveTemp = true; }
                    }
                }//�����е����ֻ����涨��ͬһ��
            }
            break;
        }
    }
}

void game2048::mapCalculate(direction dir,int calcMode){
    switch(dir){
        case UP:{
            this->mapMove(UP,calcMode);
            for(int i=0;i<size;++i){
                for(int j=0;j<size-1;++j){
                    if(gameMap[j][i].calculateGrid(gameMap[j+1][i],calcMode)){
                        if(calcMode){
                            user[order%2].score+=gameMap[j][i].getValue();
                        }
                        else { this->moveTemp = true; }
                    }
                }//�ٽ�������
            }
            this->mapMove(UP,calcMode);
            break;
        }
        case DOWN:{
            this->mapMove(DOWN,calcMode);
            for(int i=0;i<size;++i){
                for(int j=size-1;j>0;--j){
                    if(gameMap[j][i].calculateGrid(gameMap[j-1][i],calcMode)){
                        if(calcMode){
                            user[order%2].score+=gameMap[j][i].getValue();
                        }
                        else { this->moveTemp = true; }
                    }
                }//�ٽ�������
            }
            this->mapMove(DOWN,calcMode);
            break;
        }
        case LEFT:{
            this->mapMove(LEFT,calcMode);
            for(int i=0;i<size;++i){
                for(int j=0;j<size-1;++j){
                    if(gameMap[i][j].calculateGrid(gameMap[i][j+1],calcMode)){
                        if(calcMode){
                            user[order%2].score+=gameMap[i][j].getValue();
                        }
                        else { this->moveTemp = true; }
                    }
                }//�ٽ�������
            }
            this->mapMove(LEFT,calcMode);
            break;
        }
        case RIGHT:{
            this->mapMove(RIGHT,calcMode);
            for(int i=0;i<size;++i){
                for(int j=size-1;j>0;--j){
                    if(gameMap[i][j].calculateGrid(gameMap[i][j-1],calcMode)){
                        if(calcMode){
                            user[order%2].score+=gameMap[j][i].getValue();
                        } else { this->moveTemp = true; }
                    }
                }//�ٽ�������
            }
            this->mapMove(RIGHT,calcMode);
            break;
        }
    }
    if(calcMode){
        if(mode%2){
            if(!this->isStopped()){
                cout<<this->dirJudge()<<endl;
                printMap();
                cout<<'['<<user[0].username<<']'<<"��ǰ�÷֣�"<<user[0].score+user[1].score<<endl;
                cout<<"������ָ�";
                cin>>this->dir;
                order++;	
            }
        } else {
            if(!this->isStopped()){
                string dirTemp = this->dirJudge();
                printMap();
                cout<<'['<<user[order%2].username<<']'<<"��ǰ�÷֣�"<<user[order%2].score<<endl;
                cout<<"������"<<'['<<user[(order+1)%2].username<<']'<<"���в�����"<<endl;
                if(dirTemp.length()==1&&user[order%2].isCheated&&!user[order%2].isPerformed){
                    do{
                        fflush(stdin);
                        cout<<user[order%2].cheat<<' '<<"ͬ���밴'"<<dirTemp<<'\''<<':';
                        cin>>this->dir;
                    }while(this->dir!=dirTemp[0]);
                    user[order%2].isPerformed = true;
                    order++;
                } else {
                    cout<<"������ָ�";
                    cin>>this->dir;
                    order++;	
                }
            }
        }
    }
}

string game2048::dirJudge(){
    string res = "";
    for(int i=0;i<4;++i){
        this->mapCalculate(direction(i),0);
        if(this->moveTemp){
            res.append(dirCharacter[i]);
            this->moveTemp = false;
        }
    }
    return res;
}

void game2048::printMap(){
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j) cout<<"+-----";
        cout<<'+'<<endl;
        for(int j=0;j<size;++j) gameMap[i][j].printGrid();
        cout<<'|'<<endl;
    }
    for(int i=0;i<size;++i) cout<<"+-----";
        cout<<'+'<<endl;
}

bool game2048::isStopped(){
    int type = 0, cnt = 0;
    for(int i=0;i<size;++i){
    	for(int j=0;j<size;++j){
            if(gameMap[i][j].getValue()) cnt++;//ͳ�Ʒ����Ԫ����
	        if(gameMap[i][j].getValue()==this->goal) { type = 1; break; }
		}
	}//�����鿴 �Ƿ���Ŀ������
    if(type==1){
        this->isStop = true;
    }//��Ŀ������
    else{
        if(cnt<size*size){
            this->generateTwo();
        }//ûװ��
        this->isStop = this->dirJudge()=="" ? true : false;
    }//û��Ŀ�����־��ж��ܲ����ƶ�

    return isStop;
}

void game2048::gamePlay(){
    while(!isStop){
        if(dir=='c'&&mode==2&&!cheatTool){
            if(!user[order%2].isCheated){
                cin>>user[order%2].cheat;
                user[order%2].isCheated = true;
                cheatTool = true;
                fflush(stdin);
                cout<<"cheatָ��ɹ����������������ͼ������";
                cin>>dir;
            }
            else{
                fflush(stdin);
                cout<<"�Ѿ��洢��cheatָ��������ͼ������";
                cin>>dir;
            }
        }
        else fflush(stdin);
        while(dir!='w'&&dir!='z'&&dir!='a'&&dir!='s'){
            fflush(stdin);
            cout<<"�Ƿ����룡����������ָ�";
            cin>>dir;
        }
        while(this->dirJudge().find(dir)==-1){
            fflush(stdin);
            cout<<"��Ч���룡����������ָ�";
            cin>>dir;
        }
        if(dir=='w')  mapCalculate(UP);
        else if(dir=='z')  mapCalculate(DOWN);
        else if(dir=='a')  mapCalculate(LEFT);
        else if(dir=='s')  mapCalculate(RIGHT);
    }
}

void game2048::gameOver(){
    this->printMap();
    if(mode%2){
    	cout<<"��Ϸ������"<<endl;
    	cout<<'['<<user[0].username<<']'<<"���յ÷֣�"<<user[0].score+user[1].score<<endl;
	} else {
		cout<<"��Ϸ������"<<endl;
		cout<<'['<<user[0].username<<']'<<"���յ÷֣�"<<user[0].score<<endl;
		cout<<'['<<user[1].username<<']'<<"���յ÷֣�"<<user[1].score<<endl;
		if(user[0].score!=user[1].score){
			printf("[%s]ʤ����\n", user[0].score>user[1].score?user[0].username:user[1].username); 
		} else {
			cout<<"��Ϸƽ�֣�"<<endl; 
		}
	}
}