# mayan-number-game

A small C++ project that prints Maya numerals for a given non-negative integer and includes a simple interactive game where the user matches a decimal number to one of three Maya representations.

## What it implements
- Part 1 — printMayanNumber(int): converts and prints the Maya representation (base-20 stacked symbols: dots = 1, bars = 5, shell/zero). Implemented as multiple helper functions (digit printing, place handling).
- Part 2 — interactive game: prompts for a maximum (>=10), generates a correct random answer and two plausible incorrect answers, displays three Maya numbers in random order labeled a/b/c, and validates user input until a/b/c is entered. Handles input errors.
- Part 3 — main(): prints the Maya representation of 5,212 then runs the game loop.


## Run

The program first prints the Maya form of 5,212, then begins the game. Follow the on-screen prompts (enter an integer >= 10 to play; enter a/b/c to answer; enter a number < 10 to exit).

Non-interactive testing (feed answers from a file):
```bash
# create a file with responses, e.g. initial max, choice, then exit
@"
12
b
5
"@ > input.txt
.\maya_numbers < input.txt
```

## Example output (trimmed)
```
The Mayan representation of 5,212 is:

  ooo
 ====
 ====
------
    @
------
   oo
 ====
 ====

Welcome to the Mayan number game!
Enter a number greater than 10 ...
Which of these Mayan numbers is equal to 6?

a.
 ====

b.
    o
 ====

c.
 oooo
 ====

Enter a, b or c:
```
