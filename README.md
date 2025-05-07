# Console Strategy Game

This is a simple C++ console-based strategy game where the player can move around a grid, place walls, and build structures while defending against invading raiders. The game uses ASCII and emoji characters to represent the game state visually in the terminal.

## Features

- Move the player using arrow keys.
- Build structures like Town Halls, Walls, Gold Mines, and Elixir Collectors.
- Spend resources (Gold, Elixir) to construct and defend.
- Raiders spawn periodically and attack your buildings.
- Buffered drawing for smooth screen updates.

## Controls

| Key       | Action                     |
|-----------|----------------------------|
| Arrow Keys | Move player               |
| Space     | Toggle wall placement mode |
| T         | Build Town Hall           |

## Dependencies

- Windows OS (uses `windows.h` and `GetTickCount`)
- Code::Blocks or any other Windows-compatible C++ environment

## Building and Running

1. Clone or download the repository.
2. Open the project in Code::Blocks.
3. Build and run the project.

Ensure that all the header and source files (e.g., `Board.h`, `Player.h`, `Raider.h`, etc.) are correctly added to the project.

## File Structure

- `main.cpp` — Game loop and rendering logic
- `Raider.h/.cpp` — Enemy unit behavior
- `Board.h/.cpp` — Grid and object management
- `Player.h/.cpp` — Player control and resources
- `Building.h`, `Wall.h`, `TownHall.h`, etc. — Game objects

## Notes

- Emoji rendering may depend on your terminal/font.
- Game performance and visuals are optimized for Windows console.

## License

MIT License (or specify your own)
