#include "sudo_generator.h"
#include "sudo_solver.h"
// #include "board.h"

extern ofstream f;

SudoGenerator::SudoGenerator(/* args */)
{
    
}

SudoGenerator::~SudoGenerator()
{
}


void copySquare(Board &board, int src_x, int src_y, bool isRow)
{
        int rand_tmp = rand() % 2 + 1;
        int order_first[3] = {1, 2, 0};
        int order_second[3] = {2, 0, 1};
        if (rand_tmp == 2)
        {
            order_first[0] = 2;
            order_first[1] = 0;
            order_first[2] = 1;
            order_second[0] = 1;
            order_second[1] = 2;
            order_second[2] = 0;
        }
        for (int i = 0; i < 3; i++)
        {
            if (isRow)
            {
                board[src_x][i] = board[src_x + order_first[0]][src_y + i];
                board[src_x + 1][i] = board[src_x + order_first[1]][src_y + i];
                board[src_x + 2][i] = board[src_x + order_first[2]][src_y + i];
                board[src_x][i + 6] = board[src_x + order_second[0]][src_y + i];
                board[src_x + 1][i + 6] = board[src_x + order_second[1]][src_y + i];
                board[src_x + 2][i + 6] = board[src_x + order_second[2]][src_y + i];
            }
            else
            {
                board[i][src_y] = board[src_x + i][src_y + order_first[0]];
                board[i][src_y + 1] = board[src_x + i][src_y + order_first[1]];
                board[i][src_y + 2] = board[src_x + i][src_y + order_first[2]];
                board[i + 6][src_y] = board[src_x + i][src_y + order_second[0]];
                board[i + 6][src_y + 1] = board[src_x + i][src_y + order_second[1]];
                board[i + 6][src_y + 2] = board[src_x + i][src_y + order_second[2]];
            }
        }
 }

void SudoGenerator::generate_end_map(const Command& command){
    vector<Board> boards;
    for(int i = 0;i < command.endboard_number;i++){
        vector<vector<char> > board(9, vector<char>(9, '$'));
        vector<int> row = getRandOrder();
        for (int i = 0; i < 3; i++)
        {
            board[3][i + 3] = row[i] + '1';
            board[4][i + 3] = row[i + 3] + '1';
            board[5][i + 3] = row[i + 6] + '1';
        }
        copySquare(board, 3, 3, true);
        copySquare(board, 3, 3, false);
        copySquare(board, 3, 0, false);
        copySquare(board, 3, 6, false);
        boards.push_back(board);
    }
    f.open("../endmap.txt");
    writeToFile(boards,"th EndMap-----------");


}

int get_different_hard_level_dig_holes(int game_hard_level){
    int digHoles;
    switch (game_hard_level)
    {
    case 1:
        //25-34
        digHoles = rand()% 10 + 25;
        break;
    case 2:
        //35-44
        digHoles = rand()% 10 + 35;
        break;
    case 3:
        // 45-55
        digHoles = rand()% 11 + 45;
        break;
    default:
        //20-24
        digHoles = rand()% 5 + 20;
        break;
    }
    return digHoles;
}

void SudoGenerator::generate_sudo_game(const Command& command){
    int digHoles;
    SudoSolver solver = SudoSolver();
    vector<Board> boards;
    for(int i = 0; i < command.game_number;){
        if(command.hole_number!=0)
            digHoles = command.hole_number;
        else
            digHoles = get_different_hard_level_dig_holes(command.game_hard_level);
    
        vector<vector<char> > board(9, vector<char>(9, '$'));
        vector<int> row = getRandOrder();
        for (int i = 0; i < 3; i++)
        {
            board[3][i + 3] = row[i] + '1';
            board[4][i + 3] = row[i + 3] + '1';
            board[5][i + 3] = row[i + 6] + '1';
        }
        copySquare(board, 3, 3, true);
        copySquare(board, 3, 3, false);
        copySquare(board, 3, 0, false);
        copySquare(board, 3, 6, false);
        
        int digCount = digHoles;
        while (digHoles)
        {
            int x = rand() % 9;
            int y = rand() % 9;
            if (board[x][y] == '$')
                continue;
            char tmp = board[x][y];
            board[x][y] = '$';
            digHoles--;
        }
    if(command.is_unique){
        cout<<"解唯一"<<endl;
        solver.solve_sudo_game(board);
        if(solver.isAnswerUnique()){
             i++;
             boards.push_back(board);
        }
    }
    else{
        i++;
        boards.push_back(board);
    }
    }
  
    f.open("../sudogame.txt");
    writeToFile(boards,"th SudoGame-----------");
}