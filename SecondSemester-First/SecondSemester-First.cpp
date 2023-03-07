#include <iostream>
#include <fstream>

using namespace std;

// Инициализация вспомогательных констант
constexpr char NEW_LINE = '\n';
constexpr char END_OF_STRING = '\0';
constexpr char END_OF_INFO_SYMBOL = '.';
constexpr char COMBINATIONS_SPLIT_SYMBOL = ' ';
constexpr auto EMPTY_STRING = (char*)("");
constexpr auto END_OF_FILE = (char*)("eof");
constexpr auto STRING_MAX_BUFFER_LENGTH = 256;
constexpr auto SYMBOLS_AMOUNT = 256;

// Инициализация полей для взаимодействия с файлом
const char* FILE_NAME = "file.txt";
ifstream file(FILE_NAME);

// Получение длины строки
int getLengthOf(char* str) {
	auto n = 0;

	while (str[n] != END_OF_STRING) n += 1;

	return n;
}

// Чтение строки из файла
char* readLineFromFile(const char endSymbol) {
	if (!file) {
		cout << "Файл " << FILE_NAME << " не найден!\n";
		return END_OF_FILE;
	}

	if (file.peek() == EOF)
		return EMPTY_STRING;

	// Инициализация переменных для чтения строки
	auto* buffer = new char[STRING_MAX_BUFFER_LENGTH] {};
	auto value = (char)file.get();
	auto lineIndex = 0;

	// Добавляем очередной элемент строки в буффер, пока он не равен окончательному символу
	while (value != endSymbol) {
		buffer[lineIndex] = value;
		value = (char)file.get();
		lineIndex += 1;
	}

	if (lineIndex == 0) {
		if (endSymbol == NEW_LINE)
			cout << "\nНе задан список буквосочетаний\n";
		else
			return EMPTY_STRING;
	}

	if (endSymbol == NEW_LINE && lineIndex > 0) {
		buffer[lineIndex] = COMBINATIONS_SPLIT_SYMBOL;
	}

	return buffer;
}

// Получение количества вхождений комбинации в строке
int getCountOfCombinationIn(char* line, char* combination) {
	auto count = 0;
	auto combinationIndex = 0; // "каретка" комбинации
	auto lineIndex = 0;
	auto combinationLength = getLengthOf(combination);

	while (line[lineIndex] != END_OF_STRING) {
		// Если очередной элемент строки равен очередному элементу комбинации, то передвигаем "каретку" комбинации вправо
		// Иначе переносим "каретку" комбинации в изначальное положение (0)
		if (line[lineIndex] == combination[combinationIndex]) {
			combinationIndex += 1;

			// Если "каретка" достигла конца комбинации, то это значит, что мы нашли очередное вхождение комбинации
			if (combinationLength == combinationIndex) {
				count += 1;
				combinationIndex = 0;
			}
		}
		else combinationIndex = 0;

		lineIndex += 1;
	}

	return count;
}

// Вывод количества вхождений каждой комбинации
void displayCountOfLetterCombinationsIn(char* line, char* combinations) {
	auto currentCombination = new char[STRING_MAX_BUFFER_LENGTH];
	auto combinationIndex = 0;
	auto combinationsLineIndex = 0;

	// Разделяем строку комбинаций по пробелу и выводим количество для каждой комбинации
	while (combinations[combinationsLineIndex] != END_OF_STRING) {
		// Если очередной элемент строки не равен пробелу, то передвигаем каретку и добавляем элемент в текущую комбинацию
		// Иначе мы считали очередную комбинацию и выводим её количество
		if (combinations[combinationsLineIndex] != COMBINATIONS_SPLIT_SYMBOL) {
			currentCombination[combinationIndex] = combinations[combinationsLineIndex];
			combinationIndex += 1;
		}
		else {
			currentCombination[combinationIndex] = END_OF_STRING; // Добавляем символ "окочания строки" в конец комбинации

			auto count = getCountOfCombinationIn(line, currentCombination);

			cout << "Количество вхождений " << currentCombination << ": " << count << endl;

			// Очистка памяти и возвращение переменных в исходное значение
			delete[] currentCombination;
			currentCombination = new char[STRING_MAX_BUFFER_LENGTH];
			combinationIndex = 0;
		}

		combinationsLineIndex += 1;
	}

	delete[] currentCombination;
}

// Вывод наиболее часто встречающегося символа
void displayMaxCountOfSymbolIn(char* line) {
	auto* symbolsCounts = new int[SYMBOLS_AMOUNT] {}; // Массив с счётчиками для каждого символа. Индекс символа в массиве = ASCII коду символа
	auto lineIndex = 0;
	auto maxCount = -1;
	auto symbol = '\0';
	auto currentSymbolCode = -1; // ASCII код текущего символа в строке

	while (line[lineIndex] != END_OF_STRING) {
		// Увеличиваем счётчик текущего символа
		currentSymbolCode = line[lineIndex];
		symbolsCounts[currentSymbolCode] += 1;

		// Если текущий счётчик больше максимального, то меняем максимальные счётчик и символ на текущие
		if (symbolsCounts[currentSymbolCode] > maxCount) {
			symbol = line[lineIndex];
			maxCount = symbolsCounts[currentSymbolCode];
		}

		lineIndex += 1;
	}

	cout << "Наиболее часто встречающийся символ: " << symbol << " | Число вхождений: " << maxCount << endl;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	int answer;
	char* combinations = new char[STRING_MAX_BUFFER_LENGTH];
	char* line = new char[STRING_MAX_BUFFER_LENGTH];

	cout << "как вы хотите ввести строки?\n1. с клавитатуры\n2. из файла\n";
	if (!(cin >> answer)) {
		cout << "Ошбика!\n";
		return 0;
	}
	if (answer < 1 && answer>2) {
		cout << "Ошбика!\n";
		return 0;
	}

	if (answer == 1) {
		cout << "\nВведите строку из буквосочетаний:" << endl;;

		cin.ignore();

		cin.getline(combinations, STRING_MAX_BUFFER_LENGTH);
		int length = getLengthOf(combinations);
		combinations[length] = ' ';
		combinations[length + 1] = '\0';

		cout << "\nВведите символьную строку : " << endl;

		cin.getline(line, STRING_MAX_BUFFER_LENGTH);
	}

	// Считывание строк из файла
	if (answer == 2) {
		combinations = readLineFromFile(NEW_LINE);

		if (combinations == END_OF_FILE)
			return EXIT_FAILURE;
		if (combinations == EMPTY_STRING) {
			cout << "Файл " << FILE_NAME << " пустой!\n";
			return EXIT_FAILURE;
		}

		line = readLineFromFile(END_OF_INFO_SYMBOL);

		file.close();

		if (line == EMPTY_STRING) {
			cout << "\nНе задана символьная строка\n";
			return EXIT_FAILURE;
		}
	}

	cout << "\nСимвольная строка: <" << line << ">\n\n";

	// Вывод информации с помощью вспомогательных функций
	displayCountOfLetterCombinationsIn(line, combinations);
	displayMaxCountOfSymbolIn(line);

	return EXIT_SUCCESS; // test from ilya
}