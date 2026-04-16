Вариант 16. Определить структурный тип, описывающий расписание маршрутов электропоездов 
 (название маршрута, пункт отправления, пункт прибытия, время отправления, время
 прибытия, количество вагонов, тип электропоезда : товарный, пассажирский,
 ремонтный и др.).Заполнить структурный массив 20 - с записями.Переписать из
 исходного массива в другой массив, информацию только о тех пассажирских
 маршрутах, что идут в туристические города.Затем новый массив отсортировать по
 пункту отправления вагонов.Вывести все данные по конкретному электропоезду.
 Вывести 3 самых коротких пассажирских поезда.Реализовать функцию изменения
 данных о маршруте.Реализовать вывод отфильтрованных данных в виде оберточной функции.

#include <iostream>
#include <cstring>
#include <clocale>

using namespace std;

enum TrainType {
    PASSENGER,
    FREIGHT,
    REPAIR,
    OTHER
};

struct Time {
    int hours;
    int minutes;
};

struct Route {
    char nameRoute[50];
    char depPoint[50];
    char arrPoint[50];
    Time depTime;
    Time arrTime;
    int wagonCount;
    TrainType type;
};

bool isTouristCity(const char* city) {
    if (strcmp(city, "Сочи") == 0 ||
        strcmp(city, "Адлер") == 0 ||
        strcmp(city, "Казань") == 0 ||
        strcmp(city, "Санкт-Петербург") == 0 ||
        strcmp(city, "Калининград") == 0 ||
        strcmp(city, "Минеральные Воды") == 0 ||
        strcmp(city, "Кисловодск") == 0 ||
        strcmp(city, "Ялта") == 0 ||
        strcmp(city, "Севастополь") == 0) {
        return true;
    }
    return false;
}

void initData(Route arr[], int size) {
    auto setRoute = [](Route& r, const char* name, const char* from, const char* to,
        int h1, int m1, int h2, int m2, int wag, TrainType t) {
            strcpy_s(r.nameRoute, name);
            strcpy_s(r.depPoint, from);
            strcpy_s(r.arrPoint, to);
            r.depTime.hours = h1;   r.depTime.minutes = m1;
            r.arrTime.hours = h2;   r.arrTime.minutes = m2;
            r.wagonCount = wag;
            r.type = t;
        };

    setRoute(arr[0], "Ласточка-Юг", "Москва", "Сочи", 8, 0, 20, 30, 10, PASSENGER);
    setRoute(arr[1], "Волга-Экспресс", "Москва", "Казань", 7, 15, 14, 45, 12, PASSENGER);
    setRoute(arr[2], "Балтийский ветер", "Москва", "Калининград", 18, 0, 10, 0, 15, PASSENGER);
    setRoute(arr[3], "Кавказ", "Москва", "Минеральные Воды", 19, 20, 16, 40, 18, PASSENGER);
    setRoute(arr[4], "Ласточка-Крым", "Москва", "Севастополь", 14, 0, 10, 0, 12, PASSENGER);
    setRoute(arr[5], "Подмосковные вечера", "Москва", "Тверь", 6, 0, 8, 30, 6, PASSENGER);
    setRoute(arr[6], "Ока", "Москва", "Нижний Новгород", 7, 0, 11, 0, 8, PASSENGER);
    setRoute(arr[7], "Сибирь", "Новосибирск", "Омск", 10, 0, 14, 0, 12, PASSENGER);
    setRoute(arr[8], "Урал", "Екатеринбург", "Пермь", 9, 0, 13, 0, 10, PASSENGER);
    setRoute(arr[9], "Дон", "Москва", "Ростов-на-Дону", 20, 0, 8, 0, 16, PASSENGER);
    setRoute(arr[10], "Грузовой Север", "Мурманск", "Москва", 12, 0, 23, 0, 50, FREIGHT);
    setRoute(arr[11], "Уголь-Восток", "Кемерово", "Новосибирск", 5, 0, 12, 0, 60, FREIGHT);
    setRoute(arr[12], "Ремонтник-1", "Депо Москва", "Депо Тула", 2, 0, 4, 0, 2, REPAIR);
    setRoute(arr[13], "Грузовой Юг", "Ростов-на-Дону", "Краснодар", 15, 0, 18, 0, 40, FREIGHT);
    setRoute(arr[14], "Ремонтник-2", "Депо СПб", "Депо Выборг", 3, 0, 5, 30, 3, REPAIR);
    setRoute(arr[15], "Аллегро", "Санкт-Петербург", "Хельсинки", 8, 0, 11, 30, 8, PASSENGER);
    setRoute(arr[16], "Экспресс-Юг", "Краснодар", "Сочи", 9, 0, 12, 0, 8, PASSENGER);
    setRoute(arr[17], "Пригородный", "Москва", "Владимир", 17, 0, 19, 30, 4, PASSENGER);
    setRoute(arr[18], "Турист-Байкал", "Иркутск", "Улан-Удэ", 10, 0, 12, 0, 10, PASSENGER);
    setRoute(arr[19], "Сапсан-Север", "Санкт-Петербург", "Москва", 9, 0, 12, 30, 10, PASSENGER);
}

void printRoute(const Route& r) {
    cout << r.nameRoute << "\t\t";
    cout << r.depPoint << "\t\t";
    cout << r.arrPoint << "\t\t";
    cout << r.depTime.hours << ":";
    if (r.depTime.minutes < 10) cout << "0";
    cout << r.depTime.minutes << "\t";
    cout << r.wagonCount << "\t\t";
    switch (r.type) {
    case PASSENGER: cout << "Пасс."; break;
    case FREIGHT:   cout << "Груз."; break;
    case REPAIR:    cout << "Рем.";  break;
    default:        cout << "Проч."; break;
    }
    cout << endl;
}

void printHeader() {
    cout << "Название\t\tОткуда\t\tКуда\t\tВремя\tВагоны\tТип" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}

int filterTouristPassenger(const Route source[], int srcSize, Route dest[]) {
    int count = 0;
    for (int i = 0; i < srcSize; ++i) {
        if (source[i].type == PASSENGER && isTouristCity(source[i].arrPoint)) {
            dest[count] = source[i];
            count++;
        }
    }
    return count;
}

void bubbleSortByDepPoint(Route arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (strcmp(arr[j].depPoint, arr[j + 1].depPoint) > 0) {
                Route temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void findByName(const Route arr[], int size, const char* name) {
    cout << "\n--- Поиск: " << name << " ---" << endl;
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (strcmp(arr[i].nameRoute, name) == 0) {
            printHeader();
            printRoute(arr[i]);
            found = true;
        }
    }
    if (!found) cout << "Не найдено" << endl;
}

void findShortestTrains(const Route arr[], int size) {
    Route passArr[20];
    int passCount = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == PASSENGER) {
            passArr[passCount] = arr[i];
            passCount++;
        }
    }
    if (passCount == 0) return;
    for (int i = 0; i < passCount - 1; ++i) {
        for (int j = 0; j < passCount - i - 1; ++j) {
            if (passArr[j].wagonCount > passArr[j + 1].wagonCount) {
                Route temp = passArr[j];
                passArr[j] = passArr[j + 1];
                passArr[j + 1] = temp;
            }
        }
    }
    cout << "\n--- 3 самых коротких пассажирских поезда ---" << endl;
    printHeader();
    int limit = (passCount < 3) ? passCount : 3;
    for (int i = 0; i < limit; ++i) {
        printRoute(passArr[i]);
    }
}

void updateRoute(Route arr[], int size, const char* name) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(arr[i].nameRoute, name) == 0) {
            cout << "\nНайден: " << arr[i].nameRoute << endl;
            cout << "Текущее кол-во вагонов: " << arr[i].wagonCount << endl;
            cout << "Введите новое значение: ";
            cin >> arr[i].wagonCount;
            cout << "Обновлено" << endl;
            return;
        }
    }
    cout << "Маршрут не найден" << endl;
}

void displayFilteredWrapper(const Route arr[], int size) {
    cout << "\n=== ПАССАЖИРСКИЕ В ТУРИСТИЧЕСКИЕ ГОРОДА (отсортировано) ===" << endl;
    if (size == 0) {
        cout << "Список пуст" << endl;
        return;
    }
    printHeader();
    for (int i = 0; i < size; ++i) {
        printRoute(arr[i]);
    }
    cout << "================================================================================" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int SIZE = 20;
    Route allRoutes[SIZE];
    initData(allRoutes, SIZE);
    printHeader();
    for (int i = 0; i < SIZE; ++i) {
        printRoute(allRoutes[i]);
    }
    Route touristRoutes[SIZE];
    int touristCount = filterTouristPassenger(allRoutes, SIZE, touristRoutes);
    cout << "\nНайдено маршрутов в туристические города: " << touristCount << endl;
    bubbleSortByDepPoint(touristRoutes, touristCount);
    displayFilteredWrapper(touristRoutes, touristCount);
    findByName(allRoutes, SIZE, "Ласточка-Юг");
    findShortestTrains(allRoutes, SIZE);
    updateRoute(allRoutes, SIZE, "Ока");
    findByName(allRoutes, SIZE, "Ока");
    return 0;
}
