#include <stdio.h>
#include <stdlib.h>

/* a function which calculates the day of the week for 1st January */
int weekFirstJan(int year){
    int firstJan;
    int num = year - 1;
    firstJan = (1 + 5 * (num % 4) + 4 * (num % 100) + 6 * (num % 400)) % 7;
    return firstJan;
}

/* a function which rounds down a decimal to an integer */
int roundDecimal(double decimal){
    int result;
    result = (int)decimal;
    return result;
}

/* a function which calculates if a year is a leap year or not */
int isLeapYear(int year){
    int leap = 0;
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        leap = 1;
    }
    return leap;
}

/* calculates how many days have passed before month */
int daysPassed(int leap, int month){
    int sum;
    int adjust;
    if(month <= 2){
        adjust = 0;
    } else if (leap == 1 && month > 2) {
        adjust = 1;
    }  else if (leap != 1 && month > 2) {
        adjust = 2;
    }

    sum = ((367 * month - 362) / 12)- adjust;
    return roundDecimal(sum);
}


/* a function which calculates the ordinal day */
int findOrdinalDay(int sum, int leap, int day, int month){
    int ordinalDay;
    ordinalDay = day + sum;
    return ordinalDay;
}

/* a function which calculates the ISO weekday number */
int findIsoWeekdayNum(int firstJan, int ordinalDay){
    int isoWeekDay;
    isoWeekDay = ((ordinalDay + firstJan - 2) % 7)+1;
    if (isoWeekDay <= 0){
        isoWeekDay += 7;
    }
    return isoWeekDay;
}

/* a function which calculates the ISO week number */
int isoWeekNum(int ordinalDay, int isoWeekday){
    int isoWeek;
    isoWeek = (ordinalDay - isoWeekday + 10) / 7;
    return isoWeek;
}

/* a function which calculates the ISO week year */
int isoWeekYear(int isoWeek, int month, int year){
    if (month == 1 && isoWeek >= 52){
        year--;
    } else if (month == 12 && isoWeek == 1){
        year++;
    }else if (month == 1 && isoWeek == 0) {
        year--;
    }
    return year;
}

/* a function which calculates the weeks in a year */
int findWeekInYear(int firstJan, int leap, int year){
    int weekInYear;
    if (firstJan == 4 || (leap == 1 && firstJan ==3)) {
        weekInYear = 53;
    }else {
        weekInYear = 52;
    }
    return weekInYear;
}

/* finding how many days are in a month */
int findDaysInMonth(int month, int year){
    int daysInMonth;
    if (month == 2) {
        if (isLeapYear(year)==1) {
            daysInMonth = 29;
            return daysInMonth;
        }else {
            daysInMonth = 28;
            return daysInMonth;
        }
    }

    if (month <= 7){
    if (month % 2 == 0) {
        daysInMonth = 30;
    }else{
        daysInMonth = 31;
    } 
    }else {
        if (month % 2 == 0) {
            daysInMonth = 31;
        }else{
            daysInMonth = 30;
        } 
    }
    return daysInMonth;
}

int findIsoYear(int year, int month, int isoWeek){
    int isoYear;
    if (month == 1 && (isoWeek == 0 || isoWeek >= 52)) {
        isoYear = year - 1;
    }else if (month == 12 && isoWeek == 1) {
        isoYear = year + 1;
    }else {
        isoYear = year;
    }
    return isoYear;
}

int main(int argc, char **argv){
    int day, month, year;
    int leap, firstJan, sum, ordinalDay, isoWeekday, isoWeek, weekInYear, isoYear = 0;
    int prevYear, prevFirstJan, prevLeap;
    char *endptr1, *endptr2, *endptr3 ;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <DD> <MM> <YYYY>\n", argv[0]);
        return 1;
    }

    /* using strtol to get input*/
    /*converting strings to integers and validating the values*/
    day = strtol(argv[1], &endptr1, 10); 
    if (*endptr1 != '\0'){
        return 1;
    } 
    month = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0'){
        return 1;
    }
    year = strtol(argv[3], &endptr3, 10);
    if (*endptr3 != '\0'){
        return 1;
    }
    

    /* checking validity of dates*/
    if (year < 1900 || year > 2100) {
        return 1;
    }
    if (month < 1 || month > 12) {
        return 1;
    }
    if (day < 1 || day > findDaysInMonth(month, year)) {
        return 1;
    }

    leap = isLeapYear(year);
    firstJan = weekFirstJan(year);
    sum = daysPassed(leap, month);
    ordinalDay = findOrdinalDay(sum, leap, day, month);
    isoWeekday = findIsoWeekdayNum(firstJan, ordinalDay);
    isoWeek = isoWeekNum(ordinalDay, isoWeekday);
    weekInYear = findWeekInYear(firstJan, leap, year);

    if (isoWeek == 0) {
        prevYear     = year - 1;
        prevLeap     = isLeapYear(prevYear);
        prevFirstJan = weekFirstJan(prevYear);
        isoWeek      = findWeekInYear(prevFirstJan, prevLeap, prevYear); 
        isoYear      = findIsoYear(year, month, isoWeek);             
    } else if (isoWeek > weekInYear) {
        if (isoWeekday < 4) {
            isoWeek = 1;                                              
        } else {
            isoWeek = weekInYear;                                    
        }
        isoYear = findIsoYear(year, month, isoWeek);                    
    } else {
        isoYear = findIsoYear(year, month, isoWeek);                     
    }

    /*printing calendar date*/
    printf("%04d-%02d-%02d\n",year,month, day);
    /*printing ordinal date*/
    printf("%04d-%03d\n",year, ordinalDay);
    /*printing week date*/
    printf("%04d-W%02d-%d\n",isoYear, isoWeek, isoWeekday);

    return 0;
} 