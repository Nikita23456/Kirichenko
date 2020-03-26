#include "monom.h"

Monom::Monom(int _coef, int x, int y, int z)
{
	if ((x<0) || (y<0) || (z<0) || (x>19) || (y>19) || (z>19))
		throw "Incorrect power";
	coef = _coef;
	power = x * 400 + y * 20 + z;
}

int Monom::GetCoef() const
{
	return coef;
}

int Monom::GetX() const
{
	return (power / 400);
}

int Monom::GetY() const
{
	return ((power % 400) / 20);
}

int Monom::GetZ() const
{
	return (power % 20);
}

ostream& operator << (ostream& ostr, const Monom& m)
{
	if ((m.GetCoef() == 0) || (m.GetPower() == 0))
		cout << m.GetCoef();
	else
		ostr << m.GetCoef() << "x^" << m.GetX() << "y^" << m.GetY() << "z^" << m.GetZ();
	return ostr;
}



int Monom::GetPower() const
{
	return power;
}

void Monom::SetCoeff(int _coef)
{
	coef = _coef;
}

Monom::Monom(int _coef, int _power)
	: coef(_coef), power(_power)
{
}

Monom Monom::operator*(const Monom& m)
{
	Monom temp;
	temp.coef = this->coef * m.coef;
	int x = this->GetX() + m.GetX();
	int y = this->GetY() + m.GetY();
	int z = this->GetZ() + m.GetZ();
	if ((x>19) || (y>19) || (z>19))
		throw "Degree more than 9";
	temp.power = x * 400 + y * 20 + z;
	return temp;
}

void Monom::SetPower(int x, int y, int z)
{
	power = x * 400 + y * 20 + z;
}