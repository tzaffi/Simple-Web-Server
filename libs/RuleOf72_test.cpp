//
// Created by zeph on 11/12/16.
//

#include <iostream>
#include <list>
#include "RuleOf72_Tester.h"

int main() {

    RuleOf72_Tester tester;
    std::list<void (*)()> tests = tester.getTests();
    for (std::list<void (*)()>::iterator it= tests.begin();
         it != tests.end();
         ++it)
    {
        (*it)();
    }
    std::cout << std::endl << "Test suite is complete";
    return 0;
}