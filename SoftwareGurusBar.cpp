#include <iostream>
#include <cmath>

#include "SoftwareGurusBar.h"

int main(){

    unsigned int userSeats;
    cout << "Welcome to the Software Gurus Bar Simulation!" << endl;
    cout << "Enter number of seats in bar to simulate: ";
    cin >> userSeats;
    theBar.setBarSeats(userSeats);

    cout << "Starting simulation . . ." << endl;

    unsigned int t = 0;

    //Simulates 4 hours (240 minutes)
    while (t < 240){
       
        t += randBetween(2,5); //new group arrives every 2-5 minutes
     
        theSim.schedEvent(new ArriveEvent(t, randBetween(1,5))); //eventQueue filled ArriveEvents 
    }
    
    theSim.run();

    cout << "Total Profits: $" << theBar.profit << endl;

    return 0;
}

