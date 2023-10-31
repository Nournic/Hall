#include <iostream>
#include <string>
#include "classes.cpp"
#include <ctime>
#pragma warning(disable : 4996)
#include <set>
#include <tuple>

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


int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "RU");

	size_t hallsValue; //Количество залов
	Time_t CurrentTime;
	Time_t start_day; //Начало дня, нужно для составления расписания
	Time_t day_end; //Конец дня, нужно для составления расписания
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
	set<unsigned> listHallsWithCurrentFilm;
	unsigned choose_day;
	unsigned count_bilets;


	//Раздача случайно длительности фильмам из массива с именами фильмов
	Time_t filmDuration[10];
	for (size_t i{}; i != 10; ++i) {
		filmDuration[i].setTime(0, durationsFilms[i][0], durationsFilms[i][1], 0, 0, 0);
	}

	cout << "Вид от кассира" << '\n'
		<< "Введите количество кинозалов -> "; // проверки нет
	while (!(cin >> hallsValue) || cin.peek() != 10) {// количество залов
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Введите количество кинозалов -> ";
	}

	cout << "Хотите случайно заполнить залы? (Y/N): ";
	while (!(cin >> otvet) || cin.peek() != 10 || (toupper(otvet) != 'N' && toupper(otvet) != 'Y')) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Хотите случайно заполнить залы? (Y/N): ";
	}
	Hall* hallsList = new Hall[hallsValue];; //Массив с залами, размер задан hallsValue
	if (otvet == 'Y') {
		for (unsigned i{}; i != hallsValue; i++) {
			hallsList[i].SetName(to_string(i + 1));
			hallsList[i].SetMatrix(5 + rand() % 10, 5 + rand() % 10);
			hallsList[i].SetType("general");
		}
	}
	else {
		string name;
		char type;
		for (unsigned i{}; i != hallsValue; i++) {
			cout << "Введите название для кинозала " << i + 1 << " зала -> "; cin >> name;
			hallsList[i].SetName(name); // установка имени зала.
			cout << "Выберите тип зала ('g' - обычный, 's' - с диванами, 'v' - VIP, 'c' - детский) -> "; 
			cin >> type; // установка типа зала.
			hallsList[i].SetType(typeSelect(type));
			cinemaHall(i + 1, hallsList); // задаем параметры количества мест и рядов для каждого объекта в массиве, собств. матрицы.
		}
	}
	cout << "Структура кинозалов настроена. Введённые данные:" << '\n';
	for (unsigned i{}; i != hallsValue; i++) {
		hallsList[i].PrintInfo(); // метод вывода информации, чтобы увидеть результат.
	}
	system("pause");
	system("cls");


	cout << "Вид от покупателя" << '\n';

	// Текущее время
	time_t ttime = time(0);
	tm* now = localtime(&ttime);
	CurrentTime.setTime(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon+1, now->tm_year+1900);
	// заполнение залов фильмами и рандомная рассадка людей
	Time_t temp_t_again;
	temp_t_again.setTime(0, 30, 0, 0, 0, 0);
	for (size_t i{}; i != hallsValue; i++) {
		hallsList[i].randomFillSeats(); // рандомно сажаем людей :)

		start_day.setTime(0, 0, 8, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear());
		day_end.setTime(0, 0, 23, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear());
		
		// Рандомная раздача фильмов залу на 7 дней
		for (unsigned d{ 1 }; d != 8; d++) {
			for (short film{}; film != 8; film++) {
				short random = rand() % 10;

				// Провека, чтобы предыдущий фильм не совпадал со следующим
				if (film != 0) {
					while (hallsList[i].getFilms(d)[film - 1].getName() == filmNames[random]) {
						random = rand() % 10;
					}
				}

				// Добавление фильма в список фильмов на день
				if (start_day < (day_end - filmDuration[random])) {
					hallsList[i].addFilm(filmNames[random], start_day, filmDuration[random], d);
					start_day = start_day + filmDuration[random] + temp_t_again;
				}
			}
			day_end.addTime(0, 0, 0, 1, 0, 0); // переход на следующих день
			start_day.setTime(0, 0, 8, start_day.getDay(), start_day.getMonth(), start_day.getYear());
			start_day.addTime(0, 0, 0, 1, 0, 0);
		}
	};

	// начинается сущий кошмар
	do {
		again = anotherday = false; // 
		do {
			if (anotherday == false) {
				do {
					anotherfilm = false;
					cout << "\nСписок фильмов\n";
					for (size_t i{}; i != 10; ++i) {
						cout << i + 1 << ") " << filmNames[i] << '\n';
					}
					cout << "Хотите посмотреть информацию о каком-либо фильме? (Y/N): "; 
					while (!(cin >> otvet) || cin.peek() != 10 || (toupper(otvet) != 'N' && toupper(otvet) != 'Y')) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Хотите посмотреть информацию о каком-либо фильме? (Y/N): ";
					}
					if (otvet == 'Y') {
						cout << "Введите номер фильма: ";
						while (!(cin >> filmNumber) || cin.peek() != 10) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "Введите номер фильма: ";
						}
						bool exit = false;
						while (exit == false) {
							cout << "\nНазвание: " << filmNames[filmNumber - 1] << "\nЗалы: ";
							bool temp_bool=false;
							for (size_t i{}; i != hallsValue; ++i) {
								for (size_t j{}; j != 8; ++j) {
									if (hallsList[i].getFilms(day)[j].getName() == filmNames[filmNumber - 1] && hallsList[i].getFilms(day)[j].getTimeStart() > CurrentTime) {
										if (temp_bool == false) {
											cout << i + 1 << " ";
											temp_bool = true;
										}
									}
								}
								temp_bool = false;
							}
							cout << "\nДлительность: ";
							cout << durationsFilms[filmNumber - 1][1] << " час";
							if (durationsFilms[filmNumber - 1][1]%10 == 0 || (durationsFilms[filmNumber - 1][1] % 10 <=9 && durationsFilms[filmNumber - 1][1] % 10>=5)) cout << "ов";
							else if (durationsFilms[filmNumber - 1][1]%10 > 1 && durationsFilms[filmNumber - 1][1] % 10 <=4) cout << "а";
							cout <<" " << durationsFilms[filmNumber - 1][0] << " минут";
							if (durationsFilms[filmNumber - 1][0] % 10 == 1) cout << "а";
							else if (durationsFilms[filmNumber - 1][0] % 10 > 1 && durationsFilms[filmNumber - 1][0] % 10 <= 4) cout << "ы";
							cout << "\n\n";
							cout << "Для просмотра предыдущего фильма введите 0, для просмотра следующего фильма введите 1" << '\n'
								<< "Для выхода из режима просмотра введите 2" << '\n'; 
							while (!(cin >> continue_inspection) || cin.peek() != 10 || (continue_inspection<0 && continue_inspection>2)) {
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout << "Для просмотра предыдущего фильма введите 0, для просмотра следующего фильма введите 1" << '\n'
									<< "Для выхода из режима просмотра введите 2" << '\n';
							}
							if (continue_inspection == 0 && filmNumber > 1) filmNumber -= 1;
							else if (continue_inspection == 1 && filmNumber < 10) filmNumber += 1;
							else if (continue_inspection == 2) exit = true;
						}
					}

					continue_inspection = -1;
					choose_number_film = 0;
					anotherfilm = false;
					listHallsWithCurrentFilm.clear();
					cout << "Выберите номер желаемого фильма: ";
					while (!(cin >> choose_number_film) || cin.peek() != 10 || (choose_number_film < 1 && choose_number_film>10)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Выберите номер желаемого фильма: ";
					}
					for (unsigned i{}; i != hallsValue; ++i) {
						for (unsigned j{}; j != 8; ++j) {
							if (hallsList[i].getFilms(day)[j].getName() == filmNames[choose_number_film - 1] && hallsList[i].getFilms(day)[j].getTimeStart() > CurrentTime) {
								listHallsWithCurrentFilm.insert(i + 1);
							}
						}
					}

					if (listHallsWithCurrentFilm.empty()) {
						cout << "К сожалению, данный фильм не показывают сегодня. У вас есть вариант выбрать другой или придти в другой день\n0 - другой фильм\t1 - другой день\n";
						while (!(cin >> continue_inspection) || cin.peek() != 10 || (continue_inspection < 0 && continue_inspection>1)) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "К сожалению, данный фильм не показывают сегодня. У вас есть вариант выбрать другой или придти в другой день\n0 - другой фильм\t1 - другой день\n";
						}
					}

					if (continue_inspection == 1) anotherday = true;
					else if (continue_inspection == 0) anotherfilm = true;
					else if (continue_inspection != -1){
						cout << "Выбран неверный ответ, запущен процесс выбора фильма\n";
					}
				} while (anotherfilm == true);
				if (anotherday == false) {
					cout << "Выберите один из этих залов, в которых можно будет просмотреть фильм сегодня: ";
					for (int n : listHallsWithCurrentFilm)
						cout << n << ' ';
					cout << '\n';
					unsigned currHallNumber{ 0 };
					while (!(cin >> currHallNumber) || cin.peek() != 10 || (currHallNumber < 1 && currHallNumber>currHallNumber)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Выберите один из этих залов, в которых можно будет просмотреть фильм сегодня: ";
						for (int n : listHallsWithCurrentFilm)
							cout << n << ' ';
						cout << '\n';
					}
					if (currHallNumber > 0) currHallNumber -= 1;

                    //вывод залов с заданным фильмом
                    unsigned mins, hours;
                    char UserChooseTime = 'N';
                    Film chooseFilm;
                    chooseFilm.setStart(23, 23, 23, 23, 23, 23);
                    Film temp;
                    temp.setStart(23, 23, 23, 23, 23, 23);
                    cout << "Вы хотите выбрать время? (Y/N): ";
					while (!(cin >> UserChooseTime) || cin.peek() != 10 || (toupper(UserChooseTime) != 'N' && toupper(UserChooseTime) != 'Y')) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Вы хотите выбрать время? (Y/N): ";
					}
                    if (UserChooseTime == 'Y') {
                        do {
							Film temp_film;
                            for (size_t i{}; i != 8; ++i) {
                                temp_film = hallsList[currHallNumber].getFilms(day)[i];
                                if (filmNames[choose_number_film - 1] == temp_film.getName() && temp_film.getTimeStart() > CurrentTime ) {
                                    cout << "Время начала: "; hallsList[currHallNumber].getFilms(day)[i].getTimeStart().printTimeWithoutSeconds();
									cout << '\n'; 
                                }
                            }
                            cout << "Введите время начала фильма (часы и минуты через пробел): ";
                            cin >> hours >> mins;
							while (!(cin >> hours) || !(cin >> mins) || cin.peek() != 10 || (toupper(UserChooseTime) != 'N' && toupper(UserChooseTime) != 'Y')) {
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout << "Введите время начала фильма (часы и минуты через пробел): ";
							}
                            for (size_t i{}; i != 8; ++i) {
                                if (hallsList[currHallNumber].getFilms(day)[i].getTimeStart().getHour() == hours && hallsList[currHallNumber].getFilms(day)[i].getTimeStart().getMin() == mins) {
                                    Time_t timee;
                                    timee.setTime(hallsList[currHallNumber].getFilms(day)[i].getTimeStart().getSec(), hallsList[currHallNumber].getFilms(day)[i].getTimeStart().getMin(), hallsList[currHallNumber].getFilms(1)[i].getTimeStart().getHour(), CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear());
                                    if (timee > CurrentTime) {
                                        chooseFilm = hallsList[currHallNumber].getFilms(day)[i];
                                    }
                                }
                            }
                        } while (chooseFilm.getTimeStart() == temp.getTimeStart());
                    }

					count_bilets = 0;					
					hallsList[currHallNumber].PrintMatrix();
					unsigned count_bilets;
					cout << "Сколько билетов купить: "; cin >> count_bilets;
					char showVariants;
					bool choose_hand = false;
					cout << "Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N): "; cin >> showVariants;
					if (showVariants == 'Y') { // Вывод вариантов рассадки
						showSeatsVariants(hallsList[currHallNumber].getMatrix(), count_bilets, hallsList[currHallNumber]);
					}
					// Ручной выбор мест
					fillSeatsByUser(count_bilets, hallsList[currHallNumber]);
					hallsList[currHallNumber].PrintMatrix();
					Time_t temp_t;

					temp_t.setTime(0, hallsList[currHallNumber].getFilms(day)[choose_number_film - 1].getTimeStart().getMin(), hallsList[currHallNumber].getFilms(day)[choose_number_film - 1].getTimeStart().getHour(), 0, 0, 0);
					hallsList[currHallNumber].addProfit(TicketCost(temp_t, hallsList[currHallNumber], 1, 1)*count_bilets);
					complete = true;
						
                    }
                    
                
            }
			if (anotherday == true && day == 1 && complete==false) {

				cout << "Вывод выбранного фильма на неделю\n";
				Time_t temp_time;
				temp_time = CurrentTime;
				for (unsigned d{ day + 1 }; d != 8; d++) {
					unsigned c = 0;
					temp_time.addTime(0, 0, 0, 1, 0, 0);
					for (unsigned i{}; i != hallsValue; ++i) {
						for (unsigned j{}; j != 8; ++j) {
							if (hallsList[i].getFilms(d)[j].getName() == filmNames[choose_number_film - 1]) {
								c += 1;
							}
						}
					}
					if (c != 0) {
						bool abc = false;;
						cout << temp_time.getDay() << " число: ";
						for (unsigned i{}; i != hallsValue; ++i) {
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
				cin >> choose_day;

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

				for (unsigned i{}; i != hallsValue; ++i) {
					for (unsigned j{}; j != 8; ++j) {
						if (hallsList[i].getFilms(day)[j].getName() == filmNames[choose_number_film - 1]) {
							curr_hall = i;
						}
					}
				}
				if (curr_hall != -1) {
					cout << "Рассадка на выбранный день\n";
					hallsList[curr_hall].PrintMatrix();
					cout << "Сколько билетов купить: "; cin >> count_bilets;
					char showVariants;
					bool choose_hand = false;
					cout << "Хотите увидеть варианты рассадки согласно купленным билетам? (Y/N): "; cin >> showVariants;
					if (showVariants == 'Y') { // Вывод вариантов рассадки
						showSeatsVariants(hallsList[curr_hall].getMatrix(), count_bilets, hallsList[curr_hall]);
					}
					// Ручной выбор мест
					fillSeatsByUser(count_bilets, hallsList[curr_hall]);
					hallsList[curr_hall].PrintMatrix();
					hallsList[curr_hall].addProfit(250*count_bilets);
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
	for (size_t i{}; i != hallsValue; ++i) {
		profit += hallsList[i].getProfit();
	}
	cout << "Кинозал получил прибыли: " << profit;

	return 0;
}

void cinemaHall(unsigned k, Hall* halls) // функция задает размеры залов.
{
	unsigned cols, rows; // количество мест в ряду, рядов.
	cout << "Выберите размеры для " << k << "-го кинозала." << '\n'; // 2 таких зала.
	cout << "Введите количество рядов в зале -> "; cin >> rows;
	cout << "Введите количество мест в каждом ряду -> "; cin >> cols;
	halls[k - 1].SetMatrix(rows, cols); // просто заполняет матрицы элементов массива залов за счёт встроенного метода.
}

string typeSelect(char tp) // отдельная функция выбора типа кинозала.
{
	switch (tp) {
	case 'g':
		cout << "Выбран вариант: обычный" << '\n';
		return "general";
	case 's':
		cout << "Выбран вариант: с диванами" << '\n';
		return "soft";
	case 'v':
		cout << "Выбран вариант: VIP" << '\n';
		return "VIP";
	case 'c':
		cout << "Выбран вариант: детский" << '\n';
		return "children's";
	default:
		cout << "Вы ввели неверный символ, автоматически выбран вариант: обычный" << '\n';
		return "general";
	}
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
		cout << "Выберете место для зрителя " << seat << " (r c): ";
		cin >> currRow >> currCol;
		currHall.SetSeat(currRow - 1, currCol - 1);
		seat++;
	}
}