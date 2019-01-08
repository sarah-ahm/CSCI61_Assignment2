#ifndef EVENT_H
#define EVENT_H

#include "minPQ.h" //minPQ
using namespace std;

//Abstract base class for derived classes of concrete events 
//Derived class objects will be used to fill the SimulationFramework priority queue
class Event : public minPQ<Event>{
public: 
    Event (unsigned int t) {time = t;}
    unsigned int time;
    //Describes how Event will be processes. Defined in derived classes.
    virtual void processEvent() { }
    bool compare(Event* x, Event* y) {return x->time > y->time;} //compares Event and derived class objects based on time value 
};

//Framework for Event objects 
//Runs a simulation based on priority queue and type-specific processEvent()
class SimulationFramework{
public: 
    SimulationFramework() {currentTime = 0;}
    //Adds new Event object to priority queue
    void schedEvent(Event *newEvent){
        eventQueue.insert(*newEvent);  
    }
    //Processes events until eventQueue is empty
    void run();
    //Events are produced based on their probability rather than randomly
    int weightedProbability(vector<unsigned int> probs, vector<unsigned int> results);
    unsigned int currentTime;
private:
    minPQ<Event> eventQueue;
};


void SimulationFramework::run(){
    while(!eventQueue.isEmpty()){
        Event nextEvent = eventQueue.getMin( ); //get next event 
        eventQueue.deleteMin( ); //delete event from eventQueue
        currentTime = nextEvent.time; //update time
        nextEvent.processEvent( ); //process event using late-binding
    }
}

int SimulationFramework::weightedProbability(unsigned int probs[], unsigned int results[]){

    int sum = probs[0] + probs[1] + probs[3];

    int randNum = rand() % sum;
 
    switch(randNum){
        case randNum < probs[0]: return results[0];
        case randNum <= (probs[1] + probs[2]): return results[1];
        default: return results[2];
    }
}

#endif