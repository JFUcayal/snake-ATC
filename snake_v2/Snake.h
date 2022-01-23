#pragma once
#include<list>
#include "coordenates.h"
#include<iostream>

using namespace std;

class Snake {
    list <coordenates> elements;
    coordenates coords;
    size_t size;
    char type;
    WINDOW* game;

public:
    Snake(WINDOW*);
    void print(int);
    bool move(int);
    void eraseTail();
    coordenates GetHeadPosition();
    bool findApple(const coordenates&);
    bool overlapApple(const coordenates&);
};

