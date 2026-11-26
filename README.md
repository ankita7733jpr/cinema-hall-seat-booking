# Cinema Hall Seat Booking System

A beginner-friendly console application written in **C** that lets a user view, book, and search cinema seats.

## Features

- Displays a 5 x 6 seat grid (`O` = available, `X` = booked)
- Books a seat by row and column number
- Prevents double booking
- Searches for a seat using **linear search**
- Shows the exact memory address of a seat using **pointer arithmetic**
- Handles invalid input and out-of-range seat numbers

## Concepts Demonstrated

1. **2D Arrays** — the cinema hall is stored as `char hall[ROWS][COLS]`
2. **Linear Search** — seats are checked one by one from `hall[0][0]`
3. **Address Calculation** — the program prints both:
   - `&hall[row][col]`
   - `base + (row * COLS) + col`

## Project Structure

```text
.
├── cinema.c    # Complete C source code
└── README.md   # Project documentation
```

## Compile and Run

### Windows (MinGW/GCC)

```bash
gcc cinema.c -o cinema.exe
cinema.exe
```

### Linux / macOS

```bash
gcc cinema.c -o cinema
./cinema
```

## Sample Menu

```text
===== CINEMA HALL BOOKING SYSTEM =====
1. Display seats
2. Book a seat
3. Search a seat (Linear Search)
4. Exit
```

## Sample Output

```text
       COLUMNS
        1  2  3  4  5  6

ROWS
Row 1:    O   O   O   O   O   O
Row 2:    O   O   X   O   O   O
Row 3:    O   O   O   O   O   O
Row 4:    O   O   O   O   O   O
Row 5:    O   O   O   O   O   O

Legend: O = Available, X = Booked
```

## Notes

- Rows and columns are entered starting from **1**, while the array uses **0-based** indexes.
- The seat grid is 5 rows by 6 columns (30 seats).
