#include "cinema.h"

ScreeningRoom::ScreeningRoom() {
    room_name = new string("");
    numseats = new int(0);
    numrow = new int(0);
    seatrows = new vector<SeatRow*>;
}
ScreeningRoom::ScreeningRoom(const string& name, int numseats) {
    room_name = new string(name);
    this->numseats = new int(numseats);
    seatrows = new vector<SeatRow*>;
    
}
ScreeningRoom::ScreeningRoom(const string& name, int numrow, int seatsPerRow) {
    room_name = new string(name);
    numseats = new int(numrow*seatsPerRow);
    this->numrow = new int(numrow);
    seatrows = new vector<SeatRow*>;
    for(int i = 0; i < numrow; i++) {
        char label = 'A' + i;
        SeatRow* row = new SeatRow(label, seatsPerRow);
        seatrows->push_back(row);
    }
}
ScreeningRoom::ScreeningRoom(const ScreeningRoom& other) {
    room_name = new string(*other.room_name);
    numseats = new int(*other.numseats);
    numrow = new int(*other.numrow);
    seatrows = new vector<SeatRow*>;
    for(int i = 0; i < *numrow; i++){
        SeatRow* row = other.getSeatRow(i+'A');
        this->seatrows->push_back(new SeatRow(*row));  // the problem

    }
}
ScreeningRoom& ScreeningRoom::operator=(const ScreeningRoom& other) {
    if (this != & other) {
        *room_name = *other.room_name;
        *numseats = *other.numseats;
        *numrow = *other.numrow;
        for(auto seatrow: *seatrows) {
            delete seatrow;
        }
        seatrows->clear();
        for(auto seatrow: *other.seatrows) {
            this->seatrows->push_back(new SeatRow(*seatrow));
        }
    }
    return *this;
}
ScreeningRoom::~ScreeningRoom() {
    for (auto seat : *seatrows) {
        delete seat;
    }
    delete seatrows;
    delete room_name;
    delete numseats;
}



istream& operator>>(istream& in, ScreeningRoom& room) {
    string name;
    int rows, seatsPerRow;
    cout << "Enter room name: ";
    in >> name;
    cout << "Enter number of rows: ";
    in >> rows;
    cout << "Enter seats per row: ";
    in >> seatsPerRow;
    *room.room_name = name;
    *room.numseats = rows * seatsPerRow;

    // Clean up old seatrows if any
    for (auto row : *room.seatrows) delete row;
    room.seatrows->clear();

    for (int i = 0; i < rows; ++i) {
        char rowLabel = 'A' + i;
        string seatType = (rowLabel >= 'D' && rowLabel <= 'J') ? "VIP" : "Regular";
        SeatRow* row = new SeatRow(rowLabel, seatsPerRow, seatType);
        in >> *row;
        room.seatrows->push_back(row);
    }
    return in;
}

ostream& operator<<(ostream& out, const ScreeningRoom& room) {
    out << "Room name: " << *room.room_name << "\n";
    out << "Total seats: " << *room.numseats << "\n";
    out << "Seat Rows:\n";
    for (auto row : *room.seatrows) {
        out << *row;
    }
    return out;
}
void ScreeningRoom::readFromFile(ifstream& fin) {
    string name;
    int rows, seatsPerRow;
    fin >> name >> rows >> seatsPerRow;
    *room_name = name;
    *numseats = rows * seatsPerRow;

    // Clean up old seatrows if any
    for (auto row : *seatrows) delete row;
    seatrows->clear();

    for (int i = 0; i < rows; ++i) {
        char rowLabel = 'A' + i;
        string seatType = (rowLabel >= 'D' && rowLabel <= 'J') ? "VIP" : "Regular";
        SeatRow* row = new SeatRow(rowLabel, seatsPerRow, seatType);
        row->readFromFile(fin);
        seatrows->push_back(row);
        
    }
}
void ScreeningRoom::writeToFile(ofstream& fout) const {
    int rows = seatrows->size();
    int seatsPerRow = rows > 0 ? (*seatrows)[0]->getNumSeats() : 0;
    fout << *room_name << " " << rows << " " << seatsPerRow << "\n";
    for (auto row : *seatrows) {
        row->writeToFile(fout);
    }
}

int ScreeningRoom::getNumSeat() const {return *numseats;}
SeatRow* ScreeningRoom::getSeatRow(char rowLabel) const {
    for (auto row : *seatrows) {
        if (row->getRowLabel() == rowLabel) {
            return row;
        }
    }
    return nullptr;
}
// "D-4"
bool ScreeningRoom::isSeatReserved(const string& seatPos) const {
    char rowLabel = seatPos[0];
    int seatNum = stoi(seatPos.substr(2));
    for (auto row : *seatrows) {
        if (row->getRowLabel() == rowLabel) {
            Seat* seat = row->getSeat(seatNum);
            if (seat) {
                return seat->isReserved();
            }
        }
    }
    return false;
}
bool ScreeningRoom::reserveSeat(const string& seatPos) {
    char rowLabel = seatPos[0];
    int seatNum = stoi(seatPos.substr(2));
    for (auto row : *seatrows) {
        if (row->getRowLabel() == rowLabel) {
            Seat* seat = row->getSeat(seatNum);
            if (seat) {
                seat->reserve();
                return true;
            }
        }
    }
    return false;
}
int ScreeningRoom::countUnreservedSeats() const {
    int count = 0;
    for (auto row : *seatrows) {
        count += row->countUnreservedSeats();
    }
    return count;
}
double ScreeningRoom::calculateRevenue(double basePrice) const {
    double revenue = 0;
    for (auto row : *seatrows) {
        revenue += row->calculateRevenue(basePrice);
    }
    return revenue;
}
string ScreeningRoom::getRoomName() const {
    return *room_name;
}


