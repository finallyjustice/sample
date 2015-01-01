#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

#define NUM_NODE 24
#define BASE_CHAR 'a'

template <typename T>
struct node 
{
	struct node *c[NUM_NODE];
	T val;
};

template <typename T>
class Trie
{
private:
	struct node<T> *root;

public:
	Trie();
	void insert(string s, T val);
	struct node<T>* query(string s);
};


template <typename T>
Trie<T>::Trie()
{
	root = (struct node<T>*)malloc(sizeof(struct node<T>));
	for(int i=0; i<NUM_NODE; i++)
		root->c[i] = NULL;
}

template <typename T>
void Trie<T>::insert(string s, T val)
{
	const char *a = s.c_str();
	int len = s.length();
	struct node<T> *tmp = root;

	for(int i=0; i<len; i++)
	{
		int idx = a[i]-BASE_CHAR;
		// insert new node
		if(tmp->c[idx] == NULL)
		{
			struct node<T> *n = (struct node<T> *)malloc(sizeof(struct node<T>));
			for(int j=0; j<NUM_NODE; j++)
				n->c[j] = NULL;
			tmp->c[idx] = n;
		}
		tmp = tmp->c[idx];
	}
	tmp->val = val;
}
	
template <typename T>
struct node<T>* Trie<T>::query(string s)
{
	const char *a = s.c_str();
	int len = s.length();

	struct node<T> *tmp = root;

	for(int i=0; i<len; i++)
	{
		if(tmp == NULL) 
			return NULL;

		int idx = a[i]-BASE_CHAR;
		tmp = tmp->c[idx];
	}

	return tmp;
}

int main(int argc, char **argv)
{
	Trie<int> t;
	
	string k1("dongli");
	int v1 = 111;
	t.insert(k1, v1);
	
	string k2("dangli");
	int v2 = 222;
	t.insert(k2, v2);

	string k3("dongle");
	int v3 = 333;
	t.insert(k3, v3);

	string in("dengli");
	struct node<int> *ret = t.query(in);
	if(ret == NULL)
		cout<<"Val: NULL"<<endl;
	else
		cout<<"Val: "<<ret->val<<endl;

	return 0;
}
