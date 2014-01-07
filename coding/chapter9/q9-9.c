/** File:       q9-9.c
 ** Author:     Dongli Zhang
 ** Contact:    dongli.zhang0129@gmail.com
 **
 ** Copyright (C) Dongli Zhang 2013
 **
 ** This program is free software;  you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY;  without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 ** the GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program;  if not, write to the Free Software 
 ** Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*  Q9.9. 8 Queen problem
 */

/* usage: gcc q9-9.c -o q9-9 */

#include <stdio.h>

int check(int row, int *cfr)
{
	int i;
	for(i=0; i<row; i++)
	{
		int diff = abs(cfr[row]-cfr[i]);
		if(diff==0 || diff==row-i)
			return 0;
	}
	return 1;
}

void place_queen(int row, int *cfr, int board)
{
	int i;

	if(row == 8)
	{
		for(i=0; i<board; i++)
			printf("%d ", cfr[i]);
		printf("\n");
	}

	for(i=0; i<board; i++)
	{
		cfr[row] = i;
		if(check(row, cfr))
			place_queen(row+1, cfr, board);
	}
}

int main(int argc, char *argv)
{
	int i;
	int board = 8;
	int cfr[board];
	for(i=0; i<board; i++)
		cfr[i] = 0;

	place_queen(0, cfr, board);

	return 1;
}
