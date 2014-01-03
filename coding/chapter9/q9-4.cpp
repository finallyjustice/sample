/** File:       q9-4.c
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

/*  Q4.4. Return all subsets of a set
 */

/* usage: g++ q9-4.c -o q9-4 */

#include <iostream>
#include <list>

using namespace std;

list< list<int> > find_allsubset(list<int> in, int index)
{
	list< list<int> > allsubset;
	int size = in.size();
	if(size == index)
		return allsubset;

	list<int>::iterator inp = in.begin();
	advance(inp, index);
	int item = *inp;
	allsubset = find_allsubset(in, index+1);

	list< list<int> > tmpset;
	for(list< list<int> >::iterator its=allsubset.begin(); its!=allsubset.end(); its++)
	{
		list<int> tmp = *its;
		tmp.push_back(item);
		tmpset.push_back(tmp);
	}
	list<int> tmp;
	tmp.push_back(item);
	tmpset.push_back(tmp);

	for(list< list<int> >::iterator its=tmpset.begin(); its!=tmpset.end(); its++)
		allsubset.push_back(*its);
	return allsubset;
}

int main(int argc, char **argv)
{
	list<int> in;
	in.push_back(1);
	in.push_back(3);
	in.push_back(5);
	in.push_back(7);
	in.push_back(9);

	list< list<int> > allsubset = find_allsubset(in, 0);
	int i = 1;
	for(list< list<int> >::iterator its=allsubset.begin(); its!=allsubset.end(); its++)
	{
		cout<<i<<": ";
		i++;
		for(list<int>::iterator it=its->begin(); it!=its->end(); it++)
			cout<<*it<<" ";
		cout<<endl;
	}
	cout<<i<<": "<<endl;
}
