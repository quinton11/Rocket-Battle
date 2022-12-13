#include "FileManager.h"

FileManager *FileManager::fInstance = nullptr;
std::string FileManager::fileName = "scores.txt";
std::string FileManager::currentPlayer;
int FileManager::currentScore;
std::map<std::string, int> FileManager::playerScores;

FileManager::FileManager()
{
    // check if file exists
    struct stat buffer;
    // fileName = "scores.txt";
    int te = stat(fileName.c_str(), &buffer);
    bool exists = (te == 0);
    if (!exists)
    {
        // file does not exist, create file
        std::ofstream outfile(fileName);
       // std::cout << "HS File Created" << std::endl;
    }
    else
    {
        //std::cout << "HS File exists" << std::endl;
    }
}

void FileManager::release()
{
    delete fInstance;
    fInstance = nullptr;
}
FileManager::~FileManager()
{
    // delete memory

    // null pointer
}

FileManager *FileManager::getInstance()
{
    return fInstance;
}

void FileManager::createInstance()
{
    if (fInstance == nullptr)
    {
        fInstance = new FileManager();
    }
    bool done = readHS();
    if (done)
    {
       // std::cout << "Entries" << std::endl;
    }
    else
    {
        //std::cout << "No Entries" << std::endl;
    }
    int s = playerScores.size();
    //std::cout << "Entries: " << s << std::endl;
}

// Read all players and highscores to be displayed in highscore screen
bool FileManager::readHS()
{
    // open file
    bool read = false;
    std::ifstream infile(fileName);
    std::string word, subword, pname;
    std::istringstream st;
    int score;

    while (std::getline(infile, word))
    {
        read = true;
        st = std::istringstream(word);
        while (std::getline(st, subword, '\t'))
        {
            if (std::stringstream(subword) >> score)
            {
                score = std::stoi(subword);
            }
            else
            {
                pname = subword;
            }
        }
        playerScores.insert(std::pair<std::string, int>(pname, score));
    }
    // read each line and store in player's:scores map
    // for each line read tab separated values and store in map
    return read;
}

// Take player name and high score and change to new highscore
bool FileManager::writeHS()
{
    // open the file in write mode
    std::ofstream outfile(fileName);
    std::stringstream temp;

    std::map<std::string, int>::iterator it;
    // stringify each entry and push to stream

    for (it = playerScores.begin(); it != playerScores.end(); it++)
    {
        temp << it->first << "\t" << it->second << std::endl;
    }
    // write stream to file
    struct stat buffer;
    // fileName = "scores.txt";
    int te = stat(fileName.c_str(), &buffer);
    bool exists = (te == 0);
    if (!exists)
    {
        // file does not exist, create file
        std::ofstream outfile(fileName);
        //std::cout << "HS File Created" << std::endl;
    }
    outfile << temp.str();
}

bool FileManager::writeHSM(std::string player, int score)
{
    // write to map,and call writeHS to write to file
    bool exists = nameExists(player);
    if (!exists)
    {
        // new player
        playerScores.insert(std::pair<std::string, int>(player, score));
        return true;
    }
    // player exists
    // hence we update the scores
    playerScores[player] = score;
    return false;
}

bool FileManager::nameExists(std::string name)
{
    //std::cout << fileName << std::endl;
    std::map<std::string, int>::iterator it;
    for (it = playerScores.begin(); it != playerScores.end(); it++)
    {
        if (it->first == fileName)
        {
            return true;
        }
    }
    return false;
    // checks if player name is in list of players
}

bool FileManager::replace(std::string n, int s)
{
    // given a name and score replace or update existing entry
    // return true if done else false
}

std::string FileManager::stringify(std::string n, int s)
{
    // get name and highscore and convert to string
    std::ostringstream scorestream;
    scorestream << s;
    std::string score(scorestream.str());

    std::string entry = n + "\t" + score;
    return entry;
}

// we read playerScores map and display players in select player menu
// do same for highscore menu