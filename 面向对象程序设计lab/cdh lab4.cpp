#include<iostream>
#include <cstdlib>
#include<ctime>
#include<cmath>
#include<cstring>
using namespace std;
class Game2048{
    private:
    int dimension=4;
    int mapkey[6][6];
    string order;//��������
    int traget=2048;
    int get_one_score;//ÿһ���ƶ��ĵ÷�
    int pattern_order;//��Ϸģʽ��ѡ��
    bool optional_order[4];//��Ч����
    string request_order;//����Ҫ�����
    int optional_order_number;//��Ч����������
    int save_user_number=0;//��¼Ҫ��cheat���û�
    int cheat_number=1;//����cheat�Ĵ���
    bool cheat_singal=false;//�Ѿ���ʼ��cheat����

    public:
    void WelcomePage();//��ӡ��Ϸ��ʼ����
    void PrintGame();/*���ڴ�ӡ��Ϸ����*/
    void ClearMap();
    void MoveGame();/*��Ӧ��Ϸ�����������ƶ�*/
    void GetOrder();/*��ȡָ��*/
    void CreateRandomTwo();/*�������λ�õ�2*/
    void ChangeTarget();/*�ı���ϷĿ��*/
    bool CheckTarget();//����Ƿ�ﵽ��Ϸ���
    int GetPattern_order();//��ȡģʽ����
    int Get_get_one_score();//��ȡÿһ�ε÷�
    void GetOptional_order();//�õ��ĸ������Ƿ���Ч
    void CheckOptional_order();//����ĸ������Ƿ���Ч���Ա������Ϸ
    void StartCheat(int use_number);//�û�ʹ��cheat�Ľ���
    void ExecuteCheat(int use_number);//ִ��cheat
    bool EndGame();//�ж��Ƿ������Ϸ
    void CountOptional_order();//������Ч����������
    void SetDimension(int size);
    char GetSingleOrder();
};
char Game2048::GetSingleOrder(){
    char single_order;
    if(optional_order[0]){
        single_order='a';
    }else if(optional_order[1]){
        single_order='d';
    }else if(optional_order[2]){
        single_order='w';
    }else if(optional_order[3]){
        single_order='s';
    }
    return single_order;

}

void Game2048::ExecuteCheat(int use_number){
    if(cheat_singal && (use_number==save_user_number) && (optional_order_number==1) && (cheat_number>0)){
        while(1){
            char a=GetSingleOrder();
            cout<<"["<<request_order<<"]"<<" ͬ��������"<<'['<<a<<']'<<endl;
            cin>>order;
            if(order[0]==a){
                break;
            }
            cout<<"the order is wrong,please enter again"<<endl;
            
        }
        cout<<"please enter order to continue game"<<endl;
        cheat_number--;
    }


}

void Game2048::SetDimension(int size){
    while(1){
        if(size>=2 && size<=5){
            dimension=size;
            cout<<"dimension is set successufully"<<endl;
            break;
        }
        cout<<"the size is wrong ,please enter size again"<<endl;
        cin>>size;
    }
}

bool Game2048::EndGame(){
    if(optional_order_number==0){
        cout<<"game over"<<endl;
        return true;
    }else{
        return false;
    }
}

void Game2048::CountOptional_order(){
    optional_order_number=0;
    for(int i=0;i<4;i++){
        if(optional_order[i]){
            optional_order_number++;
        }
    }
}

void Game2048::StartCheat(int user_number){
    string cheat_order="c";
    save_user_number=(user_number+1)%pattern_order;
    if(order==cheat_order){
        cin>>request_order;
        if(pattern_order==1){
            cout<<"this is single mode,you cannot use the order,please enter order again"<<endl;
            cin>>order;
        }else{
            if(cheat_number==0){
                cout<<"the number of cheat has ran out,please enter order again"<<endl;
                cin>>order;
            }else{
                cheat_singal=true;
                cout<<"request_order is saved,please enter order again"<<endl;
                cin>>order;
            }
        }
    }
}

void Game2048::GetOptional_order(){
    int ret=0;
    for(int i=0;i<dimension;i++){
        for(int j=dimension-1;j>0;j--){
            if(mapkey[i][j]>0){
                if(mapkey[i][j-1]==mapkey[i][j] || mapkey[i][j-1]==0){
                    optional_order[0]=true;
                    ret=1;
                }
            }
        }
    }
    if(ret==0){
        optional_order[0]=false;
    }
    ret=0;//�ж��Ƿ���������� "a"
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension-1;j++){
            if(mapkey[i][j]>0){
                if(mapkey[i][j+1]==mapkey[i][j] || mapkey[i][j+1]==0){
                    optional_order[1]=true;
                    ret=1;
                }
            }
        }
    }
    if(ret==0){
        optional_order[1]=false;
    }
    ret=0;//�ж��Ƿ���������� "d"
    for(int i=dimension-1;i>0;i--){
        for(int j=0;j<dimension;j++){
            if(mapkey[i][j]>0){
                if(mapkey[i-1][j]==mapkey[i][j] || mapkey[i-1][j]==0){
                    optional_order[2]=true;
                    ret=1;
                }
            }
        }
    }
    if(ret==0){
        optional_order[2]=false;
    }
    ret=0;;//�ж��Ƿ���������� "w"
    for(int i=0;i<dimension-1;i++){
        for(int j=0;j<dimension;j++){
            if(mapkey[i][j]>0){
                if(mapkey[i+1][j]==mapkey[i][j] || mapkey[i+1][j]==0){
                    optional_order[3]=true;
                    ret=1;
                }
            }
        }
    }
    if(ret==0){
        optional_order[3]=false;
    }
    ret=0;;//�ж��Ƿ���������� "s"
    
}

int Game2048::Get_get_one_score(){
    return get_one_score;
}

void Game2048::WelcomePage(){
    cout<<"-----------------start game2048 ----------------"<<endl;
    cout<<"\nplease choose play model"<<endl;
    cout<<"1. single mode"<<endl;
    cout<<"2. double mode"<<endl;
    cout<<"please enter serial number of model ��";
    cin>>pattern_order;


}

int Game2048::GetPattern_order(){
    return pattern_order;
}

void Game2048::GetOrder(){
    cin>>order;
}/*��ȡָ��*/


void Game2048::MoveGame(){
    get_one_score=0;
    while (1){
        ChangeTarget();
        if(order.length()!=1){
            cout<<"wrong order,please enter order again\n";
            cin>>order;
            continue;
        }
        switch (order[0]){
        case 'a' :
            if(optional_order[0]==false){
                cout<<"you cannot enter the order,please enter other optional order"<<endl;
                cin>>order;
                continue;
            }
            for(int i=0;i<dimension;i++){
                int temp=0;//ָ���һ������֮�󲻶ϸ���
                for(int j=1;j<dimension;j++){
                    if(mapkey[i][j]>0){
                        if(mapkey[i][temp]==0){//���mapkey[i][temp]==0����ô����0������������
                            mapkey[i][temp]=mapkey[i][j];
                            mapkey[i][j]=0;
                        }else{
                            if(mapkey[i][j]==mapkey[i][temp]){//�����ȣ���ǰһ����2������Ϊ0
                                mapkey[i][temp]*=2;
                                mapkey[i][j]=0;
                                get_one_score+=mapkey[i][temp];
                                temp++;//����ָ����һ����
                                
                            }else{
                                temp++;
                                int a=mapkey[i][temp];//����������
                                mapkey[i][temp]=mapkey[i][j];
                                mapkey[i][j]=a;
                            }
                        }
                    }
                }


            }
            // cout<<get_one_score;
            return ;
        case 'd':
            if(optional_order[1]==false){
                cout<<"you cannot enter the order,please enter other optional order"<<endl;
                cin>>order;
                continue;
            }
            for(int i=0;i<dimension;i++){
                int temp=dimension-1;
                for(int j=dimension-2;j>=0;j--){
                    if(mapkey[i][j]>0){
                        if(mapkey[i][temp]==0){
                            mapkey[i][temp]=mapkey[i][j];
                            mapkey[i][j]=0;
                        }else{
                            if(mapkey[i][j]==mapkey[i][temp]){
                                mapkey[i][temp]*=2;
                                mapkey[i][j]=0;
                                get_one_score+=mapkey[i][temp];
                                temp--;
                                
                            }else{
                                temp--;
                                int a=mapkey[i][temp];
                                mapkey[i][temp]=mapkey[i][j];
                                mapkey[i][j]=a;
                            }
                        }
                    }
                }


            }
            return ;
        case 'w':
            if(optional_order[2]==false){
                    cout<<"you cannot enter the order,please enter other optional order"<<endl;
                    cin>>order;
                    continue;
                }
            for(int j=0;j<dimension;j++){
                int temp=0;
                for(int i=1;i<dimension;i++){
                    if(mapkey[i][j]>0){
                        if(mapkey[temp][j]==0){
                            mapkey[temp][j]=mapkey[i][j];
                            mapkey[i][j]=0;
                        }else{
                            if(mapkey[i][j]==mapkey[temp][j]){
                                mapkey[temp][j]*=2;
                                mapkey[i][j]=0;
                                get_one_score+=mapkey[temp][j];
                                temp++;
                                
                            }else{
                                temp++;
                                int a=mapkey[temp][j];
                                mapkey[temp][j]=mapkey[i][j];
                                mapkey[i][j]=a;
                            }
                        }
                    }
                }


            }
            return ;
        case 's':
            if(optional_order[3]==false){
                cout<<"you cannot enter the order,please enter other optional order"<<endl;
                cin>>order;
                continue;
            }
            for(int j=0;j<dimension;j++){
                int temp=dimension-1;
                for(int i=dimension-2;i>=0;i--){
                    if(mapkey[i][j]>0){
                        if(mapkey[temp][j]==0){
                            mapkey[temp][j]=mapkey[i][j];
                            mapkey[i][j]=0;
                        }else{
                            if(mapkey[i][j]==mapkey[temp][j]){
                                mapkey[temp][j]*=2;
                                mapkey[i][j]=0;
                                get_one_score+=mapkey[temp][j];
                                temp--;
                            }else{
                                temp--;
                                int a=mapkey[temp][j];
                                mapkey[temp][j]=mapkey[i][j];
                                mapkey[i][j]=a;
                            }
                        }
                    }
                }


            }
            return ;
        default:
            cout<<"wrong order,please enter order again\n";
            cin>>order;


            

    }
    
        
    }
    
    
    
}

void Game2048::ClearMap(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            mapkey[i][j]=0;
        }

    }
}

void Game2048::CreateRandomTwo(){
    int count=0;/*ȷ��ʣ��Ŀո���*/
    int cnt=0;/*�����������randomdirectionƥ��*/
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(mapkey[i][j]==0){
                count++;
            }
        }

    }/*ȷ��ʣ��ո���*/
    if(count){      /*������пո���ܽ���ѭ���������2*/
         srand(time(NULL));
         int randomdirection=rand()%count+1;
         for(int i=0;i<dimension;i++){
             for(int j=0;j<dimension;j++){
                 if(mapkey[i][j]==0){
                     cnt++;
                 }
                 if(cnt==randomdirection){
                     mapkey[i][j]=2;
                     return ;/*��Ҫ����ѭ��*/
                 }
                
             }
         }


    }
}

void Game2048::PrintGame(){
    for(int i=0;i<dimension;i++){
        for(int k=0;k<dimension;k++){
            cout<<"+-----";
        }
        cout<<"+"<<endl;
        for(int j=0;j<dimension;j++){
            
            if(mapkey[i][j]==0){
                cout<<"|     ";
            }
            int a=(int)log10(mapkey[i][j]);
            switch (a)/*Ϊ��ʹ���־����ܾ��У���ֻ��������λ��*/
            {
            case 0:
                cout<<"|  "<<mapkey[i][j]<<"  ";
                break;
            case 1:
                cout<<"|  "<<mapkey[i][j]<<" ";
                break;
            case 2:
                cout<<"| "<<mapkey[i][j]<<" ";
                break;
            case 3:
                cout<<"| "<<mapkey[i][j]<<"";
            default:
                break;
            }
            
        }
        cout<<"|"<<endl;

    }
    for(int k=0;k<dimension;k++){
            cout<<"+-----";
        }
        cout<<"+"<<endl;
}

void Game2048::ChangeTarget(){
    string change_order="-t";//�˳��������ͽ��ܵ�����һ�¾͸ı�traget
    if(order==change_order){
        traget=64;
        cout<<"the traget_value is changed,please enter order again"<<endl;
        cin>>order;//�ٴν���ָ����Ժͺ���ƥ��
    }
}

bool Game2048::CheckTarget(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(mapkey[i][j]==traget){
                return true;
            }
        }
    }
    return false;

}

class Person{
    private:
    int score;//�û����ܷ���
    string username;//�û���
    public:
    void Initializa(int i);//��ʼ���û����ͷ���
    void CountScores(Game2048& game);//�õ�ÿһ��������Ϸ�ķ���
    void PrintScores();//��ӡ�÷�
    int GetScores();//��ȡ�÷֣��Ա��ж�˭ʤ��
    void OperationTip();//��ӡ��һ�������ߵ���ʾ
    void WinGame();//��ʾӮ�ñ���
};

void Person::WinGame(){
    cout<<"["<<username<<"] win the game"<<endl;
}

void Person::PrintScores(){
        cout<<"["<<username<<"] score :"<<score<<endl;
    }

void Person::OperationTip(){
    cout<<"The next operator is �� "<<username<<endl;
}

int Person::GetScores(){
    return score;
}

void Person::Initializa(int i){
    cout<<"please enter "<<i+1<<" user's username��";
    cin>>username;
    score=0;
}

void Person::CountScores(Game2048& game){
    score+=game.Get_get_one_score();
}

int main(int argc,char* argv[]){
    Game2048 game;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-s")==0){
            game.SetDimension(atoi(argv[i+1]));
        }

    }
    game.WelcomePage();//��ӭ����
    int user_number=game.GetPattern_order();//�õ���Ϸ�������Ա�ʵ����person �ĸ���
    Person users[user_number];
    for(int i=0;i<user_number;i++){
        users[i].Initializa(i);//��ʼ����������
    }
    game.ClearMap();//��ʼ�����ʹ��ȫ��Ϊ0
    game.CreateRandomTwo();
    game.CreateRandomTwo();//���������������2
    game.PrintGame();
    int count=0;
    while(1){
        game.GetOptional_order();
        game.CountOptional_order();
        if(game.CheckTarget() || game.EndGame()){
            break;
        }
        users[count].OperationTip();
        game.ExecuteCheat(count);
        game.GetOrder();
        game.StartCheat(count);
        game.MoveGame();
        game.CreateRandomTwo();
        game.PrintGame();
        users[count].CountScores(game);
        users[count].PrintScores();
        count++;
        count%=user_number;//��count��ѭ����������ÿһ���û����β���

    }
    if(user_number==1){
        users[0].WinGame();
    }else if(user_number==2){
        if(users[0].GetScores()>users[1].GetScores()){
            users[0].WinGame();
        }else if(users[0].GetScores()<users[1].GetScores()){
            users[1].WinGame();
        }else{
            cout<<"you are draw"<<endl;
        }//�ж�˭��ʤ
    }


}