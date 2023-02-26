#pragma once                                                                    
#include <iostream>
#include <string>

using namespace std;

class Actor {
    protected:
    int speed = 5;
    string name;
    int hp = 5;
    int damage = 1;


    public:
    virtual int GetSpeed() {
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

    int GetHp() {
        return hp;
    }
    void SetHp(int newHp) {
        hp = newHp;
    }

    virtual int GetDamage() {
        return damage;
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
    int GetDamage() override {
        if (fireDamage > 10) {
            return damage + 2;
        }
        else if (fireDamage > 0) {
            return damage + 1;
        }
        return damage;
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

class Monster : public Actor {

    protected:
    bool isTough = false;

    public:

    void SetIsTough(bool newIsTough) {
        isTough = newIsTough;
    }
    int GetDamage() override {
        if (isTough) {
            return damage + 1;
        }
        return damage;
    }

    int GetSpeed() override {

        if (isTough) {
            if(speed - 3 <= 0) {
                return 1;
            }
            else {
                return speed - 3;
            }
        }
        return speed;
    }
};

class Kobold : public Monster {
    int fireDamage = 0;

    public:
    int GetFireDamage() {
        return fireDamage;
    }
    void SetFireDamage(int newFire) {
        fireDamage = newFire;
    }
    int GetDamage() override {
        int tempDamage = 1;
        if (isTough) {
            tempDamage += 1;
        }
        if (fireDamage > 0) {
            tempDamage += 1;
        }
        return tempDamage;
    }
    int GetSpeed() {
        return speed - 1;
    }

};

class Tabaxi : public Monster {

    public:
        int GetSpeed() override {
            return speed + 15;
        }
};
