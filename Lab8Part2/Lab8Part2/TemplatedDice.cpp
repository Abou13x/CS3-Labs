// Games, Template Method example
// Abou Diomande
// 10/19/2022

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl; using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
    Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

    // template method
    void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_ = 0;

        initializeGame();

        for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
            makeMove(i);
            if (i == playersCount_ - 1)
                ++movesCount_;
        }
        printWinner();
    }

    virtual ~Game() {}

protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual void printWinner() = 0;
    virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
    // returns true if winner is decided
    static const int noWinner = -1;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
    // implementing concrete methods
    void initializeGame() {
        playersCount_ = rand() % numPlayers_ + 1; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Monopoly, player " << playerWon_ << " won in "
            << movesCount_ << " moves." << endl;
    }

private:
    static const int numPlayers_ = 8; // max number of players
    static const int minMoves_ = 20; // nobody wins before minMoves_
    static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game {
public:
    void initializeGame() {
        playersCount_ = numPlayers_; // initalize players
        for (int i = 0; i < numPlayers_; ++i)
            experience_[i] = rand() % maxExperience_ + 1;
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = (rand() % maxMoves_) / experience_[player];
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Chess, player " << playerWon_
            << " with experience " << experience_[playerWon_]
            << " won in " << movesCount_ << " moves over"
            << " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
            << endl;
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 2; // nobody wins before minMoves_
    static const int maxMoves_ = 100; // somebody wins before maxMoves_
    static const int maxExperience_ = 5; // player's experience
    // the higher, the greater probability of winning
    int experience_[numPlayers_];
};

//Dice game implementation

class Dice : public Game {
public:
    void initializeGame() {
        playersCount_ = numPlayers_;// initializing variables
        computerPassed_ = false;
        humanPassed_ = false;
    }
    void makeMove(int player) {
        int computerChoice;// temporary variable to keep track or score and choice
        char humanChoice;
        int computerCurrScore;
        int humanCurrScore;
        if (movesCount_ > 0) {
            if (!computerPassed_) { //checking if computer passed
                computerChoice = rand() % 2; //randomizing computer choice
                if (!computerChoice) {
                    computerPassed_ = true;//setting its pass to true
                }
      
            }
            if (!humanPassed_) {
                cout << "Do you want to roll again? [y/n]";
                cin >> humanChoice;
                if (humanChoice == 'n') {//skip if human does not want to roll
                    humanPassed_ = true;
                }
                else if (humanChoice != 'y') {
                    cout << "Invalide input" << endl;
                }

            }
        }

        cout << "Round: "<<movesCount_ + 1<<"  Computer rolled: ";
        if (!computerPassed_) {//only roll if the computer asn't passed
               computerCurrScore = 0;
           for (int i = 0; i < 5; i++) {
               int randNumber = rand() % 6 + 1;
               cout << randNumber << " ";
               computerCurrScore += randNumber; // adding the the computer rolls
           }
           cout << " = " << computerCurrScore;
           //taking the highest score between the previous and current score
           computerScore_ = computerScore_ > computerCurrScore ? computerScore_ : computerCurrScore;
           cout << ", computer's highest score = " << computerScore_ << endl;

        }
        else {
            //if computer passed
            cout << "passed, computer's highest score =  " << computerScore_ << endl;
        }

        cout << "You rolled: ";
        if (!humanPassed_) {//only roll if the human asn't passed
                humanCurrScore = 0;
            for (int i = 0; i < 5; i++) {
                int randNumber = rand() % 6 + 1;
                cout << randNumber << " ";
                humanCurrScore += randNumber; // adding the the human rolls
            }
            cout << " = " << humanCurrScore;
            //taking the highest score between the previous and current score
            humanScore_ = humanScore_ > humanCurrScore ? humanScore_ : humanCurrScore;
            cout << ", your highest score = " << humanScore_ << endl;

        }
        else {
            //if human passed
            cout << "passed, your highest score =  " << humanScore_ << endl;
        }
    }
    //Deciding the winner
    void printWinner() {
        if (computerScore_ >= humanScore_) {
            cout << "You lost!" << endl;
        }
        else {
            cout << "You win!" << endl;
        }
    }
    //ends game if reached 3 rounds or both players passed
    virtual bool endOfGame() {
        if (movesCount_ == 3 || (humanPassed_ && computerPassed_)){
            return true;
        }
        else {
            return false;
        }
    }

private:
    int computerScore_;
    int humanScore_;
    static const int numPlayers_ = 1;
    bool computerPassed_;
    bool humanPassed_;
};

int main() {
    srand(time(nullptr));

    Game* gp = nullptr;

    // play chess 10 times
    for (int i = 0; i < 10; ++i) {
        gp = new Chess;
        gp->playGame();
        delete gp;
    }


    // play monopoly 8 times
    for (int i = 0; i < 8; ++i) {
        gp = new Monopoly;
        gp->playGame();
        delete gp;
    }
    //play dice game
    gp = new Dice;
    gp->playGame();
    delete gp;
}