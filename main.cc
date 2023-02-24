#include "map.h"
#include <unistd.h>
#include "actor.h"
#include <memory>

const int MAX_FPS = 90; //Cap frame rate 
const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

//Turns on full screen text mode
void turn_on_ncurses() {
    initscr();//Start curses mode
    start_color(); //Enable Colors if possible
    init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
    init_pair(2,COLOR_CYAN,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    clear();
    noecho();
    cbreak();
    timeout(TIMEOUT); //Set a max delay for key entry
}

//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
    clear();
    endwin(); // End curses mode
    if (system("clear")) {}
}

int main() {
    turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
    Map map;
    int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
    int old_x = -1, old_y = -1;
    
    //MY CODE START ********************************************************************
    
    turn_off_ncurses();
    
    string tempCharName;
    int tempSpeed;
    string tempType;
    int count = 0;
    int tempMoney = 0;
    
    vector<shared_ptr<Actor>> vec;

    Actor actorChar;
    bool actorTaken = false;
    Hero heroChar;
    bool heroTaken = false;
    Tiefling tieChar;
    bool tieflingTaken = false;
    Elf elfChar;
    bool elfTaken = false;
    Gnome gnomeChar;
    bool gnomeTaken = false;

    while (true) {

        if(actorTaken && heroTaken && tieflingTaken && elfTaken && gnomeTaken) {
            cout << "All types taken!! Let's begin" << endl;
            break;
        }

        cout << "Adding a new player? Pick a type " << endl;
        cout << "Available Types: ";

        if (!actorTaken) cout << "Actor, ";
        if (!heroTaken) cout << "Hero, ";
        if (!tieflingTaken) cout << "Tiefling, ";
        if (!elfTaken) cout << "Elf, ";
        if (!gnomeTaken) cout << "Gnome";
        
        cout << endl;

        cout << "--or if 'done' type done--" << endl;
        cin >> tempType;

        count++;

        for (int i = 0; i < tempType.size(); i++) {
            tempType.at(i) = toupper(tempType.at(i));
        }

        if (tempType == "DONE") break;

        if (tempType != "TIEFLING" && tempType != "ELF" && tempType != "GNOME"
                && tempType != "ACTOR" && tempType != "HERO"){
            cout << "Enter Valid Type!!" << endl;
            continue;
        }

        if((tempType == "ACTOR" && actorTaken) || (tempType == "HERO" && heroTaken) ||
                (tempType == "TIEFLING" && tieflingTaken) || (tempType == "ELF" && elfTaken) ||
                (tempType == "GNOME" && gnomeTaken) ) {
            cout << "*Type already taken! Pick another*\n" << endl;
            count--;
            continue;
        }

         cout << "Enter Character " << count << " name: ";
         cin >> tempCharName;

         cout << "Enter Character " << count << " speed: ";
         cin >> tempSpeed;

        if (tempType == "ACTOR") {

            actorChar.SetName(tempCharName);
            actorChar.SetSpeed(tempSpeed);

            vec.push_back(make_shared<Actor>(actorChar));

            actorTaken = true;

        }
        else if (tempType == "HERO") {

            heroChar.SetName(tempCharName);
            heroChar.SetSpeed(tempSpeed);

            cout << "Enter amount of Character " << count << " money: ";
            cin >> tempMoney;
            heroChar.AddMoney(tempMoney);

            vec.push_back(make_shared<Hero>(heroChar));

            heroTaken = true;
        }
        else if (tempType == "TIEFLING") {

            tieChar.SetName(tempCharName);
            tieChar.SetSpeed(tempSpeed);

            cout << "Enter amount of Character " << count << " money: ";
            cin >> tempMoney;
            tieChar.AddMoney(tempMoney);

            int fireDamage = 0;
            cout << "Enter fire damage: ";
            cin >> fireDamage;
            tieChar.SetFire(fireDamage);

            vec.push_back(make_shared<Tiefling>(tieChar));

            tieflingTaken = true;
        }
        else if(tempType == "ELF") {

            elfChar.SetName(tempCharName);
            elfChar.SetSpeed(tempSpeed);

            cout << "Enter amount of Character " << count << " money: ";
            cin >> tempMoney;
            elfChar.AddMoney(tempMoney);

            char magic;
            cout << "Is this character magic (y or n): ";
            cin >> magic;
            if(magic == 'y') {
                elfChar.SetIsMagic(true);
            }

            elfTaken = true;
        }
        else if(tempType == "GNOME") {

            gnomeChar.SetName(tempCharName);
            gnomeChar.SetSpeed(tempSpeed);

            cout << "Enter amount of Character " << count << " money: ";
            cin >> tempMoney;
            gnomeChar.AddMoney(tempMoney);

            char tools;
            cout << "Does this character have tools? (y or n): ";
            cin >> tools;
            if (tools == y) {
                gnomeChar.SetHasTools(true);
            }
            gnomeTaken = true;
        }

        cout << endl;
    }

    turn_on_ncurses();

    //END MY CODE ********************************************************

    while (true) {
        int ch = getch(); // Wait for user input, with TIMEOUT delay
        if (ch == 'q' || ch == 'Q') break;
        else if (ch == RIGHT) {
            x++;
            if (x >= Map::SIZE) x = Map::SIZE - 1; //Clamp value
        }
        else if (ch == LEFT) {
            x--;
            if (x < 0) x = 0;
        }
        else if (ch == UP) {
            /* If you want to do cin and cout, turn off ncurses, do your thing, then turn it back on
            turn_off_ncurses();
            string s;
            cin >> s;
            cout << s << endl;
            sleep(1);
            turn_on_ncurses();
            */
            y--;
            if (y < 0) y = 0;
        }
        else if (ch == DOWN) {
            y++;
            if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
        }
        else if (ch == ERR) { //No keystroke
            ; //Do nothing
        }
        //Stop flickering by only redrawing on a change
        if (x != old_x or y != old_y) {
            /* Do something like this, idk 
            if (map.get(x,y) == Map::TREASURE) {
                map.set(x,y,Map::OPEN);
                money++;
            } else if (map.get(x,y) == Map::WALL) {
                x = old_x;
                y = old_y;
            }
            */
            //clear(); //Put this in if the screen is getting corrupted
            map.draw(x,y);
            mvprintw(Map::DISPLAY+1,0,"X: %i Y: %i\n",x,y);
            refresh();
        }
        old_x = x;
        old_y = y;
        usleep(1'000'000/MAX_FPS);
    }
    turn_off_ncurses();

}
