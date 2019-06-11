#include <bits/stdc++.h>
#include <conio.h>

#define width 20            //map settings
#define heigh 20            //      20*20 - default

#define startXPos 10        //snake settings
#define startYPos 10        //      x=10,y=10 - default
#define body char(248)      //
#define head '0'            //
#define dieHead '*'         //
#define startLen 4          //

#define LEFT_DOWN 187       //snake body settings
#define LEFT_UP 188         //
#define RIGHT_UP '╚'        //
#define RIGHT_DOWN '╔'      //
#define BODY_VERTICAL 186   //
#define BODY_HORISONTAL 205 //

#define UP_KEY 119           //movement settings
#define DOWN_KEY 115         //
#define LEFT_KEY 97          //
#define RIGHT_KEY 100        //
#define PAUSE_KEY 32         //

                            //game settings
#define DIFFICULTY 5        //1 - very slow, 2 - easy, 5 - medium, 10 - hard
#define APPLE '*'           //

using namespace std;

vector < vector < char > > pole(width, vector < char > (heigh, ' '));
vector < pair < int, int > > snake(0);
vector < pair < int, int > > eatedApples(0);

int xDir = 1, yDir = 0;
int appleX, appleY;
int score = 0, best;

char setBody (int x, int y, int pos){
    if(snake[pos+1].first == x-1 && snake[pos-1].second == y-1) return LEFT_UP;
    if(snake[pos-1].first == x-1 && snake[pos+1].second == y-1) return LEFT_UP;

    if(snake[pos+1].first == x-1 && snake[pos-1].second == y+1) return LEFT_DOWN;
    if(snake[pos-1].first == x-1 && snake[pos+1].second == y+1) return LEFT_DOWN;

    if(snake[pos+1].first == x+1 && snake[pos-1].second == y+1) return RIGHT_UP;
    if(snake[pos-1].first == x+1 && snake[pos+1].second == y+1) return RIGHT_UP;

    if(snake[pos+1].first == x+1 && snake[pos-1].second == y-1) return RIGHT_DOWN;
    if(snake[pos-1].first == x+1 && snake[pos+1].second == y-1) return RIGHT_DOWN;

    if(snake[pos+1].second == y+1 && snake[pos-1].second == y-1) return BODY_VERTICAL;
    if(snake[pos-1].second == y+1 && snake[pos+1].second == y-1) return BODY_VERTICAL;

    if(snake[pos+1].first == x+1 && snake[pos-1].first == x-1) return BODY_HORISONTAL;
    if(snake[pos-1].first == x+1 && snake[pos+1].first == x-1) return BODY_HORISONTAL;
}

void render (int isDie){
    for (int i = 0; i < width; ++i){
        for(int j = 0; j < heigh; ++j){
            pole[i][j] = ' ';
        }
    }

    pole[appleX][appleY] = APPLE;

    for(int i = 0; i < width; ++i){
        pole[i][0] = '#';
        pole[i][heigh-1] = '#';
    }
    for (int i = 0; i < heigh; ++i){
        pole[0][i] = '#';
        pole[width-1][i] = '#';
    }

    //pole[snake[0].first][snake[0].second] = body;
    for (int i = 0; i < snake.size() - 1; ++i){
        //pole[snake[i].first][snake[i].second] = setBody(snake[i].first, snake[i].second, i);
        pole[snake[i].first][snake[i].second] = body;
    }
    if (isDie) pole[snake[snake.size() - 1].first][snake[snake.size() - 1].second] = dieHead;
    else pole[snake[snake.size() - 1].first][snake[snake.size() - 1].second] = head;

    system ("cls");
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < heigh; ++j){
            cout<<pole[j][i];
        }
        if(i == 0){
            cout<<"   score: "<<score;
        }
        if(i == 1){
            if(best > score) cout<<"   best: "<<best;
            else cout<<"   best: "<<score;
        }
        cout<<endl;
    }
}

bool inSnake (int x, int y){
    for(int i = 0; i < snake.size(); ++i){
        if(snake[i].first == x && snake[i].second == y){
            return 1;
        }
    }
    return 0;
}

void makeApple (){
    appleX = rand() % (width-2)+1;
    appleY = rand() % (heigh-2)+1;
    while(inSnake(appleX, appleY)){
        appleX = rand() % (width-2)+1;
        appleY = rand() % (heigh-2)+1;
    }
}

bool makeLonger (){
    if(eatedApples.size() > 0){
        if(eatedApples[0].first == snake[0].first && eatedApples[0].second == snake[0].second){
            eatedApples.erase(eatedApples.begin());
            score++;
            return 1;
        }
    }
    return 0;
}

void event (){
    if(!makeLonger()){
        snake.erase(snake.begin());
    }
    snake.push_back(make_pair(snake[snake.size()-1].first + xDir, snake[snake.size()-1].second + yDir));

    if(snake[snake.size()-1].first == appleX && snake[snake.size()-1].second == appleY){
        eatedApples.push_back(make_pair(appleX, appleY));
        makeApple();
    }
}

bool die(){
    if (snake[snake.size()-1].first == 0 || snake[snake.size()-1].first == width-1 || snake[snake.size()-1].second == 0 || snake[snake.size()-1].second == heigh-1) return 1;

    for (int i = 0; i < snake.size() - 1; ++i){
        if (snake[snake.size()-1].first == snake[i].first && snake[snake.size()-1].second == snake[i].second) return 1;
    }
    return 0;
}

void movement (){
    if (kbhit()){
        int dir;
        dir = getch();

        if (dir == UP_KEY && yDir != 1){
            xDir = 0;
            yDir = -1;
        }
        if (dir == DOWN_KEY && yDir != -1){
            xDir = 0;
            yDir = 1;
        }
        if (dir == LEFT_KEY && xDir != 1){
            xDir = -1;
            yDir = 0;
        }
        if (dir == RIGHT_KEY && xDir != -1){
            xDir = 1;
            yDir = 0;
        }
        if(dir == PAUSE_KEY){
            for(int i = 0; i < 100000000; ++i){}
            system("pause");
        }
    }
}

void setNewBest (){
    if(score > best){
        ofstream setBest("Scores.txt");
        setBest<<score;
    }
}

void main_game_loop (){
    int isDie;
    makeApple();
    while (true) {
        movement();
        event();
        isDie = die();
        render(isDie);
        if(isDie) return;
        setNewBest();
        for(int i = 0; i  < 200000000 / DIFFICULTY; ++i){}
    }
}

int main()
{
    for (int i = 0; i < startLen; ++i){
        snake.push_back(make_pair(startXPos + i, startYPos));
    }
    srand(time(NULL));

    ifstream getBest("Scores.txt");
    getBest>>best;

    cout<<"Please select correct language on your keyboard.."<<endl;
    system("pause");

    main_game_loop();

    for(int i = 0; i < 500000000; ++i){}
    system("cls");
    cout<<"score: "<<score<<endl;
    cout<<"best: "<<best<<endl;
    for(int i = 0; i < 500000000; ++i){}
    system("pause");

    return 0;
}