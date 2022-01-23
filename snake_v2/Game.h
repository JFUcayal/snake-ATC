#pragma once
#include "Apple.h"
#include "Snake.h"
#include<iostream>
#include<string>
#include<vector>
#include "coordenates.h"

using namespace std;

class Game
{
    string name;
    int score;
    Snake esnake;
    Apple fruit;
    WINDOW* game;
    int gameSpeed;
    int deltaScore;

public:
    vector <int> players;
    Game(WINDOW*);
    int settings();
    void play();
    void scores();
    void GamePause();
    void GameOver();
    int mainMenu();
};
