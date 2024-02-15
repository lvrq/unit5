/*
Ian Pinegar
2024SP COSC-1436-57002
2/15/24
Description: This program calculates and displays weekly pay for employees, factoring in hours worked, hourly rate, and employment status, with appropriate deductions for taxes and benefits.
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <locale> //locale header
#include <cctype> //tolower() and toupper()

using namespace std;

const double CLOCK_HOURS = 40.0;
const double OVERTIME_RATE = 2.0;
const double SS_RATE = 0.062;
const double MED_RATE = 0.0145;
const double FIT_LOW_RATE = 0.12;
const double FIT_HIGH_RATE = 0.15;
const double DENTAL_FULLTIME = 17.00;
const double RETIREMENT_FULLTIME = 77.00;

double weeklyPay(double, double, const string &, int);

int main() {
    cout << fixed << setprecision(2);

    //Test values
    cout << "Ian's weekly pay: $" << weeklyPay(32.5, 100.25, "Tyson", 1) << endl;
    cout << "Melivin's weekly pay: $" << weeklyPay(45.0, 55.25, "Melivin", 1) << endl;
    cout << "Susan's weekly pay: $" << weeklyPay(15.0, 65.25, "Susan", 2) << endl;
    cout << "Mika's weekly pay: $" << weeklyPay(41.0, 14.75, "Mika", 1) << endl;
    cout << "Eldridge's weekly pay: $" << weeklyPay(25.0, 15.0, "Eldridge", 2) << endl;
    cout << "Freedom's weekly pay: $" << weeklyPay(55.0, 203.50, "Freedom", 1) << endl;

    //Convert "TCC-TR IS COOL" to lowercase
    cout << "Converting 'TCC-TR IS COOL' to lowercase: ";
    string text1 = "TCC-TR IS COOL";
    for (char &c : text1) {
        cout << (char)tolower(c); // Convert each character to lowercase
    }
    cout << endl;

    //Convert "i will succeed at c++" to uppercase
    cout << "Converting 'i will succeed at c++' to uppercase: ";
    string text2 = "i will succeed at c++";
    for (char &c : text2) {
        cout << (char)toupper(c); // Convert each character to uppercase
    }
    cout << endl;

    return 0;
}

double weeklyPay(double hours, double rate, const string &name, int empType) {
    double netPay = 0.0, grossPay = 0.0, taxableWages = 0.0;
    double fitTax = 0.0, dental = 0.0, retirement = 0.0;
    double overtimeHours = (hours > CLOCK_HOURS) ? (hours - CLOCK_HOURS) : 0.0;
    double fitRate = (rate < 15.0) ? FIT_LOW_RATE : FIT_HIGH_RATE;

    //locale for formatting
    locale loc;
    cout.imbue(loc);

    cout << "\033[1;32m" << uppercase << name << "\033[0m" << endl; 

    cout << "Status: " << ((empType == 1) ? "Fulltime" : "Parttime") << endl;
    cout << "Hours Worked: " << hours << ", Rate: $" << rate << endl;

    //gross pay
    grossPay = (hours <= CLOCK_HOURS) ? (hours * rate) :
               ((CLOCK_HOURS * rate) + (overtimeHours * OVERTIME_RATE * rate));

    cout << "Gross Pay: $" << grossPay << endl;

    //deductions
    if (empType == 1) { //Fulltime employee deductions
        dental = DENTAL_FULLTIME;
        retirement = RETIREMENT_FULLTIME;
        cout << "Dental Deduction: $" << dental << endl;
        cout << "Retirement Deduction: $" << retirement << endl;
    }

    taxableWages = grossPay - (dental + retirement);
    fitTax = taxableWages * fitRate;

    cout << "FIT Tax Amount: $" << fitTax << endl;

    //Social Security and Medicare taxes
    double ssTaxes = grossPay * SS_RATE;
    double medTaxes = grossPay * MED_RATE;

    cout << "Social Security Taxes: $" << ssTaxes << endl;
    cout << "Medicare Taxes: $" << medTaxes << endl;

    //net pay
    netPay = grossPay - (dental + retirement + fitTax + ssTaxes + medTaxes);
    cout << "Net Pay: $" << netPay << endl;

    return netPay;
}