# 1.1 结构功能最好的代码

---

## 优点：

+ 自己编写  robustInput 函数,大大简化用户输入字符串命令的判断

  + ```cpp
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
    ```

  + **优点详解:**通过参数中的缺省参数,这样可以使得开发者自己确定用户输入了哪些字符是合法有效的,要比普通的添加"或"判断的可读性和实用性高很多

  + **举例说明:** 

    + 假如不使用该函数,判断用户输入是否合法,并将输入的值作为2048方格的维数时一般会采用如下方式:

      + ```cpp
        if(gameDimension == 3 || gameDimension == 4 || gameDimension == 5 || gameDimension == 2){
                    //TODO:赋值维数
                    break;
                }
                else{
                    //TODO:提示用户输入不正确
                }
        ```

      + 这样的方式显示起来可读性很差,并且在后期修改时较为麻烦

    + 假如使用了该函数,判断用户输入是否合法只需要调用该函数,将判断封装了起来

      + ```cpp
        console.setting.row = console.setting.col = robustInput(3,'3','4','5')-'0';
        ```

      + 这样的方式就更加简洁并且可以复用,使得封装更加完善

  ---

+ 抽象出了 interact 类,该类用于作为第三方连接,将chessboard类和player类分离开,确保这两个类里不包含彼此的冗余信息,使得代码的耦合度大大降低

  + ```cpp
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
    //该类主要用于操纵整个游戏的进程,它可以连接player和chessboard,游戏里的一系列操作
    //都是用该类获取player和chessboard的数据进行
    ```

  + **优点详解:**由于该类相当于一个游戏系统的连接人,管理者,因此在进行游戏时,棋盘和使用者作为独立的整体,不需要相互传递参数,可以大大降低耦合度,使得代码的可扩展性提高

  + **举例说明:**

    + 假如没有抽象出该类,那么当想要向更新棋盘中的信息时可能需要向棋盘传递用户的参数,:

      + ```cpp
        void updateChessboard(player p){
        	//TODO:利用用户的用户名等信息并更新棋盘
        }
        ```

      + 这样的话其类与类之间的耦合度就会非常高,不符合封装的原则

    + 此时抽象出了该类以后,就可以将棋盘和用户的信息传递给这个"第三方管理者",使得结构更加清晰

      + ```cpp
        void interact::playGame(chessboard& board){
        	//TODO:处理用户输入并更新棋盘等
        }
        ```

---

- 在四个方向更新细胞图时使用了方向参数,由此避免了四个方向上的大量的代码粘贴

  - ```cpp
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
    ```

  - **优点详解:**利用dr, dc, str, stc等变量的使用,使得上下左右移动的代码可以被统一,只需要更改参数的值即可,减少了代码冗余,使程序更加精简

  - **举例说明:**

    - 假如没有这些方向参数,那么就会出现这种情况:

      - ```cpp
        void upUpdateCells();
        void downUpdateCells();
        void leftUpdateCells();
        void rightUpdateCells();
        ```

      - 而这些函数都有着相同的功能,唯一的区别只在于更新棋盘的方向,会造成大量的冗余不必要的代码,而使用方向参数则会使得其十分简洁



---

## 功能增量:

- 可以记录单人模式或者多人模式下最高分数,支持历史最高查询

  - ```cpp
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
    ```

  - 该类可以用于记录用户曾经单人以及多人模式下的最高分和最低分,并且将其存储在一个txt文件里,支持历史记录查询

  - 函数实现实例:

    - ```cpp
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
      ```

    - ```cpp
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
      ```

  ---

- 支持最多5人进行游戏,同时游戏结束时可以对5个人的分数进行排序,记录等

  - ```cpp
    void interact::setPlayers(){
    	system("CLS");
    	cout<<"----------game preparation----------"<<endl<<endl;
    	cout<<"choose the number of players( 1~5 )"<<endl;
        //=====================================
        //此处支持5人游戏
        //=====================================
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
    ```

  - 这样就可以提高游戏的可玩性,扩展了游戏的使用环境

---

## 不足:

- 未进行分文件,将所有类的声明,函数的声明,函数的实现等等都放置在同一个cpp文件当中,使得整个文件看起来较为复杂和臃肿,同时也使得信息隐藏被破坏

  - 建议: 可以更改为 .h文件, .cpp文件 和 main.cpp文件,将它们分文件存储,结构会更加清晰

- 在程序中仍然留存断言,断言应该在调试时存在,在程序完成后应该注释掉或者删除,防止程序运行时异常退出

  - ```cpp
    assert(length <= digits);
    assert(1<row && row<=maxR && 1<col && col<=maxC);
    assert(0<=possibility_2 && possibility_2<=100); 
    ```

---

# 1.2 改进余地较大的代码

- 函数传递参数过多,代码耦合度太高

  - ```cpp
    void printCells(std::vector<Cell> cells,std::vector<User> users,int steps,int modeNum,int ROW,int COL);
    std::vector<Cell> createCells(int ROW,int COL);
    void userInput(std::vector<Cell> &cells,int endNum,std::vector<User> &users,int &steps,int modeNum,int ROW,int COL);
    void updateCells(std::vector<Cell> &cells,char order,std::vector<User> &users,int &steps,int ROW,int COL,int modeNum);
    void createRand2(std::vector<Cell> &cells,std::vector<User> &users,int modeNum);
    void ifTest(int &endNum);
    int welcomePage(int &ROW,int &COL);
    std::vector<User> createUsers(int modeNum);
    void endGame(std::vector<User> users,int modeNum);
    void upUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
    void downUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
    void leftUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
    void rightUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
    int* moveDirection(std::vector<Cell> cells, std::vector<User> users, int ROW, int COL, int &steps);
    void updateCells(std::vector<Cell> &cells,char order,std::vector<User> &users,int &steps,int ROW,int COL,int modeNum,std::string orderString,char directionChar);
    ```

  - 可以看到,每一个函数都需要跟进许多参数,不仅可读性非常低,而且代码的可维护性等也非常差

- 改进建议: 

  1.  可以将函数中频繁出现的参数设置为全局变量,从而减少其中传递参数的复杂性
  2.  可以再抽象出一个game类,将这些全局的函数都放置于game类当中,然后让game类获取到这些所有的参数,便可以将这些参数的传递大大简化

---

- 判断用户输入指令以后棋盘有没有实质上的变化时,使用了复制一份原棋盘,再依次比对新棋盘的各个位置是否和原棋盘一致,这样会导致消耗大量的内存,降低了程序的性能

  - ```cpp
    void updateCells(vector<Cell> &cells,char order,vector<User> &users,int &steps,int ROW,int COL,int modeNum){
        vector<Cell> copyCells = cells;
        //TODO: 更新细胞图
        //...
        //当细胞图真正发生改变时,才能生成一个2并且让步数加一
        bool changed = false;
        for (int i = 0; i < cells.size();i++){
            if(cells[i].getValue()!=copyCells[i].getValue()){
                createRand2(cells, users, modeNum);
                steps++;
                changed = true;
                break;
            }
        }
        //若是没有让棋盘发生变化,那么就是无效输入
        if(changed == false && order != 'c'){
            cout << "The operator has not changed the map, please input again:" << endl;
        }
        
    }
    ```

- 改进建议: 优化比较棋盘是否发生改变的算法并且抽象封装成一个函数:

  - ```cpp
    
    ```

  - 

