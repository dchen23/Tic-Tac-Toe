#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "board.h"
#include "player.h"

TEST_CASE("check is_winner() function") {
    Board board;
    Player bot1('X', "bot1");
    Player bot2('O', "bot2");
    board.set_board( {{'X', 'X', 'X'}, {' ', 'O', ' '}, {' ', ' ', 'O'}} );
    CHECK(board.is_winner(bot1) == true);
    CHECK(board.is_winner(bot2) == false);
    board.set_board( {{'X', 'O', 'X'}, {'O', 'O', 'X'}, {'X', 'O', ' '}} );
    CHECK(board.is_winner(bot1) == false);
    CHECK(board.is_winner(bot2) == true);
    board.set_board( {{'X', 'O', 'X'}, {'O', 'X', 'X'}, {'O', 'X', 'O'}} );
    CHECK(board.is_winner(bot1) == false);
    CHECK(board.is_winner(bot2) == false);
}

TEST_CASE("check if the tokens layout is legit") {
    Board board;
    Player mock1('X', "mock1");
    Player mock2('O', "mock2");
    while (true) {
        board.print_board();
        if (board.is_winner(mock2) || board.is_tie()) {
            break;
        }
        while (!(board.submit_move(mock1))) {
            continue;
        }
        CHECK(board.is_legit() == true);
        board.print_board();
        if (board.is_winner(mock1) || board.is_tie()) {
            break;
        }
        while (!(board.submit_move(mock2))) {
            continue;
        }
        CHECK(board.is_legit() == true);
    }
}