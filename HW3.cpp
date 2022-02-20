#include <iostream>

// Task 1
  int PI =3.14159265358979323846;

float getRadian(float degree)
{
	return (PI / 180) * degree;
}

class Figure
{
public:
	virtual float area() = 0;
	virtual ~Figure() = 0;
};

class Parallelogram : public Figure
{
private:
	float m_side_a;
	float m_side_b;
	float m_height;
protected:
	float getSideA() const
	{
		return m_side_a;
	}

	float getSideB() const
	{
		return m_side_b;
	}
public:
	Parallelogram(float side_a, float height, float side_b = 0.0)
		: m_side_a(side_a), m_side_b(side_b), m_height(height) { }

	float area()
	{
		float area = m_side_a * m_height;

		std::cout << "Площадь параллелограмма равна " << area << std::endl;

		return area;
	}
};

class Circle : public Figure
{

};

class Rectangle : public Parallelogram
{
public:
	Rectangle(float side_a, float side_b)
		: Parallelogram(side_a, side_b, side_b) { }

	float area()
	{
		float area = getSideA() * getSideB();

		std::cout << "Площадь прямоугольника равна " << area << std::endl;

		return area;
	}
};

class Square : public Parallelogram
{
	Square(float side_a, float side_b)
		: Parallelogram(side_a, side_b, side_b) { }

	float area()
	{
		float area = getSideA() * getSideB();

		std::cout << "Площадь квадрата равна " << area << std::endl;

		return area;
	}
};

class Rhombus : public Parallelogram
{
	Rhombus(float side_a, float side_b)
		: Parallelogram(side_a, side_b, side_b) { }

	float area()
	{
		float area = getSideA() * getSideB();

		std::cout << "Площадь ромба равна " << area << std::endl;

		return area;
	}
};



// Task 2

class Car
{
private:
	std::string m_company;
	std::string m_model;
protected:
	std::string getCompany() const
	{
		return m_company;
	}

	std::string getModel() const
	{
		return m_model;
	}
public:
	Car(std::string company, std::string model) : m_company(company), m_model(model)
	{
		std::cout << "Транспортное средство компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

class PassengerCar : virtual public Car
{
public:
	PassengerCar(std::string company, std::string model) : Car(company, model)
	{
		std::cout << "Легковой автомобиль компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

class Bus : virtual public Car
{
public:
	Bus(std::string company, std::string model) : Car(company, model)
	{
		std::cout << "Автобус компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(std::string company, std::string model) :
		PassengerCar(company, model), Bus(company, model), Car(company, model)
	{
		std::cout << "Минивэн компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

// Task 3

class Fraction
{
private:
	bool is_zero;
	bool is_integer;
	int numerator;
	int denominator;

	/*
	 * Поиск наибольшего общего делителя
	 * для числителя и знаменателя
	 */
	int NOD(int n1, int n2)
	{
		int div;
		if (n1 == n2)  return n1;
		int d = n1 - n2;
		if (d < 0)
		{
			d = -d;
			div = NOD(n1, d);
		}
		else
			div = NOD(n2, d);

		return div;
	}

	/*
	 * Поиск наименьшего общего кратного
	 * для знаменателей
	 */
	int NOK(int n1, int n2)
	{
		return n1 * n2 / NOD(n1, n2);
	}

	/*
	 * Функция сокращения дроби
	 */
	void reduceFraction(int& a, int& b)
	{
		int divisor = NOD(abs(a), abs(b));
		a = a / divisor;
		b = b / divisor;
	}
public:
	Fraction() : numerator(0), denominator(0)
	{
		is_zero = true;
		is_integer = true;
	}

	Fraction(int num, int dnum) : numerator(num), denominator(dnum)
	{
		if (numerator == 0 || denominator == 0)
		{
			std::cout << "Числитель или знаменатель не может быть нулевым!\n"
				<< "Число будет инициализировано нулём!" << std::endl;
			numerator = 0;
			denominator = 0;
			is_zero = true;
			is_integer = true;
		}
		else
		{
			is_zero = false;
			is_integer = (abs(numerator) == abs(denominator) || denominator == 1);
		}
	}

	friend std::ostream& operator<<(std::ostream&, const Fraction&);

	Fraction operator+(const Fraction&);
	Fraction operator-(const Fraction&);
	Fraction operator*(const Fraction&);
	Fraction operator/(const Fraction&);

	Fraction operator-() const;

	bool operator==(const Fraction&);
	bool operator!=(const Fraction&);
	bool operator<(const Fraction&);
	bool operator>=(const Fraction&);
	bool operator>(const Fraction&);
	bool operator<=(const Fraction&);
};

std::ostream& operator<<(std::ostream& s, const Fraction& f)
{
	if (f.is_integer)
	{
		if (f.is_zero)
			s << f.numerator;
		else
			s << f.numerator / f.denominator;
	}
	else
		s << f.numerator << '/' << f.denominator;

	return s;
}


// Task 4


class Card
{
public:
	enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

	Card(rank r = ACE, suit s = SPADES, bool ifu = true) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) { }

	int GetValue() const;
	void Flip();

	
private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

int Card::GetValue() const
{
	int value = 0;
	if (m_IsFaceUp)
	{
		value = m_Rank;
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}

void Card::Flip()
{
	m_IsFaceUp = !m_IsFaceUp;
}

int main() {

	return 0;
}