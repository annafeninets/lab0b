#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <cctype>

using namespace std;

// Структура для хранения слова и его частоты
struct WordFreq {
    string word;
    int count;
    double percent;

    bool operator<(const WordFreq& other) const {
        return count > other.count; // Сортировка по убыванию частоты
    }
};

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 3) {
        cout << "Использование: lab0b.exe input.txt output.csv" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cout << "Ошибка! Не могу открыть " << argv[1] << endl;
        return 1;
    }

    list<string> lines;
    map<string, int> wordCount;
    string line;
    int totalWords = 0;

    // Сохраняем строки и обрабатываем
    while (getline(inputFile, line)) {
        lines.push_back(line);
        string word = "";
        for (int i = 0; i < line.length(); i++) {
            if (isalnum(line[i])) {
                word += line[i];
            } else if (!word.empty()) {
                string clean = word;
                if (!clean.empty()) {
                    wordCount[clean]++;
                    totalWords++;
                }
                word = "";
            }
        }
        if (!word.empty()) {
            string clean = word;
            if (!clean.empty()) {
                wordCount[clean]++;
                totalWords++;
            }
        }
    }
    inputFile.close();

    // Преобразование в список с расчетом процентов и сортировкой
    list<WordFreq> wordFreqList;
    for (map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it) {
        if (totalWords > 0) {
            double freq = (it->second * 100.0) / totalWords;
            wordFreqList.push_back({it->first, it->second, freq});
        }
    }
    wordFreqList.sort();

    // Запись в CSV
    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cout << "Ошибка! Не могу создать " << argv[2] << endl;
        return 1;
    }

    outputFile << "Слово,Частота,Частота (в %)\n";
    for (list<WordFreq>::iterator it = wordFreqList.begin(); it != wordFreqList.end(); ++it) {
        outputFile << it->word << "," << it->count << "," << it->percent << "%\n";
    }
    outputFile.close();

    cout << "Готово! Файл " << argv[2] << " создан." << endl;
    return 0;
}