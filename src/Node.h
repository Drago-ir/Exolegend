#ifndef NODE_H
#define NODE_H

//#include "Constants.h"
#include <cmath>
#include "gladiator.h"

using namespace std;

//NOTE : this constants needs to be adapted everytime a simulation from another maze size launched !
static constexpr int NB_OF_MAZE_SQUARES = 196;//196 or 36

static constexpr int MAZE_WIDTH = sqrt(NB_OF_MAZE_SQUARES);
static constexpr int BRANCHING_FACTOR = 5;
static constexpr int NB_OF_TEAMS = 2;
static constexpr int NB_OF_ROBOTS_PER_TEAMS = 2;
static constexpr int INT_DUMMY_VALUE = -1;
static constexpr char CHAR_DUMMY_VALUE = -1;
static constexpr char GORANE_TEAM = true;
static constexpr char ENEMY_TEAM = false;
static constexpr double MAX_NODE_VALUE = 1.0;
static constexpr double MIN_NODE_VALUE = 0.0;
static constexpr double DRAW_NODE_VALUE = 0.5;
static constexpr char UP_MASK = 1;
static constexpr char RIGHT_MASK = 2;
static constexpr char DOWN_MASK = 4;
static constexpr char LEFT_MASK = 8;
static constexpr char COIN_MASK = 16;
//beautiful coin mask is a coin of value 2
static constexpr char BEAUTIFUL_COIN_MASK = 64;
//marvelous coin mask is a coin of value 5
static constexpr char MARVELOUS_COIN_MASK = 128;
static constexpr char GAS_MASK = 32;//gas mask... lol, #warzone

//parameters 4 robots
static constexpr char GORANE1_INDEX = 0;
static constexpr char GORANE2_INDEX = 1;
static constexpr char ENEMY1_INDEX = 0;
static constexpr char ENEMY2_INDEX = 1;

struct GoraneRobot{
    int location = 0;
    int coinNb = 0;
    bool isAlive = false;
    int previousLocation = -1000;
    bool cannotTurnBack = false;
};

class Team{
    public :
        //create a team with 2 robots
        GoraneRobot robots[NB_OF_ROBOTS_PER_TEAMS];
        int coinNb = 0;
        bool isAlive = false;
        bool robotTakingItsTurn = false;

    public :
    Team(GoraneRobot *paramRobots){
        for(int i=0; i < NB_OF_ROBOTS_PER_TEAMS; i++){
            this->robots[i] = paramRobots[i];
        }
        updateCoins();
        updateLives();
    }
    
    Team(){
        for(int i=0; i < NB_OF_ROBOTS_PER_TEAMS; i++){ 
            struct GoraneRobot defaultRobot = {0, 0, true};
            this->robots[i] = defaultRobot;
        }
    }

    void updateCoins(){
        int count = 0;
        for(int i = 0; i < NB_OF_ROBOTS_PER_TEAMS; i++){
            count += this->robots[i].coinNb;
        }
        this->coinNb = count;
    }

    void updateLives(){
        bool allRobotsDead = true;
        for(int i = 0; i < NB_OF_ROBOTS_PER_TEAMS; i++){
            if (this->robots[i].isAlive)
                allRobotsDead = false;
        }
        this->isAlive = !allRobotsDead;
    }
};

class Node
{   public :
        char maze[NB_OF_MAZE_SQUARES] = {0};
        Team teams[NB_OF_TEAMS];
        bool teamTakingItsTurn;
        int timeUntilGasClosing;
        int gasClosingInterval;
        int gasClosures = 0;
        int coinsOnGround = -1;

        bool isCombatOngoing = false;
        bool robotsInCombat[2] = {false, false};
        

    public :
        //default constructor with no parameter
        Node();
        //default constructor, when no info about parent nor children
        Node(char *paramMaze, Team *paramTeams, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing);
        //copy constructor
        Node(const Node &rhs);

        //for the moment, not a constructor. it will be in some hours !
        void translateGladiatorToNode(Gladiator *pGladiator);

        int getDescendanceSize();
        void setToNextLegalChildIndex(int *pChildIndex);
        int getLocationIncrement(char childIndex);

        void configureChild(char childIndex);

        void configureRobotsLocationInChildNode(int locationIncrement);
        void configureCoinsInChildNode();
        void configureTimeInChildNode();
        void configureGasInChildNode();
        void warzone();
        void configureRobotsLivesInChildNode();
        void configureRobotTakingTurnInChildNode();

        void countCoinsOnGround();
        bool isTerminal();
        bool areAllRobotsDead();
        double evaluate();
        double getNodeValue();
        bool isSquareInTheGas(int location);
        void printNode();
        void killAllRobotExceptOneTakingTurn();
};

#endif
