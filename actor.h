#pragma once                                                                    
#include <iostream>
#include <string>

using namespace std;

class Actor {
    protected:
    int speed = 5;
    string name;

    public:
    int GetSpeed() {
        return speed;
    }
    void SetSpeed(int newSpeed) {
        speed = newSpeed;
    }

    string GetName() {
        return name;
    }
    void SetName(string newName) {
        name = newName;
    }
};

class Hero : public Actor {
    protected:
    int money = 0;

    public:
    int GetMoney() {
        return money;
    }
    void AddMoney(int newMoney) {
        money = money + newMoney;
    }
};

class Tiefling : public Hero{
    int fireDamage = 0;

    public:
    int GetFire() {
        return fireDamage;
    }
    void SetFire(int newFire) {
        fireDamage = newFire;
    }
};

class Elf : public Hero {
    bool isMagic = false;

    public:
    bool GetIsMagic() {
        return isMagic;
    }
    void SetIsMagic(bool newIsMagic) {
        isMagic = newIsMagic;
    }
};

class Gnome : public Hero {
    bool hasTools = false;

    public:
    bool GetHasTools() {
        return hasTools;
    }
    void SetHasTools(bool newHasTools) {
        hasTools = newHasTools;
    }
};
