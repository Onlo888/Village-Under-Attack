#pragma once
#ifndef BOARD_H
#define BOARD_H
#include "Position.h"
#include "Building.h"
#include "TownHall.h"
#include "Entity.h"
#include <vector>
class Player;
class Board {
private:
    int SizeX;
    int SizeY;
    std::vector<Building*> buildings;
    std::vector<Entity*> entities;
    TownHall* townHall;
    Player* player;

public:
    void PlaceTownHall() {
        Position center(SizeX/2, SizeY/2);
        if (!townHall) {
            townHall = new TownHall(center);
            AddBuilding(townHall);
        }
    }
    Board(int sizeX, int sizeY);

    // Vérifie si une position est hors limites
    bool IsOutOfBounds(Position pos) const;

    // Compte les bâtiments du même type
    int CountBuildingType(const Building& targetBuilding) const;

    // Vérifie les collisions avec d'autres bâtiments
    bool CollidesWith(const Building& newBuilding) const;

    // Ajoute un bâtiment en respectant les contraintes
    bool AddBuilding(Building* newBuilding);

    // Getters
    int getSizeX() const { return SizeX; }
    int getSizeY() const { return SizeY; }
    const std::vector<Building*>& getBuildings() const { return buildings; }
    Player* getPlayer() const { return player; }
    TownHall* getTownHall() const { return townHall; }

    // Setters (optionnels)
    void setPlayer(Player* p) { player = p; }
    void setTownHall(TownHall* th) { townHall = th; }
    bool isPositionValid(const Position&) const;
    void Draw() const;
    virtual ~Board();
};

#endif // BOARD_H
