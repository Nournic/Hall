#include <string>
#include <iostream>
#include "time.cpp"
#include <vector>
#include <iomanip>
using namespace std;

class Seat {
private:
    unsigned price_seat{ 0 };
    bool vip_status{ false };
    char status_seat{ '0' };

public:

    void setStatus(char status) {
        status_seat = status;
    }

    char getStatus() {
        return status_seat;
    }

    void setVip() {
        vip_status = true;
    }

    bool getVip() {
        return vip_status;
    }

    void setPrice(unsigned price) {
        price_seat = price;
    }

    int getPrice() {
        return price_seat;
    }

};

class Film {
private:
    string name{};
    Time_t start{};
    Time_t end{};
    Time_t duration_film{};
    string genre{};

public:
    void setStart(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 1, unsigned months = 1, unsigned years = 1970) {
        start.setTime(secs, mins, hours, days, months, years);
    }
    void setStart(Time_t startt) {
        start = startt;
    }
    void setGenre(string string) {
        genre = string;
    }
    string getGenre() {
        return genre;
    }

    void setEnd(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 1, unsigned months = 1, unsigned years = 1970) {
        end.setTime(secs, mins, hours, days, months, years);
    }
    void setDuration(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 0, unsigned months = 0, unsigned years = 0) {
        Time_t duration;
        duration.setTime(secs, mins, hours, days, months, years);
        end = start + duration;
    }
    void setDuration(Time_t duration) {
        end = start + duration;
        duration_film = duration;
    }

    Time_t getDuration() {
        return duration_film;
    }
    Time_t getTimeStart() {
        return start;
    }
    Time_t getTimeEnd() {
        return end;
    }

    string getName() {
        return name;
    }

    void setName(string names) {
        name = names;
    }
};

class Hall
{
private:
    unsigned line{};
    unsigned seat{};
    string name_hall = "";
    Seat** matrix{};
    const size_t size = 7;
    Film** films{};
    unsigned profit{ 0 };
    string type{ "" };
public:

    void SetType(string h_type) // добавлено
    {
        type = h_type; // добавление типа для объекта класса Зал.
    }

    void SetName(string h_name) { // Имя кинозала
        name_hall = h_name;
    }
    
    void SetMatrix(unsigned h_line, unsigned h_seat) { // задание матрицы мест 
        line = h_line; seat = h_seat;
        matrix = new Seat* [line] {};
        films = new Film * [7] {};
        for (size_t i{}; i != line; ++i) {
            matrix[i] = new Seat[seat];
        }
        for (size_t i{}; i != 7; ++i) {
            films[i] = new Film[8]{};
        }
    }

    void addProfit(unsigned money) {
        profit += money;
    }

    unsigned getCollumns() {
        return seat;
    }

    unsigned getRows() {
        return line;
    }

    unsigned getProfit() {
        return profit;
    }

    void addFilm(string name, Time_t start, Time_t duration, unsigned day) {
        Film filmss;
        filmss.setName(name);
        filmss.setStart(start);
        filmss.setDuration(duration);
        for (size_t i{}; i != 8; ++i) {
            if (films[day - 1][i].getName() == "") {
                films[day - 1][i] = filmss;
                return;
            }
        }
    }

    Seat** getMatrix() {
        return matrix;
    }

    Film* getFilms(unsigned day) {
        return films[day - 1];
    }

    void outputFilms(unsigned day) {
        for (size_t i{}; i != 8; ++i) {
            cout << films[day - 1][i].getName() << " ";
        }
    }

    void deleteMatrix() {
        for (size_t i{}; i != line; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        for (size_t i{}; i != 7; ++i) {
            delete[] films[i];
        }
        delete[] films;
        
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

    void PrintInfo() { // вывод информации о кинозале
        cout << left << "Имя: " << setw(5) << name_hall << '\t' << "Рядов: " << setw(3) << line << '\t' <<
            "Мест: " << setw(3) << seat << '\t' << 
            "Тип: " << setw(8) << type << '\n';
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