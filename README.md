# Minesweeper Game

## Overview

This is a console-based implementation of the Minesweeper game.

## Compilation

To compile the game, use the provided `Makefile` with the following command:

```bash
make
```

This will build the executable.

## Clean Up

To remove the compiled files and clean up the project directory, use:

```bash
make clean
```

This command will delete the generated executable and any other temporary files.

## How to Play

1. **Starting the Game:** Run the game executable from the terminal:

```bash
./minesweeper
```

2. **Controls:**
    - Write s (y x) to select the cell in (y x)-
    - Write f (y x) to flag the cell in (y x)-

3. **Objective:** Reveal all cells that do not contain mines without detonating any mines. Flag cells where you suspect mines are located to help you avoid them.

4. **Winning and Losing:** You win by revealing all non-mine cells. The game ends if you reveal a cell containing a mine.

## Recommendations

- **Color Support:** For the best experience, use a terminal that supports color to see the game’s visual features as intended.
