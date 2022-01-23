#include "Game.h"
#include<iostream>
#include<fstream>
#include <cstring>
using namespace std;

Game::Game(WINDOW* game) :esnake(game), fruit(game), score(0), gameSpeed(125), deltaScore(1){
    this->game = game;
}

int Game::mainMenu() {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //main menu composto por duas janelas uma que dá display ao texto da snake obtido do .txt e outra janela para o menu de opçoes
    WINDOW* snakeText = newwin(13, xMax - 14, 1, 7);
    box(snakeText, 0, 0);

    WINDOW* menuwin = newwin(6, 10, yMax - 12, (xMax / 2) - 4);
    box(menuwin, 0, 0);

    //refresh das janelas->update visual em relação ao que está em memoria
    refresh();
    wrefresh(menuwin);
    wrefresh(snakeText);

    //permitir que as teclas sejam utilizadas
    keypad(menuwin, true);

    string escolhas[4] = { "PLAY","SCORES","SETTINGS","EXIT" };
    int choice = 0;
    int highlight = 0;

    //config das cores do display da janela snakeText
    init_color(COLOR_YELLOW, 999, 999, 0);
    init_color(COLOR_GREEN, 00, 400, 00);
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    wattron(snakeText, COLOR_PAIR(1));

    //le do ficheiro e imprime com o formato personalizado na janela do texto da snake
    fstream inputfile("nomesnake.txt");
    string line;

    int y = -1;
    if (inputfile.is_open())
    {
        while (getline(inputfile, line))
        {
            y++;
            mvwprintw(snakeText, y, 2, "%s", line.c_str());
        }
    }
    else
    {
        printw("Didnt find file `nomesnake.txt`\n");
    }

    wrefresh(snakeText);
    inputfile.close();
    wattroff(snakeText, COLOR_PAIR(1));

    //choice == 10 -> ENTER(opçao selecionada)
    while (choice != 10)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == highlight)
            {
                //dá highlight à opçao em q se encontra
                wattron(menuwin, A_REVERSE);
            }
            mvwprintw(menuwin, i + 1, 1, escolhas[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        choice = wgetch(menuwin);

        //sistema do menu usando as teclas cima/baixo
        switch (choice)
        {
        case KEY_UP:
            highlight--;
            //ambos os if's fazem com que o menu "nao saia do seu alcance"
            if (highlight == -1)
            {
                highlight = 0;
            }
            break;

        case KEY_DOWN:
            highlight++;
            if (highlight == 4)
            {
                highlight = 3;
            }
            break;

        default:
            break;
        }

        //limpar e chamar a funçao com base na escolha que é guardada atraves do numero da var highlight
    }

    system("cls");


    //com base no valor que retorna entra em cada funçao especifica no main.cpp(snake_v2.cpp)
    if (highlight == 0)
    {
        //menu();
        return 1;
    }
    else if (highlight == 1)
    {
        //scores();
        return 2;
    }
    else if (highlight == 2)
    {
        //settings();
        return 3;
    }
    else if (highlight == 3)
    {
        exit(1);
    }
}

int Game::settings() {

    //Mudar caracteristicas do elementos do jogo
    erase();
    start_color();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //sistema de apresentação parecido com o main menu
    //2 janelas utilizadas-> uma para o display com o texto personalizado retirado de um ficheiro txt outra para o menu de escolha(3 modos de jogo + retornar para o menu)

    WINDOW* gameModeText = newwin(10, 65, 7, 25);
    box(gameModeText, 0, 0);

    WINDOW* gameModeWin = newwin(6, 14, yMax - 10, (xMax / 2) - 9);
    box(gameModeWin, 0, 0);

    //refresh de ambas as janelas
    refresh();
    wrefresh(gameModeText);
    wrefresh(gameModeWin);

    keypad(gameModeWin, true);

    string escolhas[4] = { "CHEETAH","SNAKE","SNAIL","EXIT TO MENU" };
    int choice = 0;
    int highlight = 0;

    init_color(COLOR_YELLOW, 999, 999, 0);
    init_color(COLOR_GREEN, 00, 400, 00);
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    wattron(gameModeText, COLOR_PAIR(1));

    //display personalizado->ficheiro .txt
    fstream inputfile("gamemodes.txt");
    string line;

    int y = -1;
    if (inputfile.is_open())
    {
        while (getline(inputfile, line))
        {
            y++;
            mvwprintw(gameModeText, y, 2, "%s", line.c_str());
        }
    }
    else
    {
        printw("Didnt find file `gamemodes.txt`\n");
    }

    wrefresh(gameModeText);
    inputfile.close();
    wattroff(gameModeText, COLOR_PAIR(1));

    //menu de escolha entre os 3 modos de jogo e retornar para o menu principal
    while (choice != 10)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == highlight)
            {
                wattron(gameModeWin, A_REVERSE);
            }
            mvwprintw(gameModeWin, i + 1, 1, escolhas[i].c_str());
            wattroff(gameModeWin, A_REVERSE);
        }

        choice = wgetch(gameModeWin);

        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
            {
                highlight = 0;
            }
            break;

        case KEY_DOWN:
            highlight++;
            if (highlight == 4)
            {
                highlight = 3;
            }
            break;

        default:
            break;
        }
    }

    erase();

    //3 modos de jogo em que cada um deles tem uma velocidade e sistema de pontos diferente
    if (highlight == 0)
    {
        //CHEETAH
        gameSpeed = 75;
        deltaScore = 3;
        return 1;
    }
    else if (highlight == 1)
    {
        //SNAKE
        gameSpeed = 125;
        deltaScore = 2;
        return 2;
    }
    else if (highlight == 2)
    {
        //SNAIL
        gameSpeed = 250;
        deltaScore = 1;
        return 3;
    }
    else if (highlight == 3)
    {
        //EXIT TO MAIN MENU
        return 4;
    }

    return 4;
}

void Game::play() {

    int lastKey = 0;
    keypad(game, TRUE);

    refresh();

    //display do nome do jogador e do respetivo score
    mvwaddstr(stdscr, 4, 5, "PLAYER NAME:");
    mvwaddstr(stdscr, 4, 100, "SCORE:");

    wrefresh(stdscr);
    wborder(game, 219, 219, 254, 254, 254, 254, 254, 254);
    wrefresh(game);
    curs_set(TRUE);

    //inserir nome
    nodelay(stdscr, false);
    echo();
    cbreak();
    char name[20];
    move(4, 18);
    wgetstr(stdscr, name);
    mvprintw(4, 18, "%s", name);
    mvwaddstr(stdscr, 4, 5, "PLAYER NAME:");
    mvwaddstr(stdscr, 4, 100, "SCORE:");
    wrefresh(stdscr);
    noecho();
    curs_set(FALSE);

    int i = 0;

    //primeira vez que entra no jogo adiciona uma fruta no ecrã numa posição randomizada
    fruit.addFood();
    fruit.printFood();

    //ciclo jogo
    while (i == 0) {
        //update score
        mvprintw(4, 108, "%d", score);
        refresh();

        //print da cobra na pos atual e com o tamanho atual
        esnake.print(gameSpeed);

        //recebe a key do utilizador para comandar a cobra
        int key = wgetch(game);

        //nao deixa que a cobra inverta o sentido
        if (key == -1 || (lastKey == KEY_RIGHT && key == KEY_LEFT) || (lastKey == KEY_LEFT && key == KEY_RIGHT) || (lastKey == KEY_DOWN && key == KEY_UP) || (lastKey == KEY_UP && key == KEY_DOWN) || (key != KEY_RIGHT && key != KEY_LEFT && key != KEY_DOWN && key != KEY_UP && key != 27)) {

            key = lastKey;
        }

        //key == 27 -> ESCAPE KEY
        if (key == 27) {

            GamePause();
        }
        else
            lastKey = key;

        //faz o movimento da cobra e verifica se esta bate contra uma das paredes ou nela própria
        if (!(esnake.move(key))) {
            GameOver();
            getch();
            erase();
            break;
        }

        //verifica a posição da cobra e se esta intersetar uma maça incrementa o seu tamanho assim como o seu score(dependendo do modo de jogo em que se encontra)
        if (esnake.findApple(fruit.getPosition())) {

            wrefresh(game);
            //verifica se a fruta aparece numa posição ocupada pela cobra
            do {
                fruit.addFood();    //gera outra posição random para a fruta
            } while (esnake.overlapApple(fruit.getPosition()));

            //print da maça no ecra(janela do jogo)
            fruit.printFood();

            //sistema de pontuação
            score = deltaScore + score;
        }
    }

    //ordenação dos scores a partir do ficheiro scores.txt

    vector <string> playerName;
    vector <int> highScores;
    string aux_name;
    int aux_score;

    //acede ao ficheiro scores.txt e importa a informação para os vetores playerName e highScores
    ifstream outputfile("scores.txt");
    if (outputfile.is_open())
    {
        while (!(outputfile.eof())) {
            outputfile >> aux_score;
            outputfile >> aux_name;
            if (aux_score < 0)
                break;
            highScores.push_back(aux_score);
            playerName.push_back(aux_name);
        }

    }
    else
    {
        printw("didnt find file 'scores.txt'\n");
    }
    outputfile.close();

    //player atual
    playerName.push_back(name);
    highScores.push_back(score);


    //sistema de ordenação de scores
    for (int i = 0; i < highScores.size(); i++)
    {
        for (int j = i + 1; j < highScores.size(); j++)
        {
            if (highScores[i] < highScores[j])      //verifica as duas primeiras posiçoes atuais(vao incrementando ao longo do ciclo) e se a 2ª for maior que a 1ª trocam de posição
            {
                aux_score = highScores[i];          //transfere para uma variavel auxiliar
                highScores[i] = highScores[j];      //1ª posiçao toma o valor da segunda
                highScores[j] = aux_score;          //2ª posição toma o valor da primeira fornceida pela variavel auxiliar

                aux_name = playerName[i];           //mesmo principio utilizado mas para os nomes(strings)
                playerName[i] = playerName[j];
                playerName[j] = aux_name;
            }
        }
        //apenas para os 10 melhores scores
        if (i == 10) {
            highScores.pop_back();
            playerName.pop_back();
        }
    }

    //print no ficheiro .txt os scores devidamente organizados e atualizados
    ofstream inputfile("scores.txt");
    if (inputfile.is_open())
    {
        for (int i = 0; i < highScores.size(); i++) {
            //se o vetor estiver vazio nao dá print a nada
            if (highScores[i] < 0)
                break;
            //verifica se é a ultima posição para nao imprimir um endl, pois este desformata o ficheiro causando problemas na utilização do menu Scores
            if (i + 1 < highScores.size())
                inputfile << highScores[i] << endl << playerName[i] << endl;
            else
                inputfile << highScores[i] << endl << playerName[i];
        }

    }
    else
    {
        printw("didnt find file 'scores.txt'\n");
    }
    inputfile.close();


}

void Game::scores() {

    //menu de apresentação dos 10 melhores scores

    WINDOW* highScore = newwin(14, 55, 3, 32);
    wborder(highScore, 219, 219, 254, 254, 254, 254, 254, 254);

    mvwprintw(stdscr, 20, 47, "PRESS ANY KEY TO CONTINUE");
    wrefresh(stdscr);
    wrefresh(highScore);

    keypad(highScore, true);

    vector <string> playerName;
    vector <int> highScores;
    string aux_name;
    int aux_score;
    
    //ler do ficheiro .txt e apresentar no menu scores com o formato personalizado
    ifstream outputfile("scores.txt");
    if (outputfile.is_open())
    {
        while (!(outputfile.eof())) {

            outputfile >> aux_score;
            outputfile >> aux_name;
            //se o ficheiro estiver vazio nao dá print
            if (aux_score < 0)
                break;
            highScores.push_back(aux_score);
            playerName.push_back(aux_name);
        }

    }
    else
    {
        printw("didnt find file 'scores.txt'\n");
    }
    outputfile.close();

    //formato de apresentação dos 10 melhores scores

    for (int i = 1; i <= 10; i++) {
        mvwprintw(highScore, 2 + i, 6, "%d", i);
        mvwaddch(highScore, 2 + i, 8, '.|');

    }

    mvwaddstr(highScore, 1, 10, "PLAYERS NAME");
    mvwaddstr(highScore, 2, 10, "-----------------------------------");
    mvwaddstr(highScore, 1, 40, "SCORE");
    mvwaddstr(highScore, 2, 40, "----");
    for (int i = 0; i < highScores.size(); i++) {
        mvwprintw(highScore, 3 + i, 10, "%s", playerName[i].c_str());
        mvwprintw(highScore, 3 + i, 40, "%d", highScores[i]);
    }

    //refresh e espera pela a interação do utilizador com o teclado para voltar para o menu principal
    wrefresh(highScore);
    wgetch(highScore);
    werase(highScore);
}

void Game::GamePause() {

    //função que é chamada quando o utilizador pressiona a tecla ESCAPE a meio do jogo,
    //esta dá display ao formato de pause personalizado e aguarda qualquer interação do utlizador com o teclado para retomar o jogo a partir da mesma posição
    WINDOW* gamepause = newwin(5, 40, 0, 40);

    keypad(gamepause, true);

    //formato personalizado do pause
    mvwprintw(gamepause, 1, 1, " _____ _____ _____ _____ _____ ____  ");
    mvwprintw(gamepause, 2, 1, "|  _  |  _  |  |  |   __|   __|    \\ ");
    mvwprintw(gamepause, 3, 1, "|   __|     |  |  |__   |   __|  |  |");
    mvwprintw(gamepause, 4, 1, "|__|  |__|__|_____|_____|_____|____/ ");
    mvwprintw(stdscr, 26, 46, "PRESS ANY KEY TO CONTINUE");
    refresh();

    //espera pela interação do utilizador e apaga o texto de paused assim como o press any key to continue
    wgetch(gamepause);
    mvwprintw(stdscr, 26, 46, "                          ");
    werase(gamepause);
    wrefresh(gamepause);
}

void Game::GameOver() {

    //função chamada quando a cobra bate contra uma das paredes ou contra ela própria e 
    //apresenta dentro da janela de jogo o formato personalizado de game over retirado de um ficheiro txt.
    //Espera pela interação do utilizador para voltar ao menu principal
    WINDOW* gameover = newwin(15, 70, 7, 25);
    wborder(gameover, 219, 219, 254, 254, 254, 254, 254, 254);

    //imprime o design do gameover dentro da tela de jogo anunciando o fim da partida
    fstream inputfile("gameover.txt");
    string line;

    int y = 2;
    if (inputfile.is_open())
    {

        while (getline(inputfile, line))
        {
            y++;
            mvwprintw(gameover, y, 7, "%s", line.c_str());
        }
    }
    else
    {
        printw("didnt find file 'gamepause.txt'\n");
    }
    wrefresh(gameover);
    inputfile.close();

}