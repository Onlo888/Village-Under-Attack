#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "Board.h"
#include "Player.h"
#include "Building.h"
#include "Wall.h"
#include "TownHall.h"
#include "Raider.h"
#include "GoldMine.h"
#include "ElixirCollector.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define T_KEY 116

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void drawBoardBuffered(Board& board, Player& player, const std::vector<Raider*>& raiders) {
    int offsetX = 15;
    int boardWidth = board.getSizeX();
    int boardHeight = board.getSizeY();
    int infoX = offsetX + boardWidth + 5;

    std::ostringstream buffer;

    buffer << "\x1b[?25l"; // Cacher le curseur
    buffer << "\x1b[2J";   // Effacer l'écran
    buffer << "\x1b[H";    // Positionner en haut à gauche
    buffer << "\x1b[" << 1 << ";" << (infoX + 1) << "HGold: " << player.getResources().getGold();
    buffer << "\x1b[" << 2 << ";" << (infoX + 1) << "HElixir: " << player.getResources().getElixir();

    for (int y = 0; y < boardHeight; y++) {
        buffer << "\x1b[" << (y + 5) << ";" << (offsetX + 1) << "H";
        for (int x = 0; x < boardWidth; x++) {
            bool printed = false;

            if (y == 0 || y == boardHeight - 1 || x == 0 || x == boardWidth - 1) {
                buffer << "·";
                continue;
            }

            if (player.getPosition().X == x && player.getPosition().Y == y) {
                buffer << player.getRepr();
                printed = true;
            } else {
                for (Building* b : board.getBuildings()) {
                    if (b->collidesWith(Position(x, y))) {
                        Position topLeft = b->getPosition();
                        int centerX = topLeft.X + b->getSizeX() / 2;
                        int centerY = topLeft.Y + b->getSizeY() / 2;
                        if (x == centerX && y == centerY) {
                            buffer << b->getRepr();
                        } else {
                            buffer << " ";
                        }
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) {
                for (Raider* r : raiders) {
                    if (r->getPosition().X == x && r->getPosition().Y == y) {
                        buffer << r->getRepr();
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) buffer << " ";
        }
    }

    std::cout << buffer.str() << std::flush;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(console, &cursorInfo);

    srand(static_cast<unsigned int>(time(nullptr))); // Init aléatoire

    Board board(70, 20);
    Player player(Position(5, 5));
    board.setPlayer(&player);

    int centerX = board.getSizeX() / 2;
    int centerY = board.getSizeY() / 2;

    GoldMine* gm = new GoldMine(Position(centerX - 4, centerY));
    ElixirCollector* ec = new ElixirCollector(Position(centerX + 2, centerY));
    board.AddBuilding(gm);
    board.AddBuilding(ec);

    std::vector<Raider*> raiders;
    unsigned long lastSpawnTime = GetTickCount(); // Remplacer DWORD par unsigned long

    bool placingWalls = false;
    static Position lastWallPos = { -1, -1 };

    while (true) {
        if (_kbhit()) {
            int key = _getch();

            if (key == KEY_UP) player.moving(board, 0, -1);
            if (key == KEY_DOWN) player.moving(board, 0, 1);
            if (key == KEY_LEFT) player.moving(board, -1, 0);
            if (key == KEY_RIGHT) player.moving(board, 1, 0);

            if (key == SPACE) {
                placingWalls = !placingWalls;
            }

            if (key == T_KEY) {
                Position playerPos = player.getPosition();
                Position buildingPos = { playerPos.X + 2, playerPos.Y };
                TownHall* th = new TownHall(buildingPos);
                board.AddBuilding(th);
            }
        }

        if (placingWalls && player.getResources().getGold() >= 5) {
            Position pos = player.getPosition();
            if (pos.X != lastWallPos.X || pos.Y != lastWallPos.Y) {
                bool exists = false;
                for (Building* b : board.getBuildings()) {
                    if (b->collidesWith(pos)) {
                        exists = true;
                        break;
                    }
                }

                if (!exists) {
                    board.AddBuilding(new Wall(pos));
                    player.getResources().spendGold(5);
                    lastWallPos = pos;

                    if (player.getResources().getGold() < 5) {
                        placingWalls = false;
                    }
                }
            }
        }

        // ✅ Apparition aléatoire d'un Raider toutes les 5 secondes
        unsigned long currentTime = GetTickCount();
        if (currentTime - lastSpawnTime >= 5000) {
            int x = rand() % (board.getSizeX() - 2) + 1;
            int y = rand() % (board.getSizeY() - 2) + 1;
            Raider* newRaider = new Raider(Position(x, y));
            raiders.push_back(newRaider);
            lastSpawnTime = currentTime;
        }

        // ✅ Mise à jour de tous les raiders
        for (Raider* r : raiders) {
            r->Update(board);
        }

        drawBoardBuffered(board, player, raiders);
        Sleep(30);
    }

    return 0;
}
