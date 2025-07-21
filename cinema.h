#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Movie;
class ScreeningRoom;
class SeatRow;
class Seat; 
class ScreeningSchedule;
class Date;

class Movie {
private:
    string* title;
    int* duration;
    int* release_year;
public:
    Movie();
    Movie(const string& title, int duration, int year);
    Movie(const Movie& other);
    Movie& operator=(const Movie& other);
    ~Movie();

    friend istream& operator>> (istream& in, Movie& movie);
    friend ostream& operator << (ostream& out, const Movie& movie);
    void readFromFile(ifstream& fin);
    void writeToFile(ofstream& fout) const;

    string getTitle() const;
    int getDuration() const;
    int getReleaseYear() const;
};

 // Forward declaration
class ScreeningRoom {
private:
    string* room_name;
    int* numseats; // total seats
    int* numrow;
    vector<SeatRow*>* seatrows;
public:
    ScreeningRoom();
    ScreeningRoom(const string& name, int numseats);
    ScreeningRoom(const string& name, int numrow, int seatsPerRow);
    ScreeningRoom(const ScreeningRoom& other);
    ScreeningRoom& operator=(const ScreeningRoom& other);
    ~ScreeningRoom();

    friend istream& operator>>(istream& in, ScreeningRoom& room);
    friend ostream& operator<<(ostream& out, const ScreeningRoom& room);    
    void readFromFile(ifstream& fin);
    void writeToFile(ofstream& fout) const;

    SeatRow* getSeatRow(char rowLabel) const;
    int getNumSeat() const;
    bool isSeatReserved(const string& seatPos) const;
    bool reserveSeat(const string& seatPos);
    int countUnreservedSeats() const;
    double calculateRevenue(double basePrice) const;
    string getRoomName() const;
};

// Forward declaration
class SeatRow {
private:
    char* rowlabel;
    int* seatsPerRow;
    vector<Seat*>* seats;
public:
    SeatRow();
    SeatRow(char rowlabel, int seatsPerRow, const string& seatStatus = "available",const string& seatType = "Regular");
    SeatRow(const SeatRow& other);
    SeatRow& operator=(const SeatRow& other);
    ~SeatRow();

    friend istream& operator>>(istream& in, SeatRow& row);
    friend ostream& operator<<(ostream& out, const SeatRow& row);    
    void readFromFile(ifstream& fin);
    void writeToFile(ofstream& fout) const;

    Seat* getSeat(int seatNum) const;
    char getRowLabel() const;
    int getNumSeats() const;
    int countUnreservedSeats() const;
    double calculateRevenue(double basePrice) const;
};

class Seat {
private:
    int* seatnum;
    char* rowlabel;
    string* status; // "reserved" or "available"
    string* type;   // "Regular", "VIP", "Couple-Left", "Couple-Right"
public:
    Seat();
    Seat(int seatnum, char rowlabel, const string& status = "available", const string& type = "Regular");
    Seat(const Seat& other);
    Seat& operator=(const Seat& other);
    ~Seat();

    friend istream& operator >> (istream& in, Seat& seat);
    friend ostream& operator <<(ostream& out, const Seat& seat);
    void readFromFile(ifstream& fin);
    void writeToFile(ofstream& fout) const;

    bool isReserved() const;
    void reserve();
    string getType() const;
    int getSeatNum() const;
    char getRowLabel() const;
    void setCouplePair(Seat* pair);
    Seat* getCouplePair() const;
private:
    Seat* couplePair = nullptr;
};


class ScreeningSchedule {
private:
    Movie* movie;
    ScreeningRoom* screening_room;
    Date* start_time;
    Date* end_time;
    double* base_price;
public:
    ScreeningSchedule();
    ScreeningSchedule(Movie* movie, ScreeningRoom *room, const Date& start, double basePrice);
    ScreeningSchedule(const ScreeningSchedule& other);
    ScreeningSchedule& operator=(const ScreeningSchedule& other);
    ~ScreeningSchedule();

    friend istream& operator >> (istream &is, ScreeningSchedule & schedule);
    friend ostream& operator << (ostream &is, const ScreeningSchedule & schedule);
    void readFromFile(ifstream& fin, const vector<Movie*>& movies, const vector<ScreeningRoom*>& rooms);
    void writeToFile(ofstream& fout) const;

    void calculateEndTime();
    double getBasePrice() const;
    Movie* getMovie() const;
    ScreeningRoom* getRoom() const;
    Date* getStartTime() const;
    Date* getEndTime() const;
};

class Date {
private:
    int* day;
    int* month;
    int* year;
    int* hour;
    int* minute;
public:
    Date();
    Date(int day, int month, int year, int hour, int minute);
    Date(const string& dateStr); // "dd-MM-yyyy hh:mm"
    Date(const Date& other);
    Date& operator=(const Date& other);
    ~Date();

    friend istream& operator >> (istream& in, Date& date);
    friend ostream& operator << (ostream& out, const Date& date);
    void readFromFile(ifstream& fin);
    void writeToFile(ofstream& fout) const;

    bool isLeapYear();
    void Validate();
    void addMinutes(int minutes);
};