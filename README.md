ISO Date Converter

This project implements a date conversion program in C that transforms a user-provided Gregorian calendar date into three standardized ISO 8601 formats:

Calendar date: YYYY-MM-DD

Ordinal date: YYYY-DDD

ISO week date: YYYY-Www-D

Developed as part of coursework in Computer Science at the University of Nottingham, this program demonstrates structured procedural programming, algorithmic problem solving, and accurate calendar computation without external libraries.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Features

The program calculates:
• Leap years based on Gregorian calendar rules
• Ordinal day of the year
• ISO week number and ISO year
• ISO weekday number (Monday = 1, Sunday = 7)

It validates input dates within the range 1900–2100, returns a non-zero exit code for invalid input, and follows a modular design with distinct functions for each computation.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Example

Input:
./ISODateConverter 4 6 1945

Output:
1945-06-04
1945-155
1945-W23-1

(4 June 1945 corresponds to Monday of week 23 in 1945.)

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Compilation

Ensure a C compiler such as GCC is installed.

To compile:
gcc -Wall -ansi -pedantic -errors -o ISODateConverter ISODateConverter.c

To run:
./ISODateConverter <DAY> <MONTH> <YEAR>

Example:
./ISODateConverter 1 1 2000

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Usage Notes

The program expects exactly three integer arguments in the order: DAY, MONTH, YEAR.
Input validation ensures that the provided date is valid within the Gregorian calendar.
Invalid or out-of-range inputs cause the program to exit silently with a non-zero status code.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Technical Overview

The program uses Gauss’ algorithm to determine the weekday of January 1 for a given year and applies modular arithmetic to derive ISO weekday numbers and week numbers.

It implements separate helper functions for:
• Leap year detection
• Ordinal day calculation
• ISO week and ISO year determination

All calculations use integer arithmetic only, with no external date-handling libraries.
