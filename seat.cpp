#include "cinema.h"

Seat::Seat() {
    seatnum = new int(0);
    rowlabel = new char('A');
    status = new string ("available");
    type = new string ("Regular");
}
Seat::Seat(int seatnum, char rowlabel,const string& status, const string& type) {
    this->seatnum = new int(seatnum);
    this->rowlabel = new char(rowlabel);
    this->status = new string(status);
    this->type = new string (type);
}
Seat::Seat(const Seat& other) {

    seatnum = new int (*other.seatnum);
    rowlabel = new char(*other.rowlabel);
    status = new string(*other.status);
    type = new string(*other.type);

}
Seat& Seat::operator=(const Seat& other) {
    if(this != &other) {
        *seatnum = *other.seatnum;
        *rowlabel = *other.rowlabel;
        *status = *other.status;
        *type = *other.type;
    }
    return *this;
}
Seat::~Seat() {
    delete seatnum;
    delete rowlabel;
    delete status;
    delete type;
}

istream& operator >>(istream& in, Seat& seat) {
    int seatnum;
    char row;
    string t;
    cout << "Enter seatnum: ";
    in >> seatnum;
    cout << "Enter row label: ";
    in >> row;
    cout << "Enter type: ";
    in >> t;
    in.ignore();
    *seat.seatnum = seatnum;
    *seat.rowlabel = row;
    *seat.type = t;

    return in;
}
ostream& operator <<(ostream& out, const Seat& seat) {
    out << "Seat Pos: " << *seat.rowlabel << "-" << *seat.seatnum << endl;
    return out;
}
Seat* Seat::getCouplePair() const { return couplePair; }
void Seat::setCouplePair(Seat* pair) { couplePair = pair; }

void Seat::readFromFile(ifstream& fin) {
    int sn;
    char rl;
    string st, tp;
    fin >> sn >> rl >> st >> tp;
    *seatnum = sn;
    *rowlabel = rl;
    *status = st;
    *type = tp;
}
void Seat::writeToFile(ofstream& fout) const {
    fout << *rowlabel << "-"<< *seatnum << " " << *status << " " << *type << "\n";
}

bool Seat::isReserved() const {
    return *status == "reserved";
}
void Seat::reserve() {
    if(!this) return;
    *status = "reserved";
}

string Seat::getType() const {return *type;}
int Seat::getSeatNum() const {return *seatnum;}
char Seat::getRowLabel() const {return *rowlabel;}