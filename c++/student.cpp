#include <iostream>
#include <stdio.h>

using namespace std;

class Student
{
private:
	int id;
	char name[20];

public:
	Student();
	~Student();
	int getId();
	char* getName();
};

Student::Student()
{
	id = 100;
	sprintf(name, "Justice");
}

Student::~Student()
{
	
}

int Student::getId()
{
	return this->id;
}

char* Student::getName()
{
	return this->name;
}

int main(int argc, char **argv)
{
	Student *s = new Student();
	cout<<"ID: "<<s->getId()<<endl;
	cout<<"Name: "<<s->getName()<<endl;
}
