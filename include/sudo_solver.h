#ifndef SUDO_SOLVER_H
#define SUDO_SOLVER_H
#include "command.h"
#include "board.h"

class SudoSolver{
    private:
        int rowUsed[9];
        int columnUsed[9];
        int blockUsed[9];
        vector<Board> result;
        vector<pair<int, int>> spaces;
    public:
        void solve_sudo_games(const Command& command);
        void solve_sudo_game(Board board);
        void dfs_search(Board &board, int pos);
        void flip(int i, int j, int digit);
        void clearState();
        bool isAnswerUnique();
};

#endif