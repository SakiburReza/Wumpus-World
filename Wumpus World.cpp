#include <iostream>
#include <cmath>
#include <sstream>
#include<cstdlib>
#include<cstdio>


using namespace std;

#define GRIDSIZE 4
#define UP      5
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3
#define NORMAL  0
#define HIT     1
#define MISS    2
#define FINISH  3


string to_string(int x) {
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}

class WumpusWorld;



class Position {

    int x, y;

public:

    Position (int x, int y) {
        this->x = x;
        this->y = y;
    }

    Position() {}

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight() {
        x++;
        if(x>3) {x=3;cout<<"It can't move right.\n";}
    }

    void moveLeft() {
        x--;
        if(x<0) {x=0;cout<<"It can't move left.\n";}
    }

    void moveUp() {
        y++;
        if(y>3) {y=3;cout<<"It can't move up.\n";}
    }

    void moveDown() {
        y--;
         if(y<0) {y=0;cout<<"It can't move down.\n";}
    }

    bool isAdjacent(Position p) {
        //implement the function
        if(p.getX()==x&&(p.getY()-1==y||p.getY()+1==y)) return true;
        if(p.getY()==y&&(p.getX()-1==x||p.getX()+1==x)) return true;
        else return false;
    }

    bool isSamePoint(Position p) {
        //implement the function
        if(p.getX()==x&&p.getY()==y) return true;
        else return false;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }


};


class Wumpus {

    bool killed;
    Position p;

public:

    Wumpus(int x, int y) {
        p = Position(x, y);
        killed = false;
    }

    Wumpus() {
        //...
    }

    void kill() {
        killed = true;

    }

    Position getPosition() {
        return p;
    }
    bool iskilled(){
        return !killed;
    }


};


class Pit {

    bool killed;
    Position p;

public:

    Pit(int x, int y) {
        p = Position(x, y);
        killed = false;
    }

    Pit() {
        //...
    }



    Position getPosition() {
        return p;
    }


};



class Player {

    int direction;
    int total_shots=MAX_SHOTS;
    bool killed;
    Position p,w;
    Wumpus wu;
   //
   // WumpusWorld wum;

public:

    Player() {
        //...
            p=Position(0,0);
            direction=UP;

    }

    void turnLeft() {
        //...
      if(direction==UP) direction=LEFT;
      else if(direction==RIGHT) direction=UP;
      else if(direction==LEFT) direction=DOWN;
      else if(direction==DOWN) direction=RIGHT;
    }

    void turnRight() {
        //...
        if(direction==UP) direction=RIGHT;
     else if(direction==RIGHT) direction=DOWN;
    else if(direction==LEFT) direction=UP;
      if(direction==DOWN) direction=LEFT;

    }

    void moveForward() {
        //...
        if(direction==LEFT) p.moveLeft();
        if(direction==RIGHT) p.moveRight();
        if(direction==UP) p.moveUp();
        if(direction==DOWN) p.moveDown();

    }

    bool isAdjacent(Position pos) {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos) {
        return p.isSamePoint(pos);
    }

    bool kill() {
        killed = true;
        return false;
    }
    Position getPosition() {
        return p;
    }

    string getPositionInfo() {
        return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }

    string getDirectionInfo() {
        string s;
        if (direction == UP) s = "up";
        if (direction == DOWN) s = "down";
        if (direction == LEFT) s = "left";
        if (direction == RIGHT) s = "right";
        return "Player is moving at direction: " + s;
    }

    int shoot(Position wumPosition){
        if(total_shots>0){

        if(direction==UP)
            if(wumPosition.getX()==p.getX()&&wumPosition.getY()-1==p.getY())
                {--total_shots;wu.kill();return HIT;}
             else {--total_shots; return MISS;}

        else if(direction==DOWN)
            if(wumPosition.getX()==p.getX()&&wumPosition.getY()+1==p.getY())
                {--total_shots;wu.kill(); return HIT;}
            else {--total_shots; return MISS;}
        else if(direction==RIGHT)
            if(wumPosition.getX()-1==p.getX()&&wumPosition.getY()==p.getY())
                {--total_shots;wu.kill(); return HIT;}
                else {--total_shots; return MISS;}
        else if(direction==LEFT)
            if(wumPosition.getX()+1==p.getX()&&wumPosition.getY()==p.getY())
                {--total_shots;wu.kill(); return HIT;}
                else {--total_shots; return MISS;}
        }
        else return FINISH;
       // wum.showGameState();

    }


};



class WumpusWorld {

private:

    Player player;
    Wumpus wumpus;
    Position gold_position,pit_position;
    bool ended;
    Pit pit;
    int isHit;

public:

    WumpusWorld(){
        //...
    }

    WumpusWorld(int wumpus_x, int wumpus_y) {
        //...
        isHit=NORMAL;
        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(rand()%4,rand()%4);
        pit_position=Position(rand()%4,rand()%4);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y) {
        //...
        isHit=NORMAL;
        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit_position=Position(rand()%4,rand()%4);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y) {
        //...
        isHit=NORMAL;
        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit=Pit(pit_x,pit_y);
    }



    void moveForward() {
        player.moveForward();
        return showGameState();
    }

    void turnLeft() {
        player.turnLeft();
        return showGameState();
    }

    void turnRight() {
        player.turnRight();
        return showGameState();
    }

    void shoot() {
        //...
        isHit=player.shoot(wumpus.getPosition());
        showGameState();

    }

    void showGameState() {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;

        if(isHit==HIT){
            cout<<"Wumpus is killed"<<endl;
            wumpus.kill();
            isHit=NORMAL;
        }
        else if(isHit==MISS){
            cout<<"Shot Missed"<<endl;
            isHit=NORMAL;
        }
        else if(isHit==FINISH){
            cout<<"No shots available"<<endl;
            isHit=NORMAL;
        }

        if(wumpus.iskilled())   if (player.isAdjacent(wumpus.getPosition())) {
            cout << "Stench!" << endl;
        }

        if(wumpus.iskilled())  if (player.isSamePoint(wumpus.getPosition())) {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }
         if (player.isAdjacent(pit.getPosition())) {
            cout << "breez!" << endl;
        }

        if (player.isSamePoint(pit.getPosition())) {
            cout << "Player is gonna to rotten!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
       }

        if (player.isSamePoint(gold_position)) {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
        }
    }



    bool isOver() {
        return ended;
    }

};


int main()
{
    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
     wumpus_x=1;wumpus_y=2;
    gold_x=0;gold_y=2;
    pit_x=2;pit_y=1;






    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
    w.showGameState();
    while (!w.isOver()) {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1) {
            w.moveForward();
        } else if (c == 2) {
            w.turnLeft();
        } else if (c == 3) {
            w.turnRight();
        } else if (c == 4) {
            w.shoot();
        }


    }

    return 0;
}
