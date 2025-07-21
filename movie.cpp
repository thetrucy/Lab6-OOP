
#include "cinema.h"


// Movie class implementation
Movie::Movie() {
    title = new string("");
    duration = new int(0);
    release_year = new int(0);
}

Movie::Movie(const string& t, int d, int y) {
    title = new string(t);
    duration = new int(d);
    release_year = new int(y);
}

Movie::Movie(const Movie& other) {
    title = new string(*other.title);
    duration = new int(*other.duration);
    release_year = new int(*other.release_year);
}

Movie& Movie::operator=(const Movie& other) {
    if (this != &other) {
        if (!title) title = new string();
        if (!duration) duration = new int();
        if (!release_year) release_year = new int();
        *title = *other.title;
        *duration = *other.duration;
        *release_year = *other.release_year;
    }
    return *this;
}

Movie::~Movie() {
    delete title;
    delete duration;
    delete release_year;
}

istream& operator>>(istream& in, Movie& movie) {
    string t;
    int d, y;
    cout << "Enter title: ";
    getline(in, t);
    cout << "Enter duration (minutes): ";
    in >> d;
    cout << "Enter release year: ";
    in >> y;
    in.ignore();
    *movie.title = t;
    *movie.duration = d;
    *movie.release_year = y;

    return in;
}

ostream& operator<<(ostream& out, const Movie& movie) {
    if (!movie.title || !movie.duration || !movie.release_year) {
        out << "Invalid Movie object\n";
        return out;
    }
    out << "Title: " << *movie.title << endl;
    out << "Duration: " << *movie.duration << " minutes" << endl;
    out << "Release Year: " << *movie.release_year << endl;
    return out;
}

void Movie::readFromFile(ifstream& fin) {
    getline(fin, *title);
    fin >> *duration;
    fin >> *release_year;
    fin.ignore();
}

void Movie::writeToFile(ofstream& fout) const {
    fout << *title << endl;
    fout << *duration << endl;
    fout << *release_year << endl;
}

string Movie::getTitle() const { return *title; }
int Movie::getDuration() const { return *duration; }
int Movie::getReleaseYear() const { return *release_year; }