#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include <set>
#include <tuple>
#include <fstream>
#include <sstream>

#pragma warning(disable : 4996)

#define Ull unsigned long long

using namespace std;

class Time_t {
private:
	Ull milisec{ 0 };
	Ull sec{ 0 };
	Ull min{ 0 };
	Ull hour{ 0 };
	Ull day{ 0 };
	Ull month{ 0 };
	Ull year{ 0 };
public:
	void setTime(Ull secs, Ull mins = 0, Ull hours = 0, Ull days = 0, Ull months = 0, Ull years = 0) {
		if (secs >= 60 && secs % 60 == 0) sec = 1;
		else sec = secs;
		if (mins >= 60 && mins % 60 == 0) min = 1;
		else min = mins;
		if (hours >= 24 && hours % 24 == 0) hour = 1;
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

	Ull getSec() {
		return sec;
	}

	Ull getMin() {
		return min;
	}

	Ull getHour() {
		return hour;
	}

	Ull getDay() {
		return day;
	}

	Ull getMonth() {
		return month;
	}

	Ull getYear() {
		return year;
	}
	void setDay(unsigned num) {
		day = num;
	}

	Ull getMilisec() {
		return milisec;
	}

	void setMilisec(Ull total_time) {
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
		Ull secs = sec + rhs.sec;
		Ull mins = min + rhs.min;
		Ull hours = hour + rhs.hour;
		Ull days = day + rhs.day;
		Ull months = month + rhs.month;
		Ull years = year + rhs.year;
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
		Ull secs = sec - rhs.sec;
		Ull mins = min - rhs.min;
		Ull hours = hour - rhs.hour;
		Ull days = day - rhs.day;
		Ull months = month - rhs.month;
		Ull years = year - rhs.year;
		if (secs < 0) {
			secs = secs + 60;
			mins -= 1;
		}
		if (mins < 0) {
			mins = mins + 60;
			hours -= 1;
		}
		if (hours < 0) {
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
			days = days + 28;
			months -= 1;
		}
		if (months < 1) {
			months = months + 12;
			years -= 1;
		}
		unsigned long long total_time = secs + mins * 60 + hours * 3600 + days * 24 * 3600 + months * 720 * 3600 + years * 12 * 720 * 3600;
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
		if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
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

class Film {
private:
	unsigned ID{};

	string name, genre, director, ageRating, description;

	Time_t duration;

	unsigned basicTicketCost{ 300 };

public:

	void setFilmData(string Data[7]) {
		ID = stoul(Data[0]);

		name = Data[1]; genre = Data[2];
		director = Data[3]; ageRating = Data[4];
		description = Data[6];

		duration.setTime(0, stoul(Data[5]) % 60, stoul(Data[5]) / 60, 0, 0, 0);
	}

	string getName() {
		return name;
	}

	unsigned getbasicTicketCost() {
		return basicTicketCost;
	}

	void printBaseInfo() {
		cout << left << setw(5) << ID <<
			setw(20) << name <<
			setw(20) << genre <<
			setw(20) << director <<
			setw(20) << ageRating <<
			setw(20) << duration.getMin() << '\n';
	}

	void printDescription() {
		cout << description << '\n';
	}

	Time_t getDuration() {
		return duration;
	}

};

class Seat
{
private:
	unsigned price{};
	char status{ '*' };
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

class Hall
{
private:
	unsigned ID{};

	string type;
	unsigned line{};
	unsigned seat{};

	Seat** matrix{};

public:

	void SetSeat(unsigned i, unsigned j) { // изменить статус места 
		matrix[i][j].setStatus('@');
	}

	bool GetSeatStatus(unsigned i, unsigned j) {
		return matrix[i][j].getStatus() == '*';
	}

	void setHallData(string Data[4]) {
		ID = stoul(Data[0]);

		type = Data[1];

		line = stoul(Data[2]); seat = stoul(Data[3]);

		matrix = new Seat * [line];
		for (unsigned i{}; i != line; ++i) {
			matrix[i] = new Seat[seat];
		}

		char elems[2] = { '0', '*' };
		for (unsigned i{}; i != line; ++i) {
			for (unsigned j{}; j != seat; ++j) {
				matrix[i][j].setStatus(elems[rand() % 2]);
			}
		}

	}

	unsigned getColumns() {
		return seat;
	}

	unsigned getRows() {
		return line;
	}

	unsigned getID() {
		return ID;
	}

	string getType() {
		return type;
	}

	Seat** getMatrix() {
		return matrix;
	}

	void SetSeat(unsigned fs, unsigned ls, unsigned row) { // заполнение мест
		for (unsigned i = fs; i <= ls; ++i) {
			matrix[row][i].setStatus('@');
		}
	}

	void PrintMatrix() { // вывод матрицы мест
		cout << "_____" << "SCREEN" << "_____" << '\n';
		for (unsigned i{}; i != line; ++i) {
			cout << setw(3) << i + 1;
			for (unsigned j{}; j != seat; ++j) {
				cout << matrix[i][j].getStatus() << " ";
			}
			cout << '\n';
		}
		cout << '\n';
	}

	void PrintInfo() {
		cout << left << setw(5) << ID <<
			setw(20) << type <<
			setw(20) << line <<
			setw(20) << seat << '\n';
	}
};

class Seans
{
private:
	unsigned ID{};

	Hall seanceHall{};
	Film seanceFilm{};

	Time_t startTime{};
	Time_t endTime{};

	double ticketCost{};
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

	void setTicketCost(double s_ticketcost) {
		ticketCost = s_ticketcost;
	}

	double getTicketCost() {
		return ticketCost;
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

	void printInfo() {
		cout << ID << '\t'; startTime.printTimeWithoutSeconds(); cout << '\t' << seanceHall.getID() << '\t' << '\n';
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
	Time_t date;
	vector<Seans> seansList;
public:
	void setDate(Time_t d_date) {
		date = d_date;
	}

	Ull getMonthNum() {
		return date.getMonth();
	}

	Ull getDayNum() {
		return date.getDay();
	}

	unsigned getSeansListSize() {
		return (unsigned)seansList.size();
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

bool checkSeatStatus(unsigned, unsigned, Hall);
double getPriceCoeff(const string&, const unsigned);
double buyTicketOnChooseDay(const Ull);

void showSeatsVariants(Seat**, const unsigned, Hall);
void fillSeatsByUser(unsigned, Hall);
void printFilmsData();
void printHallsData();
void showConfig();
void manualHallAdd();
void manualFilmAdd();
void getDataFromFiles();
void manualConfigEdit();
void printSchedule();

char command; // главная переменная команды

Time_t CurrentTime; // Текущее время, нужно для составления расписания
Time_t start_day; // Начало дня, нужно для составления расписания
Time_t end_day; // Конец дня, нужно для составления расписания

const string filmFiles[] = {
	"Barbie.txt", "Test1.txt", "Test2.txt", "Test3.txt", "Test4.txt", "Test5.txt", "Test6.txt", "Test7.txt", "Test8.txt", "Test9.txt"
};

const string hallFiles[]{
	"0.txt", "1.txt", "2.txt", "3.txt", "4.txt", "5.txt", "6.txt", "7.txt"
};

Day Schedule[7]; // расписание

vector<Film> filmsList; // вектор фильмов класса Film
vector<Hall> hallsList; // вектор кинозалов класса Hall

int main() {
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "RU");

	set<unsigned> listSessionsWithCurrentFilm;

	command = 'E'; // по умолчанию - выход из меню кассира
	do
	{
		system("cls");

		cout << "<Панель управления кинотеатром>" << '\n';
		cout << '\n' << "Список доступных команд:" << '\n' << '\n'
			<< "\t0 ~ Выставить параметры согласно текущим файлам конфигурации" << '\n'
			<< "\t1 ~ Редактировать параметры вручную" << '\n'
			<< "\t2 ~ Просмотреть текущие параметры" << '\n'
			<< "\tE ~ Перейти в меню работы с покупателем" << '\n';
		cout << '\n' << "Выберете команду из списка: ";

		cin >> command;
		switch (command)
		{
		case '0':
			getDataFromFiles();
			break;
		case '1':
			showConfig();
			manualConfigEdit();
			break;
		case '2':
			showConfig();
			system("pause && cls");
			break;
		case 'E':
			system("cls");
			cout << "Выход из панели управления" << '\n';
			system("pause && cls");
			break;
		default:
			break;
		}

	} while (command != 'E');

	cout << "<Вид от покупателя>" << '\n' << '\n';

	vector<Seans> todaySessionsList = Schedule[0].getSeansList();

	cout << "\t1) Посмотреть афишу фильмов на сегодня" << '\n'
		<< "\t2) Посмотреть расписание на ближайшую неделю" << '\n' << '\n';
	cout << "Какая информация вас интересует: "; cin >> command;

	Ull date{};
	int n{ 1 };
	double PROFIT{};
	switch (command)
	{
	case '1':
		cout << "\t\t\t\t   " << "<Дата> " << Schedule[0].getDayNum() << '.' << Schedule[0].getMonthNum() << '\n';

		cout << '#' << '\t' << left << setw(17) << "<Время>"
			<< setw(25) << "<Фильм>"
			<< setw(20) << "<Зал>"
			<< setw(10) << "<Цена билета>" << '\n';

		for (Seans currSeans : Schedule[0].getSeansList()) {
			cout << setw(5) << n++;
			currSeans.getStartTime().printTimeWithoutSeconds(); cout << '-'; currSeans.getEndTime().printTimeWithoutSeconds(); cout << '\t';
			cout << setw(20) << currSeans.getFilm().getName(); cout << '\t';
			cout << left << setw(10) << currSeans.getHall().getID() << ' ' << '(' << currSeans.getHall().getType() << ')'; cout << '\t';
			cout << left << setw(10) << currSeans.getTicketCost();
			cout << '\n';
		}
		cout << '\n';

		PROFIT = buyTicketOnChooseDay(0);
		break;
	case '2':
		system("cls");

		printSchedule();

		cout << "> На какой день хотите купить билет? -> "; cin >> date;

		PROFIT = buyTicketOnChooseDay(date - CurrentTime.getDay());

		break;
	default:
		break;
	}

	cout << "К оплате " << PROFIT << '\n';

	return 0;
}

void showSeatsVariants(Seat** arr, const unsigned humans, Hall currHall) {
	vector<tuple<unsigned, unsigned, unsigned>> indexes;
	unsigned row = currHall.getRows();
	unsigned column = currHall.getColumns();
	for (unsigned i{}; i != row; ++i) {
		int fs = -1, ls = -1;
		unsigned slots{ 0 };
		for (unsigned j{}; j != column; ++j) {
			if (arr[i][j].getStatus() == '0') {
				slots++;
				if (fs == -1) fs = j;
			}
			if (arr[i][j].getStatus() == '*' || j + 1 == column) {
				if (slots >= humans) {
					ls = j - (1 * arr[i][j].getStatus() == '*');
					indexes.push_back(make_tuple(i, fs, ls));
				}
				fs = ls = -1; slots = 0;
			}
		}
	}
	if (indexes.size() != 0) {
		for (unsigned i{}; i != indexes.size(); ++i) {
			cout << "Вариант рассадки " << i + 1 << "-> "
				<< "Ряд: " << get<0>(indexes[i]) + 1 << " "
				<< "Места: " << get<1>(indexes[i]) + 1 << "-"
				<< get<2>(indexes[i]) + 1 << '\n';
		}
	}
	else {
		cout << "К сожалению вашу группу невозможно посадить в один ряд, попробуйте ручной выбор мест" << '\n';
	}

}

void fillSeatsByUser(unsigned humans, Hall currHall) {
	unsigned currRow, currCol, seat{};
	while (humans--)
	{
		do {
			cout << "Выберете место для зрителя " << ++seat << " (ряд место): ";
			cin >> currRow >> currCol;
		} while (!checkSeatStatus(currRow - 1, currCol - 1, currHall));
		currHall.SetSeat(currRow - 1, currCol - 1);
	}
}

bool checkSeatStatus(unsigned currRow, unsigned currCol, Hall currHall) {
	if (currHall.GetSeatStatus(currRow, currCol)) {
		cout << "Данное место занято, выберете другое место" << '\n';
		return false;
	}
	return true;
}

void printFilmsData() {
	cout << "<Параметры фильмов>" << '\n';
	cout << left << setw(5) << "ID" << setw(20) << "Title" << setw(20) << "Genre" << setw(20) << "Director"
		<< setw(20) << "Age rating" << setw(20) << "Duration" << '\n';
	for (Film currFilm : filmsList) {
		currFilm.printBaseInfo();
	}

	cout << '\n';
}

void printSchedule() {
	int n{};

	cout << "<Текущее расписание>" << '\n';

	for (Day currDay : Schedule) {
		cout << "\t\t\t\t   " << "<Дата> " << currDay.getDayNum() << '.' << currDay.getMonthNum() << '\n';

		cout << "ID" << "     " << left << setw(17) << "<Время>"
			<< setw(25) << "<Фильм>"
			<< setw(20) << "<Зал>"
			<< setw(10) << "<Цена билета>" << '\n';

		for (Seans currSeans : currDay.getSeansList()) {
			cout << setw(5) << n++;
			currSeans.getStartTime().printTimeWithoutSeconds(); cout << '-'; currSeans.getEndTime().printTimeWithoutSeconds(); cout << '\t';
			cout << setw(22) << currSeans.getFilm().getName();
			cout << setw(3) << currSeans.getHall().getID() << ' ' << '(' << currSeans.getHall().getType() << ')'; cout << '\t' << '\n';
		}
		cout << '\n';
		n = 0;
	}
}

void printHallsData() {
	cout << "<Параметры залов>" << '\n';
	cout << left << setw(5) << "ID" << setw(20) << "Type" << setw(20) << "Rows" << setw(20) << "Cols" << '\n';
	for (Hall currHall : hallsList) {
		currHall.PrintInfo();
	}

	cout << '\n';
}

void showConfig() {
	system("cls");

	printHallsData();

	printFilmsData();

	printSchedule();
}

void manualHallAdd() {
	do
	{
		system("cls");
		unsigned hallsValue = (unsigned)hallsList.size(); // текущий size вектора залов

		printHallsData(); // вывод текущих данных о залах

		cout << "> Введите ID зала, который хотите отредактировать ('+' - добавить новый зал) -> "; cin >> command;

		unsigned hallID;
		if (command == '+')
			hallID = hallsValue; // command == '+' => ID нового зала = размеру вектора
		else
			hallID = (unsigned)(command - '0'); // command != '+' => ID выбранного зала = command - '0'

		string Data[4]; // массив для хранения данных о зале

		cout << "> Выберите тип зала ('general' - обычный, 'soft' - с диванами, 'VIP' - VIP, 'children' - детский) -> "; cin >> Data[1];
		cout << "> Выберите размеры для кинозала." << '\n';
		cout << "> Введите количество рядов в зале -> "; cin >> Data[2];
		cout << "> Введите количество мест в каждом ряду -> "; cin >> Data[3];

		Data[0] = to_string(hallID);
		if (command == '+') {
			Hall newHall; // создание нового экземпляра класса Hall
			newHall.setHallData(Data); // установка параметров зала
			hallsList.push_back(newHall); // добавление нового зала в вектор залов
		}
		else {
			hallsList[hallID].setHallData(Data); // обновление параметров зала
			// Правда нужно предварительно удалить старую матрицу
		}

		system("cls");

		printHallsData(); // вывод текущих данных о залах

		cout << "> Закончить редактирование залов? (1 - да, 0 - нет) -> "; cin >> command;
	} while (command == '0');

	system("cls");
}

void manualFilmAdd() {
	do
	{
		system("cls");
		unsigned filmsValues = (unsigned)filmsList.size(); // текущий size вектора фильмов

		printFilmsData(); // вывод текущих данных о фильмах

		cout << "> Введите ID фильма, который хотите отредактировать ('+' - добавить новый фильм) -> "; cin >> command;

		unsigned filmID;
		if (command == '+')
			filmID = filmsValues; // command == '+' => ID нового фильма = размеру вектора
		else
			filmID = (unsigned)(command - '0'); // command != '+' => ID выбранного фильма = command - '0'

		string Data[7]; // массив для хранения данных о фильме

		cin.ignore(1, '\n');

		cout << "> Введите название фильма -> "; getline(cin, Data[1]);
		cout << "> Введите жанр фильма -> "; getline(cin, Data[2]);
		cout << "> Укажите режиссёра фильма -> "; getline(cin, Data[3]);
		cout << "> Укажите возрастной рейтинг фильма -> "; getline(cin, Data[4]);
		cout << "> Укажите продолжительность фильма -> "; getline(cin, Data[5]);

		bool addDes; // наличие описания
		cout << "Желаете добавить описание фильма? (0 - нет, 1 - да) -> "; cin >> addDes;

		Data[6] = "Отсутствует"; // описание по умолчанию
		if (addDes) {
			cout << "> Введите описание фильма -> "; getline(cin, Data[6]);
		}

		Data[0] = to_string(filmID);
		if (command == '+') {
			Film newFilm; // создание нового экземпляра класса Film
			newFilm.setFilmData(Data); // установка параметров фильма
			filmsList.push_back(newFilm); // добавление нового фильма в вектор фильмов
		}
		else {
			filmsList[filmID].setFilmData(Data); // обновление текущих данных о фильме
		}


		system("cls");

		printFilmsData(); // вывод текущих данных о фильмах

		cout << "> Закончить редактирование фильмов? (1 - да, 0 - нет) -> "; cin >> command;
	} while (command == '0');

	system("cls");
}

void getDataFromFiles() {
	system("cls");
	filmsList.clear(); hallsList.clear();

	// заполнение вектора фильмов
	for (string fileName : filmFiles) {
		ifstream in("Files\\Films\\" + fileName); // открываем файл на чтение

		string fl; getline(in, fl); // считываем первую строку из файла
		stringstream ss(fl);

		string filmData[7]; string feature;

		/*
			Делим данную строку по символу '_'
			и каждый полученный параметр записываем в filmData
		*/

		int n{};
		while (getline(ss, feature, '_')) {
			filmData[n] = feature;
			n++;
		}


		// Считываем описание фильма
		string description;
		getline(in, description, '#');
		filmData[6] = description;

		Film newFilm; // Создаём новый экземпляр класса Film
		newFilm.setFilmData(filmData); // Устанавливаем данные о фильме
		filmsList.push_back(newFilm); // Добавляем фильм в вектор фильмов

		in.close(); // закрываем файл
	}
	
	// Заполнение вектора залов
	for (string hallName : hallFiles) {
		ifstream in("Files\\Halls\\" + hallName); // открываем файл на чтение

		string fl; getline(in, fl); // считываем первую строку из файла
		stringstream ss(fl);

		string hallData[4]; string feature;

		/*
			Делим данную строку по символу '_'
			и каждый полученный параметр записываем в HallData
		*/

		int n{};
		while (getline(ss, feature, '_')) {
			hallData[n] = feature;
			n++;
		}

		Hall newHall; // Создаём новый экземпляр класса Hall
		newHall.setHallData(hallData); // Устанавливаем данные о зале
		hallsList.push_back(newHall); // Добавляем зал в вектор залов

		in.close();
	}
	
	const unsigned HALLSVALUE = (unsigned)hallsList.size();
	const unsigned FILMSVALUE = (unsigned)filmsList.size();

	// Текущее время
	time_t ttime = time(0);
	tm* now = localtime(&ttime);
	CurrentTime.setTime(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon + (Ull)1, now->tm_year + (Ull)1900);

	// заполнение залов фильмами и случайная рассадка людей
	Time_t temp_t_again;
	temp_t_again.setTime(0, 30, 0, 0, 0, 0);

	start_day.setTime(0, 0, 8, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear()); // время начала работы залов
	end_day.setTime(0, 0, 23, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear()); // время конца работы залов

	// Составление расписания
	for (unsigned day{}; day < 7; day++) {
		Day newDay;

		Time_t currDayStart; currDayStart.setTime(0, 0, 8, start_day.getDay() + day, CurrentTime.getMonth(), CurrentTime.getYear());
		Time_t currDayEnd; currDayEnd.setTime(0, 0, 23, start_day.getDay() + day, CurrentTime.getMonth(), CurrentTime.getYear());

		newDay.setDate(currDayStart);

		int n{}; bool flag = true;
		do
		{
			Seans newSeans;
			newSeans.setID(n++); // Установка ID

			unsigned randomHallID = rand() % HALLSVALUE;
			newSeans.setHall(hallsList[randomHallID]); // установка случайного зала

			unsigned randomFilmID = rand() % FILMSVALUE;
			newSeans.setFilm(filmsList[randomFilmID]); // установка случайного фильма

			double PriceCoeff = getPriceCoeff(newSeans.getHall().getType(), newSeans.getFilm().getbasicTicketCost());
			newSeans.setTicketCost(PriceCoeff); // установка цены билета

			newSeans.setStartTime(currDayStart); // установка времени начала

			currDayStart = currDayStart + filmsList[randomFilmID].getDuration();

			newSeans.setEndTime(currDayStart); // установка времени конца

			currDayStart = currDayStart + temp_t_again; // + перерыв

			// пока продолжительность фильма умещается в график
			flag = currDayEnd > newSeans.getEndTime();
			if (flag) newDay.addSeans(newSeans);
		} while (flag);

		Schedule[day] = newDay;
	}

	cout << "Параметры успешно обновлены согласно файлам конфигурации" << '\n';
	system("pause && cls");
}

void manualConfigEdit() {
	do
	{
		cout << "Список доступных команд:" << '\n'
			<< "\t0 - Редактировать список залов" << '\n'
			<< "\t1 - Редактировать список фильмов" << '\n'
			<< "\t2 - Редактировать расписание сеансов" << '\n'
			<< "\t3 - Вернуться в главное меню" << '\n';
		cout << '\n' << "Выберете команду из списка: ";

		cin >> command;
		switch (command)
		{
		case '0':
			manualHallAdd();
			break;
		case '1':
			manualFilmAdd();
			break;
		case '3':
			system("cls");
			break;
		default:
			break;
		}

		showConfig();
	} while (command != '3');

}

double buyTicketOnChooseDay(const Ull day) {

	char otvet = 'Y';
	do
	{
		system("cls");

		cout << "\t\t\t\t   " << "<Дата> " << Schedule[day].getDayNum() << '.' << Schedule[day].getMonthNum() << '\n';

		cout << '#' << '\t' << left 
			<< setw(17) << "<Время> "
			<< setw(25) << "<Фильм> "
			<< setw(20) << "<Зал> "
			<< setw(10) << "<Цена билета> " << '\n';

		int n{ 1 };
		for (Seans currSeans : Schedule[day].getSeansList()) {
			cout << setw(5) << n++; // номер сеанса
			currSeans.getStartTime().printTimeWithoutSeconds(); cout << '-'; currSeans.getEndTime().printTimeWithoutSeconds(); cout << '\t'; // время начала и конца сенача
			cout << setw(20) << currSeans.getFilm().getName(); cout << '\t'; // название фильма
			cout << currSeans.getHall().getID() << ' ' << '(' << currSeans.getHall().getType() << ')' << '\n'; // ID и тип зала
		}
		cout << '\n';

		cout << "> Хотите посмотреть подробную информацию о каком-либо фильме? (Y/N): ";
		while (!(cin >> otvet) || cin.peek() != 10 || (toupper(otvet) != 'N' && toupper(otvet) != 'Y')) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "> Хотите посмотреть подробную информацию о каком-либо фильме? (Y/N): ";
		}

		if (otvet == 'Y') {
			unsigned filmNumber;
			cout << "> Введите номер сеанса фильма, о котором хотите увидеть подробную информацию: "; cin >> filmNumber;
			Schedule[day].getSeans(filmNumber - 1).getFilm().printBaseInfo(); Schedule[day].getSeans(filmNumber - 1).getFilm().printDescription();
			system("pause");
		}
	} while (otvet == 'Y');

	unsigned chooseSeans;
	cout << "> Выберите номер желаемого сеанса: ";
	while (!(cin >> chooseSeans) || cin.peek() != 10 || (chooseSeans < 1 && chooseSeans>10)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "> Выберите номер желаемого сеанса: ";
	}

	Schedule[day].getSeans(chooseSeans - 1).getHall().PrintMatrix();

	cout << "> Сколько билетов хотите купить? -> ";

	unsigned ticketsCount;
	while (!(cin >> ticketsCount) || cin.peek() != 10) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "> Сколько билетов хотите купить? -> ";
	}

	char showVariants;
	cout << "> Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N) -> ";
	while (!(cin >> showVariants) || cin.peek() != 10 || (toupper(showVariants) != 'Y' && toupper(showVariants) != 'N')) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "> Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N) -> ";
	}
	if (showVariants == 'Y') { // Вывод вариантов рассадки
		showSeatsVariants(Schedule[day].getSeans(chooseSeans - 1).getHall().getMatrix(), ticketsCount, Schedule[day].getSeans(chooseSeans - 1).getHall());
	}

	// Ручной выбор мест
	fillSeatsByUser(ticketsCount, Schedule[day].getSeans(chooseSeans - 1).getHall());
	Schedule[day].getSeans(chooseSeans - 1).getHall().PrintMatrix();

	double PROFIT = ticketsCount * Schedule[day].getSeans(chooseSeans - 1).getTicketCost();

	return PROFIT;
}

double getPriceCoeff(const string& type, const unsigned basicPrice) {
	vector<pair<string, double>> priceCoeff{
		{ "children", 0.75 },
		{ "general", 1 },
		{ "soft", 1.5 },
		{ "VIP", 2 },
	};

	for (pair<string, double> coeff : priceCoeff) {
		if (coeff.first == type) return coeff.second * basicPrice;
	}

	return .0;
}
