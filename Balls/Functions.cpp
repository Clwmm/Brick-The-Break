#include "Functions.h"

int Functions::fromRandom(int a, int b)
{
    return (rand() % (b - a + 1)) + a;
}