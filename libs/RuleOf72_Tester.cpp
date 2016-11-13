//
// Created by zeph on 11/12/16.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include "RuleOf72_Tester.h"
#include "RuleOf72.h"

void assertAlmostEqual(double x, double y, double TOLERANCE = 0){
    assert(std::fabs(x-y) <= TOLERANCE);
}

void simplisticRule_test(){
    std::cout << std::endl
              << "BEGIN simplisticRule_test"
              << std::endl;

    bool success = false;
    double doublingTime= 8, expectedInterestRate= 9,
    interestRate= 10, expectedDoublingTime = 7.2;

    RuleOf72 ro72;
    double actualInterestRate = ro72.interestRateFromDoublingTime(doublingTime);
    std::cout << std::endl << "ro72.interestRateFromDoublingTime(" << doublingTime << ") = " << actualInterestRate;
    assert(actualInterestRate == expectedInterestRate);

    double actualDoublingTime = ro72.doublingTimeFromInterestRate(interestRate);
    std::cout << std::endl << "ro72.doublingTimeFromInterestRate(" << interestRate << ") = " << actualDoublingTime;
    assert(actualDoublingTime == expectedDoublingTime);

    success = true;
    std::cout << std::endl
              << (success ? "SUCCESS" : "FAILURE")
              << std::endl
              << "END simplisticRule_test"
              << std::endl;
}


void mathematicalRule_test(){
    const double TOLERANCE = 0.000001;
    std::cout << std::endl
              << "BEGIN mathematicalRule_test"
              << std::endl;

    bool success = false;
    double doublingTime= 8, mathematicalInterestRate = 9.050773266525765920701065576070797,
            interestRate= 10, mathematicalDoublingTime = 7.272540897341719083319903674960021674;

    RuleOf72 ro72;

    double actualInterestRate = ro72.mathematicalRateFromDoublingTime(doublingTime);
    std::cout << std::endl << "ro72.mathematicalRateFromDoublingTime(" << doublingTime << ") = " << actualInterestRate;
    assertAlmostEqual(actualInterestRate, mathematicalInterestRate, TOLERANCE);

    double actualDoublingTime = ro72.mathematicalTimeFromInterestRate(interestRate);
    std::cout << std::endl << "ro72.mathematicalTimeFromInterestRate(" << interestRate << ") = " << actualDoublingTime;
    assertAlmostEqual(actualDoublingTime, mathematicalDoublingTime, TOLERANCE);

    success = true;

    std::cout << std::endl
              << (success ? "SUCCESS" : "FAILURE")
              << std::endl
              << "END mathematicalRule_test"
              << std::endl;
}

template<typename T> void printCell(T t, const int &width, const char &separator)
{
    std::cout << std::left << std::setw(width) << std::setfill(separator) << t << '|';
}

template<typename T> void printRow(T a, T b, T c, T d)
{
    printCell(a, 20, ' ');
    printCell(b, 35, ' ');
    printCell(c, 15, ' ');
    printCell(d, 15, ' ');
    std::cout << std::endl;
}

void prettyPrinter_test(){
    RuleOf72 ro72;
    bool success = false;
    std::cout << std::endl
              << "BEGIN prettyPrinter_test"
              << std::endl;

    std::cout << ro72.report(8);
    success = true;

    std::cout << std::endl
              << (success ? "SUCCESS" : "FAILURE")
              << std::endl
              << "END prettyPrinter_test"
              << std::endl;
}

void comparisonTablePrinter(){
    RuleOf72 ro72;
    std::cout << std::endl << std::endl;
    printRow("Rate or Years", "Rule of 72 Years or Rate", "True Years", "True Rate");
    printRow("_____________", "________________________", "__________", "_________");
    for (double i = 1; i <= 20; ++i){
        printRow(i,
                 ro72.interestRateFromDoublingTime(i),
                 ro72.mathematicalTimeFromInterestRate(i),
                 ro72.mathematicalRateFromDoublingTime(i)
        );
    }
}

std::list<void (*)()> RuleOf72_Tester::getTests()
{
    std::list<void (*)()> res= {
            simplisticRule_test,
            mathematicalRule_test,
            prettyPrinter_test,
            comparisonTablePrinter
    };
    return res;
};
