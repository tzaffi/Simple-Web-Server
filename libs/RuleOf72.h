//
// Created by zeph on 11/12/16.
//

#ifndef SIMPLE_WEB_SERVER_RULEOF72_H
#define SIMPLE_WEB_SERVER_RULEOF72_H

#include <iomanip>

/*
 * Let:
 *   r = annual percentage interest rate of an investment
 *   T = amount of time it takes the investment to double
 *
 * The rule of 72 states that:
 *   r T = 72
 * i.e:
 *   r = 72 / T
 * or
 *   T = 72 / r
 *
 * With math, one can show that the actual rule is:
 *   ln(1 + r) T = ln 2
 * i.e:
 *   r = 2 ^ (1/T) - 1
 * or
 *   T = ln 2 / ln (1+r)
 */

class RuleOf72 {
public:
    static double interestRateFromDoublingTime(double doublingTime);
    static double doublingTimeFromInterestRate(double interestRate);

    static double mathematicalRateFromDoublingTime(double doublingTime);
    static double mathematicalTimeFromInterestRate(double interestRate);

    static std::string report(double yearsOrRate);
};


#endif //SIMPLE_WEB_SERVER_RULEOF72_H
