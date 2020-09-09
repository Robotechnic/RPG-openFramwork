#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player(int x, int y, string spriteUrl, string name, bool displayName = true, int maxLife = 100);
};

#endif // PLAYER_H
