#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
using namespace std;


//Game Content
//Player Stuff
int numMonsters = 0;
int points = 0;
bool prinFound = false;

string areaTypes[4] = { "Forest","Cave","Dungeon","Desert" };
//FOREST
string monstersOfForest[]  = { "Heffalump", "Woozle", "Jagular", "Backson" };
int    hpOfForest[]        = { 100,         100,      100,       100 };
int    damageOfForest[]    = { 5,           5,        5,         5 };
int    damageResOfForest[] = { 1,           1,        1,         1 };
//CAVE
string monstersOfCave[]  = { "Adrianasaurus Rex", "Jackiesaurus Rex", "Chrisasaurus Rex" };
int    hpOfCave[]        = { 100,                 100,                100 };
int    damageOfCave[]    = { 5,                   5,                  5 };
int    damageResOfCave[] = { 1,                   1,                  1 };
//DUNGEON
string monstersOfDungeon[]  = { "Nokk", "Bruni", "Gale", "Earth Giant" };
int    hpOfDungeon[]        = { 100,    100,     100,    100 };
int    damageOfDungeon[]    = { 5,      5,       5,      5 };
int    damageResOfDungeon[] = { 1,      1,       1,      1 };
//DESERT
string monstersOfDesert[]  = { "Oogie Boogie", "Brunosaurus Rex", "Dr. Finkelstein", "Lock", "Shock" };
int    hpOfDesert[]        = { 100,            100,               100,               100,    100 };
int    damageOfDesert[]    = { 5,              5,                 5,                 5,      5 };
int    damageResOfDesert[] = { 1,              1,                 1,                 1,      1 };

//ITEMS
string items[]      = { "Sword", "Wand", "Staff", "Trident" };
int    itemDamage[] = { 15,      20,     15,      20 };

//Helper Functions
void repeat(string x, int y) {
    for (int i = 0; i < y; i++)
        cout << x;
}
void delay(int t) {
    this_thread::sleep_for(chrono::milliseconds(t));
}
void typer(string x) {
    for (int i = 0; i < x.length(); i++) {
        cout << x[i];
        delay(40);
    }
}
void clear() {
    system("cls");
}
int genRand(int upto) {
    //returns an int n as 0 <= n < upto
    return rand() % upto;
}

//Definitions

class item {
public:
    string type;
    int damage;
    item() {
        type = "Nothing...";
        damage = 0;
    }
    void makeItem(string x, int y) {
        type = x;
        damage = y;
    }
};

class monster {
public:
    string type;
    int damage;
    int damRes;
    int hp;
};

class area {
public:
    int numForPlacement;
    string type;
    bool monsterPre;
    monster currMonster;
    item currItem;
    area* left;
    area* right;
    area* prev;

    bool prinPre = false;

    string genType() {
        int x = genRand(4);
        return areaTypes[x];
    }
    monster genMon(string areaType) {
        numMonsters++;
        int index = 0; //f, c, du, de
        monster qtPie;
        if (areaType == areaTypes[0]) {
            index = genRand(sizeof(monstersOfForest) / sizeof(monstersOfForest[0]));
            qtPie.type = monstersOfForest[index];
            qtPie.hp = hpOfForest[index];
            qtPie.damage = damageOfForest[index];
            qtPie.damRes = damageResOfForest[index];
        }
        if (areaType == areaTypes[1]) {
            index = genRand(sizeof(monstersOfCave) / sizeof(monstersOfCave[0]));
            qtPie.type = monstersOfCave[index];
            qtPie.hp = hpOfCave[index];
            qtPie.damage = damageOfCave[index];
            qtPie.damRes = damageResOfCave[index];
        }
        if (areaType == areaTypes[2]) {
            index = genRand(sizeof(monstersOfDungeon) / sizeof(monstersOfDungeon[0]));
            qtPie.type = monstersOfDungeon[index];
            qtPie.hp = hpOfDungeon[index];
            qtPie.damage = damageOfDungeon[index];
            qtPie.damRes = damageResOfDungeon[index];
        }
        if (areaType == areaTypes[3]) {
            index = genRand(sizeof(monstersOfDesert) / sizeof(monstersOfDesert[0]));
            qtPie.type = monstersOfDesert[index];
            qtPie.hp = hpOfDesert[index];
            qtPie.damage = damageOfDesert[index];
            qtPie.damRes = damageResOfDesert[index];
        }
        return qtPie;
    }
    item genItem() {
        int index = genRand(sizeof(items) / sizeof(items[0]));
        item qtPie;
        qtPie.type = items[index];
        qtPie.damage = itemDamage[index];
        return qtPie;
    }

    area() {
        numForPlacement = -1;
        left = nullptr;
        right = nullptr;
        prev = nullptr;
    }
    area(int x) {
        numForPlacement = x;
        left = nullptr;
        right = nullptr;
        prev = nullptr;

        //Gen Factors
        type = genType();
        int isThereMon = genRand(2);
        if (isThereMon == 0)
            monsterPre = true;
        else
            monsterPre = false;
        if (monsterPre)
            currMonster = genMon(type);
        else
            currItem = genItem();
    }
};

class tree {
public:
    area* root;
    tree() {
        root = nullptr;
        generateAreas();
    }
    void areaInsert(int x) {
        area* b = new area(x);

        if (root == nullptr)
            root = b;
        else {
            area* p = root;

            while (true) {
                if (x < p->numForPlacement) {
                    if (p->left == nullptr) {
                        p->left = b;
                        break;
                    }
                    p = p->left;
                }
                else {
                    if (p->right == nullptr) {
                        p->right = b;
                        break;
                    }
                    p = p->right;
                }
            }
        }
    }
    void generateAreas() {
        areaInsert(50);
        int baseNum = 50;
        for (int i = 25; i <= 75; i += baseNum) {
            areaInsert(i);
        }
        baseNum /= 2;
        for (int i = 12; i <= 90; i += baseNum) {
            areaInsert(i);
        }
        baseNum /= 2;
        for (int i = 7; i <= 98; i += baseNum) {
            areaInsert(i);
        }
    }
    void printR(area* p) {
        if (p == nullptr) {

        }
        else {
            printR(p->left);
            cout << p->numForPlacement << " type: " << p->type << 
                " is there a monster: " << p->monsterPre << 
                " monster: " << p->currMonster.type << 
                " item: " << p->currItem.type <<
                " princess is here?: " << p->prinPre << endl;
            printR(p->right);
        }
    }
    void print() {
        printR(root);
        cout << endl;
    }
    void chosen() {
        area* p = root;
        while (p->left != nullptr) {
            if (genRand(2) == 0)
                p = p->left;
            else
                p = p->right;
        }
        p->prinPre = true;
    }
};

class player {
public:
    int health;
    item equipped;
    int invSpot;
    area* currentArea;

    item one;
    item two;
    item three;
    item four;
    item five;
    string name;
    player() {
        cout << "Enter your name: ";
        cin >> name;
        health = 100;
        invSpot = 1;
        equipped = one;
        one.makeItem("Nothing...", 0);
        two.makeItem("Nothing...", 0);
        three.makeItem("Nothing...", 0);
        four.makeItem("Nothing...", 0);
        five.makeItem("Nothing...", 0);
    }
    string playerChoice() {
        string opt;
        cout << "> ";
        cin >> opt;
        return opt;
    }
    void displayInv() {
        cout << "1. " << one.type << " >> " << one.damage << endl;
        cout << "2. " << two.type << " >> " << two.damage << endl;
        cout << "3. " << three.type << " >> " << three.damage << endl;
        cout << "4. " << four.type << " >> " << four.damage << endl;
        cout << "5. " << five.type << " >> " << five.damage << endl;
    }
    void chooseItem() {
        clear();
        int opt;
        displayInv();
        cout << "\nChoose a number to equipped item:\n";
        while (true) {
            cout << ">";
            cin >> opt;
            if (opt == 1) {
                equipped = one;
                break;
            }
            else if (opt == 2) {
                equipped = two;
                break;
            }
            else if (opt == 3) {
                equipped = three;
                break;
            }
            else if (opt == 4) {
                equipped = four;
                break;
            }
            else if (opt == 5) {
                equipped = five;
                break;
            }
            else
                cout << "Not a valid option. Please choose between 1 and 5." << endl;
        }
    }
    void pickUpItem() {
        clear();
        displayInv();
        cout << "Choose a slot to swap " << currentArea->currItem.type << ">>" << currentArea->currItem.damage << " with, or '-1' to change your mind." << endl;
        int opt;
        while (true) {
            cout << ">";
            cin >> opt;
            if (opt == 1) {
                item cSave = one;
                one = currentArea->currItem;
                currentArea->currItem = cSave;
                break;
            }
            else if (opt == 2) {
                item cSave = two;
                two = currentArea->currItem;
                currentArea->currItem = cSave;
                break;
            }
            else if (opt == 3) {
                item cSave = three;
                three = currentArea->currItem;
                currentArea->currItem = cSave;
                break;
            }
            else if (opt == 4) {
                item cSave = four;
                four = currentArea->currItem;
                currentArea->currItem = cSave;
                break;
            }
            else if (opt == 5) {
                item cSave = five;
                five = currentArea->currItem;
                currentArea->currItem = cSave;
                break;
            }
            else if (opt == -1)
                break;
            else
                cout << "Not a valid option. Please choose between 1 and 5." << endl;
        }
    }
};


void gameStart(string name) {
    typer("Princess Isabella: I will go searching for Ahtohallan and bring back the sun drop flower");
    cout << endl << endl;
    typer("Troll Grand Pabbie: You must not... no one has made it to Ahtohallan and back. Its far too dangerours");
    cout << endl << endl;
    typer("Princess Isabella: If I don't then Arendelle will be no more");
    cout << endl << endl;
    typer("Troll Grand Pabbie: Okay but if you are not back in 30 days, I will send ");
    typer(name);
    typer(" to look for you");
    cout << endl << endl;
    typer("(30 days later)");
    cout << endl << endl;
    typer("Troll Grand Pabbie: Isabella hasn't made it back... let me warn ");
    typer(name);
    cout << endl << endl;
    typer("(knock, knock)");
    cout << endl << endl;
    typer("(door opens)");
    cout << endl << endl;
    typer(name);
    typer(": Grand Pabbie what brings you here ?");
    cout << endl << endl;
    typer("Troll Grand Pabbie: I'm afraid Princess Isabella isn't back yet from Ahtohallan.");
    cout << endl << endl;
    typer("I hate to ask but you are the only person that might have a chance to find her");
    cout << endl << endl;
    typer("if you can't find her and the sun drop flower... Arendelle and everyone with us will perish");
    cout << endl << endl;
}
void gameEnd(string name) {
    clear();
    typer(name);
    typer(": I see the princess!");
    cout << endl << endl;
    typer("Princess Isabella: ");
    typer(name);
    typer(", thank you for coming to look for me. I got lost after I found the sundrop flower.");
    cout << endl << endl;
    typer("(Princess Isabella shows the sundrop flower)");
    cout << endl << endl;
    typer(name);
    typer(": Princess Isabella lets take you home!");
    cout << endl << endl;
}
void HUD(player you) {
    cout << "Player: " << you.name << endl;
    cout << "Health: " << you.health << endl;

    repeat("-", 20);
    cout << endl;

    cout << "Currently Equipped: " << you.equipped.type << endl;
    cout << "Item does " << you.equipped.damage << " damage." << endl;

    repeat("-", 20);
    cout << endl;

    cout << "Area: " << you.currentArea->type << endl;
    cout << "Area contains: ";
    if (you.currentArea->monsterPre)
        cout << you.currentArea->currMonster.type << " >> " << you.currentArea->currMonster.damage << "\nMonster Health: " << you.currentArea->currMonster.hp;
    else
        cout << you.currentArea->currItem.type << " >> " << you.currentArea->currItem.damage;
    cout << endl;

    repeat("-", 20);
    cout << endl;
    
}
void conter() {
    string opt = "n";
    cout << "Enter 'c' to continue...\n>";
    while (opt != "c")
        cin >> opt;
}

//TREES
tree up;
tree down;
tree lefty;
tree righty;

void atCastle(player& you) {
    typer("You are currently at the castle.");
    cout << endl;
    typer("You can go up, down, left, or right.");
    cout << endl;
    typer("Choose your move:");
    cout << endl;
    while (true) {
        cout << ">";
        string opt;
        cin >> opt;
        if (opt == "up") {
            you.currentArea = up.root;
            break;
        }
        else if (opt == "down") {
            you.currentArea = down.root;
            break;
        }
        else if (opt == "left") {
            you.currentArea = lefty.root;
            break;
        }
        else if (opt == "right") {
            you.currentArea = righty.root;
            break;
        }
        else {
            cout << "That is not an option my guy ._.\n";
        }
    }
}

int main() {
    cout << "Loading...\n";

    int whichTree = genRand(4);
    switch (whichTree) {
    case 0:
        up.chosen();
        break;
    case 1:
        down.chosen();
        break;
    case 2:
        lefty.chosen();
        break;
    case 3:
        righty.chosen();
        break;
    default:
        cout << "ERROR - SWITCH" << endl;
        break;
    }
    
    /*
    cout << "UP:" << endl;
    up.print();
    cout << "DOWN:" << endl;
    down.print();
    cout << "LEFT:" << endl;
    lefty.print();
    cout << "RIGHT:" << endl;
    righty.print();
    conter();
    */

    player you;
    clear();

    gameStart(you.name);

    conter();
    clear();

    atCastle(you);

    string opt;
    while (true) {
        clear();
        if (you.currentArea->currMonster.hp <= 0 && you.currentArea->monsterPre) {
            you.currentArea->monsterPre = false;
            points += 10;
            clear();
            cout << "You have slain the monster!" << endl;
            cout << "You gained 10 points :)" << endl;
            conter();
            clear();
        }
        if (you.currentArea->monsterPre) {
            you.health -= you.currentArea->currMonster.damage;
            cout << "The " << you.currentArea->currMonster.type << " did " << you.currentArea->currMonster.damage <<
                " damage on you!" << endl;
            cout << endl;
        }
        if (you.health <= 0) {
            clear();
            cout << "You have died... " << endl;
            cout << "You lost 10 points :(" << endl;
            points -= 10;
            you.health = 100;
            conter();
            clear();
            atCastle(you);
            clear();
        }
        HUD(you);
        if (you.currentArea->prinPre) {
            prinFound = true;
            break;
        }
        opt = you.playerChoice();
        if (opt == "left") {
            if (you.currentArea->left != nullptr) {
                you.currentArea = you.currentArea->left;
            }
            else {
                typer("You have reached the edge of the world. You must go back.");
                cout << endl;
                typer("Because the world is flat, of course.");
                cout << endl;
                conter();
            }
        }
        else if (opt == "right") {
            if (you.currentArea->right != nullptr) {
                you.currentArea = you.currentArea->right;
            }
            else {
                typer("You have reached the edge of the world. You must go back.");
                cout << endl;
                typer("Because the world is flat, of course.");
                cout << endl;
                conter();
            }
        }
        else if (opt == "back") {
            if (you.currentArea->prev != nullptr) {
                you.currentArea = you.currentArea->prev;
            }
            else {
                atCastle(you);
            }
        }
        else if (opt == "attack") {
            if (you.currentArea->monsterPre) {
                you.currentArea->currMonster.hp -= you.equipped.damage / you.currentArea->currMonster.damRes;
                cout << "You did " << you.equipped.damage / you.currentArea->currMonster.damRes << " damage on the " <<
                    you.currentArea->currMonster.type << "." << endl;
            }
            else {
                cout << "You're attacking the air!" << endl;
            }
            conter();
        }
        else if (opt == "inventory") {
            you.chooseItem();
        }
        else if (opt == "grab") {
            if (!you.currentArea->monsterPre) {
                you.pickUpItem();
            }
            else {
                cout << "There is nothing to pick up... Fight!" << endl;
                conter();
            }
        }
        else if (opt == "quit" || opt == "exit" || opt == "q")
            break;
        else if (opt == "help") {
            cout << "left\n";
            cout << "right\n";
            cout << "back\n";
            cout << "attack\n";
            cout << "inventory\n";
            cout << "grab\n";
            cout << "quit\n";
            conter();
        }
        else {
            cout << "ERROR - INVALID OPTION\n";
            conter();
        }
    }
    if (prinFound) {
        gameEnd(you.name);
    }
    conter();
    clear();
    cout << "You got " << points << " points!";
    if (points <= 10)
        cout << "I've seen better..." << endl;
    else
        cout << "Good job!" << endl;
    cout << "You could have gotten " << numMonsters * 10 << " points out of the entire map." << endl << endl;
    return 0;
}