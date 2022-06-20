#include "algorithms.h"

void SRepeatFinder::calc(std::string& s){
    for(long long i = 0; i < s.length(); i++){
        if(mp.find(s[i]) == mp.end())mp[s[i]] = 1;
        else mp[s[i]]++;
    }
}


void SRepeatFinder::calc(QString& s){
    for(int i = 0; i < s.length(); i++){
        if(mp2.find(s[i]) == mp2.end())mp2[s[i]] = 1;
        else mp2[s[i]]++;
    }
}


std::unordered_map<char, int> SRepeatFinder::get_data(){
    return mp;
}

QMap<QChar, int> SRepeatFinder::get_qdata()
{
    return mp2;
}


void SRepeatFinder::clear(){
    mp.clear();
    mp2.clear();
}


void LengthSorter::calc(std::string& s){
    long long n = -1;

    long long n2 = s.find(' ');
    if(n2 == std::string::npos)n2 = s.length() - 1;
    std::string word;
    long long len;

    while(n2 != std::string::npos){
        if(n2 - n - 1 > 0){
            word = s.substr(n + 1, n2 - n - 1);
            len = word.length();
            if(len > 0){
                if(mp.find(len) == mp.end())mp[len] = {word};
                else mp[len].push_back(word);
            }
        }
        n = n2;
        n2 = s.find(' ', n2 + 1);
    }
    word = s.substr(n + 1, s.length() - n - 2);
    len = word.length();
    if(len > 0){
        if(mp.find(len) == mp.end())mp[len] = {word};
        else mp[len].push_back(word);
    }
}



void LengthSorter::calc(QString& s){
    QStringList qlist = s.split(" ");
    for(QString word: qlist){
        long long len = word.length();
        if(mp2.find(len) == mp2.end())mp2[len] = {word};
        else mp2[len].push_back(word);
    }
//    long long n = -1;

//    long long n2 = s.find(' ');
//    if(n2 == std::string::npos)n2 = s.length() - 1;
//    std::string word;
//    long long len;

//    while(n2 != std::string::npos){
//        if(n2 - n - 1 > 0){
//            word = s.substr(n + 1, n2 - n - 1);
//            len = word.length();
//            if(mp.find(len) == mp.end())mp[len] = {word};
//            else mp[len].push_back(word);
//        }
//        n = n2;
//        n2 = s.find(' ', n2 + 1);
//    }
//    word = s.substr(n + 1, s.length() - n - 2);
//    len = word.length();
//    if(mp.find(len) == mp.end())mp[len] = {word};
//    else mp[len].push_back(word);
}


std::map<int, std::vector<std::string>> LengthSorter::get_data(){
    return mp;
}

QMap<int, QVector<QString> > LengthSorter::get_qdata()
{
    return mp2;
}

void LengthSorter::clear()
{
    mp.clear();
    mp2.clear();
}
