#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>

const int SIZE = 10;

enum Cell {
    EMPTY = '~',
    SHIP = 'S',
    HIT = 'X',
    MISS = 'O'
};

class BattleField {
private:
    std::vector<std::vector<char>> field;
    int shipsLeft;

    bool canPlaceShip(int x, int y, int length, bool horizontal) const {
        for (int i = -1; i <= length; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = horizontal ? x + i : x + j;
                int ny = horizontal ? y + j : y + i;
                if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                    if (field[nx][ny] == SHIP) return false;
                }
            }
        }
        for (int i = 0; i < length; ++i) {
            int nx = horizontal ? x + i : x;
            int ny = horizontal ? y : y + i;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE) return false;
        }
        return true;
    }

    void placeShip(int x, int y, int length, bool horizontal) {
        for (int i = 0; i < length; ++i) {
            int nx = horizontal ? x + i : x;
            int ny = horizontal ? y : y + i;
            field[nx][ny] = SHIP;
        }
        shipsLeft += length;
    }

public:
    BattleField() : field(SIZE, std::vector<char>(SIZE, EMPTY)), shipsLeft(0) {}

    void placeShipsRandomly() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, SIZE - 1);
        std::uniform_int_distribution<> dir(0, 1);

        int shipCounts[] = {4, 3, 2, 1}; // 1 four-deck, 2 three-deck, etc.
        int shipLengths[] = {1, 2, 3, 4};

        for (int type = 0; type < 4; ++type) {
            for (int count = 0; count < shipCounts[type]; ++count) {
                bool placed = false;
                while (!placed) {
                    int x = dis(gen);
                    int y = dis(gen);
                    bool horizontal = dir(gen);
                    int len = shipLengths[type];
                    if (canPlaceShip(x, y, len, horizontal)) {
                        placeShip(x, y, len, horizontal);
                        placed = true;
                    }
                }
            }
        }
    }

    bool shoot(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return false;
        if (field[x][y] == HIT || field[x][y] == MISS) return false;

        if (field[x][y] == SHIP) {
            field[x][y] = HIT;
            shipsLeft--;
            return true;
        } else {
            field[x][y] = MISS;
            return false;
        }
    }

    bool allShipsSunk() const {
        return shipsLeft == 0;
    }

    void print(bool hideShips = false) const {
        std::cout << "  ";
        for (int i = 0; i < SIZE; ++i) std::cout << i << " ";
        std::cout << "\n";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << i << " ";
            for (int j = 0; j < SIZE; ++j) {
                if (hideShips && field[i][j] == SHIP)
                    std::cout << EMPTY << " ";
                else
                    std::cout << field[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "Добро пожаловать в Морской бой!\n";
    std::cout << "Координаты вводятся как: строка столбец (например: 3 5)\n\n";

    BattleField playerField, computerField;
    playerField.placeShipsRandomly();
    computerField.placeShipsRandomly();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, SIZE - 1);

    while (true) {
        std::cout << "\n--- Ваше поле ---\n";
        playerField.print();
        std::cout << "\n--- Поле компьютера ---\n";
        computerField.print(true);

        int x, y;
        std::cout << "\nВаш ход (строка столбец): ";
        if (!(std::cin >> x >> y)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            std::cout << "Координаты вне поля. Попробуйте снова.\n";
            continue;
        }

        bool hit = computerField.shoot(x, y);
        if (hit) {
            std::cout << "Попадание!\n";
            if (computerField.allShipsSunk()) {
                std::cout << "\nПоздравляем! Вы победили!\n";
                break;
            }
        } else {
            std::cout << "Мимо!\n";
        }

        // Ход компьютера
        std::cout << "\nХод компьютера...\n";
        bool compHit;
        do {
            x = dis(gen);
            y = dis(gen);
            compHit = playerField.shoot(x, y);
        } while (!compHit && !(playerField.allShipsSunk())); // Простая стратегия: случайные выстрелы

        if (compHit) {
            std::cout << "Компьютер попал в (" << x << ", " << y << ")!\n";
            if (playerField.allShipsSunk()) {
                std::cout << "\nКомпьютер потопил все ваши корабли. Вы проиграли!\n";
                break;
            }
        } else {
            std::cout << "Компьютер промахнулся (" << x << ", " << y << ").\n";
        }
    }

    std::cout << "\n--- Финальное поле компьютера ---\n";
    computerField.print(); // Показываем корабли компьютера в конце

    return 0;
}
