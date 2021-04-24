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
        int value;//格子的值
    public:
        gameGrid();//初始化 赋0值
        void setValue(int value);//设置value
        int getValue();//取到value
        int calculateGrid(gameGrid& target, int calcMode = 1);//把target计算到调用该函数的对象
        void printGrid();//打印格子
};

struct gameUser{
    int score = 0;//存储得分
    char username[100];//存储用户名
    bool isCheated = false;//存储是否已经动用cheat指令
    bool isPerformed = false;
    char cheat[100];//存储用户作弊的内容
};

class game2048{
    private:
        int size;//存储地图尺寸
        gameGrid** gameMap;//存储2048字符
        bool moveTemp;//用来存储预测操作是否造成了移动
        int goal;//存储游戏结束目标
        int mode = 1;//存储游戏模式，1为单人2为双人，默认单人
        unsigned char order = 0;//存储双人模式的顺序
        gameUser user[2];//存储用户信息
        bool cheatTool = false;
    public:
    	bool isStop;//存储是否结束
        char dir = 0;
        game2048();//初始化
        void setSize(int initSize);//初始化尺寸
        void gameStart();//开始游戏
        void setGoal(int goal);//设立目标
        void generateTwo();//生成2
        void printMap();//打印地图
        bool isStopped();//判断是否结束
        void mapMove(direction dir, int moveMode = 1);//移动某一行/列
        void mapCalculate(direction dir, int calcMode = 1);//进行移动计算
        void gamePlay();//进行游戏
        string dirJudge();//判断哪些方向能够移动
        void gameOver();//游戏结束界面
};

int main(int argc, char* argv[]){
    game2048 gm;
    if(argc>2 && !strcmp(argv[1], "-s")) {
        int initSize = (int)argv[2][0]-'0';
        if(initSize>=2&&initSize<=5) gm.setSize(initSize);
        else {
            do{
                cout<<"输入尺寸参数非法！请重新输入：";
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
    }//如果两者数值相等且不为0，进行运算

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
    cout<<"-----游戏开始-----"<<endl;
    cout<<"请进行模式选择："<<endl;
    cout<<"1：单人模式"<<endl;
    cout<<"2：双人模式"<<endl;
    cout<<"请键入所对应模式的序号：";
    cin>>mode;
    if(mode%2){
    	cout<<"请输入P1玩家名：";
        cin>>user[0].username;
        generateTwo();
        printMap();
        cout<<'['<<user[0].username<<']'<<"当前得分："<<user[0].score+user[1].score<<endl;
        cout<<"请输入指令：";
        cin>>dir;
    }//单人模式
    else{
        cout<<"请输入P1玩家名：";
        cin>>user[0].username;
        cout<<"请输入P2玩家名：";
        cin>>user[1].username;
        generateTwo();
        printMap();
        cout<<"现在由"<<'['<<user[order%2].username<<']'<<"进行操作！"<<endl;
        cout<<"请输入指令：";
        cin>>dir; 
    }//双人模式
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
    //两个指针，pt1存储遍历过的位置，pt2存储最接近开头的0位置
    int pt1, pt2;
    switch(dir){
        case UP:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = 0;
                while(pt1<size&&gameMap[pt1][i].getValue()!=0){ pt1++; pt2++; }//寻找起始位置
                while(pt1<size){
                    if(gameMap[pt1][i].getValue()==0){ pt1++; }
                    else{
                        if(moveMode){
                            gameMap[pt2++][i].setValue(gameMap[pt1][i].getValue());
                            gameMap[pt1++][i].setValue(0);
                        }
                        else { pt1++; this->moveTemp = true; }
                    }
                }//让所有的数字滑到规定的同一边
            }
            break;
        }
        case DOWN:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = size-1;
                while(pt1>=0&&gameMap[pt1][i].getValue()!=0){ pt1--; pt2--; }//寻找起始位置
                while(pt1>=0){
                    if(gameMap[pt1][i].getValue()==0){ pt1--; }
                    else{
                        if(moveMode){
                            gameMap[pt2--][i].setValue(gameMap[pt1][i].getValue());
                            gameMap[pt1--][i].setValue(0);
                        }
                        else { pt1--; this->moveTemp = true; }
                    }
                }//让所有的数字滑到规定的同一边
            }
            break;
        }
        case LEFT:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = 0;
                while(pt1<size&&gameMap[i][pt1].getValue()!=0){ pt1++; pt2++; }//寻找起始位置
                while(pt1<size){
                    if(gameMap[i][pt1].getValue()==0){ pt1++; }
                    else{
                        if(moveMode){
                            gameMap[i][pt2++].setValue(gameMap[i][pt1].getValue());
                            gameMap[i][pt1++].setValue(0);
                        }
                        else { pt1++; this->moveTemp = true; }
                    }
                }//让所有的数字滑到规定的同一边
            }
            break;
        }
        case RIGHT:{
            for(int i=0;i<size;++i){
                pt1 = pt2 = size-1;
                while(pt1>=0&&gameMap[i][pt1].getValue()!=0){ pt1--; pt2--; }//寻找起始位置
                while(pt1>=0){
                    if(gameMap[i][pt1].getValue()==0){ pt1--; }
                    else{
                        if(moveMode){
                            gameMap[i][pt2--].setValue(gameMap[i][pt1].getValue());
                            gameMap[i][pt1--].setValue(0);
                        }
                        else { pt1--; this->moveTemp = true; }
                    }
                }//让所有的数字滑到规定的同一边
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
                }//再进行运算
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
                }//再进行运算
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
                }//再进行运算
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
                }//再进行运算
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
                cout<<'['<<user[0].username<<']'<<"当前得分："<<user[0].score+user[1].score<<endl;
                cout<<"请输入指令：";
                cin>>this->dir;
                order++;	
            }
        } else {
            if(!this->isStopped()){
                string dirTemp = this->dirJudge();
                printMap();
                cout<<'['<<user[order%2].username<<']'<<"当前得分："<<user[order%2].score<<endl;
                cout<<"现在由"<<'['<<user[(order+1)%2].username<<']'<<"进行操作！"<<endl;
                if(dirTemp.length()==1&&user[order%2].isCheated&&!user[order%2].isPerformed){
                    do{
                        fflush(stdin);
                        cout<<user[order%2].cheat<<' '<<"同意请按'"<<dirTemp<<'\''<<':';
                        cin>>this->dir;
                    }while(this->dir!=dirTemp[0]);
                    user[order%2].isPerformed = true;
                    order++;
                } else {
                    cout<<"请输入指令：";
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
            if(gameMap[i][j].getValue()) cnt++;//统计非零的元素数
	        if(gameMap[i][j].getValue()==this->goal) { type = 1; break; }
		}
	}//遍历查看 是否有目标数字
    if(type==1){
        this->isStop = true;
    }//有目标数字
    else{
        if(cnt<size*size){
            this->generateTwo();
        }//没装满
        this->isStop = this->dirJudge()=="" ? true : false;
    }//没有目标数字就判断能不能移动

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
                cout<<"cheat指令成功！接下来请输入地图操作：";
                cin>>dir;
            }
            else{
                fflush(stdin);
                cout<<"已经存储过cheat指令！请输入地图操作：";
                cin>>dir;
            }
        }
        else fflush(stdin);
        while(dir!='w'&&dir!='z'&&dir!='a'&&dir!='s'){
            fflush(stdin);
            cout<<"非法输入！请重新输入指令：";
            cin>>dir;
        }
        while(this->dirJudge().find(dir)==-1){
            fflush(stdin);
            cout<<"无效输入！请重新输入指令：";
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
    	cout<<"游戏结束！"<<endl;
    	cout<<'['<<user[0].username<<']'<<"最终得分："<<user[0].score+user[1].score<<endl;
	} else {
		cout<<"游戏结束！"<<endl;
		cout<<'['<<user[0].username<<']'<<"最终得分："<<user[0].score<<endl;
		cout<<'['<<user[1].username<<']'<<"最终得分："<<user[1].score<<endl;
		if(user[0].score!=user[1].score){
			printf("[%s]胜利！\n", user[0].score>user[1].score?user[0].username:user[1].username); 
		} else {
			cout<<"游戏平局！"<<endl; 
		}
	}
}