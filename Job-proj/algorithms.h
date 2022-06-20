#pragma once
#define DEBUG

#include<unordered_map>
#include<map>
#include<vector>
#include<string>
#include <QString>
#include <QVector>
#include <QMap>
#ifdef DEBUG
#include <typeinfo>
#endif


class Algorithm
{
public:
    virtual void calc(QString& s);
    virtual void calc(std::string& s);
    virtual void clear();
};

// Анализировать файл будем построчно.
// Сделано так, чтобы анализировать файл построчно, т.к есть вероятность, что размер полученной из файла строки будет больше, чем может вместить в себя string

class SRepeatFinder// Нахождение повторений каждого символа
{
private:
    std::unordered_map<char, int>mp;
    QMap<QChar, int>mp2;// словарь (буква, кол-во повторений)
public:
    void calc(std::string& s);
    void calc(QString& s1);
    std::unordered_map<char, int> get_data();
    QMap<QChar, int> get_qdata();
    void clear();
};


class LengthSorter // Распределение слов по их длинам.
{
private:
    std::map<int, std::vector<std::string>>mp;
    QMap<int, QVector<QString>>mp2;// словарь (длина слова, кол-во слов n-ой длины)
public:
    void calc(std::string& s);
    void calc(QString& s);
    std::map<int, std::vector<std::string>> get_data();
    QMap<int, QVector<QString>> get_qdata();
    void clear();
    //std::unordered_map<int, std::string>& get_map(std::string);
};
