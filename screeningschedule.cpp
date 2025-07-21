#include "cinema.h"

ScreeningSchedule::ScreeningSchedule() {
    movie = new Movie();
    screening_room = new ScreeningRoom();
    start_time = new Date();
    end_time = new Date();
    base_price = new double(0);
}

ScreeningSchedule::ScreeningSchedule(Movie* m, ScreeningRoom* r, const Date& start, double basePrice) {
    movie = m;
    //cout<<r->getSeatRow('B');
    screening_room = new ScreeningRoom(*r);
    cout<<"running"<<endl;
    start_time = new Date(start);
    end_time = new Date(start);
    end_time->addMinutes(movie->getDuration());

    base_price = new double(basePrice);
    cout<<"schedule created\n";
}

ScreeningSchedule::ScreeningSchedule(const ScreeningSchedule& other) {
    movie = new Movie(*other.movie);
    screening_room = new ScreeningRoom(*other.screening_room);
    start_time = new Date(*other.start_time);
    end_time = new Date(*other.end_time);
    base_price = new double(*other.base_price);
}

ScreeningSchedule& ScreeningSchedule::operator=(const ScreeningSchedule& other) {
    if (this != &other) {
        movie = other.movie;
        screening_room = other.screening_room;
        *start_time = *other.start_time;
        *end_time = *other.end_time;
        *base_price = *other.base_price;
    }
    return *this;
}

ScreeningSchedule::~ScreeningSchedule() {
    delete movie;
    delete screening_room;
    delete start_time;
    delete end_time;
    delete base_price;
}
/*
void ScreeningSchedule::input(istream& in) {
    // Implement as needed
}*/

istream& operator>>(istream& in, ScreeningSchedule& schedule) {
    // Implement as needed
    return in;
}

ostream& operator<<(ostream& out, const ScreeningSchedule& schedule) {
    out << "Movie: " << schedule.movie->getTitle() << "\n";
    out << "Room: " << schedule.screening_room->getRoomName() << "\n";
    out << "Start: " << *schedule.start_time << "\n";
    out << "End: " << *schedule.end_time << "\n";
    out << "Base Price: " << *schedule.base_price << "\n";
    return out;
}

void ScreeningSchedule::readFromFile(ifstream& fin, const vector<Movie*>& movies, const vector<ScreeningRoom*>& rooms) {
    // Implement as needed
}

void ScreeningSchedule::writeToFile(ofstream& fout) const {
    fout << movie->getTitle() << endl;
    fout << screening_room->getRoomName() << endl;
    fout << start_time << endl;
    fout << end_time << endl;
    fout << *base_price << endl;
}



double ScreeningSchedule::getBasePrice() const { return *base_price; }
Movie* ScreeningSchedule::getMovie() const { return movie; }
ScreeningRoom* ScreeningSchedule::getRoom() const { return screening_room; }
Date* ScreeningSchedule::getStartTime() const { return start_time; }
Date* ScreeningSchedule::getEndTime() const { return end_time; }
