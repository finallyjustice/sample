#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>

using namespace std;

#define NUM_ALPH 26

struct Node {
	struct Node *next[NUM_ALPH];
	bool isString;
};

class Trie {
private:
	struct Node *root;
	struct Node *alloc_node();
	void deconstruct(struct Node *n);
public:
	Trie();
	~Trie();
	void insert(string s);
	int find(string s);
};

Trie::Trie()
{
	root = alloc_node();
}

Trie::~Trie()
{
	deconstruct(root);
}
	
void Trie::deconstruct(struct Node *n)
{
	for(int i=0; i<NUM_ALPH; i++) {
		if(n->next[i] != NULL)
			deconstruct(n->next[i]);
	}
	free(n);
}

void Trie::insert(string s)
{
	const char *data = s.c_str();
	int size =s.size();

	struct Node *tmp = this->root;
	for(int i=0; i<size; i++) {
		int idx = data[i]-'a';
		if(tmp->next[idx] == NULL) {
			tmp->next[idx] = alloc_node();
		}
		tmp = tmp->next[idx];
	}
	tmp->isString = 1;
}
	
int Trie::find(string s)
{
	const char *data = s.c_str();
	int size = s.size();

	struct Node *tmp = this->root;
	for(int i=0; i<size; i++) {
		int idx = data[i]-'a';
		if(tmp->next[idx] == NULL)
			return 0;
		tmp = tmp->next[idx];
	}
	return tmp->isString;
}
	
struct Node* Trie::alloc_node()
{
	struct Node *n = (struct Node *)malloc(sizeof(struct Node));
	for(int i=0; i<NUM_ALPH; i++)
			n->next[i] = NULL;
	n->isString = 0;
	return n;
}

int main(int argc, char **argv)
{
	Trie t;
	string s1 = "hello";
	string s2 = "hel";
	string s3 = "hepo";
	string s4 = "huli";
	string s5 = "abcdef";
	t.insert(s1);
	t.insert(s1);
	t.insert(s1);
	t.insert(s1);
	t.insert(s3);
	t.insert(s4);

	cout<<"S1: "<<t.find(s1)<<endl;
	cout<<"S2: "<<t.find(s2)<<endl;
	cout<<"S3: "<<t.find(s3)<<endl;
	cout<<"S4: "<<t.find(s4)<<endl;
	cout<<"S5: "<<t.find(s5)<<endl;

	return 0;
}
