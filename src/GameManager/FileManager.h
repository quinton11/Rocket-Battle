#pragma once
#include <iostream>
#include <fstream>
#include "sys/stat.h"
#include "string"
#include "vector"
#include "sstream"
#include "map"

class FileManager
{
private:
    static std::string fileName;

    static std::fstream scorefile;
    static std::vector<std::string> players;
    static FileManager *fInstance;
    static bool nameExists(std::string name);
    static bool replace(std::string n, int s);
    std::string stringify(std::string n, int s);
    FileManager();
    ~FileManager();

public:
    static std::string currentPlayer;
    static int currentScore;
    static std::map<std::string, int> playerScores;
    static FileManager *getInstance();
    static void createInstance();
    static void release();
    static bool readHS();
    static bool writeHS();
    static bool writeHSM(std::string player, int score);
};