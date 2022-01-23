#pragma once
#include<curses.h>
#include "coordenates.h"
#include <time.h>
#include<iostream>
#include "Snake.h"

class Apple
{
    coordenates pos;
    chtype fruit = '@';
    WINDOW* game;

public:
    Apple(WINDOW*);
    void addFood();
    void printFood();
    coordenates getPosition();
};

