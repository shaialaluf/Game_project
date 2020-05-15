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
void addToPositionsArr(boardPos curr, boardPosArray **validPosBoard, Move m);
void swapMoves(Move* m1, Move* m2);
void delMoves(int row, int col, int move_index, movesArray **moves);

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