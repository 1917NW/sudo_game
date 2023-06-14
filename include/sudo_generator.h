#include "command.h"
class SudoGenerator
{

public:
    SudoGenerator();
    ~SudoGenerator();
    void generate_endGame(const Command& command);
    void generate_sudo_game(const Command& command);
    
};

