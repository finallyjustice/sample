/** File:       q9-8.c
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

/*  Q9.8. NUM of ways to Compose n cents with 1-cent, 5-cent, 10-cent and 25-cent
 */

/* usage: gcc q9-8.c -o q9-8 */

#include <stdio.h>

int makeChangeIter(int n)
{
	int i, j, k;
	int tot = 0;

	for(i=0; i*25<=n; i++)
	{
		int rem_i = n-i*25;
		for(j=0; j*10<=rem_i; j++)
		{
			int rem_j = rem_i-j*10;
			for(k=0; k*5<=rem_j; k++)
			{
				tot++;
			}
		}
	}

	return tot;
}

int makeChangeRecv(int n, int denom)
{
	int next_denom;
	switch(denom)
	{
		case 25:
			next_denom = 10;
			break;
		case 10:
			next_denom = 5;
			break;
		case 5:
			next_denom = 1;
			break;
		case 1:
			return 1;
			break;
		case 0:
			return 0;
			break;
	}

	int i;
	int tot = 0;
	for(i=0; i*denom<=n; i++)
	{
		tot += makeChangeRecv(n-i*denom, next_denom);
	}
	return tot;
}

int main(int argc, char **argv)
{
	printf("%d, %d\n", makeChangeIter(10000), makeChangeRecv(10000, 25));	
	return 1;
}
