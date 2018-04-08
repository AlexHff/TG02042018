#include "Misc.h"

void pause(int dur) {
    int temp = time(NULL) + dur;

    while(temp > time(NULL));
}
