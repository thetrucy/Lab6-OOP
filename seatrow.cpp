#include "cinema.h"

SeatRow::SeatRow() {
    rowlabel = new char('A');
    seatsPerRow = new int(0);
    seats = new vector<Seat*>;
}
SeatRow::SeatRow(char rowlabel, int seatsPerRow, const string& seatStatus, const string& seatType) {
    this->rowlabel = new char(rowlabel);
    this->seatsPerRow = new int(seatsPerRow);
    this->seats = new vector<Seat*>;
    for(int i = 0; i < seatsPerRow; i++) {
        Seat* seat = new Seat(i+1, rowlabel);
        seats->push_back(seat);
    }
}
SeatRow::SeatRow(const SeatRow& other) {
    rowlabel = new char(*other.rowlabel);
    seatsPerRow = new int(*other.seatsPerRow);
    seats = new vector<Seat*>;
    for (auto seat : *other.seats) {
        seats->push_back(new Seat(*seat));
    }
}
SeatRow& SeatRow::operator=(const SeatRow& other) {
    if(this != &other) {
        delete rowlabel;
        delete seatsPerRow;
        for (auto seat : *seats) {
            delete seat;
        }
        seats->clear();

        rowlabel = new char(*other.rowlabel);
        seatsPerRow = new int(*other.seatsPerRow);
        for (auto seat : *other.seats) {
            seats->push_back(new Seat(*seat));
        }
    }
    return *this;
}

SeatRow::~SeatRow() {
    for (auto seat : *seats) {
        delete seat;
    }
    delete seats;
    delete rowlabel;
    delete seatsPerRow;
}

istream& operator>>(istream& in, SeatRow& row) {
    int seatsPerRow;
    cout << "Enter number of seats for row " << *row.rowlabel << ": ";
    in >> seatsPerRow;
    *row.seatsPerRow = seatsPerRow;
    
    for (auto seat : *row.seats) delete seat;
    row.seats->clear();
    for (int i = 0; i < seatsPerRow; ++i) {
        Seat* seat = new Seat(i, *row.rowlabel);
        in >> *seat;
        row.seats->push_back(seat);
    }
    
    return in;
}

ostream& operator<<(ostream& out, const SeatRow& row) {
    out << "Row " << *row.rowlabel << ": ";
    for (auto seat : *row.seats) {
        out << seat->getSeatNum() << "(" << seat->getType() << "," << (seat->isReserved() ? "R" : "A") << ") ";
    }
    out << "\n";
    return out;
}

Seat* SeatRow::getSeat(int seatNum) const { return seats->at(seatNum); }
char SeatRow::getRowLabel() const {return *rowlabel;}
int SeatRow::getNumSeats() const {return seats->size();}
int SeatRow::countUnreservedSeats() const {
    int count = 0;
    for (auto seat : *seats) {
        if (seat->getType() == "Couple-Left") {
            if (!seat->isReserved() && seat->getCouplePair() && !seat->getCouplePair()->isReserved()) {
                count += 2; // Both seats are available
            }
        } else if (seat->getType() == "Couple-Right") {
            continue; // Already counted with Couple-Left
        } else {
            if (!seat->isReserved()) count++;
        }
    }
    return count;
}
double SeatRow::calculateRevenue(double basePrice) const {
    double revenue = 0.0;
    for (auto seat: *seats) {
        if(seat->getType() == "Regular")
            revenue += basePrice;
        else if (seat->getType() == "VIP")
            revenue += basePrice + 20000;
        else if (seat->getType() == "Couple-Left")
            revenue += 2* (basePrice + 20000);
    }   
    return revenue;
}
void SeatRow::readFromFile(ifstream& fin) {
    int seatsPerRow;
    fin >> seatsPerRow;
    for (auto seat : *seats) delete seat;
    seats->clear();
    for (int i = 0; i < seatsPerRow; ++i) {
        Seat* seat = new Seat();
        seat->readFromFile(fin);
        seats->push_back(seat);
    }
}
void SeatRow::writeToFile(ofstream& fout) const {
    fout << seats->size() << "\n";
    for (auto seat : *seats) seat->writeToFile(fout);
}

