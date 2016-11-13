//
// Created by zeph on 11/12/16.
//

#include "RuleOf72.h"
#include <cmath>


const char *htmlFormat =
        "<h1 style=\"color: #5e9ca0;\">Welcome to the <em><span style=\"color: #0000ff;\">"
        "<strong>Rule of 72</strong></span></em> Demo</h1>\n"
        "<ol style=\"list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;\">\n"
        "<li style=\"clear: both;\">You entered <em><span style=\"background-color: #ffff00;\">%.6g</span></em>&nbsp;"
        "[at the&nbsp;end of the url "
        "<a href=\"http://www.tzaffi.xyz/ruleof72?2\">www.tzaffi.xyz/ruleof72?<span style=\"background-color: #ffff00;\">%.6g</span></a>]"
        "</li>\n"
        "<li style=\"clear: both;\">(It&nbsp;<em>could be that you meant the number of&nbsp;"
        "<span style=\"color: #ff6600;\">years</span> for an investment to double or the annual percentage "
        "<span style=\"color: #ff6600;\">rate</span> of return)</em></li>\n"
        "<li style=\"clear: both;\"></li>\n"
        "<li style=\"clear: both;\"></li>\n"
        "<li style=\"clear: both;\">According to the rule of 72, "
        "the answer is <span style=\"background-color: #ffff00;\"><em>%.6g</em></span>&nbsp;"
        "(<em><span style=\"color: #ff6600;\">rate</span></em> or<em>&nbsp;"
        "<span style=\"color: #ff6600;\">years</span>)</em></li>\n"
        "<li style=\"clear: both;\"></li>\n"
        "<li style=\"clear: both;\"></li>\n"
        "<li style=\"clear: both;\">But the mathematically, the&nbsp;annual percentage "
        "<span style=\"color: #ff6600;\"><em>rate</em></span>&nbsp;of return to achieve doubling "
        "in&nbsp;<em><span style=\"background-color: #ffff00;\">%.6g</span>&nbsp;</em>years is&nbsp;"
        "<em><span style=\"background-color: #ffff00;\">%.6g%%</span>&nbsp;</em>which is off by "
        "<em><span style=\"background-color: #ffff00;\">%.6g%%</span></em>&nbsp;&nbsp;</li>\n"
        "<li style=\"clear: both;\">And mathematically, the number of years to double if the "
        "rate were&nbsp;<em><span style=\"background-color: #ffff00;\">%.6g%%</span></em>&nbsp;is&nbsp;"
        "<em><span style=\"background-color: #ffff00;\">%.6g</span>&nbsp;</em>"
        "which is a off by <em><span style=\"background-color: #ffff00;\">%.6g</span></em>&nbsp;years</li>\n"
        "</ol>";

double RuleOf72::interestRateFromDoublingTime(double doublingTime) {
    return 72.0 / doublingTime;
}

double RuleOf72::doublingTimeFromInterestRate(double interestRate) {
    return RuleOf72::interestRateFromDoublingTime(interestRate);
}

double RuleOf72::mathematicalRateFromDoublingTime(double doublingTime) {
    return 100 * (std::pow(2, 1/doublingTime) - 1);
}

double RuleOf72::mathematicalTimeFromInterestRate(double interestRate) {
    return std::log(2) / std::log(1 + interestRate/100);
}

std::string RuleOf72::report(double yearsOrRate) {
    const int L = std::string(htmlFormat).length();
    char buffer[2*L];
    double ro72answer = RuleOf72::interestRateFromDoublingTime(yearsOrRate);
    double realRate = RuleOf72::mathematicalRateFromDoublingTime(yearsOrRate);
    double realYears = RuleOf72::mathematicalTimeFromInterestRate(yearsOrRate);
    double realRateDiff = std::fabs(realRate-ro72answer);
    double realYearsDiff = std::fabs(realYears-ro72answer);
    std::snprintf(buffer, 2*L, htmlFormat,
                  yearsOrRate,
                  yearsOrRate,
                  ro72answer,
                  yearsOrRate,
                  realRate,
                  realRateDiff,
                  yearsOrRate,
                  realYears,
                  realYearsDiff
    );
    return std::string(buffer) + "\n<!--- \n\n\nL = " + std::to_string(L) + "\n\n\n-->";
}
