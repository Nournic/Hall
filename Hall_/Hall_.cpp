#include <iostream>
#include <string>
#include "classes.cpp"
#include <ctime>
#pragma warning(disable : 4996)
#include <set>
#include <tuple>
#include <fstream>
#include <sstream>

using namespace std;

const string filmNames[10] = { "Миссия невыполнима: декабрьская сессия", "ПМИ: борьба с искусственым интеллектом", "Форсаж 11: заезд  до 1 корпуса", "Тайна ПМИ", "Программисты удачи", "Оппенгеймер", "Барби", "Элементарно", "Тролли 3", "Смешарики снимают кино" };
const unsigned filmscount = 10;
//durationFilms - 1 значение минуты, 2 часы
const unsigned durationsFilms[10][2] = { {43, 2}, {24, 1}, {21, 2}, {45, 1}, {24, 1}, {0, 3}, {54, 1}, {41, 1}, {32, 1}, {51, 0} };

string typeSelect(char);
void cinemaHall(unsigned, Hall*); // функция задает размеры залов.
int TicketCost(Time_t, Hall, unsigned, unsigned);
void showSeatsVariants(Seat**, const unsigned, Hall);
void fillSeatsByUser(unsigned, Hall);
bool checkSeatStatus(unsigned, unsigned, Hall);


char command; // главная переменная команды

string filmFiles[] = {
	"Barbie.txt"
};

string hallFiles[]{
	"0.txt", "1.txt", "2.txt"
};

Day Sсhedule[7]; // расписание
vector<Film> filmsList; // вектор фильмов класса Film
vector<Hall> hallsList; // вектор кинозалов класса Hall

void printFilmsData() {
	cout << "Параметры фильмов" << '\n';
	cout << left << setw(5) << "ID" << setw(20) << "Title" << setw(20) << "Genre" << setw(20) << "Director"
		<< setw(20) << "Age rating" << setw(20) << "Duration" << '\n';
	for (Film currFilm : filmsList) {
		currFilm.printInfo();
	}

	cout << '\n';
}

void printHallsData() {
	cout << "Параметры залов" << '\n';
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
}

void manualHallAdd() {
	do
	{
		system("cls");
		size_t hallsValue = hallsList.size(); // текущий size вектора залов

		printHallsData(); // вывод текущих данных о залах

		cout << "Введите ID зала, который хотите отредактировать ('+' - добавить новый зал): "; cin >> command;

		int hallID;
		if (command == '+')
			hallID = hallsValue; // command == '+' => ID нового зала = размеру вектора
		else
			hallID = command - '0'; // command != '+' => ID выбранного зала = command - '0'

		string Data[4]; // массив для хранения данных о зале

		cout << "Выберите тип зала ('g' - обычный, 's' - с диванами, 'v' - VIP, 'c' - детский) -> "; cin >> Data[1];
		cout << "Выберите размеры для кинозала." << '\n';
		cout << "Введите количество рядов в зале -> "; cin >> Data[2];
		cout << "Введите количество мест в каждом ряду -> "; cin >> Data[3];

		Data[0] = to_string(hallID);
		if (command == '+') {
			Hall newHall; // создание нового экземпляра класса Hall
			newHall.setHallData(Data); // установка параметров зала
			newHall.setMatrix(); // создание матрицы мест зала
			hallsList.push_back(newHall); // добавление нового зала в вектор залов
		}
		else {
			hallsList[hallID].setHallData(Data); // обновление параметров зала
			hallsList[hallID].setMatrix(); // обновление матрицы мест зала
			// Правда нужно предварительно удалить старую матрицу
		}

		system("cls");

		printHallsData(); // вывод текущих данных о залах

		cout << "Закончить редактирование залов? (1 - да, 0 - нет): "; cin >> command;
	} while (command == '0');

	system("cls");
}

void manualFilmAdd() {
	do
	{
		system("cls");
		size_t filmsValues = filmsList.size(); // текущий size вектора фильмов

		printFilmsData(); // вывод текущих данных о фильмах

		cout << "Введите ID фильма, который хотите отредактировать ('+' - добавить новый фильм): "; cin >> command;

		unsigned filmID;
		if (command == '+')
			filmID = filmsValues; // command == '+' => ID нового фильма = размеру вектора
		else
			filmID = command - '0'; // command != '+' => ID выбранного фильма = command - '0'

		string Data[7]; // массив для хранения данных о фильме

		cin.ignore(1, '\n');

		cout << "Введите название фильма: "; getline(cin, Data[1]);
		cout << "Введите жанр фильма: "; getline(cin, Data[2]);
		cout << "Укажите режиссёра фильма: "; getline(cin, Data[3]);
		cout << "Укажите возрастной рейтинг фильма: "; getline(cin, Data[4]);
		cout << "Укажите продолжительность фильма: "; getline(cin, Data[5]);

		bool addDes; // наличие описания
		cout << "Желаете добавить описание фильма? (0 - нет, 1 - да): "; cin >> addDes;

		Data[6] = "Отсутствует"; // описание по умолчанию
		if (addDes) {
			cout << "Введите описание фильма: "; getline(cin, Data[6]);
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

		cout << "Закончить редактирование фильмов? (1 - да, 0 - нет): "; cin >> command;
	} while (command == '0');

	system("cls");
}

void getDataFromFiles() {
	system("cls");

	/*if (!filmFiles->empty() || !hallFiles->empty()) {
		cout << "!! Внимание, текущая конфигурация не пуста, уверены что хотите перезаписать данные? !!";
	}*/
	filmsList.clear();
	hallsList.clear();

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

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "RU");

	Time_t CurrentTime;
	Time_t start_day; //Начало дня, нужно для составления расписания
	Time_t end_day; //Конец дня, нужно для составления расписания
	bool again = false; //Повтор, если покупатель захотел ещё раз сходить в кино
	bool anotherday = false; //Если покупатель решил придти в другой день, запускается ветка выбора дня
	bool complete = false;  //Если покупатель закончил с фильмами, то выход из циклов
	unsigned day{ 1 };
	char choosefilmtoday = 'N';
	char otvet{ 'N' };
	unsigned continue_inspection;
	unsigned choose_number_film;
	bool anotherfilm;
	unsigned filmNumber;
	set<unsigned> listSeansWithCurrentFilm;
	unsigned choose_day;
	unsigned count_bilets;

	command = 'E'; // по умолчанию - выход из меню кассира
	do
	{
		system("cls");

		cout << "Панель управления кинотеатром" << '\n';
		cout << '\n' << "Список доступных команд:" << '\n'
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

	system("pause");
	system("cls");

	cout << "Вид от покупателя" << '\n';

	// Текущее время
	time_t ttime = time(0);
	tm* now = localtime(&ttime);
	CurrentTime.setTime(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

	// заполнение залов фильмами и случайная рассадка людей
	Time_t temp_t_again;
	temp_t_again.setTime(0, 30, 0, 0, 0, 0);
	const size_t HALLSVALUE = hallsList.size();

	start_day.setTime(0, 0, 8, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear()); // время начала работы залов
	end_day.setTime(0, 0, 23, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear()); // время конца работы залов

	for (unsigned day{}; day < 7; day++) {
		Day newDay;

		int n{}; bool flag = true;
		do
		{
			Seans newSeans;
			newSeans.setID(n);

			short randomHallID = rand() % hallsList.size();
			newSeans.setHall(hallsList[randomHallID]);

			short randomFilmID = rand() % filmsList.size();
			newSeans.setFilm(filmsList[randomFilmID]);

			newSeans.setStartTime(start_day);
			newSeans.setEndTime(start_day + filmsList[randomFilmID].getDuration() + temp_t_again);

			if (newSeans.getEndTime() <= end_day)
				newDay.addSeans(newSeans);
			else
				flag = false;

			start_day = newSeans.getEndTime();

		} while (flag);

		Sсhedule[day] = newDay;
		end_day.addTime(0, 0, 0, 1, 0, 0); // // переход на следующих день

		start_day.setTime(0, 0, 8, start_day.getDay(), start_day.getMonth(), start_day.getYear());
		start_day.addTime(0, 0, 0, 1, 0, 0);
	}

	// начинается сущий кошмар
	do {
		again = anotherday = false; // 
		do {
			if (anotherday == false) {

				vector<Seans> todaySeansList = Sсhedule[0].getSeansList();

				do {
					anotherfilm = false;
					cout << "\nСписок фильмов\n";
					for (unsigned i{}; i != filmsList.size(); ++i) {
						cout << i + 1 << ') ' << filmsList[i].getName() << '\n';
					}

					do
					{
						cout << "Хотите посмотреть подробную о каком-либо фильме? (Y/N): ";
						while (!(cin >> otvet) || cin.peek() != 10 || (toupper(otvet) != 'N' && toupper(otvet) != 'Y')) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "Хотите посмотреть информацию о каком-либо фильме? (Y/N): ";
						}

						if (otvet == 'Y') {
							unsigned filmNumber;
							cout << "Введите номер фильма, о котором хотите увидеть подробную информацию: "; cin >> filmNumber;
							filmsList[filmNumber].printInfo(); filmsList[filmNumber].printDescription();
							system("pause");
						}
					} while (otvet == 'Y');

					continue_inspection = -1;
					choose_number_film = 0;
					anotherfilm = false;
					listSeansWithCurrentFilm.clear();

					cout << "Выберите номер желаемого фильма: ";
					while (!(cin >> choose_number_film) || cin.peek() != 10 || (choose_number_film < 1 && choose_number_film>10)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Выберите номер желаемого фильма: ";
					}

					for (Seans currSeans : todaySeansList) {
						if (currSeans.getFilm().getName() == filmsList[choose_number_film - 1].getName() && currSeans.getStartTime() > CurrentTime) {
							listSeansWithCurrentFilm.insert(currSeans.getID());
						}
					}

					if (listSeansWithCurrentFilm.empty()) {
						cout << "К сожалению, данный фильм не показывают сегодня. У вас есть вариант выбрать другой фильм или прийти в другой день\n0 - другой фильм\t1 - другой день\n";
						while (!(cin >> continue_inspection) || cin.peek() != 10 || (continue_inspection < 0 && continue_inspection>1)) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "К сожалению, данный фильм не показывают сегодня. У вас есть вариант выбрать другой или прийти в другой день\n0 - другой фильм\t1 - другой день\n";
						}
					}

					if (continue_inspection == 1) anotherday = true;
					else if (continue_inspection == 0) anotherfilm = true;

				} while (anotherfilm == true);

				if (anotherday == false) {
					cout << "Выберите один из этих сеансов показа выбранного фильма: ";
					for (int n : listSeansWithCurrentFilm)
						cout << n << ' ';
					cout << '\n';

					unsigned currSeansNumber{ 0 };
					while (!(cin >> currSeansNumber) || cin.peek() != 10 || (currSeansNumber < 1 && currSeansNumber>currSeansNumber)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Выберите один из этих сеансов показа выбранного фильма: ";
						for (int n : listSeansWithCurrentFilm)
							cout << n << ' ';
						cout << '\n';
					}

					//вывод сеансов с заданным фильмом
					unsigned mins, hours;
					char UserChooseTime = 'N';

					cout << "Вы хотите выбрать время? (Y/N): ";
					while (!(cin >> UserChooseTime) || cin.peek() != 10 || (toupper(UserChooseTime) != 'N' && toupper(UserChooseTime) != 'Y')) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Вы хотите выбрать время? (Y/N): ";
					}

					if (UserChooseTime == 'Y') {
						do {
							for (unsigned SeansID : listSeansWithCurrentFilm) {
								cout << "Время начала: "; todaySeansList[SeansID].getStartTime().printTimeWithoutSeconds();
							}

							cout << "Введите время начала фильма (часы и минуты через пробел): ";
							while (!(cin >> hours) || !(cin >> mins) || cin.peek() != 10) {
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout << "Введите время начала фильма (часы и минуты через пробел): ";
							}

							/*for (size_t i{}; i != 8; ++i) {
								if (hallsList[currSeansNumber].getFilms(day)[i].getTimeStart().getHour() == hours && hallsList[currSeansNumber].getFilms(day)[i].getTimeStart().getMin() == mins) {
									Time_t timee;
									timee.setTime(hallsList[currSeansNumber].getFilms(day)[i].getTimeStart().getSec(), hallsList[currSeansNumber].getFilms(day)[i].getTimeStart().getMin(), hallsList[currSeansNumber].getFilms(1)[i].getTimeStart().getHour(), CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear());
									if (timee > CurrentTime) {
										chooseFilm = hallsList[currSeansNumber].getFilms(day)[i];
									}
								}
							}*/

						} while (chooseFilm.getTimeStart() == temp.getTimeStart());
					}

					count_bilets = 0;
					hallsList[currSeansNumber].PrintMatrix();
					unsigned count_bilets;
					cout << "Сколько билетов купить: ";

					while (!(cin >> count_bilets) || cin.peek() != 10) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Сколько билетов купить: ";
					}

					char showVariants;
					bool choose_hand = false;
					cout << "Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N): ";
					while (!(cin >> showVariants) || cin.peek() != 10 || (toupper(showVariants) != 'Y' && toupper(showVariants) != 'N')) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N): ";
					}
					if (showVariants == 'Y') { // Вывод вариантов рассадки
						showSeatsVariants(hallsList[currSeansNumber].getMatrix(), count_bilets, hallsList[currSeansNumber]);
					}
					// Ручной выбор мест
					fillSeatsByUser(count_bilets, hallsList[currSeansNumber]);
					hallsList[currSeansNumber].PrintMatrix();
					Time_t temp_t;

					temp_t.setTime(0, hallsList[currSeansNumber].getFilms(day)[choose_number_film - 1].getTimeStart().getMin(), hallsList[currSeansNumber].getFilms(day)[choose_number_film - 1].getTimeStart().getHour(), 0, 0, 0);
					hallsList[currSeansNumber].addProfit(TicketCost(temp_t, hallsList[currSeansNumber], 1, 1) * count_bilets);
					complete = true;

				}


			}
			if (anotherday == true && day == 1 && complete == false) {

				cout << "Вывод выбранного фильма на неделю\n";
				Time_t temp_time;
				temp_time = CurrentTime;
				for (unsigned d{ day + 1 }; d != 8; d++) {
					unsigned c = 0;
					temp_time.addTime(0, 0, 0, 1, 0, 0);
					for (unsigned i{}; i != HALLSVALUE; ++i) {
						for (unsigned j{}; j != 8; ++j) {
							if (hallsList[i].getFilms(d)[j].getName() == filmNames[choose_number_film - 1]) {
								c += 1;
							}
						}
					}
					if (c != 0) {
						bool abc = false;;
						cout << temp_time.getDay() << " число: ";
						for (unsigned i{}; i != HALLSVALUE; ++i) {
							for (unsigned j{}; j != 8; ++j) {
								if (hallsList[i].getFilms(d)[j].getName() == filmNames[choose_number_film - 1]) {
									if (abc == false) { hallsList[i].getFilms(d)[j].getTimeStart().printTimeWithoutSeconds(); cout << " "; abc = true; }

								}
							}
							abc = false;
						}
						cout << '\n';
					}
				}
				int curr_hall = -1;
				cout << "Выберите день: ";

				while (!(cin >> choose_day) || cin.peek() != 10) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Выберите день: ";
				}

				temp_time = CurrentTime;
				if (choose_day >= 1 && choose_day < 7) choose_day += 31;
				temp_time.addTime(0, 0, 0, choose_day - CurrentTime.getDay(), 0, 0);
				if (temp_time.getMonth() > CurrentTime.getMonth()) {
					if (temp_time.getMonth() == 4 || temp_time.getMonth() == 6 || temp_time.getMonth() == 9 || temp_time.getMonth() == 11) temp_time.setDay(temp_time.getDay() + 30);
					else if (temp_time.getMonth() == 1 || temp_time.getMonth() == 3 || temp_time.getMonth() == 5 || temp_time.getMonth() == 7 || temp_time.getMonth() == 8 || temp_time.getMonth() == 10 || temp_time.getMonth() == 12) temp_time.setDay(temp_time.getDay() + 31);
					else if (temp_time.getMonth() == 2) temp_time.setDay(temp_time.getDay() + 28);
				}
				if (temp_time.getDay() > 30) day = day + (temp_time.getDay() - CurrentTime.getDay() - 1);
				else day = day + (temp_time.getDay() - CurrentTime.getDay());
				if (choose_day > 31) choose_day -= 31;

				for (unsigned i{}; i != HALLSVALUE; ++i) {
					for (unsigned j{}; j != 8; ++j) {
						if (hallsList[i].getFilms(day)[j].getName() == filmNames[choose_number_film - 1]) {
							curr_hall = i;
						}
					}
				}
				if (curr_hall != -1) {
					cout << "Рассадка на выбранный день\n";
					hallsList[curr_hall].PrintMatrix();
					cout << "Сколько билетов купить: ";
					while (!(cin >> count_bilets) || cin.peek() != 10) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Сколько билетов купить: ";
					}
					char showVariants;
					bool choose_hand = false;
					cout << "Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N): ";
					while (!(cin >> showVariants) || cin.peek() != 10 || (toupper(showVariants) != 'Y' && toupper(showVariants) != 'N')) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N): ";
					}
					if (showVariants == 'Y') { // Вывод вариантов рассадки
						showSeatsVariants(hallsList[curr_hall].getMatrix(), count_bilets, hallsList[curr_hall]);
					}
					// Ручной выбор мест
					fillSeatsByUser(count_bilets, hallsList[curr_hall]);
					hallsList[curr_hall].PrintMatrix();
					hallsList[curr_hall].addProfit(250 * count_bilets);
					complete = true;
				}
				else {
					cout << day;
					cout << "Данный фильм ни разу не покажут на этой неделе, выберете другой фильм";
					anotherfilm = true;
				}


			}
		} while (anotherday == true && complete == false);

		//Оплата
		//userHall.addProfit(1/* счёт оплаты*/);
		if (complete == true) {
			again = false;
		}
		else {
			again = true;
		}
	} while (again == true);
	unsigned profit{ 0 };
	for (size_t i{}; i != HALLSVALUE; ++i) {
		profit += hallsList[i].getProfit();
	}
	cout << "Кинозал получил прибыли: " << profit;

	return 0;
}

int TicketCost(Time_t time, Hall hall, unsigned seat_r, unsigned seat_c) {

	int sessionTime_h = time.getHour();

	int price = 0;
	if (sessionTime_h == 8)
	{
		price += 250;
	}
	if (sessionTime_h > 9 && sessionTime_h <= 15)
	{
		price += 350;
	}
	if ((sessionTime_h > 15 && sessionTime_h < 24))
	{
		price += 500;
	}
	if (hall.getCollumns() % 4)
	{
		if ((seat_r > hall.getCollumns() / 4 + 1 && seat_r < (hall.getCollumns() * 3) / 4 + 1) && (seat_c > hall.getRows() / 4 + 1 && seat_c < (hall.getRows() * 3) / 4 + 1))
		{
			price += 100;
		}
	}
	else
	{
		if ((seat_r > hall.getCollumns() / 4 && seat_r < (hall.getCollumns() * 3) / 4) && (seat_c > hall.getRows() / 4 && seat_c < (hall.getRows() * 3) / 4))
		{
			price += 100;
		}
	}
	return price;
}
void showSeatsVariants(Seat** arr, const unsigned humans, Hall currHall) {
	vector<tuple<unsigned, unsigned, unsigned>> indexes;
	size_t row = currHall.getRows();
	size_t column = currHall.getCollumns();
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
		for (size_t i{}; i != indexes.size(); ++i) {
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
	unsigned seat = 1;
	unsigned currRow, currCol;
	while (humans--)
	{
		do {
			cout << "Выберете место для зрителя " << seat << " (r c): ";
			cin >> currRow >> currCol;

		} while (!checkSeatStatus(currRow - 1, currCol - 1, currHall));
		currHall.SetSeat(currRow - 1, currCol - 1);
		seat++;
	}
}
bool checkSeatStatus(unsigned currRow, unsigned currcol, Hall currHall) {
	if (currHall.GetSeatStatus(currRow, currcol) == '*') {
		cout << "Данное место занято, выберете другое место" << '\n';
		return false;
	}
	return true;
}