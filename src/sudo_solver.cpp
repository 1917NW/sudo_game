#include <string.h>
#include "sudo_solver.h"
#include "command.h"

extern ofstream f;

void SudoSolver::solve_sudo_games(const Command& command){
    vector<Board> boards = read_from_file(command.board_path);
    cout<<command.board_path<<endl;
    cout<<boards.size()<<endl;
    int count = 1;
    for(Board board : boards){
        cout<<count<<endl;
        solve_sudo_game(board);
        cout<<"res:"<<result.size()<<endl;

        f.open("../answer.txt");
        f<<"-----------"<<count++<<"th Answers-----------"<<endl;
        cout<<count<<endl;
        writeToFile(result,"th Answer-----------");
    }

}

void SudoSolver::solve_sudo_game(Board board){
    
     clearState();
     for (int i = 0; i < 9; i++)
     {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '$')
            {
                spaces.push_back(pair<int, int>(i, j));
            }
            else
            {
                int digit = board[i][j] - '1';
                flip(i, j, digit);
            }
        }
     }
     cout<<"solve_sudo_game"<<endl;
     dfs_search(board, 0);
    
}

void SudoSolver::flip(int i, int j, int digit)
{
    rowUsed[i] ^= (1 << digit);
    columnUsed[j] ^= (1 << digit);
    blockUsed[(i / 3) * 3 + j / 3] ^= (1 << digit);
}

void SudoSolver::clearState(){
     memset(rowUsed, 0, sizeof(rowUsed));
     memset(columnUsed, 0, sizeof(columnUsed));
     memset(blockUsed, 0, sizeof(blockUsed));
     spaces.clear();
     result.clear();
}

void SudoSolver::dfs_search(Board &board, int pos){
     if (pos == spaces.size())
        {
            result.push_back(board);
            return;
        }
        int i = spaces[pos].first;
        int j = spaces[pos].second;
        int mask = ~(rowUsed[i] | columnUsed[j] | blockUsed[(i / 3) * 3 + j / 3]) & 0x1ff;
        int digit = 0;
        while (mask)
        {
            if (mask & 1)
            {
                flip(i, j, digit);
                board[i][j] = '1' + digit;
                dfs_search(board, pos + 1);
                flip(i, j, digit);
            }
            mask = mask >> 1;
            digit++;
        }
}

 bool SudoSolver::isAnswerUnique(){
    return result.size() ==1;
 }