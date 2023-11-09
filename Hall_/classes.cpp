#include <string>
#include <iostream>
#include "time.cpp"
#include <vector>
#include <iomanip>
using namespace std;

class Seans
{
private:
    unsigned ID;

    Hall seanceHall{};
    Film seanceFilm{};

    Time_t startTime{};
    Time_t endTime{};
public:
    void setHall(Hall s_hall) {
        seanceHall = s_hall;
    }

    Hall getHall() {
        return seanceHall;
    }

    void setID(unsigned s_id) {
        ID = s_id;
    }

    unsigned getID() {
        return ID;
    }

    void setFilm(Film s_film) {
        seanceFilm = s_film;
    }

    void setStartTime(Time_t s_starttime) {
        startTime = s_starttime;
    }

    void setEndTime(Time_t s_endtime) {
        endTime = s_endtime;
    }

    Time_t getEndTime() {
        return endTime;
    }

    Time_t getStartTime() {
        return startTime;
    }

    Film getFilm() {
        return seanceFilm;
    }

};

class Day
{
private:
    string date;
    vector<Seans> seansList;
public:
    void setDate(string d_date) {
        date = d_date;
    }
    string getDate() {
        return date;
    }

    size_t getSeansListSize() {
        return seansList.size();
    }

    vector<Seans> getSeansList() {
        return seansList;
    }

    void addSeans(Seans d_seans) {
        seansList.push_back(d_seans);
    }
    Seans getSeans(int d_seansnum) {
        return seansList[d_seansnum];
    }
};

class Seat
{
private:
    unsigned price;
    char status;
public:
    void setStatus(char s_status) {
        status = s_status;
    }
    char getStatus() {
        return status;
    }

    void setPrice(unsigned s_price) {
        price = s_price;
    }
    unsigned getPrice() {
        return price;
    }
};

class Film {
private:
    string filmData[7];

    Time_t duration{};
public:

    void setFilmData(string Data[7]) {
        for (int i{}; i < 7; i++) {
            filmData[i] = Data[i];
        }
    }

    string getName() {
        return filmData[1];
    }

    void printInfo() {
        cout << left << setw(5) << filmData[0] << setw(20) << filmData[1] << setw(20) << filmData[2]
            << setw(20) << filmData[3] << setw(20) << filmData[4]
            << setw(20) << filmData[5] << '\n';
    }

    void printDescription() {
        cout << filmData[6] << '\n';
    }

    Time_t getDuration() {
        duration.setTime(0, stoul(filmData[5]) % 60, stoul(filmData[5]) / 60, 0, 0, 0);
        return duration;
    }

};

class Hall
{
private:
    unsigned ID;

    string type;
    unsigned line{};
    unsigned seat{};

    Seat** matrix{};

    string hallData[4];
public:

    unsigned getID() {
        return ID;
    }

    void setHallData(string Data[4]) {
        for (int i{}; i < 4; i++) {
            hallData[i] = Data[i];
        }
    }

    void setMatrix() { // задание матрицы мест 
        matrix = new Seat * [line] {};
        for (size_t i{}; i != line; ++i) {
            matrix[i] = new Seat[seat];
        }
    }

    unsigned getCollumns() {
        return seat;
    }

    unsigned getRows() {
        return line;
    }

    Seat** getMatrix() {
        return matrix;
    }

    ~Hall() {
        for (size_t i{}; i != line; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void SetSeat(size_t fs, size_t ls, size_t row) { // заполнение мест
        for (size_t i = fs; i <= ls; ++i) {
            matrix[row][i].setStatus('@');
        }
    }

    char GetSeatStatus(size_t i, size_t j) { // получить статус места 
        return matrix[i][j].getStatus();
    }

    size_t GetLine() { // получить число рядов 
        return line;
    }

    size_t GetSeat() { // получить число мест в каждом ряду 
        return seat;
    }

    void PrintMatrix() { // вывод матрицы мест
        for (size_t i{}; i != line; ++i) {
            for (size_t j{}; j != seat; ++j) {
                cout << matrix[i][j].getStatus() << " ";
            }
            cout << '\n';
        }
        cout << '\n';
    }

    void PrintInfo() {
        cout << left << setw(5) << hallData[0] << setw(20) << hallData[1] << setw(20) << hallData[2]
            << setw(20) << hallData[3] << '\n';
    }

    void randomFillSeats() { // рандомно сажаем людей :)
        char elems[2] = { '0', '*' };
        for (size_t i{}; i != line; ++i) {
            for (size_t j{}; j != seat; ++j) {
                matrix[i][j].setStatus(elems[rand() % 2]);
            }
        }
    }

    void SetSeat(size_t i, size_t j) { // изменить статус места 
        matrix[i][j].setStatus('@');
    }
};