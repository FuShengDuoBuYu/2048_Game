#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdarg>
#include <conio.h>

#undef NDEBUG
#include <assert.h>
using namespace std;

class player{
	string name;
	int score;
public:
	static bool scoreLess(const player* a, const player* b){return a->getScore()>b->getScore();}
	player(string n) : name(n), score(0) { };
	int getScore() const {return score;}
	string getName() const {return name;}
	friend class interact;
}; 

char robustInput(int count,...){    //当输入的字符在参数列表时，返回该字符；否则再次输入字符 
	va_list ap;
	va_start(ap,count);
	char c,*p;
	p=(char*)malloc(sizeof(char)*count);
	for(int i=0;i<count;i++)
		*(p+i)=va_arg(ap,int);
	va_end(ap);
	int i;
	do{
		c=_getch();
		for(i=0;i<count;i++)
			if(c==*(p+i))
				break;
	}while(i==count&&printf("invalid input\n"));
	free(p);
	return c;
}

class settings{
public:
	int row, col;
	int possibility_2;
	int goal;
	bool isAuthorized;
	settings() : row(4), col(4), possibility_2(90), goal(2048), isAuthorized(false) { };
	void reset();
	friend void authorize(settings& s);
};

void settings::reset(){
	if(!isAuthorized){
		cout<<endl<<"sorry, [user mode] cannot change the settings."<<endl<<endl;
		system("PAUSE");
		return ;
	}
	cout<<endl<<"row: ", cin>>row;
	cout<<"col: ", cin>>col;
	cout<<"possibility of 2(%): ", cin>>possibility_2;
	cout<<"goal: ", cin>>goal;
}

class achievements{
	static int solo_bestScore;
	static int solo_biggestValue;
	static string solo_playerName; 
	
	static int multi_bestTotalScore;
	static int multi_biggestValue;
	static int multi_bestSoloScore;
	static string multi_soloPlayerName;
	static int multi_playerNumber;
	static vector<string> multi_playerName;
	
	static void write();
public:
	static void print();
	static void read();
	static bool update(int s, int v, string n);
	static bool update(int ts, int v, vector<player*>& q);
};
int achievements::solo_bestScore = 0;
int achievements::solo_biggestValue = 0;
string achievements::solo_playerName = "NULL"; 
int achievements::multi_bestTotalScore = 0;
int achievements::multi_biggestValue = 0;
int achievements::multi_bestSoloScore = 0;
string achievements::multi_soloPlayerName = "NULL";
int achievements::multi_playerNumber = 0;
vector<string> achievements::multi_playerName;

void achievements::read(){
	ifstream infile;
	infile.open("./achievements.txt", ios::in);
	if(!infile.is_open()){
		write();
	}
	infile>>solo_bestScore>>solo_biggestValue>>solo_playerName;
	infile>>multi_bestTotalScore>>multi_biggestValue>>multi_bestSoloScore>>multi_soloPlayerName>>multi_playerNumber;
	multi_playerName.clear();
	for(int i=0; i<multi_playerNumber; i++){
		string name;
		infile>>name;
		achievements::multi_playerName.push_back(name);
	}
	infile.close();
}

void achievements::print(){
	read();
	system("CLS");
	cout<<"------------achievements------------"<<endl<<endl;
	cout<<"SoloPlayer Mode:"<<endl<<endl;
	cout<<"  Best Score : "<<solo_bestScore<<endl;
	cout<<"  the Biggest Block : "<<solo_biggestValue<<endl;
	cout<<"  Created BY : "<<solo_playerName<<endl<<endl;
	cout<<"MultiPlayer Mode:"<<endl<<endl;
	cout<<"  Best Total Score : "<<multi_bestTotalScore<<endl;
	cout<<"  the Biggest Block : "<<multi_biggestValue<<endl;
	cout<<"  Created BY : ";
	for(int i=0; i<multi_playerName.size(); i++)
		cout<<multi_playerName[i]<<"  ";
	cout<<endl<<endl;
	cout<<"  Best Solo Score : "<<multi_bestSoloScore<<endl;
	cout<<"  Created BY : "<<multi_soloPlayerName<<endl<<endl;
}

bool achievements::update(int s, int v, string n){
	if(s <= solo_bestScore)
		return false;
	solo_bestScore = s;
	solo_biggestValue = v;
	solo_playerName = n;
	write();
	return true;
}

bool achievements::update(int ts, int v, vector<player*>& q){
	bool retval = false;
	if(ts > multi_bestTotalScore){
		multi_bestTotalScore = ts;
		multi_biggestValue = v;
		multi_playerNumber = q.size();
		multi_playerName.clear();
		for(int i=0; i<q.size(); i++){
			multi_playerName.push_back(q[i]->getName());
		}
		write();
		retval = true;
	}
	if(q[0]->getScore() > multi_bestSoloScore){
		multi_bestSoloScore = q[0]->getScore();
		multi_soloPlayerName = q[0]->getName();
		write();
		retval = true;
	}
	return retval;
}

void achievements::write(){
	ofstream outfile;
	outfile.open("./achievements.txt");
	outfile<<solo_bestScore<<endl<<solo_biggestValue<<endl<<solo_playerName<<endl;
	outfile<<multi_bestTotalScore<<endl<<multi_biggestValue<<endl<<multi_bestSoloScore<<endl<<multi_soloPlayerName<<endl<<multi_playerNumber<<endl;
	for(int i=0; i<multi_playerName.size(); i++)
		outfile<<multi_playerName[i]<<" ";
	cout<<endl;
	outfile.close();
}

class block{
	static const unsigned int maxDigits = 7;//方块可容纳的数值的最大位数 
	static unsigned int biggestValue;
	unsigned int value;
public:
	block(int v=0) : value(v) {if(v > biggestValue)	biggestValue = v;}
	unsigned const int getValue() const {return value;}
	static unsigned int getBiggestValue() {return biggestValue;}
	friend ostream& operator<< (ostream& os, block& b);
	friend class chessboard;
};
unsigned int block::biggestValue = 0;

//居中打印方块数值，两侧用空格补齐 
ostream& operator<< (ostream& os, block& b){
	if(&b==0 || !b.getValue())    //没有指向对象时打印空格 
		return os<<"       ";
	unsigned int v = b.value;
	unsigned const int digits = block::maxDigits;
	int length = (int)log10(v) + 1;
	assert(length <= digits);
	char output[digits+1];
	output[digits] = 0; 
	for(int i=digits-1; i>=0; i--){    //根据i，将两侧赋值空格，中间赋值数值 
		if( i < (digits-length+1)/2 || i > digits - (digits-length)/2 -1)
			output[i] = ' ';
		else{
			output[i] = '0'+v%10;
			v /= 10;
		}
	}
	return os<<output;
}

class chessboard{
	static const int maxR = 10, maxC = 10;
	const int possibility_2;    //随机产生2的概率（单位：%） 
	unsigned const int row, col;
	block*** b;    //二维指针，(i,j)位置没有block时，b[i][j]=0；有block时，b[i][j]指向该block 
	
	class validDirection{
	public:
		int num;
		bool dir[4];	//a w s d依次对应0 1 2 3 
		static const char intToChar[4];
		static int charToInt(char c) {
			switch(c){
				case 'a': return 0;
				case 'w': return 1;
				case 's': return 2;
				case 'd': return 3;
			}
		}
		validDirection() : num(0) {memset(dir, 0, sizeof(dir));}
		void clear() {num=0;memset(dir, 0, sizeof(dir));}
	}validDir;
public:
	chessboard(settings& s) : row(s.row), col(s.col), possibility_2(s.possibility_2) {
		assert(1<row && row<=maxR && 1<col && col<=maxC);
		assert(0<=possibility_2 && possibility_2<=100); 
		//malloc二维指针，并全部初始化为0 
		b = (block***)malloc(sizeof(block**)*row);
		for(int i=0; i<row; i++){
			b[i] = (block**)malloc(sizeof(block*)*col);
			for(int j=0; j<col; j++){
				b[i][j] = 0;
			}
		}
		randomlyGenerat(2);
		randomlyGenerat(2);
	}
	~chessboard(){
		for(int i=0; i<row; i++)
			for(int j=0; j< col; j++)
				if(b[i][j] != 0)
					delete b[i][j];
		for(int i=0; i<row; i++)
			free(b[i]);
		free(b);
		block::biggestValue = 0;
	}
	void printBoard();
	int move(char input);
	void randomlyGenerat();
	void randomlyGenerat(int v);
	unsigned const int getRow(){return row;}
	unsigned const int getCol(){return col;}
	unsigned const int getValue(int i, int j){
		if(0<=i && i<row && 0<=j && j<col){
			if(b[i][j] != 0)
				return b[i][j]->getValue();
			else
				return 0;
		}else{
			return -1;
		}
	}
	void updateDirection(){
		validDir.clear();
		int deltaDir[4][2] = {{0,-1},{-1,0},{1,0},{0,1}};	//依次对应a w s d 
		for(int i=0; i<row; i++)
			for(int j=0; j<col; j++){
				int v = getValue(i, j);
				if(v){
					for(int k=0; k<4; k++){
						int vnxt = getValue(i+deltaDir[k][0], j+deltaDir[k][1]);
						if((vnxt == v || vnxt == 0)&&validDir.dir[k] == false){
							validDir.dir[k] = true;
							validDir.num++;
						}
					}
				}
			}
	}
	bool checkDirection(char c){
		return validDir.dir[validDirection::charToInt(c)];
	}
	int getDirNum(){return validDir.num;}
	char getUniqueDir(){
		for(int i=0; i<4; i++)
			if(validDir.dir[i])
				return validDirection::intToChar[i];
	}
};

const char chessboard::validDirection::intToChar[4] = {'w','a','s','d'};

void chessboard::printBoard(){
	for (int i=0; i<row; i++){
		for(int j=0; j<col; j++)
			cout<<"+-------";
		cout<<"+"<<endl<<"|";
		for(int j=0; j<col; j++)
			cout<<"       |";
		cout<<endl<<"|";
		for(int j=0; j<col; j++)
			cout<<*b[i][j]<<"|";
		cout<<endl<<"|";
		for(int j=0; j<col; j++)
			cout<<"       |";
		cout<<endl;
	}
	for(int j=0; j<col; j++)
		cout<<"+-------";
	cout<<"+"<<endl;
	return ;
}
 
int chessboard::move(char input){
	int dr, dc;    //位置的变化向量 
	int str, stc;    //遍历的起始位置 
	int dscore = 0;    //此次滑动得分 
	switch(input){
		case's': dr=-1, dc=0;str=row-1,stc=0;break;
		case'w': dr=1, dc=0;str=0,stc=col-1;break;
		case'd': dr=0, dc=-1;str=0,stc=col-1;break;
		case'a': dr=0, dc=1;str=row-1,stc=0;break;
	}
	int i=str, j=stc;
	for( ; 0<=i && i<row && 0<=j && j<col; i-=dc, j-=dr){    //根据滑动方向遍历每行（或列） 
		int m=i, n=j;
		while(0<=m && m<row && 0<=n && n<col){    //从行（或列）的末端逐个向前判断 
			
			if(b[m][n] == 0){    //当前位置没有方块时，将下一个方块（如果存在）移动到当前位置 
				int p=m+dr, q=n+dc;
				while(0<=p && p<row && 0<=q && q<col){
					if(b[p][q] != 0){
						b[m][n] = new block(b[p][q]->getValue());
						delete b[p][q];
						b[p][q] = 0;
						break;
					}
					p+=dr, q+=dc;
				}
			}
			
			if(b[m][n] == 0)    //当前位置仍没有方块，该行（或列）的操作已完成 
				break;
			
			int p=m+dr, q=n+dc;    //判断当前位置的方块能否和下一个方块合并 
			while(0<=p && p<row && 0<=q && q<col){
				if(b[p][q] != 0){
					if(b[p][q]->getValue() == b[m][n]->getValue()){
						delete b[m][n];
						b[m][n] = 0;
						b[m][n] = new block(b[p][q]->getValue()*2);
						dscore += b[m][n]->getValue();
						delete b[p][q];
						b[p][q] = 0;
					}
					break;
				}
				p+=dr, q+=dc;
			}
			
			m+=dr, n+=dc;    //更新当前位置 
		}
	}
	return dscore;
}

void chessboard::randomlyGenerat(){    //在随机空位按概率生成值为2或4的block 
	int i, j;
	do{
		i = rand()%row;
		j = rand()%col;
	}while(b[i][j] != 0);
	b[i][j] = new block(rand()%100<possibility_2 ? 2 : 4);
}

void chessboard::randomlyGenerat(int v){    //在随机空位生成值为v的block 
	int i, j;
	do{
		i = rand()%row;
		j = rand()%col;
	}while(b[i][j] != 0);
	b[i][j] = new block(v);
}

class Cheat{
public:
	bool isCreated;
	bool isUsed;
	int targetIndex;
	string sentence;
	Cheat() : isCreated(false), isUsed(false), targetIndex(-1), sentence("") { }
	bool isTargeted(int t) {return !isUsed && isCreated && t==targetIndex;}
};

class interact{
	int score;
	vector<player*> players;
	int playerIndex, playerNumber;
	void construct();
	void setPlayers();
	void playGame(chessboard& board); 
	void printGameInterface(chessboard& board);
	bool continueInquiry();
	void showRanking();
	void start();
	void printWelcomeInterface();
	void showSettings();
	void printSettings();
	void showAchievements();
	void updateAchievements();
public:
	settings setting;
	void game2048();
};

void interact::game2048(){
	while(true){
		system("CLS");
		printWelcomeInterface();
		switch(robustInput(6,'s','h','e','S','H','E')){
			case 's':case 'S': start();break;
			case 'e':case 'E': showSettings();break;
			case 'h':case 'H': showAchievements();break;
		}
	}
}

void interact::printWelcomeInterface(){
	cout<<"----------welcome to game 2048 !----------"<<endl<<endl;
	cout<<"start a new game [S]"<<endl;
	cout<<"check historical achievements [H]"<<endl;
	cout<<"check game settings [E]"<<endl;
}

void interact::start(){
	chessboard board(setting);
	construct();
	board.updateDirection();
	playGame(board);
	showRanking();
	updateAchievements();
}

void interact::construct(){
	score = 0;
	while(!players.empty()){
		delete players[players.size()-1];
		players.pop_back();
	}
	setPlayers();
	playerIndex = 0;
	playerNumber = players.size();
	achievements::read();
}

void interact::setPlayers(){
	system("CLS");
	cout<<"----------game preparation----------"<<endl<<endl;
	cout<<"choose the number of players( 1~5 )"<<endl;
	int n = robustInput(5,'1','2','3','4','5') - '0';//字符转换成数值 
	cout<<endl<<"please input name"<<endl<<endl;
	for(int i=1; i<=n; i++){
		cout<<"player"<<i<<":";
		string name;
		cin>>name;
		player* p = new player(name);
		players.push_back(p);
	}
	cout<<endl<<"set successfully!"<<endl<<endl;
	system("PAUSE");
	system("CLS");
}

void interact::playGame(chessboard& board){
	bool isAchieved = false;
	Cheat cheat;
	printGameInterface(board);
	while(board.getDirNum()){
		if(cheat.isTargeted(playerIndex) && board.getDirNum() == 1){
			cheat.isUsed = true;
			cout<<cheat.sentence<<" , press ["<<board.getUniqueDir()<<"] to agree."<<endl;
		}
		char input = robustInput(playerNumber>1 ? 5-cheat.isCreated : 4,'a','w','s','d','c');	//单人模式或者cheat被使用，‘c’成为无效按键 
		if(input == 'c'){
			cheat.isCreated = true;
			cout<<"please input a sentence without blank space:"<<endl;
			cin>>cheat.sentence; 
			if(playerNumber > 2){
				cout<<"please choose the target player:"<<endl;
				for(int i=0; i<playerNumber; i++)
					cout<<"["<<i+1<<"] "<<players[i]->name<<endl;
				cheat.targetIndex = robustInput(playerNumber,'1','2','3','4','5')-'1';
			}else{
				cheat.targetIndex = (playerIndex+1)%playerNumber;
			}
			cout<<endl<<"set successfully!"<<endl<<endl;
			system("PAUSE");
			printGameInterface(board);
			continue;
		}
		if(board.checkDirection(input)){
			int dscore = board.move(input);
			score += dscore;
			players[playerIndex]->score += dscore;
			board.randomlyGenerat();
			++playerIndex%=playerNumber;
			printGameInterface(board);
			if(!isAchieved && block::getBiggestValue() >= setting.goal){
				isAchieved = true;
				if(continueInquiry())
					printGameInterface(board);
				else
					return ;
			}
		}
		board.updateDirection();
	}
	cout<<"game over!"<<endl;
	system("PAUSE");
}

void interact::printGameInterface(chessboard& board){
	system("CLS");
	cout<<"score:"<<score<<endl;
	cout<<"the biggest block:"<<block::getBiggestValue()<<endl<<endl;
	board.printBoard();
	for(int i=0; i<playerNumber; i++){
		if(i == playerIndex)
			cout<<"->"<<players[i]->name<<":"<<players[i]->score<<endl;
		else
			cout<<"  "<<players[i]->name<<":"<<players[i]->score<<endl;
	}
}

bool interact::continueInquiry(){
	cout<<"you achieve the goal of "<<setting.goal<<" !"<<endl<<"continue? [Y] / [N]"<<endl;
	char input = robustInput(4,'y','Y','n','N');
	return (input == 'y' || input == 'Y') ? true : false;
}

void interact::showRanking(){
	system("CLS");
	if(playerNumber == 1)
		return ;
	cout<<"------------ranking------------"<<endl<<endl;
	sort(players.begin(), players.end(), player::scoreLess);
	int rank = 1;
	for(int i=0; i<players.size(); i++){
		cout<<rank<<". "<<players[i]->name<<" score:"<<players[i]->score<<endl;
		if(i+1 < players.size() && players[i]->score > players[i+1]->score)
			rank++;
	}
	cout<<endl;
	system("PAUSE");
}

void interact::showSettings(){
	while(true){
		printSettings();
		switch(robustInput(4,'b','c','B','C')){
			case 'b':case 'B': return ;break;
			case 'c':case 'C': setting.reset();break;
		}
	}
}

void interact::printSettings(){
	system("CLS");
	cout<<"------------settings------------"<<endl<<endl;
	cout<<"row : "<<setting.row<<endl;
	cout<<"col : "<<setting.col<<endl;
	cout<<"the possibility of 2 (%) : "<<setting.possibility_2<<endl;
	cout<<"goal : "<<setting.goal<<endl<<endl;
	cout<<"back to welcom page [B]"<<endl;
	cout<<"change the settings [C]"<<endl;
}

void interact::showAchievements(){
	achievements::print();
	cout<<"back to welcome page [B]"<<endl;
	if(robustInput(2,'b','B'))
		return ;
}

void interact::updateAchievements(){
	system("CLS");
	bool isBreak = false;
	if(playerNumber == 1)
		isBreak = achievements::update(score, block::getBiggestValue(), players[0]->name);
	else
		isBreak = achievements::update(score, block::getBiggestValue(), players);
	if(isBreak)
		cout<<"Congratulations! You break the record!"<<endl<<endl;
	else
		cout<<"What a pity.Make persistant efforts."<<endl<<endl;
	system("PAUSE");
}

void authorize(settings& s){
	if(!s.isAuthorized){
		s.isAuthorized = true;
		cout<<endl<<"enter [debugging mode] ; you're now authorized to change the settings."<<endl<<endl;
		system("PAUSE");
		system("CLS");
	}
}

int main (int argc, char* argv[]){ 
	srand(time(0));
	interact console;
	for(int i=1; i<argc; i++){    //命令行输入 -t/-s 进入debugging mode，自行设置参数 
		if(!strcmp(argv[i], "-t")){
			authorize(console.setting);
		}else if(!strcmp(argv[i], "-s")){
			authorize(console.setting);
			int size = stoi(argv[++i]);
			if(3<=size && size<=5)
				console.setting.row = console.setting.col = size;
			else{
				cout<<"plaese input 3 , 4 or 5:";
				console.setting.row = console.setting.col = robustInput(3,'3','4','5')-'0';
			}
		}
	}
	console.game2048();
	return 0;
} 
