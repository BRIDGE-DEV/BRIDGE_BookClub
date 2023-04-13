// https://www.acmicpc.net/problem/7682
// after
#include<iostream>
#include<algorithm>
using namespace std;
const string VALID = "valid";
const string INVALID = "invalid";
constexpr char X = 'X';
constexpr char O = 'O';

int countShape(const string& str, char shape)
{
	int cnt = 0;
	for (const char& c : str)
		if (c == shape) cnt++;
	return cnt;
}
bool isValidXWin(int xCompletedCnt, int oCompletedCnt, int xCnt, int oCnt) {
	return xCompletedCnt >= 3 && xCompletedCnt < 6 && oCompletedCnt == 0 && xCnt != oCnt;
}
bool isValidOWin(int xCompletedCnt, int oCompletedCnt, int xCnt, int oCnt) {
	return xCompletedCnt == 0 && oCompletedCnt >= 3 && oCompletedCnt < 6 && xCnt == oCnt;
}
bool isFullBoard(int xCompletedCnt, int oCompletedCnt, int xCnt, int oCnt) {
	return xCompletedCnt == 0 && oCompletedCnt == 0 && xCnt + oCnt == 9;
}
bool isValidTurns(int xCnt, int oCnt) {
	return xCnt >= oCnt && xCnt - oCnt <= 1;
}
bool isValidBoard(const string& board, const string& completed) {
	int xCnt = countShape(board, X);
	int oCnt = countShape(board, O);
	int xCompletedCnt = countShape(completed, X);
	int oCompletedCnt = countShape(completed, O);

	bool isValid = (isValidXWin(xCompletedCnt, oCompletedCnt, xCnt, oCnt) ||
		isValidOWin(xCompletedCnt, oCompletedCnt, xCnt, oCnt) ||
		isFullBoard(xCompletedCnt, oCompletedCnt, xCnt, oCnt)) &&
		isValidTurns(xCnt, oCnt);
	return isValid;
}

void chceckRows(const string& board, string& completed, char shape)
{
	for (int i = 0; i < 3; i++)
	{
		if (board[i * 3] == shape && board[i * 3 + 1] == shape && board[i * 3 + 2] == shape)
			for (int j = 0; j < 3; j++)	completed[i * 3 + j] = shape;
	}
}
void checkColumns(const string& board, string& completed, char shape)
{
	for (int i = 0; i < 3; i++)
	{
		if (board[i] == shape && board[i + 3] == shape && board[i + 6] == shape)
			for (int j = 0; j < 3; j++)	completed[i + j * 3] = shape;
	}
}
void checkDiagonals(const string& board, string& completed, char shape)
{
	if (board[0] == shape && board[4] == shape && board[8] == shape) 
		for (int j = 0; j < 3; j++) completed[j * 4] = shape;

	if (board[2] == shape && board[4] == shape && board[6] == shape)
		for (int j = 0; j < 3; j++) completed[j*2 + 2] = shape;
}
void checkBoard(const string& board, string& completed)
{
	chceckRows(board, completed, X);
	chceckRows(board, completed, O);
	checkColumns(board, completed, X);
	checkColumns(board, completed, O);
	checkDiagonals(board, completed, X);
	checkDiagonals(board, completed, O);
}


string getBoardStatus(const string& board)
{
	string completed = "123456789";
	checkBoard(board, completed);

	if (isValidBoard(board, completed)) 
		return VALID;
	else
		return INVALID;
}
int main()
{
	cin.tie(0)->sync_with_stdio(0);

	string input;
	while (true)
	{
		cin >> input;
		if (input == "end") break;
		cout << getBoardStatus(input) << "\n";
	}
}