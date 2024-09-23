#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>    
#include <thread>    
#include <algorithm> 
#include <random>    

using namespace std;

void delayMessage(string message, int delayTime = 3) {
    cout << message << endl;
    this_thread::sleep_for(chrono::seconds(delayTime)); 
}

bool coinFlip() {
    return rand() % 2; 
}

int main() {
    srand(time(0)); 

    
    int bulletChamber[6] = {0, 0, 0, 0, 0, 1};

    
    random_device rd;
    mt19937 g(rd());

    shuffle(begin(bulletChamber), end(bulletChamber), g);

    bool playerPass = false;
    bool botPass = false;

    delayMessage("Welcome to Russian Roulette!");
    delayMessage("O' someone who is ready to lose it all...");
    delayMessage("Now, who will go first?");
    delayMessage("Let's start with a good ol' coinflip, shall we?");
    
    string playerChoice;
    while (true) {
        cout << "Choose heads or tails (h/t): ";
        cin >> playerChoice;
        if (playerChoice == "h" || playerChoice == "t") {
            break;
        }
        cout << "Invalid choice! Please enter 'h' for heads or 't' for tails." << endl;
    }

    bool isHeads = coinFlip();
    bool playerStarts = (playerChoice == "h" && isHeads) || (playerChoice == "t" && !isHeads);

    if (playerStarts) {
        delayMessage("The coin flip shows: You go first.");
    } else {
        delayMessage("The coin flip shows: The bot goes first.");
    }

    int turn = playerStarts ? 0 : 1; 
    int bulletPosition = 0;
    
    while (true) {
        if (turn == 0) { 
            if (bulletPosition >= 6) {
                bulletPosition = 0;
            }
            
            string action;
            while (true) {
                cout << "Your turn! Choose 'hit' or 'pass': ";
                cin >> action;
                if (action == "hit" || (action == "pass" && !playerPass)) {
                    break; 
                } else if (action == "pass" && playerPass) {
                    cout << "You can only pass once!" << endl;
                } else {
                    cout << "Invalid choice! Please enter 'hit' or 'pass'." << endl;
                }
            }

            if (action == "pass") {
                playerPass = true;
                delayMessage("You passed the turn.");
                turn = 1; 
                continue;
            }

            
            if (bulletChamber[bulletPosition] == 1) {
                delayMessage("BANG!");
                delayMessage("YOU DIED");
                delayMessage("DELETING Program32...");
                break;
            } else {
                delayMessage("Click");
                delayMessage("You're safe.");
            }
            turn = 1; 
        } else { 
            if (bulletPosition >= 6) {
                bulletPosition = 0; 
            }

            if (!botPass && rand() % 2 == 0) {
                delayMessage("The bot passed the turn.");
                botPass = true;
                turn = 0; 
                continue;
            }

            delayMessage("Bot's turn...");
            
            if (bulletChamber[bulletPosition] == 1) {
                delayMessage("BANG!");
                delayMessage("CONGRATULATIONS YOU WIN!");
                delayMessage("You got nothing but this proves how lucky you are.");
                break;
            } else {
                delayMessage("Click");
                delayMessage("The opponent stays strong.");
            }
            turn = 0;
        }
        bulletPosition++;
    }

    return 0;
}

