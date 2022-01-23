#include<curses.h>
#include<iostream>
#include "Game.h"
#include "Snake.h"
#include "Apple.h"
#include "coordenates.h"

using namespace std;

WINDOW* game;

int main() {

    initscr();
    noecho();
    cbreak;
    curs_set(0);
    start_color();

    while (1) {

        //criaçao da janela de jogo
        game = newwin(20, 110, 5, 5);
        //criação do objeto do jogo
        Game game1(game);

        erase();
        //consoante o valor que recebe da funçao mainMenu executa cada uma das respetivas funçoes
        switch (game1.mainMenu())
        {
        case 1:
            game1.play();
            break;
        case 2:
            erase();
            game1.scores();
            break;
        case 3:
            if (game1.settings() != 4)
            {
                game1.play();
            }
            break;
        case 4:
            exit(1);
            break;
        }
    }
}
