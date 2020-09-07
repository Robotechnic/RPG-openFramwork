#ifndef ENTITY_H
#define ENTITY_H

#include <ofImage.h>
#include <ofTrueTypeFont.h>
#include <string>

using namespace std;

class entity
{
public:
    entity(int x, int y, string spriteUrl, string name);
    entity(const entity &e);

    void draw(ofTrueTypeFont playerFonFace);

    int getX(){
        return x;
    };
    int getY(){
        return y;
    };

protected:
    int x, y;
    /*
     * Défine image spite:
     *   0 1 2
     * 0 D D D
     * 1 L L L
     * 2 R R R
     * 3 B B B
     *
     * U: up
     * L: Left
     * R: right
     * D: down
     */

    ofImage imageSprite;
    string name,spriteUrl;

};

#endif // ENTITY_H
