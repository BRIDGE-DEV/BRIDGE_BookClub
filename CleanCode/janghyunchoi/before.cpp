// https://www.acmicpc.net/problem/7682
// before
#include<iostream>
#include<algorithm>
using namespace std;
const string VALID = "valid";
const string INVALID = "invalid";
constexpr char X = 'X';
constexpr char O = 'O';


string Check(string board)
{
    int xCnt = 0;
    int oCnt = 0;
    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] == X) xCnt++;
        else if (board[i] == O) oCnt++;
    }
    if (xCnt < oCnt || xCnt - oCnt > 1)
        return INVALID;
    
    char completed[9] = {};

    // 행 연속 체크
    for (int i = 0; i < 3; i++)
    {
        int continuousCnt = 1;
        char firstChar = board[i * 3];
        for (int j = 1; j < 3; j++)
        {
            if (board[i*3 + j] != firstChar) break;
            continuousCnt++;
        }
        if (continuousCnt == 3)
        {
            if (firstChar == X)
            {
                for (int j = 0; j < 3; j++)
                    completed[i * 3 + j] = X;
            }
            else if (firstChar == O)
            {
                for (int j = 0; j < 3; j++)
                    completed[i * 3 + j] = O;
            }
        }
    }
    // 열 연속 체크
    for (int i = 0; i < 3; i++)
    {
        int continuousCnt = 1;
        char firstChar = board[i];
        for (int j = 1; j < 3; j++)
        {
            if (board[i + j * 3] != firstChar) break;
            continuousCnt++;
        }
        if (continuousCnt == 3)
        {
            if (firstChar == X)
            {
                for (int j = 0; j < 3; j++)
                    completed[i+ j * 3] = X;
            }
            else if (firstChar == O)
            {
                for (int j = 0; j < 3; j++)
                    completed[i + j * 3] = O;
            }
        }
    }

    // 대각선 연속 체크
    int continuousCnt = 1;
    char firstChar = board[0];
    for (int j = 1; j < 3; j++)
    {
        if (board[j*4] != firstChar) break;
        continuousCnt++;
    }
    if (continuousCnt == 3)
    {
        if (firstChar == X)
        {
            for (int j = 0; j < 3; j++)
                completed[j * 4] = X;
        }
        else if (firstChar == O)
        {
            for (int j = 0; j < 3; j++)
                completed[j * 4] = O;
        }
    }
    continuousCnt = 1;
    firstChar = board[2];
    for (int j = 1; j < 3; j++)
    {
        if (board[2 + j * 2] != firstChar) break;
        continuousCnt++;
    }
    if (continuousCnt == 3)
    {
        if (firstChar == X)
        {
            for (int j = 0; j < 3; j++)
                completed[2 + j * 2] = X;
        }
        else if (firstChar == O)
        {
            for (int j = 0; j < 3; j++)
                completed[2 + j * 3] = O;
        }
    }

    int xCompleteCnt = 0;
    int oCompleteCnt = 0;
    for (int i = 0; i < 9; i++)
    {
        if (completed[i] == X) xCompleteCnt++;
        else if (completed[i] == O) oCompleteCnt++;
    }

    if (xCompleteCnt >= 3 && xCompleteCnt < 6 && oCompleteCnt == 0)
    {
        if (xCnt == oCnt)return INVALID;
        else return VALID;
    }
    else if (xCompleteCnt == 0 && oCompleteCnt >= 3 && oCompleteCnt < 6)
    {
        if(xCnt > oCnt)return INVALID;
        else return VALID;
    }
    else if (xCompleteCnt == 0 && oCompleteCnt == 0 && xCnt + oCnt == 9) return VALID;
    else return INVALID;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);

    string input;
    while (true)
    {
        cin >> input;
        if (input == "end") break;
        cout << Check(input) << "\n";
    }
}
