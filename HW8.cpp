#include <iostream>
#include <string>


using namespace std;




class DivisionByZero
{
private:
	string m_message;
public:
	DivisionByZero(string message = "") : m_message(message) {}
	const string& getMessage() const { return m_message; }
};

namespace my
{

	template <typename T>
	double div(T a, T b)
	{
		if (b == 0)
			throw DivisionByZero("??????? ?? ????!");

		return a / b;
	}

}

void exercise_1()
{
	try
	{
		double result = my::div(10, 0);
		cout << result << std::endl;
	}
	catch (const DivisionByZero& e)
	{
		cerr << e.getMessage() << std::endl;
	}
}


class Ex
{
public:
	double m_x;

	Ex(double x) : m_x(x) {};
};

class Bar
{
private:
	double m_y;
public:
	Bar(double y = 0.0) : m_y(y) {}
	void set(double a)
	{
		if ((m_y + a) > 100)
			throw Ex(a * m_y);
		else
			m_y = a;
	}
};

void exercise_2()
{
	Bar a;
	int b;

	try
	{
		while (true)
		{
			cin >> b;
			if (b == 0)
				break;
			a.set(b);
		}
	}
	catch (const Ex& e)
	{
		cout << e.m_x << std::endl;
	}
}


class OffTheField
{
	int cur_pos_x;
	int cur_pos_y;
	int new_pos_x;
	int new_pos_y;
	string m_message;
public:
	OffTheField(int c_x, int c_y, int n_x, int n_y) :
		cur_pos_x(c_x), cur_pos_y(c_y), new_pos_x(n_x), new_pos_y(n_y), m_message("")
	{
		if (new_pos_x > 10 || new_pos_x < 1)
		{
			m_message += "?????? ?????????? X! ????? ??????? ?? ??????? ????!\n";
			m_message += '[' + to_string(cur_pos_x) + ';' + to_string(cur_pos_y) + "] => [" +
				to_string(new_pos_x) + ';' + to_string(new_pos_y) + "]\n";
		}
		if (new_pos_y > 10 || new_pos_y < 1)
		{
			m_message += "?????? ?????????? Y! ????? ??????? ?? ??????? ????!\n";
			m_message += '[' + to_string(cur_pos_x) + ';' + to_string(cur_pos_y) + "] => [" +
				to_string(new_pos_x) + ';' + to_string(new_pos_y) + "]\n";
		}
	}

	const std::string& getInfo() const
	{
		return m_message;
	}
};

class IllegalCommand
{
private:
	int cur_pos_x;
	int cur_pos_y;
	int new_pos_x;
	int new_pos_y;
	string m_message;
public:
	IllegalCommand(int c_x, int c_y, int n_x, int n_y) :
		cur_pos_x(c_x), cur_pos_y(c_y), new_pos_x(n_x), new_pos_y(n_y), m_message("")
	{
		if (abs(cur_pos_x - new_pos_x) > 1)
		{
			m_message += "?????? ?????????? X! ??? ??????? ?????!\n";
			m_message += '[' + to_string(cur_pos_x) + ';' + to_string(cur_pos_y) + "] => [" +
				to_string(new_pos_x) + ';' + to_string(new_pos_y) + "]\n";
		}

		if (abs(cur_pos_y - new_pos_y) > 1)
		{
			m_message += "?????? ?????????? Y! ??? ??????? ?????!\n";
			m_message += '[' + to_string(cur_pos_x) + ';' + to_string(cur_pos_y) + "] => [" +
				to_string(new_pos_x) + ';' + to_string(new_pos_y) + "]\n";
		}

		if (cur_pos_x == new_pos_x && cur_pos_y == new_pos_y)
		{
			m_message += "?????? ?????????? X ? Y! ?????? ??????? ?? ??????? ?????!\n";
			m_message += '[' + to_string(cur_pos_x) + ';' + to_string(cur_pos_y) + "] => [" +
				to_string(new_pos_x) + ';' + to_string(new_pos_y) + "]\n";
		}
	}

	const std::string& getInfo() const
	{
		return m_message;
	}
};

class Robot
{
private:
	int pos_x;
	int pos_y;
public:
	Robot(int x = 5, int y = 5) : pos_x(x), pos_y(y)
	{
		cout << "????????? ??????? ??????: [" << pos_x << ';' << pos_y << ']' << endl;
	}

	void move(int x, int y)
	{
		if (abs(pos_x - x) > 1 || abs(pos_y - y) > 1 || (pos_x == x && pos_y == y))
			throw IllegalCommand(pos_x, pos_y, x, y);
		if (x > 10 || x < 1 || y > 10 || y < 1)
			throw OffTheField(pos_x, pos_y, x, y);

		cout << "????? ?????? [" << pos_x << ';' << pos_y << "] => [" << x << ';' << y << ']' << endl;

		pos_x = x;
		pos_y = y;
	}
};

void exercise_3()
{
	int x = 0, y = 0;
	Robot r;

	while (true)
	{
		std::cin >> x >> y;

		if (x == 0 && y == 0)
			break;

		try
		{
			r.move(x, y);
		}
		catch (const IllegalCommand& e)
		{
			cerr << e.getInfo() << endl;
		}
		catch (const OffTheField& e)
		{
			cerr << e.getInfo() << endl;
		}
	}
}

int main()
{
	exercise_1();
	exercise_2();
	exercise_3();

	return 0;
}