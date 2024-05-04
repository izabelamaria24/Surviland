#include "../headers/Portal.h"

void Portal::use() {
     hp--;
}

bool Portal::destroyed() {
    return hp <= 0;
}

int Portal::getX2() const {
    return xdest;
}

int Portal::getY2() const {
    return ydest;
}