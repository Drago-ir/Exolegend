#include <tuple>
#include <iostream>
#include <experimental/random>
#include <cmath>
#include <math.h>
#include <string>

#include "gladiator.h"
#include "Node.h"
#include "AStarNode.h"
#include "MazeStore.h"
#include "Simulator.h"

//type definitions 
struct wp{
    int i; 
    int j;
};

//global variables 
float maze_size; 
float square_size;
float wheelspeed_base = 0.2; // m/s
float max_correction_coeff = 0.95; // % of wheelspeed_base 
float kp = 0.2;
bool target_reached = false;
wp wp_array[14] = {{6,6},{7,6},{7,7},{4,7},{4,6},{5,6},{5,4},{8,4},{8,6},{9,6},{9,7},{8,7},{8,9},{5,9}};
struct wp next_waypoint = {wp_array[0].i, wp_array[0].j};
Gladiator* gladiator;
Position position;
//cout << "X:" << position.x << "  Y:" << position.y << "  A:" << position.a << "     ";
Position cposition;
double vl;
double vr;
unsigned char lifes;
double speedLimit;
unsigned char score;
MazeSquare nearestSquare;
RobotData robot_data;
wp wp_next_corner;

Node node;
bool itsMyFirstTime = true;
unsigned long startTime;

void reset();
void setup() {
    //instanciation de l'objet gladiator
    gladiator = new Gladiator();
    //enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset);
    cout << "GAME START!" << endl;
    maze_size = gladiator->maze->getSize();
    square_size = gladiator->maze->getSquareSize();

}

tuple <int, int> getPositionIndex(Position position, float squareSize){
    int i = round(position.x/squareSize - 0.5);
    int j = round(position.y/squareSize - 0.5);

    return {i,j};
}

int mazeLocation(int i, int j)
{
    return (14*i+(13-j));
}

int getPositionMazeIndex(Position position, float squareSize)
{
    int gladiatorLocationI, gladiatorLocationJ;
    std::tie(gladiatorLocationI,gladiatorLocationJ) = getPositionIndex(position, square_size);
    return (mazeLocation(gladiatorLocationI,gladiatorLocationJ));

}

tuple<int, int> inverseMazeLocation(int indx){
    return {indx/14, 13-indx%14};
}

void translateFromGladiatorToNode(){
    unsigned long translatorStartTime = millis();

    //Maze
    char maze[196] = {0};
    for (unsigned char ii=0; ii<=13; ii++)
    {
        for (unsigned char jj=0; jj<=13; jj++)
        {
            MazeSquare indexedSquare = gladiator->maze->getSquare(ii, jj);
            Coin coin = indexedSquare.coin;
            
            //CONFIGURE COINS IN MAZE

            //insert coin if not in maze already
            if (coin.value > 0 && !(maze[14*ii+(13-jj)] & COIN_MASK)){
                maze[14*ii+(13-jj)] += COIN_MASK;
                if (coin.value == 2){
                    maze[14*ii+(13-jj)] += BEAUTIFUL_COIN_MASK;
                }
                else if (coin.value == 5){
                    maze[14*ii+(13-jj)] += MARVELOUS_COIN_MASK;
                }
            }

            //or delete it if in maze although should not be
            else if (coin.value == 0 && (maze[14*ii+(13-jj)] & COIN_MASK)){
                maze[14*ii+(13-jj)] -= COIN_MASK;
                if (coin.value == 2){
                    maze[14*ii+(13-jj)] -= BEAUTIFUL_COIN_MASK;
                }
                else if (coin.value == 5){
                    maze[14*ii+(13-jj)] -= MARVELOUS_COIN_MASK;
                }
            }

            //CONFIGURE WALLS

            //if we can go up if not in maze already
            if (indexedSquare.northSquare != NULL && !(maze[14*ii+(13-jj)] & UP_MASK))
                maze[14*ii+(13-jj)] += UP_MASK;
            //if we can go down if not in maze already
            if (indexedSquare.southSquare != NULL && !(maze[14*ii+(13-jj)] & DOWN_MASK))
                maze[14*ii+(13-jj)] += DOWN_MASK;
            //if we can go left if not in maze already
            if (indexedSquare.westSquare != NULL && !(maze[14*ii+(13-jj)] & LEFT_MASK))
                maze[14*ii+(13-jj)] += LEFT_MASK;
            //if we can go right if not in maze already
            if (indexedSquare.eastSquare != NULL && !(maze[14*ii+(13-jj)] & RIGHT_MASK))
                maze[14*ii+(13-jj)] += RIGHT_MASK;

            //cout << "I'm running since " << elapsed << " milliseconds" << endl;
            //cout << node.gasClosures << " closures of the gas since start of the game and " << realTimeUntilGasClosing << " ms until next closures." << endl;

        }
    }

    //CONFIGURE GAS
    unsigned long elapsed = millis() - startTime;
    int previousGasClosures = node.gasClosures;
    node.gasClosures = elapsed/(20*1000);
    //cout << "gas closure is " << node.gasClosures << endl;
    //if gas just closed, run warzone
    if (previousGasClosures != node.gasClosures){
        //cout << "I read this LIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIINE" << endl;
        node.warzone();
    }

    unsigned long realTimeUntilGasClosing = 20*1000 - elapsed%(20*1000);
    //TODO : re-evaluate the 10 in line below (current assumption is 10 moves are possible within 20 sec)
    int movesUntilGasClosing = 8*realTimeUntilGasClosing/20000;
    //cout << movesUntilGasClosing << endl;
    /*
    if (movesUntilGasClosing < 3){
        movesUntilGasClosing = 0;
        cout << "Decreased value of moves until gas closing" << movesUntilGasClosing << endl;
    }
    */
    //gladiator->log("Test");
    //node.printNode();


    //CONFIGURE ROBOTS
    
    float squareSize = gladiator->maze->getSquareSize();
    GoraneRobot goraneRobots[NB_OF_ROBOTS_PER_TEAMS];
    GoraneRobot enemyRobots[NB_OF_ROBOTS_PER_TEAMS];

    //Retrieve data for ...
    //...my Robot
    RobotData data = gladiator->robot->getData();
    uint8_t myTeamId = data.teamId;
    uint8_t myId = data.id;
    Position myPosition = data.position;
    int myI,myJ;
    std::tie(myI,myJ) = getPositionIndex(myPosition,squareSize);
    goraneRobots[0] = GoraneRobot{mazeLocation(myI,myJ), data.score, true};

    //...other Robots
    RobotList robotList = gladiator->game->getPlayingRobotsId();
    int fooCount = 0;
    for (int ii = 0; ii<4; ii++)
    {
        RobotData robotData = gladiator->game->getOtherRobotData(robotList.ids[ii]);
        //check robot has a valid id (and it's not us)
        if (robotData.id != 0 && robotData.id != myId){
            if(robotData.teamId == myTeamId){
                //this robot is my friend !
                Position friendPos = robotData.position;
                int friendI,frienJ;
                std::tie(friendI,frienJ) = getPositionIndex(friendPos,squareSize);
                goraneRobots[1] = GoraneRobot{mazeLocation(friendI,frienJ), robotData.score, robotData.lifes!=0};
                //cout << "Coucou je suis quand meme venu passer ici pour te casser les couilles ptt salope !" << endl;
            }
            else{
                RobotData fooData = gladiator->game->getOtherRobotData(robotList.ids[ii]);
                Position fooPos = fooData.position;
                int fooI, fooJ;
                std::tie(fooI,fooJ) = getPositionIndex(fooPos,squareSize);
                enemyRobots[fooCount] = GoraneRobot{mazeLocation(fooI,fooJ), robotData.score, robotData.lifes!=0};
                if (fooCount < 1)
                    fooCount++;
                }
        }
        else{
            //gladiator->log("Missing Robots in the maze !");
        }
    }

    //CONFIGURE TEAMS
    Team goraneTeam(goraneRobots);
    Team enemyTeam(enemyRobots);

    Team teams[NB_OF_TEAMS];

    teams[GORANE_TEAM] = goraneTeam;
    teams[ENEMY_TEAM] = enemyTeam;

    node = Node(maze, teams, ENEMY_TEAM, movesUntilGasClosing);

    //TEAM & ROBOT TAKING ITS TURN
    //it's always our turn for the start !
    node.teamTakingItsTurn = GORANE_TEAM;
    node.teams[GORANE_TEAM].robotTakingItsTurn = false;

    unsigned long elapsedTimeInTranslator = millis() - translatorStartTime;
    //cout << "Spent " << elapsedTimeInTranslator << " ms translating !" << endl;

}

wp get_next_waypoint(){
    wp wp_next_target;
    int arraysize = 14;
    for (int index = 0; index < arraysize; index++){
        if(wp_array[index].i != -1){
            wp_next_target.i = wp_array[index].i; 
            wp_next_target.j = wp_array[index].j;
            wp_array[index].i = -1;
            wp_array[index].j = -1;
            //cout << "wp_next_target=(" << wp_next_target.i << "," << wp_next_target.j << ")";
            
            //find next corner from here (arraysize-2 to be able to look two steps forward)
            for (int index_cornersearch = index; index_cornersearch < arraysize-2; index_cornersearch++){
                if((wp_array[index_cornersearch].i != wp_array[index_cornersearch+2].i) && (wp_array[index_cornersearch].j != wp_array[index_cornersearch+2].j)){
                    //found a corner @ index_cornersearch + 1 (only after a corner both components (i and j) of tile x and tile x + 2 are different)
                    //cout << wp_array[index_cornersearch].i << "," << wp_array[index_cornersearch+2].i << ";" << wp_array[index_cornersearch].j << "," << wp_array[index_cornersearch+2].j;
                    wp_next_corner.i = wp_array[index_cornersearch+1].i;
                    wp_next_corner.j = wp_array[index_cornersearch+1].j;
                    //cout << "wp_next_corner=(" << wp_next_corner.i << "," << wp_next_corner.j << ")"<< endl;
                    break;
                }
            }
            break;
        }
    }
    return wp_next_target; 

}

inline float moduloPi(float a) // return angle in [-pi; pi]
{
    return (a < 0.0) ? (std::fmod(a - M_PI, 2*M_PI) + M_PI) : (std::fmod(a + M_PI, 2*M_PI) - M_PI);
}

float ind2dec(int ind, float square_size){
    return (ind + 0.5) * square_size;
}

void get_fresh_data(){
    robot_data = gladiator->robot->getData();
    position = robot_data.position;
    //cout << "X:" << position.x << "  Y:" << position.y << "  A:" << position.a << "     ";
    cposition = robot_data.cposition;
    vl = robot_data.vl; // vitesse roue gauche
    vr = robot_data.vr; // vitesse roue droite
    lifes = robot_data.lifes;
    speedLimit = robot_data.speedLimit;
    score = robot_data.score;
    nearestSquare = gladiator->maze->getNearestSquare();

}

void on_target_tile(){
    target_reached = true; 
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0); //controle de la roue droite
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0); //control de la roue gauche

    //code de votre stratégie
    //TODO : encapsulate code once fully developped
    //--------------------------------------------------------------------------
    //translate gladiator into node in order to have latest update of the maze !
    translateFromGladiatorToNode();
    int selectedIndex;
    AStarNode buffNode = AStarNode(node, nullptr, 0, true);
    buffNode.killAllRobotExceptOneTakingTurn();
    std::tie(std::ignore, selectedIndex) = buffNode.runAStar();
    //cout << "Target reached" << endl;
    //if A star returns no solution, move to center
    if (selectedIndex == -1){
        cout << "Astar did not find a solution." << endl;
        int goraneLocationI, goraneLocationJ;
        std::tie(goraneLocationI,goraneLocationJ) = inverseMazeLocation(node.teams[GORANE_TEAM].robots[GORANE1_INDEX].location);
        int absI = abs(7-goraneLocationI);
        int absJ = abs(7-goraneLocationJ);
        if (absI > absJ){
            if(goraneLocationI<7){
                selectedIndex = 3;
            } else{
                selectedIndex = 4;
            }
        }else{
            if (goraneLocationJ<7){
                selectedIndex = 2;
            } else{
                selectedIndex = 1;
            }
        }

        cout << "The selected Index : " << selectedIndex << endl;
        buffNode.getDescendanceSize();
        buffNode.setToNextLegalChildIndex(&selectedIndex);
    }

    int nextWayPoint = node.teams[GORANE_TEAM].robots[GORANE1_INDEX].location + buffNode.getLocationIncrement(selectedIndex);
    //cout << "Node says selectedIndex is " << selectedIndex << endl;
    int nextWayPointI, nextWayPointJ;

    std::tie(nextWayPointI,nextWayPointJ) = inverseMazeLocation(nextWayPoint);

    //--------------------------------------------------------------------------

    //NOTE : debug
    int goraneLocationI, goraneLocationJ;
    std::tie(goraneLocationI,goraneLocationJ) = inverseMazeLocation(node.teams[GORANE_TEAM].robots[GORANE1_INDEX].location);
    //cout << "Node thinks we are in I: " <<  goraneLocationI << " and J: " << goraneLocationJ << endl;

    RobotData goraneData = gladiator->robot->getData();
    int gladiatorLocationI, gladiatorLocationJ;
    std::tie(gladiatorLocationI,gladiatorLocationJ) = getPositionIndex(goraneData.position, square_size);
    cout << "Gladiator is in I: " <<  gladiatorLocationI << " and J: " << gladiatorLocationJ << endl;

    next_waypoint = wp{nextWayPointI, nextWayPointJ};
    //next_waypoint = get_next_waypoint();
    cout << "Next WP = ("<< next_waypoint.i << "," << next_waypoint.j<<") " << endl;
}

float calc_angular_error(){
    wp delta;
    delta.i = next_waypoint.i - nearestSquare.i;
    delta.j = next_waypoint.j - nearestSquare.j;
    float delta_x = ind2dec(next_waypoint.i, square_size) - position.x; 
    float delta_y = ind2dec(next_waypoint.j, square_size) - position.y;
    float target_direction = atan2(delta_y,delta_x);

    //cout << "orientation="<< position.a<<"  target direction=" << target_direction; 
    float error = moduloPi(target_direction-position.a); 
    return error;
}

void reset() {
    //fonction de reset:
    //initialisation de toutes vos variables avant le début d'un match
    gladiator->log("Appel de la fonction de reset");

}

void loop() {
    if(gladiator->game->isStarted()){

        unsigned long startTimeInLoop = micros();

        //test if it's first time we loop
        if(itsMyFirstTime){
            itsMyFirstTime = false;
            startTime = millis();
            on_target_tile();
        }

        get_fresh_data();
    
        if(nearestSquare.i == next_waypoint.i && nearestSquare.j == next_waypoint.j){
            on_target_tile(); //if we're on the target tile, stop and get next waypoint
        }

        else{
        float error = calc_angular_error(); //get bot orientation, target direction and calculate angular error
        //wheelspeed = wheelspeed_base / error 
        // start movement and correct delta motorspeed proportionnally to current angular error
        
        float wheelspeed_r = max(min(wheelspeed_base + kp * error,wheelspeed_base),wheelspeed_base-max_correction_coeff); // we only slow down motor speed to facilitate sharp turns (larger turn radius)
        float wheelspeed_l = max(min(wheelspeed_base - kp * error,wheelspeed_base),wheelspeed_base-max_correction_coeff);
    

        //cout << "  ctrl_error = " << error << "  wheelspeed = " << "(" << wheelspeed_l << "," << wheelspeed_r << ")" << endl; 
        //cout << "wheelspeed_r = " << wheelspeed_r << "   wheelspeed_l = " << wheelspeed_l << endl; 

        gladiator->control->setWheelSpeed(WheelAxis::RIGHT, wheelspeed_r); //controle de la roue droite
        gladiator->control->setWheelSpeed(WheelAxis::LEFT, wheelspeed_l); //control de la roue gauche

        //TODO : to crunch depending on time spent in run a star
        unsigned long timeInLoop = micros() - startTimeInLoop;
        //cout << "we took " << (int) timeInLoop <<" ms to loop" << endl;
            
        
        if (node.maze[mazeLocation(nearestSquare.i,nearestSquare.j)] & GAS_MASK)
        {
            //FonctionHalleux(wp{7,7});
            cout << " Gaz, Gaz, Gaz !!!" << endl;
        }


        if (timeInLoop < 100*1000)
            delay(100 - timeInLoop/1000);
        }
    }

    else {
        gladiator->log("Le jeu n'a pas encore commencé");
    }
    delay(3);
}