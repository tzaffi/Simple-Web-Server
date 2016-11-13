//
// Created by zeph on 11/12/16.
//

#ifndef SIMPLE_WEB_SERVER_RULEOF72_TESTER_H
#define SIMPLE_WEB_SERVER_RULEOF72_TESTER_H

#include <list>

class RuleOf72_Tester {
public:
    static std::list<void (*)()> getTests();
};


#endif //SIMPLE_WEB_SERVER_RULEOF72_TESTER_H
