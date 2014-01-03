/** File:       q9-5.c
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

/*  Q4.4. Return all permutations of a string
 */

/* usage: g++ q9-5.c -o q9-5 */

#include <iostream>
#include <list>

using namespace std;

list< list<int> > find_allperm(list<int> in, int index)
{
	list< list<int> > ret;
	int size = in.size();

	if(size == index)
		return ret;

	list<int>::iterator inp = in.begin();
	advance(inp, index);
	int item = *inp;
	list< list<int> > allperm = find_allperm(in, index+1);

	size = allperm.size();
	if(size == 0)
	{
		list<int> tmp;
		tmp.push_back(item);
		ret.push_back(tmp);
	}
	else
	{
		for(list< list<int> >::iterator its=allperm.begin(); its!=allperm.end(); its++)
		{
			int ts = its->size();
			for(int i=0; i<=ts; i++)
			{
				list<int> tmp = *its;
				list<int>::iterator tip = tmp.begin();
				advance(tip, i);
				tmp.insert(tip, item);
				ret.push_back(tmp);
			}
		}
	}

	return ret;
}

int main(int argc, char **argv)
{
	list<int> in;
	in.push_back(1);
	in.push_back(3);
	in.push_back(5);
	in.push_back(7);
	in.push_back(9);

	list< list<int> > allperm = find_allperm(in, 0);

	int c = 1;
	for(list< list<int> >::iterator its=allperm.begin(); its!=allperm.end(); its++)
	{
		cout<<c<<": ";
		c++;
		for(list<int>::iterator it=its->begin(); it!=its->end(); it++)
			cout<<*it<<" ";
		cout<<endl;
	}
}
