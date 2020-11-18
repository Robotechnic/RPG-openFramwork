#ifndef ENTITY_H
#define ENTITY_H

#include <ofImage.h>
#include <ofTrueTypeFont.h>
#include <ofGraphics.h>

#include <string>
#include <iostream>

using namespace std;

#define SPRITE_SIZE 32
#define ANNIM_DELAY 250
#define MAX_ANNIM_TIME 301
#define DEFAULT_ANNIM_STATE 1

typedef int direction;

class Entity
{
public:
    Entity(int x, int y, string spriteUrl, string name, bool displayName = true, int maxLife = 100);
    Entity(const Entity &e);

    void draw(ofTrueTypeFont playerFonFace);

    void move(direction entityDirection);

    float getX(){return x;};
    float getY(){return y;};
    void setX(int x){this->x = x;};
    void setY(int y){this->y = y;};
    int getLife(){return this->life;};
    string getName(){return this->name; };

    //constants
    static const direction UP;
    static const direction DOWN;
    static const direction LEFT;
    static const direction RIGHT;

protected:
    float x, y;
    int life,maxLife;
    bool displayName;

    /*
     * Défine image spite:
     *   0 1 2
     * 0 D D D
     * 1 L L L
     * 2 R R R
     * 3 U U U
     *
     * U: up
     * L: Left
     * R: right
     * D: down
     */
    int annimState,annimDirection,annimTime,annimStateDirection;

    ofImage imageSprite;
    string name,spriteUrl;

};

#endif // ENTITY_H
