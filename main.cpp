#include "cinema.h"


int main() {
    // Create a sample movie
    Movie movie1("Sample Movie1", 120, 2024);
    Movie* movie = new Movie("Sample Movie", 120, 2024);



    // Create a screening room with 10 rows (A-J), 10 seats per row
    ScreeningRoom room1("Room 1", 10, 10);
    ScreeningRoom* room = new ScreeningRoom("Room 1", 10, 10);
    //cout << room1;
    ScreeningRoom room2 = ScreeningRoom(*room);
    cout <<  room2;
    
    // ofstream fout("room.txt");
    // room1.writeToFile(fout);
    // fout.close();
    // ifstream fin("room.txt");
    // room1.readFromFile(fin);
    // fin.close();
    // Create a screening schedule

    Date startTime(21, 11, 2021, 13, 30);
    cout << startTime;

    // Output the screening schedule
    double basePrice = 100000; // VND
    ScreeningSchedule* schedule = new ScreeningSchedule(movie, room, startTime, basePrice);
    cout << *schedule;
    

    // Clean up
    // delete schedule;
    // delete movie;
    // delete room;

    return 0;
}
