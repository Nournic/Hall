#include <iostream>
class Time_t {
private:
    unsigned long long milisec{ 1000 * (1970 * (12 * 30 * 24 * 60 * 60) + 24 * 60 * 60 + 30 * 24 * 60 * 60) };
    unsigned sec{ 0 };
    unsigned min{ 0 };
    unsigned hour{ 0 };
    unsigned day{ 1 };
    unsigned month{ 1 };
    unsigned year{ 1970 };
public:
    void setTime(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 1, unsigned months = 1, unsigned years = 1970) {
        if (secs >= 60 && secs % 60 == 0) sec = 1;
        else sec = secs;
        if (mins >= 60 && mins % 60 == 0) min = 1;
        else min = mins;
        if (hours >= 24 && hours % 24 == 0) hours = 1;
        else hour = hours;
        if (days >= 31 && days % 31 == 0) day = 1;
        else day = days % 31;
        if (months >= 13 && months % 13 == 0) month = 1;
        else month = months % 13;
        year = years;
        milisec = 1000*(sec + min * 60 + hour * 3600 + day * 24 * 3600 + month * 720 * 3600 + year * 12 * 720 * 3600);
    }


    void printTime() {
        if (hour < 10) std::cout << '0'; std::cout << hour << ':'; if (min < 10) std::cout << '0'; std::cout << min << ':'; if (sec < 10) std::cout << '0'; std::cout << sec;
    }

    void printTimeWithoutSeconds() {
        if (hour < 10) std::cout << '0'; std::cout << hour << ':'; if (min < 10) std::cout << '0'; std::cout << min;
    }

    unsigned getSec() {
        return sec;
    }

    unsigned getMin() {
        return min;
    }

    unsigned getHour() {
        return hour;
    }

    unsigned getDay() {
        return day;
    }

    unsigned getMonth() {
        return month;
    }

    unsigned getYear() {
        return year;
    }
    void setDay(unsigned num) {
        day = num;
    }

    unsigned long long getMilisec() {
        return milisec;
    }


    bool operator==(const Time_t& rhs) const
    {
        return (milisec == rhs.milisec);
    }

    bool operator>(const Time_t& rhs) const
    {
        return (milisec > rhs.milisec);
    }

    bool operator<(const Time_t& rhs) const
    {
        return (milisec < rhs.milisec);
    }

    bool operator>=(const Time_t& rhs) const
    {
        return (milisec >= rhs.milisec);
    }

    bool operator<=(const Time_t& rhs) const
    {
        return (milisec <= rhs.milisec);
    }

    bool operator!=(const Time_t& rhs) const
    {
        return (milisec != rhs.milisec);
    }

    Time_t operator+(const Time_t& rhs) const {
        unsigned secs = sec + rhs.sec;
        unsigned mins = min + rhs.min;
        unsigned hours = hour + rhs.hour;
        unsigned days = day + rhs.day;
        unsigned months = month + rhs.month;
        unsigned years = year + rhs.year;
        if (secs >= 60) {
            secs %= 60;
            mins += 1;
        }
        if (mins >= 60) {
            mins %= 60;
            hours += 1;
        }
        if (hours >= 24) {
            hours %= 24;
            days += 1;
        }
        if (days > 30) {
            days %= 30;
            months += 1;
        }
        if (months > 12) {
            months %= 12;
            years += 1;
        }
        Time_t newData;
        newData.setTime(secs, mins, hours, days, months, years);
        return newData;
    }

    Time_t operator-(const Time_t& rhs) const {
        int secs = sec;
        int mins = min;
        int hours = hour;
        int days = day;
        int months = month;
        int years = year;
        if (secs - rhs.sec < 0) {
            secs = sec + 60 - rhs.sec;
            mins -= 1;
        }
        if (mins - rhs.min < 0) {
            mins = min + 60 - rhs.min;
            hours -= 1;
        }
        if (hours - rhs.hour < 0) {
            hours = hour + 24 - rhs.hour;
            days -= 1;
        }
        if (days - rhs.day < 1) {
            days = day + 30 - rhs.day;
            months -= 1;
        }
        if (months - rhs.month < 1) {
            months = month + 12 - rhs.month;
            years -= 1;
        }
        Time_t newData;
        newData.setTime(secs, mins, hours, days, months, years);
        return newData;
    }
    void addTime(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 0, unsigned months = 0, unsigned years = 0) {
        sec += secs;
        min += mins;
        hour += hours;
        day += days;
        month += months;
        year += years;
        if (sec >= 60) {
            sec %= 60;
            min += 1;
        }
        if (min >= 60) {
            min %= 60;
            hour += 1;
        }
        if (hour >= 24) {
            hour %= 24;
            day += 1;
        }
        if (day > 30 && (month==4 || month==6 || month == 9 || month == 11)) {
            day %= 30;
            month += 1;
        }
        else if (day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
            day %= 31;
            month += 1;
        }
        else if (day > 28 && month == 2) {
            day %= 28;
            month += 1;
        }
        if (month > 12) {
            month %= 12;
            year += 1;
        }

    }

};