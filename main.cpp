#include "cinema.h"


int main() {
    // Create a sample movie
    Movie movie1("Sample Movie1", 120, 2024);
    Movie* movie = new Movie("Sample Movie", 120, 2024);


    Seat* seat1 = new Seat(1, 'A');
    Seat seat2 = Seat(*seat1);
    cout << seat2; // good

    SeatRow* row1 = new SeatRow('A',3);
    SeatRow row2 = SeatRow(*row1);
    cout << row2; // good
    
    // Create a screening room with 10 rows (A-J), 10 seats per row
    // ScreeningRoom room1("Room 1", 10, 10);
    ScreeningRoom room1("Room 1", 3, 2);
    cout << room1; //good
    ScreeningRoom* room = new ScreeningRoom("Room 1", 3, 2);
    cout << *room; //good
    ScreeningRoom room2 = ScreeningRoom(*room);
    cout <<  room2;
    
    ofstream fout("room.txt");
    room1.writeToFile(fout);
    fout.close();
    ifstream fin("room.txt");
    room1.readFromFile(fin);
    fin.close();
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
