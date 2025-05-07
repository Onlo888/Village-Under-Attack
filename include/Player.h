#ifndef PLAYER_H
#define PLAYER_H
#include "Resources.h"
#include "Board.h"
#include <Entity.h>

class Building;
class Player : public Entity
{
    private:
        Resources resources;
        bool isBuildingMode = false;
    public:

        Player(Position position);
        void ToggleBuildMode() { isBuildingMode = !isBuildingMode; }
        bool IsBuilding() const { return isBuildingMode; }

        Building* Interact(Board& board);

        void moving(const Board& board, int dx, int dy);
        Resources& getResources();
        void Update(const Board&) override;
        const char* getRepr() const override { return "🧑"; }
        virtual ~Player();

};

#endif // PLAYER_H

