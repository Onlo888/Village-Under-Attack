#ifndef ENEMY_H
#define ENEMY_H
#include "Board.h"
#include <Npc.h>


class Enemy : public Npc
{
    private:
    bool Targeted;
    int AttackDamage;
    /*
    DWORD lastMoveTime = 0;
    DWORD moveDelay = 800;
    */

    public:
        void AttackBuilding(const Board& board);
        void Update(const Board& board) override;
        virtual ~Enemy();

       // void setMoveDelay(DWORD delay);//


    protected:

        Enemy(Position position, int attackDamage = 10);

};

#endif // ENEMY_H
