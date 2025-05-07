#include "Enemy.h"
#include "Building.h"

Enemy::Enemy(Position position, int attackDamage)
    : Npc(position, 100, "👹"), Targeted(false), AttackDamage(attackDamage) {}

void Enemy::AttackBuilding(const Board& board) {
    for (Building* building : board.getBuildings()) {
        if (building->collidesWith(getPosition())) {
            building->loseHealth(AttackDamage);
        }
    }
}


void Enemy::Update(const Board& board) {
    TownHall* th = board.getTownHall();
    Position pos = th->getPosition();
    moveTowards(board, pos);
    AttackBuilding(board);}
/*
void Enemy::setMoveDelay(DWORD delay) {
    moveDelay = delay;
}
/*/

Enemy::~Enemy()
{
    //dtor
}
