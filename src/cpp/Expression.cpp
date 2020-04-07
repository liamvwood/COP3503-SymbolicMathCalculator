//
// Created by Liam Wood on 4/18/17.
//

#include "Expression.h"

Expression* Expression::simplify() {
    leftSide->simplify();
    rightSide->simplify();
}
