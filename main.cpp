#include "Board.h"
#include "Menu.h"

int main() {
    Board board(80, 25);
    Menu menu(board);
    menu.run();
    return 0;
}