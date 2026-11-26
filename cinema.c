/* ============================================================
   Cinema Hall Seat Booking System
   Concepts used:
   1. 2D arrays
   2. Linear search
   3. Address calculation using pointer arithmetic
   ============================================================ */

#include <stdio.h>

#define ROWS 5
#define COLS 6

/* Function declarations (prototypes) */
void initializeSeats(char hall[ROWS][COLS]);
void displaySeats(char hall[ROWS][COLS]);
int  isValidSeat(int row, int col);
char linearSearchSeat(char hall[ROWS][COLS], int row, int col, int *steps);
void printSeatAddress(char hall[ROWS][COLS], int row, int col);
void bookSeat(char hall[ROWS][COLS]);
void searchSeat(char hall[ROWS][COLS]);
void clearInput(void);

int main(void)
{
    char hall[ROWS][COLS];
    int choice;

    initializeSeats(hall);

    while (1)
    {
        printf("\n===== CINEMA HALL BOOKING SYSTEM =====\n");
        printf("1. Display seats\n");
        printf("2. Book a seat\n");
        printf("3. Search a seat (Linear Search)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        /* Check if scanf read a number correctly */
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            clearInput();   /* clear the invalid input */
            continue;
        }

        switch (choice)
        {
            case 1:
                displaySeats(hall);
                break;
            case 2:
                bookSeat(hall);
                break;
            case 3:
                searchSeat(hall);
                break;
            case 4:
                printf("Thank you for using the booking system.\n");
                return 0;
            default:
                printf("Wrong choice. Please enter 1, 2, 3 or 4.\n");
        }
    }
}

/* ------------------------------------------------------------
   Fill every seat with 'O' (available).
   ------------------------------------------------------------ */
void initializeSeats(char hall[ROWS][COLS])
{
    int r, c;

    for (r = 0; r < ROWS; r++)
    {
        for (c = 0; c < COLS; c++)
        {
            hall[r][c] = 'O';
        }
    }
}

/* ------------------------------------------------------------
   Display the 2D seat grid.
   Rows and columns are shown starting from 1 for the user.
   ------------------------------------------------------------ */
void displaySeats(char hall[ROWS][COLS])
{
    int r, c;

    printf("\n       COLUMNS\n");
    printf("      ");
    for (c = 0; c < COLS; c++)
    {
        printf("%3d", c + 1);
    }
    printf("\n");

    printf("\nROWS\n");
    for (r = 0; r < ROWS; r++)
    {
        printf("Row %d:  ", r + 1);
        for (c = 0; c < COLS; c++)
        {
            printf("  %c ", hall[r][c]);
        }
        printf("\n");
    }

    printf("\nLegend: O = Available, X = Booked\n");
}

/* ------------------------------------------------------------
   Check that row and column are inside the array.
   The user enters 1-based numbers, arrays use 0-based indexes.
   ------------------------------------------------------------ */
int isValidSeat(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        return 1;   /* valid */
    }
    return 0;       /* invalid */
}

/* ------------------------------------------------------------
   Remove leftover characters after bad input.
   ------------------------------------------------------------ */
void clearInput(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* discard one character */
    }
}

/* ------------------------------------------------------------
   LINEAR SEARCH:
   We visit seats one by one from hall[0][0] to hall[ROWS-1][COLS-1]
   until we reach the seat the user asked for.

   The variable steps counts how many seats were checked.
   Returns the seat status ('O' or 'X') if found, '\0' otherwise.
   ------------------------------------------------------------ */
char linearSearchSeat(char hall[ROWS][COLS], int row, int col, int *steps)
{
    int r, c;

    *steps = 0;

    for (r = 0; r < ROWS; r++)
    {
        for (c = 0; c < COLS; c++)
        {
            (*steps)++;

            if (r == row && c == col)
            {
                /* Seat found: return its current status ('O' or 'X') */
                return hall[r][c];
            }
        }
    }

    return '\0';   /* seat not found */
}

/* ------------------------------------------------------------
   ADDRESS CALCULATION USING POINTER ARITHMETIC:

   A 2D array is stored in memory row by row.
   hall[0][0] is the first byte.
   The address of hall[row][col] is:

        base address + row * COLS + col

   We print both this calculated address and &hall[row][col]
   so we can see that they are the same.
   ------------------------------------------------------------ */
void printSeatAddress(char hall[ROWS][COLS], int row, int col)
{
    char *base = &hall[0][0];
    char *calculated = base + (row * COLS) + col;   /* pointer arithmetic */

    printf("Address using &hall[%d][%d]        : %p\n",
           row, col, (void *)&hall[row][col]);

    printf("Address using pointer arithmetic : %p\n",
           (void *)calculated);
}

/* ------------------------------------------------------------
   Book a seat:
   1. Read row and column from the user.
   2. Convert to 0-based indexes.
   3. Use linear search to confirm the position.
   4. Change 'O' to 'X' if it is free.
   ------------------------------------------------------------ */
void bookSeat(char hall[ROWS][COLS])
{
    int userRow, userCol;
    int row, col;
    int steps;
    char status;

    printf("\nEnter row number (1 to %d): ", ROWS);
    if (scanf("%d", &userRow) != 1)
    {
        printf("Invalid input.\n");
        clearInput();
        return;
    }

    printf("Enter column number (1 to %d): ", COLS);
    if (scanf("%d", &userCol) != 1)
    {
        printf("Invalid input.\n");
        clearInput();
        return;
    }

    /* Convert user numbers (1-based) to array indexes (0-based) */
    row = userRow - 1;
    col = userCol - 1;

    if (!isValidSeat(row, col))
    {
        printf("Sorry, that seat does not exist. Please choose another.\n");
        return;
    }

    /* Linear search finds the seat and returns its status ('O' or 'X') */
    status = linearSearchSeat(hall, row, col, &steps);

    if (status == '\0')
    {
        printf("Seat not found by linear search.\n");
        return;
    }

    printf("Linear search checked %d seat(s) to find this position.\n", steps);

    if (status == 'O')
    {
        hall[row][col] = 'X';
        printf("Booking successful! Seat R%dC%d is now booked.\n",
               userRow, userCol);
        printSeatAddress(hall, row, col);
    }
    else
    {
        printf("Sorry, seat R%dC%d is already taken. Please choose another.\n",
               userRow, userCol);
        printSeatAddress(hall, row, col);
    }
}

/* ------------------------------------------------------------
   Search a seat:
   Use linear search to locate the position, then read the value.
   ------------------------------------------------------------ */
void searchSeat(char hall[ROWS][COLS])
{
    int userRow, userCol;
    int row, col;
    int steps;
    char status;

    printf("\nEnter row number to search (1 to %d): ", ROWS);
    if (scanf("%d", &userRow) != 1)
    {
        printf("Invalid input.\n");
        clearInput();
        return;
    }

    printf("Enter column number to search (1 to %d): ", COLS);
    if (scanf("%d", &userCol) != 1)
    {
        printf("Invalid input.\n");
        clearInput();
        return;
    }

    row = userRow - 1;
    col = userCol - 1;

    if (!isValidSeat(row, col))
    {
        printf("That seat is outside the hall. Please try again.\n");
        return;
    }

    status = linearSearchSeat(hall, row, col, &steps);

    if (status != '\0')
    {
        printf("Linear search checked %d seat(s) to find this position.\n", steps);

        if (status == 'O')
        {
            printf("Seat R%dC%d is AVAILABLE ('O').\n", userRow, userCol);
        }
        else
        {
            printf("Seat R%dC%d is BOOKED ('X').\n", userRow, userCol);
        }

        printSeatAddress(hall, row, col);
    }
    else
    {
        printf("Seat was not found.\n");
    }
}
