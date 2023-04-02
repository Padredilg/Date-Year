/*
Author: Luiz Padredi
Date: 04/1/2023
Assignment 4: Date Year
Repository: https://github.com/Padredilg/Date-Year
*/

#include <iostream>

using namespace std;

bool isLeapYear(int year);
string getOrdinal(int age);

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
        DateYear(int monthPar, int dayPar, int yearPar);
        DateYear();
        void inputFullDate();
        void outputFullDate();
        int getYear();
        void setYear(int yearPar);
        friend bool DateCompare(DateYear date1, DateYear date2);
        int BDCountdown(DateYear birthday);

};

//testing out classes
int main()
{
    DateYear birthDate;
    DateYear today;

    cout << endl
         << "====================================================="
         << endl << endl
         << "Please input your date of birth."
         << endl;
    birthDate.inputFullDate();
    birthDate.outputFullDate();

    cout << endl << endl
         << "Please input today's date."
         << endl;
    today.inputFullDate();
    today.outputFullDate();

    if(DateCompare(birthDate, today))
        cout << "\nHappy Birthday!!!\n";
    else
        cout << "\nYour next birthday is coming up in " << today.BDCountdown(birthDate) << " days." << endl;

    DateYear importantDate = DateYear(7,4,1776);
    if(DateCompare(importantDate, today))
        cout << "\nToday is 4th of July!! Happy Independence Day!\n";
    else
        cout << "\nNext 4th of July is in " << today.BDCountdown(importantDate) << " days.\n";

    importantDate.set_date(12,25);
    if(DateCompare(importantDate, today))
        cout << "\nToday is December 25th!! Merry Christmas!\n";
    else
        cout << "\nNext Christmas is in " << today.BDCountdown(importantDate) << " days.\n";

    importantDate.setYear(birthDate.getYear());
    cout << "\nAt the end of this year, you will experience your New Years of number " << today.getYear() - importantDate.getYear() << "!\n";

    return 0;
}

DateYear::DateYear(int monthPar, int dayPar, int yearPar){
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

    int thisYearCalendar[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(isLeapYear(year)){
        thisYearCalendar[1] += 1;
    }
    int day = get_day();
    int month = get_month();

    if((year < 0) || (year > thisYear) || (month < 1) || (month > 12) || (day < 1) || (day > thisYearCalendar[month-1]))
    {
        cout << "Illegal date. Aborting program.\n";
        exit(1);
    }
}

void DateYear::outputFullDate(){
   cout << get_month() << "/" << get_day() << "/" << getYear() << endl;
}

int DateYear::getYear(){ return year; }
void DateYear::setYear(int yearPar){ year = yearPar; }

bool DateCompare(DateYear date1, DateYear date2){
    return ( date1.year == date2.year ) && equal(date1, date2);
}

int DateYear::BDCountdown(DateYear birthday){
    int todayMonth = get_month();
    int todayDay = get_day();
    int birthdayMonth = birthday.get_month();
    int birthdayDay = birthday.get_day();
    int daysLeftToBD = 0;

    int thisYearCalendar[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(isLeapYear(year)){
        thisYearCalendar[1] += 1;
    }

    //if birthday month is in the future,
    if(todayMonth < birthdayMonth){
        //add current month and months in between
        //don't add birthday month
        for(int i = todayMonth; i < birthdayMonth; i++){
            daysLeftToBD += thisYearCalendar[i-1];
        }

        //subtract current day
        daysLeftToBD -= todayDay;

        //add birthday day
        daysLeftToBD += birthdayDay;
    }

    //if same month
    else if(todayMonth == birthdayMonth){
        //if today is before birthday difference is left
        if(todayDay < birthdayDay){
            daysLeftToBD = birthdayDay - todayDay;
        }

        //if today is past birthday, 365 minus the difference
        else if(todayDay > birthdayDay){
            daysLeftToBD = 365 - ( todayDay - birthdayDay );

            //if next year is leap year
            if(isLeapYear(year + 1)){
                if( birthdayMonth > 2 || ( birthdayMonth == 2 && birthdayDay == 29 ) ){
                    daysLeftToBD++;
                }
            }
        }
    }

    //if birthday month is past
    else if(todayMonth > birthdayMonth){
        //include this month and remaining months in the year
        for(int i = todayMonth; i <= 12; i++){
            daysLeftToBD += thisYearCalendar[i-1];
        }

        //include months of next year that are before the birthday month
        for(int i = 1; i < birthdayMonth; i++){
            daysLeftToBD += thisYearCalendar[i-1];
        }

        //subtract current day
        daysLeftToBD -= todayDay;

        //add birthday day
        daysLeftToBD += birthdayDay;

        //if next year is leap year
        if(isLeapYear(year + 1)){
            if( birthdayMonth > 2 || ( birthdayMonth == 2 && birthdayDay == 29 ) ){
                daysLeftToBD++;
            }
        }
    }

    return daysLeftToBD;
}

bool isLeapYear(int year) {
    bool yearIsDivisibleBy4 = year%4 == 0;
    bool yearIsDivisibleBy100 = year%100 == 0;
    bool yearIsDivisibleBy400 = year%400 == 0;

    if( year >= 400 && yearIsDivisibleBy400 )
        return true;

    if( year >= 100 && ( yearIsDivisibleBy4 && !yearIsDivisibleBy100 ) )
        return true;

    if( year < 100 && yearIsDivisibleBy4 )
        return true;

    return false;
}

///////////////////////////////////////////////////////////////////////////////////

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
