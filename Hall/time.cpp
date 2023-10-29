#include <iostream>
class Time_t {
private:
    unsigned long long milisec{0};
    unsigned sec{ 0 };
    unsigned min{ 0 };
    unsigned hour{ 0 };
    unsigned day{ 0 };
    unsigned month{ 0 };
    unsigned year{ 0 };
public:
    void setTime(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 0, unsigned months = 0, unsigned years = 0) {
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
        milisec = sec + min * 60 + hour * 3600 + day * 24 * 3600 + month * 720 * 3600 + year * 12 * 720 * 3600;
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

    void setMilisec(unsigned long long total_time) {
        milisec = total_time;
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
        if (days > 30 && (months == 3 || months == 5 || months == 8 || months == 10)) {
            days -= 30;
            months += 1;
        }
        else if (days > 31 && (months == 1 || months == 3 || months == 5 || months == 7 || months == 8 || months == 10 || months == 12)) {
            days -= 31;
            months += 1;
        }
        else if (days > 28 && months == 2) {
            days -= 28;
            months += 1;
        }
        if (months > 12) {
            months -= 12;
            years += 1;
        }
        unsigned long long total_time = secs + mins * 60 + hours * 3600 + days * 24 * 3600 + months * 720 * 3600 + years * 12 * 720 * 3600;
        Time_t newData;
        newData.setTime(secs, mins, hours, days, months, years);
        return newData;
    }

    Time_t operator-(const Time_t& rhs) const {
        int secs = sec-rhs.sec;
        int mins = min-rhs.min;
        int hours = hour-rhs.hour;
        int days = day-rhs.day;
        int months = month-rhs.month;
        int years = year-rhs.year;
        if (secs < 0) {
            secs = secs + 60;
            mins -= 1;
        }
        if (mins< 0) {
            mins = mins + 60;
            hours -= 1;
        }
        if (hours< 0) {
            hours = hours + 24;
            days -= 1;
        }
        if (days < 1 && (months == 3 || months == 5 || months == 8 || months == 10)) {
            days = days + 30;
            months -= 1;
        }
        else if (days < 1 && (months == 0 || months == 2 || months == 4 || months == 6 || months == 7 || months == 9 || months == 11)) {
            days = days + 31;
            months -= 1;
        }
        else if (days < 1 && months == 1) {
            days = days+28;
            months -= 1;
        }
        if (months< 1) {
            months = months + 12;
            years -= 1;
        }
        unsigned long long total_time = secs + mins * 60 + hours * 3600 + days * 24 * 3600 + months * 720 * 3600 + years * 12 * 720 * 3600;
        Time_t newData;
        newData.setTime(secs, mins, hours, days, months, years);
        newData.setMilisec(total_time);
        return newData;
    }
    void addTime(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 0, unsigned months = 0, unsigned years = 0) {
        sec += secs;
        min += mins;
        hour += hours;
        day += days;
        month += months;
        year += years;
        milisec = sec + min * 60 + hour * 3600 + day * 24 * 3600 + month * 720 * 3600 + year * 12 * 720 * 3600;
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