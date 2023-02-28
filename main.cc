#include "map.h"
#include <unistd.h>
#include "actor.h"
#include <memory>
#include <algorithm>

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

//Ella function
bool sortTheVec(const shared_ptr<Actor> &lhs, const shared_ptr<Actor> &rhs) {
    return lhs->GetSpeed() < rhs->GetSpeed();
}
//end Ella Function


int main() {
    turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
    Map map;
    int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
    int old_x = -1, old_y = -1;
    
    //Ella code start
    
    turn_off_ncurses();
    
     string tempCharName;
    int tempSpeed;
    string tempType;
    int count = 0;
    int tempMoney = 0;
    
    vector<shared_ptr<Actor>> vec;
    
    Tiefling tieChar;
    bool tieflingTaken = false;
    Elf elfChar;
    bool elfTaken = false;
    Gnome gnomeChar;
    bool gnomeTaken = false;
    
    while (true) {
        
        if(tieflingTaken && elfTaken && gnomeTaken) {
            cout << "All types taken!! Let's begin" << endl;
            break;
        }
        
        cout << "Adding a new player? Pick a type " << endl;
        cout << "Available Types: ";
        
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
        
        if (tempType != "TIEFLING" && tempType != "ELF" && tempType != "GNOME" ){
            cout << "Enter Valid Type!!" << endl;
            continue;
        }
        
        if( (tempType == "TIEFLING" && tieflingTaken) || (tempType == "ELF" && elfTaken) ||
                (tempType == "GNOME" && gnomeTaken) ) {
            cout << "*Type already taken! Pick another*\n" << endl;
            count--;
            continue;
        }
         
         cout << "Enter Character " << count << " name: ";
         cin >> tempCharName;
         
         cout << "Enter Character " << count << " speed: ";
         cin >> tempSpeed;
        
         if (tempType == "TIEFLING") {
            
            tieChar.SetName(tempCharName);
            tieChar.SetSpeed(tempSpeed);
            
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

            char magic;
            cout << "Is this character magic (y or n): ";
            cin >> magic;
            if(magic == 'y') {
                elfChar.SetIsMagic(true);
            }

            vec.push_back(make_shared<Elf>(elfChar));

            elfTaken = true;
        }
        else if(tempType == "GNOME") {

            gnomeChar.SetName(tempCharName);
            gnomeChar.SetSpeed(tempSpeed);

            char tools;
            cout << "Does this character have tools? (y or n): ";
            cin >> tools;
            if (tools == y) {
                gnomeChar.SetHasTools(true);
            }

            vec.push_back(make_shared<Gnome>(gnomeChar));

            gnomeTaken = true;

        }

        cout << endl;
    }

    sort(vec.rbegin(), vec.rend(), sortTheVec);
    
    //ella code end
    
    //Ben added
    CircularList<shared_ptr<Actor>> list;
    for (const auto& actor : vec) {
        list.push_back(actor);
    }
    /*
    for (const auto &a : vec) {
        cout << a->GetName() << ": " << a->GetSpeed()<< endl;
    }
    */

    turn_on_ncurses();

    

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
        // added by Ben
        if (map.get(x, y) == MAP::MONSTER) {
            for (const auto &actor : list) {
                cout << actor->GetName() << ": " << actor->GetSpeed() << endl;
                if (actor->get_isDead()) {
                    cout << actor->GetName() << " has died!" << endl;
                    auto it = find(list.begin(), list.end(), actor);
                    actor.erase(it);
                    continue;
                }
                auto victim = MAP::MONSTER;
                cout << actor->GetName() " attacks!" << endl;
                victim->take_damage() ;
                if (victim->get_isDead() == true) {
                    cout << victim->getName() << " is dead!"
                }
                break;
            }
        }
        // end Ben
        old_x = x;
        old_y = y;
        usleep(1'000'000/MAX_FPS);
    }
    turn_off_ncurses();

}
