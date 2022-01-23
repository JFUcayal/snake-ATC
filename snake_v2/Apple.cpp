#include "Apple.h"
#include<iostream>

using namespace std;

Apple::Apple(WINDOW* game) : pos({ 5,5 }) {
    this->game = game;
}

void Apple::addFood() {

    //gera uma posi��o aleatoria no ecra para a fruta, esta que � definida como um @ com cor vermelha
    int maxX = getmaxx(game);
    int maxY = getmaxy(game);

    //posi��o gerada aleatoriamente da coluna entre 3 e 100 e linha entre 3 e 120  
    pos.y = rand() % (maxX - 100) + 3;
    pos.x = rand() % (maxY - 120) + 3;

    //design visual da ma�a
    start_color();
    init_pair(2, COLOR_RED, COLOR_BLACK);
    fruit = COLOR_PAIR(2) | '@';
}

void Apple::printFood() {
    //print da ma�a no ecra de jogo na posi��o gerada anteriormente 
    mvwaddch(game, pos.y, pos.x, fruit);
    wrefresh(game);
}

coordenates Apple::getPosition() {
    //return da posi��o(coordenates) da ma�a
    return pos;
}