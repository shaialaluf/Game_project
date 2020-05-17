#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "move.h"
#include "Board.h"
# define M 5
# define N 4

void buildBoard(char ***board);
boardPosArray ** validMoves(movesArray **moves, char **board);
void freeBoardposArr(boardPosArray **PosBoard);
bool isLegalMove(boardPos current, Move m, char **board);
void addToPositionsArr(boardPos curr, boardPosArray **validPosBoard, Move m);
void printValidPosBoard(boardPosArray** validPosBoard);
void swapMoves(Move* m1, Move* m2);
movesArray** buildMovesBoard();
void freeBoardMoveArr(movesArray **moves);
void delMoves(int row, int col, int move_index, movesArray **moves);
void main()
{
	boardPosArray **validPosBoard;
	movesArray **movesboard;
	char **board;
	buildBoard(&board);
	printf("%c", board[3][3]);
	movesboard = buildMovesBoard();
	printf("%d", (**movesboard).size);
	validPosBoard = validMoves(movesboard, board);
	printValidPosBoard(validPosBoard);
}

void buildBoard(char ***board)
{
	*board = (char **)malloc(sizeof(char*)*N);//free
	for (int i = 0; i < N; i++) 
	{
		(*board)[i]= (char *)malloc(sizeof(char)*M);
	}
	for (int k = 0; k < N; k++)
	{
		for (int j = 0; j < M; j++)
		{
			(*board)[k][j] = ' ';
		}
	}
	(*board)[1][1] = '*';
	(*board)[2][2] = '*';
	(*board)[3][3] = '*';
}
boardPosArray** validMoves(movesArray **moves, char **board)
{
	int i, j, k;
	boardPos curr;
	boardPosArray** validPosBoard;
	validPosBoard = (boardPosArray **)malloc(sizeof(boardPosArray *)*(N*M));//free
	for (i = 0; i < N; i++)
	{

		for (j = 0; j < M; j++)
		{
			validPosBoard[i] = (boardPosArray *)malloc(sizeof(boardPosArray));
			curr[0] = 'A' + i;
			curr[1] = (j + 1) + '0';
			validPosBoard[i][j].size = 0;
			for (k = 0; k < moves[i][j].size; k++)
			{
				if (isLegalMove(curr, moves[i][j].moves[k], board))
				{
					addToPositionsArr(curr, validPosBoard, moves[i][j].moves[k]);
				}
				else
				{
					delMoves(i, j, k, moves);
				}
			}
		}
	}
	return validPosBoard;
}

bool isLegalMove(boardPos current, Move m, char **board)
{
	char destRow, destCol;
	destRow = current[0] + m.rows;
	destCol = current[1] + m.cols;
	if ((destRow <= 'D' && destRow >= 'A') && (destCol >= '1' && destCol <= '5'))
	{
		if (board[destRow - 'A'][destCol - '1'] == ' ')
		{
			return true;
		}
	}
	return false;
}
void addToPositionsArr(boardPos curr, boardPosArray **validPosBoard, Move m)
{
	int i, j;
	char destRow, destCol;
	i = curr[0] - 'A';
	j = curr[1] - '1';
	destRow = curr[0] + m.rows;
	destCol = curr[1] + m.cols;
	int poSize = validPosBoard[i][j].size;
	if (poSize == 0)
	{
		validPosBoard[i][j].positions = (boardPos*)malloc(sizeof(boardPos));//free
		validPosBoard[i][j].positions[0][0] = destRow;
		validPosBoard[i][j].positions[0][1] = destCol;
	}
	else
	{
		validPosBoard[i][j].positions = (boardPos*)realloc(validPosBoard[i][j].positions, sizeof(boardPos)*((poSize)+1));//free
		validPosBoard[i][j].positions[poSize][0] = destRow;
		validPosBoard[i][j].positions[poSize][1] = destCol;
	}
	(validPosBoard[i][j].size)++;
}
void delMoves(int row, int col, int move_index, movesArray **moves)
{
	int size = moves[row][col].size;
	swapMoves(&(moves[row][col].moves[move_index]), &(moves[row][col].moves[size - 1]));
	moves[row][col].moves = (Move *)realloc(moves[row][col].moves, sizeof(Move)*(size - 1));
	(moves[row][col].size)--;
}
void swapMoves(Move* m1, Move* m2)
{
	Move temp = *m1;
	*m1 = *m2;
	*m2 = temp;
}
void printValidPosBoard(boardPosArray** validPosBoard)
{
	int i, j, k;
	boardPos *temp;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf("%c%c : ", i + 'A', (j + 1) + '0');
			temp = validPosBoard[i][j].positions;
			for (k = 0; k < validPosBoard[i][j].size; k++)
			{
				printf("%s  ", temp[k]);
			}
			printf("\n");
		}

	}
}
void freeBoardposArr(boardPosArray **PosBoard)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			free(PosBoard[i][j].positions);
		}
	}
	free(PosBoard);
}
void freeBoardMoveArr(movesArray **moves)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			free(moves[i][j].moves);
		}
	}
}
movesArray** buildMovesBoard()
{
	movesArray movesBoard[N][M];
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			movesBoard[i][j].size=0;
		}
	}

	movesBoard[0][0].moves = (Move *)malloc(sizeof(Move) * 3);//free
	movesBoard[0][0].size = 3;
	movesBoard[0][0].moves[0].rows = 1;
	movesBoard[0][0].moves[0].cols = 1;
	movesBoard[0][0].moves[1].rows = 2;
	movesBoard[0][0].moves[1].cols = 2;
	movesBoard[0][0].moves[2].rows = 3;
	movesBoard[0][0].moves[2].cols = 3;

	movesBoard[1][0].moves = (Move *)malloc(sizeof(Move) * 2);//free
	movesBoard[1][0].size = 2;
	movesBoard[1][0].moves[0].rows = 2;
	movesBoard[1][0].moves[0].cols = 3;
	movesBoard[1][0].moves[1].rows = 1;
	movesBoard[1][0].moves[1].cols = -1;

	movesBoard[2][2].moves = (Move *)malloc(sizeof(Move) * 2);//free
	movesBoard[2][2].size = 2;
	movesBoard[2][2].moves[0].rows = 1;
	movesBoard[2][2].moves[0].cols = 2;
	movesBoard[2][2].moves[1].rows = 17;
	movesBoard[2][2].moves[1].cols = -2;

	movesBoard[3][3].moves = (Move *)malloc(sizeof(Move) * 1);//free
	movesBoard[0][0].size = 1;
	movesBoard[3][3].moves[0].rows = 3;
	movesBoard[3][3].moves[0].cols = 2;


	movesBoard[3][4].moves = (Move *)malloc(sizeof(Move) * 1);//free
	movesBoard[3][4].size = 1;
	movesBoard[3][4].moves[0].rows = 125;
	movesBoard[3][4].moves[0].cols = -126;

	return movesBoard;
}
