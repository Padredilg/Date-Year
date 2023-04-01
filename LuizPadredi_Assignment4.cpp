/*
Author: Luiz Padredi
Date: 03/28/2023
Assignment 4: Date Year
Repository: https://github.com/Padredilg/Date-Year
*/

#include <iostream>

using namespace std;


/*

Define a class called DateYear,
that represents any year
like 2023 in addition to the day and month (03/34/2023).

Your class will have
one member variable of type int to represent the year.
This class is a child of the DayOfYear class where the code is given in lecture14
(Lecture14_Code.cpp).

Your DateYear class should have the following member functions:
- a constructor
and a default constructor that sets the year to this year,
month to 1 and day to 1.

- an input function that reads the date (day, month, and year). Make sure to
check for inaccurate dates.

- getter and setters for the year.

- an output function that outputs the date in form of xx/xx/xxxx. It can display
to the screen or the file.

- A friend function DateCompare that compares two years and returns true
if they are the same.

- A member function BDCountdown, which calculates and returns how many
days till your birthday. This function take the birthday as the input parameter
and returns the number of days left to the birthday which should be less than
365. Take note of the month in Gregorian calendar. The Gregorian calendar
consists of the following 12 months:

January - 31 days
February - 28 days in a common year and 29 days in leap years
March - 31 days
April - 30 days
May - 31 days
June - 30 days
July - 31 days
August - 31 days
September - 30 days
October - 31 days
November - 30 days
December - 31 days

You can put the days in an array to access them for computing the number of days.

Embed your class definition in a test program.
The test program should test all the attributes
(every single function and all the data should be tested).

All your inputs and outputs can be done using the keyboard and the screen.
Even though your input/output functions can stream through files.
So, how many days is left to your birthday?

Note1: friend functions are not inheritable (the friend functions in lecture 14 code
cannot be inherited by DateYear class)

Note2: you can reuse function names and tailor them to the needs of the derived
class.

*/
const int thisYear = 2023;

//Purpose of this class: store a date (whether it's a birthday or an event)
class DayOfYear
{
    public:
        DayOfYear();    //initializes day and month to 01/01
        DayOfYear(int the_month, int the_day);
        void input( );
        void output( );
        void set_date(int new_month, int new_day);  //setter function or mutator function
        //Precondition: new_month and new_day form a possible date.
        //Postcondition: The date is reset according to the arguments.
        int get_month( );   //getter function or accessor function
        //Returns the month, 1 for January, 2 for February, etc.
        int get_day( );
        //Returns the day of the month.
        friend bool equal(DayOfYear date1,DayOfYear date2);
        //checks for equality of two dates
    private:
        void check_date( );
        int month;
        int day;
};

class DateYear : public DayOfYear
{
    private:
        int year;
    public:
        DateYear(int yearPar, int monthPar, int dayPar);
        DateYear();
        void inputFullDate();
        void outputFullDate();
        int getYear();
        void setYear(int yearPar);
        /*- a constructor
and a default constructor that sets the year to this year,
month to 1 and day to 1.*/
};

//testing out classes
int main()
{
    DateYear birthDate;
    DateYear compareDate;

    cout << endl
         << "====================================================="
         << endl << endl
         << "Please input your birthday information."
         << endl;
    birthDate.inputFullDate();

    cout << endl << endl
         << "Please input the information of the date to be compared."
         << endl;
    compareDate.inputFullDate();





    DayOfYear today, bach_birthday(3,21);
    //today.check_date();
    cout << "Enter today's date.\n";
    today.input( );
    cout << "Today's date is ";
    today.output( );
    cout << "J. S. Bach's birthday is ";
    bach_birthday.output( );
    if (equal(today,bach_birthday) )
     cout << "Happy Birthday Johann Sebastian!\n";
    else
    cout << "Happy Unbirthday Johann Sebastian!\n";


    today = bach_birthday;           //assignment operator would set values of bach_birthday to today's values
    cout << "\nNow again! I have set today's date to that of Bach's birthday\n";
    if (equal(today,bach_birthday) )
     cout << "Happy Birthday Johann Sebastian!\n";
    else
    cout << "Happy Unbirthday Johann Sebastian!\n";

    return 0;
}

DateYear::DateYear(int yearPar, int monthPar, int dayPar){
    year = yearPar;
    set_date(monthPar, dayPar);
}

DateYear::DateYear():year(thisYear){
    set_date(1, 1);
}

void DateYear::inputFullDate(){
    input();
    cout << "Enter the year: ";
    cin >> year;

    //maybe call function to make sure the day exists in the month givenand include logic to check year as well

    if ((year < 0))
    {   //input();
        cout << "Illegal date. Aborting program.\n";
        exit(1);
    }
}

int DateYear::getYear(){ return year; }
void DateYear::setYear(int yearPar){ year = yearPar; }




DayOfYear::DayOfYear()
{
    month = 1;
    day = 1;
}

DayOfYear::DayOfYear(int the_month, int the_day)
{
    month = the_month;
    day = the_day;
}

void DayOfYear::input( )
{
    cout << "Enter the month as a number: ";
    cin >> month;
    cout << "Enter the day of the month: ";
    cin >> day;
    check_date( );
}


void DayOfYear::output( )
{
    cout << "month = " << month << ", day = " << day << endl;
}


void DayOfYear::set_date(int new_month, int new_day)
{
    month = new_month;
    day = new_day;
    check_date();
}

void DayOfYear::check_date( )
{
    if ((month < 1) || (month > 12) || (day < 1) || (day > 31))
    {   //input();
        cout << "Illegal date. Aborting program.\n";
        exit(1);
    }
}

int DayOfYear::get_month( )
{
    return month;
}

int DayOfYear::get_day( )
{
    return day;
}

bool equal(DayOfYear date1,DayOfYear date2)
{
    return (date1.day == date2.day && date1.month == date2.month);
}
