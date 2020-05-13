#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "move.h"
#include "board.h"
# define M 5
# define N 4

movesArray** buildMovesBoard();
char **buildBoard();
boardPosArray ** validMoves(movesArray **moves, char **board);
bool isLegalMove(boardPos current, Move m, char **board);

void main()
{

	int i = 5;
	char t = (i + 1) + '0';
	printf("%c", t);
}
movesArray** buildMovesBoard()
{
	int i, j, k, moves_size;
	movesArray movesBoard[N][M];
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf("please enter the number of moves");
			scanf("%d", &moves_size);
			movesBoard[i][j].moves = (Move *)malloc(sizeof(Move)*moves_size);//free
			for (k = 0; k < moves_size; k++)
			{


			}
		}
	}

}
char **buildBoard()
{
	char board[N][M] = { {' ',' ',' ','*',' '},
						 {' ',' ',' ',' ',' '},
						 {' ',' ','*',' ',' '},
						 {' ',' ',' ',' ','*'} };
	return board;

}
boardPosArray** validMoves(movesArray **moves, char **board)
{
	int i, j, k;
	boardPos curr;
	boardPosArray** validPosBoard;
	validPosBoard = (boardPosArray **)malloc(sizeof(boardPosArray *)*(N*M));
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			curr[0] = 'A' + i;
			curr[1] = (j + 1) + '0';
			for (k = 0; k < moves[i][j].size; k++)
			{
				moves[i][j].moves[k];
				if (isLegalMove(curr, moves[i][j].moves[k], board))
				{
					//add func to allocte valid places
				}
			}
		}
	}
}
bool isLegalMove(boardPos current, Move m, char **board)
{
	char destRow, destCol;
	destRow = current[0] + m.rows;
	destCol = current[1] + m.cols;
	if ((destRow <= 'D' && destRow >= 'A') && (destCol>='1' && destCol<='5'))
	{
		if (board[destRow - 'A'][destCol - '1']==' ')
		{
			return true;
		}
	}
	return false;
}


