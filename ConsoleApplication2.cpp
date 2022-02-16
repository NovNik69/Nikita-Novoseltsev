/*
///////////////////////////////  TASK 3
 ______________________________________________________________________________________
 |   КЛАСС        |  РОДИТЕЛЬСКИЙ КЛАСС    |             ОПИСАНИЕ                     |
 |----------------|------------------------|------------------------------------------|
 |	  Card        |       нет              |             Карта                        |
 |----------------|------------------------|------------------------------------------|
 |	  Hand        |       нет              |    Набор карт,коллецкия объектов         |
 |	              |                        |         класса Card                      |
 |----------------|------------------------|------------------------------------------|
 |    Deck        |        Hand            |    Имеет дополнительную функциональность,|
 |	              |                        |   которая отсутсвует в классе Hand,      |
 |				  |						   |	 в частности - тасование и раздачу    |
 |----------------|------------------------|------------------------------------------|
 | GenericPlayer  |        Hand            |     Обобщенно описывает игрока. Не       |
 |                |                        |    является полноценным игроком,         | 
 |				  |						   |	  а лишь содержит элементы,           |
 |				  |						   |	  характерные как для                 |
 |				  |						   |	  игрока-человека,так и для           |
 |				  |						   |	  игрока-компьютера                   |
 |----------------|------------------------|------------------------------------------|
 |    Player      |    GenereticPlayer     |           Человек-игрок                  |
 |----------------|------------------------|------------------------------------------|
 |    House       |    GenereticPlayer     |          Компьютер-игрок                 |
 |----------------|------------------------|------------------------------------------|
 |    Game        |         нет            |               Игра                       |
 |------------------------------------------------------------------------------------|

*/


#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// 1 TASK

enum Gender
{
	GENDER_MALE,
	GENDER_FEMALE
};

class Person
{
private:
	std::string m_name;
	int m_age;
	Gender m_gender;
	float m_weight;
public:
	Person(std::string name, int age, Gender gender, float weight) :
		m_name(name), m_age(age), m_gender(gender), m_weight(weight) {}

	void setName(string name = "")
	{
		if (name == "")
		{
			cout << "Enter new name: ";
			cin >> m_name;
		}
		else
			m_name = name;
	}

	void setAge(int age = 0)
	{
		if (age == 0)
		{
		    cout << "Enter age: ";
			cin >> m_age;
		}
		else
			m_age = age;
	}

	void setWeight(float weight = 0.0)
	{
		if (weight == 0)
		{
			cout << "Enter weight: ";
			cin >> m_weight;
		}
		else
			m_weight = weight;
	}

	void printInfo() const
	{
		cout << "Name: " << m_name << endl
			<< "Age: " << m_age << endl
			<< "Sex: " << (m_gender == GENDER_MALE ? "male" : "female") << endl
			<< "Weight: " << m_weight << endl;
	}
};

class Student : public Person
{
private:
	static int count;
	int m_yos; 
public:
	Student(string name, int age, Gender gender, float weight, int yos) :
		Person(name, age, gender, weight), m_yos(yos)
	{
		count++;
	}

	static void printCount()
	{
		cout << "Number of students: " << count << endl;
	}

	void setYearStudy(int yos = 0)
	{
		if (yos == 0)
		{
			std::cout << "Year of study: ";
			std::cin >> m_yos;
		}
		else
			m_yos = yos;
	}

	void incYear()
	{
		m_yos++;
	}

	void printInfo() const
	{
		Person::printInfo();
		std::cout << "Year of study: " << m_yos << std::endl;
	}

	~Student()
	{
		count--;
	}
};

int Student::count = 0;



// 2 TASK
class Fruit
{
private:
	string m_name;
	string m_color;
public:
	void setName(string name)
	{
		m_name = name;
	}

	void setColor(string color)
	{
		m_color = color;
	}

	const string& getName() const
	{
		return m_name;
	}

	const string& getColor() const
	{
		return m_color;
	}
};

class Apple : public Fruit
{
public:
	Apple(string color = "")
	{
		if (color == "")
			color = "green";

		setName("apple");
		setColor(color);
	}
};

class Banana : public Fruit
{
public:
	Banana(string color = "")
	{
		if (color == "")
			color = "yellow";

		setName("banana");
		setColor(color);
	}
};

class GrannySmith : public Apple
{
public:
	GrannySmith()
	{
		setName("Granny Smith " + Apple::getName());
	}
};
int main()
{
	// 1 TASK
	Student Alex("Alex", 20, GENDER_MALE, 75.2, 2020);
	Alex.printInfo();
	Student::printCount();

	Student Michail("Michail", 19, GENDER_MALE, 93, 2021);
	Michail.printInfo();
	Student::printCount();

	Student Sofa("Sofa", 23, GENDER_FEMALE, 51, 2017);
	Sofa.printInfo();
	Student::printCount();


	// 2 TASK
    Apple a("red");
    Banana b;
    GrannySmith c;

    cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}

