#include<vector>
#include<time.h>
#include <stdlib.h>
using namespace std;
typedef vector<vector<char>> Board;

vector<int> getRandOrder()
{   
    srand(time(NULL));
    vector<int> order;
    bool sign[9];
    for(int i = 0; i < 9; i++){
        sign[i] = false;
    }
    while (order.size() != 9)
    {
        int num = rand() % 9;
        if (sign[num])
        {
            continue;
        }
        else
        {
            order.push_back(num);
            sign[num] =true;
        }
    }
    return order;
}