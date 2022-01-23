#include "Snake.h"
#include "coordenates.h"
#include<iostream>
#include<curses.h>
#include<string>
#include<list>
#include<vector>

using namespace std;

Snake::Snake(WINDOW* game) :coords({ 10,10 }), type('(') {

    //construtor da cobra para esta come�ar com um tamanho de 3 caracteres
    this->game = game;
    size = 3;
    elements.push_front(coords);
    coords.x++;
    elements.push_front(coords);
    coords.x++;
    elements.push_front(coords);
}

void Snake::print(int gameSpeed) {

    //print da cobra no ecr� de jogo com as propriedades visuais definidas
    start_color();
    //cor do corpo da cobra
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    //cor da cabe�a da cobra
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);

    int counter = 0;
    wattron(game, COLOR_PAIR(1));
    for (list<coordenates> ::iterator it = elements.begin(); it != elements.end(); it++) {
        if (counter == 0)
            //cabe�a da cobra com formato diferente e cor diferente
            mvwaddch(game, (*it).y, (*it).x, COLOR_PAIR(4) | ':');
        else
            //corpo da cobra
            mvwaddch(game, (*it).y, (*it).x, type);
        counter++;
    }
    wrefresh(game);
    wtimeout(game, gameSpeed);          //delay da cobra definido pelos respetivos modos de jogo
    wattroff(game, COLOR_PAIR(1));
    wattroff(game, COLOR_PAIR(4));
}

bool Snake::move(int key) {
    int counter = 0;
    switch (key) {
    case KEY_RIGHT:
        //recebe as coordenadas da cabe�a da cobra e incrementa a posi��o da cobra no eixo x
        coords = elements.front();
        coords.x++;
        elements.push_front(coords);

        //limpar a ultima posi��o da cobra
        eraseTail();

        //dete�ao da cobra se esta bateu contra a parede da direita
        if (elements.front().x > 108) {
            
            return false;   //false -> gameOver
        }
        break;

    case KEY_LEFT:
        //recebe as coordenadas da cabe�a da cobra e decrementa a posi��o da cobra no eixo x
        coords = elements.front();
        coords.x--;
        elements.push_front(coords);

        //limpar a ultima posi��o da cobra
        eraseTail();

        //dete�ao da cobra se esta bateu contra a parede da esquerda
        if (elements.front().x < 1) {
            
            return false;       //false -> gameOver
        }
        break;

    case KEY_UP:
        //recebe as coordenadas da cabe�a da cobra e decrementa a posi��o da cobra no eixo y
        coords = elements.front();
        coords.y--;
        elements.push_front(coords);

        //limpar a ultima posi��o da cobra
        eraseTail();

        //dete�ao da cobra se esta bateu contra a parede de cima
        if (elements.front().y < 1) {
            
            return false;       //false -> gameOver
        }
        break;

    case KEY_DOWN:
        //recebe as coordenadas da cabe�a da cobra e incrementa a posi��o da cobra no eixo y
        coords = elements.front();
        coords.y++;
        elements.push_front(coords);

        //limpar a ultima posi��o da cobra
        eraseTail();

        //dete�ao da cobra se esta bateu contra a parede de baixo
        if (elements.front().y > 18) {
            
            return false;       //false -> gameOver
        }
        break;

    default:
        break;
    }

    //dete��o se a cobra bate no seu pr�prio corpo
    for (list<coordenates> ::iterator it = elements.begin(); it != elements.end(); it++) {
        if (elements.front().x == (*it).x && elements.front().y == (*it).y)
            counter++;

        if (counter >= 2)
            return false;       //false -> gameOver
    }
    return true;        //true -> jogo continua
}

void Snake::eraseTail() {
    //fun��o que apaga a ultima posi��o da cobra e imprime um espa�o no seu lugar
    if (size < elements.size()) {
        wrefresh(game);

        //imprime o espa�o na sua ultima posi��o
        mvwaddch(game, elements.back().y, elements.back().x, ' ');
        //utlimo elemento da cobra apagado
        elements.pop_back();

    }
    else {
        mvwaddch(game, elements.back().y, elements.back().x, ' ');
    }
}

coordenates Snake::GetHeadPosition() {

    //retorna a posi��o da cabe�a da cobra
    return elements.front();
}

bool Snake::findApple(const coordenates& fruit) {

    //deteta a interse��o da cabe�a da cobra com a fruta no ecr�
    if (fruit.x == elements.front().x && fruit.y == elements.front().y) {
        //incrementa o tamanho da cobra se a condi��o de interse��o se verificar
        size++;
        return true;
    }
    else
        return false;
}

bool Snake::overlapApple(const coordenates& fruit) {

    //dete�ao se a fruta nasce em cima de uma posi��o previamente ocupada pelo corpo da cobra
    bool value = false;
    for (list<coordenates> ::iterator it = elements.begin(); it != elements.end(); it++) {
        if (fruit.x == (*it).x && fruit.y == (*it).y) {
            value = true;       //se a fruta for gerada em cima de uma posi��o ocupada pela cobra retorna o valor booleano de verdadeiro
        }
    }
    return value;
}