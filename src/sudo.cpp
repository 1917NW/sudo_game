#include<iostream>
#include<cstring>
#include<vector>
#include "command.h"
#include "sudo_generator.h"
#include "sudo_solver.h"


using namespace std;

Command parseCommand(int argc, char* argv[]);
void handleCommand(Command& command);
// void writeToFile(vector<Board> boards);

int main(int argc, char* argv[]){
   Command command = parseCommand(argc, argv);
   handleCommand(command);
}

void handleCommand(Command& command){
    if(command.is_create){
        SudoGenerator sudoGenerator = SudoGenerator();
        sudoGenerator.generate_endGame(command);
    }
    else if(command.is_solve){
        SudoSolver sudoSolver = SudoSolver();
        sudoSolver.solve_sudo_game(command);
    }
    else if(command.game_number!=0){
        SudoGenerator sudoGenerator = SudoGenerator();
        sudoGenerator.generate_sudo_game(command);
    }
}



Command parseCommand(int argc, char* argv[]){
    Command command = Command();
    if(strcmp(argv[1], "-c") == 0){
        command.is_create = true;
        try{
            int num = atoi(argv[2]);
            if(num >= 1 && num <= 1000000)
                command.endboard_number = num;
            else{
                cerr<<"arg c need a num between 1 and 1000000"<<endl;
                exit(0);
            }
        }
        catch(exception e){
           cerr<<"arg c need a num"<<endl;
           exit(0);
        }
    }
    else if(strcmp(argv[1], "-s") == 0){
        command.is_solve = true;
        if(argc >= 3)
            command.board_path = argv[2];
        else{
            cerr<<"arg s need a path"<<endl;
            exit(0);
        }
    }
    else{
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-n") == 0){
                try{
                   int num = atoi(argv[++i]);  
                   if(num >= 1 && num <= 10000)
                    command.game_number = num;
                    else{
                    cerr<<"arg n need a number between 1 and 10000"<<endl;
                    exit(0);
                    }
                }catch(exception e){
                    cerr<<"arg n need a number"<<endl;
                    exit(0);
                }
           
        }
        else if(strcmp(argv[i], "-m") == 0){
                try{
                    int num = atoi(argv[++i]);
                    if(num >= 1 && num <= 3)
                    command.game_hard_level = num;  
                    else{
                    cerr<<"arg m need a number between 1 and 3"<<endl;
                    exit(0);
                    }
                }catch(exception e){
                    cerr<<"arg m need a number"<<endl;
                    exit(0);
                }
        }
        else if(strcmp(argv[i], "-u") == 0){
            command.is_unique = true;
        }
        else if(strcmp(argv[i], "-r") == 0){
            try{
            int num = atoi(argv[++i]);
            if(num >= 20 && num <=55)
            command.hole_number = num;
            else{
            cerr<<"arg r need a number between 20 and 55"<<endl;
            exit(0);
            }
            }catch(exception e){
                cerr<<"arg r need a number"<<endl;
                exit(0);
            }
        }
           
    }
    
    }

    return command;
}