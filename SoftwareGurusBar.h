#ifndef SOFTWAREGURUSBAR_H
#define SOFTWAREGURUSBAR_H

#include "event.h"
using namespace std;


//For weightedProbability, change all randBewteen to weightedProb

//Simulates typical bar activity and profit based on number of seats
class SoftwareGurusBar{
public: 
    SoftwareGurusBar(){
        freeChairs = 50; //default number of chairs 
        profit = 0;
    }
    bool canSeat(unsigned int numOfPeople);
    void order(unsigned int beerType);
    void leave(unsigned int numOfPeople);
    void setBarSeats(int userSeats){freeChairs = userSeats;}
    std::vector<unsigned int> beerProbs(); //weights for weighted probability function 

    unsigned int freeChairs;
    double profit;
};

class ArriveEvent : public Event{
public:
    ArriveEvent(unsigned int time, unsigned int gs) : Event(time), groupSize(gs){  }
    void processEvent();
private:
    unsigned int groupSize;
};
 

class OrderEvent : public Event{
public:
    OrderEvent(unsigned int time, unsigned int gs) : Event(time), groupSize(gs) { }
    void processEvent();
private:
    unsigned int groupSize;
};

class LeaveEvent : public Event{
public:
    LeaveEvent(unsigned int time, unsigned int gs) : Event(time), groupSize(gs){ }
    void processEvent();
private:
    unsigned int groupSize;
};

SoftwareGurusBar theBar;
SimulationFramework theSim;


//SoftwareGurusBar 
bool SoftwareGurusBar::canSeat (unsigned int numOfPeople){

    cout << numOfPeople << " arrive at " << theSim.currentTime << endl;
    if (numOfPeople < freeChairs){
        cout << numOfPeople << " seated" << endl;
        freeChairs -= numOfPeople;
        return true;
    }else{
        cout << "No room, group leaves" << endl;
        return false;
    }
}

void SoftwareGurusBar::order (unsigned int beerType){

    cout << beerType << " ordered at" << theSim.currentTime << endl;
    cout << "Current profit is $";
    switch(beerType){
        case 1: cout << profit + 2.0 << endl; //local beer
        case 2: cout << profit + 3.0 << endl; //imported beer
        case 3: cout << profit + 4.0 << endl; //special beer
    }

}

void SoftwareGurusBar::leave (unsigned int numOfPeople){

    cout << numOfPeople << " leave at " << theSim.currentTime << endl;
    freeChairs += numOfPeople;
    
}

std::vector<unsigned int> SoftwareGurusBar::beerProbs(){
    vector<unsigned int> beerVector;
    beerVector.push_back(15);
    beerVector.push_back(60);
    beerVector.push_back(25);
    return beerVector;
}

//ArriveEvent 
void ArriveEvent::processEvent(){
    if (theBar.canSeat(groupSize)){
        theSim.schedEvent(new OrderEvent(theSim.currentTime + randBetween(2, 10), groupSize));
    }
}

//OrderEvent 
void OrderEvent:: processEvent(){
    for (int i = 0; i < groupSize; i++){
        theBar.order(randBetween(1,3));
    }
    int t = theSim.currentTime + randBetween(15, 35);
    theSim.schedEvent(new LeaveEvent(theSim.currentTime + randBetween(30, 60), groupSize));
}

//LeaveEvent 
void LeaveEvent::processEvent(){
    theBar.leave(groupSize);
}

#endif //SoftwareGurusBar, ArriveEvent, OrderEvent, LeaveEvent