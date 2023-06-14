#include<cstring>
#include "board.h"

ofstream f;

vector<int> getRandOrder()
{   
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
            sign[num] = true;
        }
    }
    for(int i : order){
        cout<<i;
    }
    cout<<endl;
    return order;
}

void writeToFile(vector<Board> boards, string sign_statement){
   
    for(int k = 0; k < boards.size(); k++){
        f<<"-----------the "<<k+1<<"th EndMap-----------"<<endl;
        for(int i = 0; i < boards[k].size(); i++){
            for(int j = 0; j<boards[k][i].size(); j++){
                //输入到文件中
                f << boards[k][i][j];
            }
            f << endl;
        }
    }
    f.close();

}

vector<Board> read_from_file(string file_path){
    ifstream infile;
    vector<Board> boards;
    infile.open(file_path);
    char data[100];
    Board tmp;
    vector<char> row;
    while (!infile.eof())
    {
        infile.getline(data, 100);
        if (data[0] == '-')
        {
            boards.push_back(Board(tmp));
            tmp.clear();
            continue;
        }
        for (int i = 0; i < strlen(data); i++)
        {
            if (('1' <= data[i] && data[i] <= '9') || data[i] == '$')
            {
                row.push_back(data[i]);
            }
        }
        tmp.push_back(vector<char>(row));
        row.clear();
    }
    infile.close();
    return boards;
}