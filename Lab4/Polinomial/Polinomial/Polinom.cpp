#include "polinom.h"



Polinom::Polinom()
{
	list.GetHead()->m = Monom(0, -1);
}

void Polinom::AddMonom(const Monom& _m)
{
	Node* current = list.GetHead()->next;
	Node* previous = list.GetHead();
	while (_m.GetPower() < current->m.GetPower())
	{
		previous = current;
		current = current->next;
	}

	if (_m.GetPower() == current->m.GetPower())
	{
		current->m.SetCoeff(current->m.GetCoef() + _m.GetCoef());
		if (current->m.GetCoef() == 0)
		{
			List::DeleteNext(previous);
		}
	}
	else 
	{
		List::Insert(previous, new Node(_m));
	}
}

Polinom Polinom:: operator + (Polinom& P)
{
	Polinom Q(*this);
	Node* p = P.list.GetHead()->next;
	Node* q = Q.list.GetHead()->next;
	Node* q1 = Q.list.GetHead();
	while (true)
	{
		if (p->m.GetPower() == q->m.GetPower())
		{
			if (p->m.GetPower() == -1)
			{
				break;
			}
			else
			{
				q->m.SetCoeff(q->m.GetCoef() + p->m.GetCoef());
				p = p->next;
				if (q->m.GetCoef() == 0)
				{
					List::DeleteNext(q1);
					q = q1->next;
				}
				else
				{
					q1 = q;
					q = q->next;
				}
			}
		}
		else
		{
			if (p->m.GetPower() < q->m.GetPower())
			{
				q1 = q;
				q = q->next;
			}
			else 
			{
				List::Insert(q1, new Node(p->m));
				q1 = q1->next;
				p = p->next;
			}
		}
	}
	return Q;
}

Polinom Polinom::operator * (double number)
{
	if (number == 0)
	{
		Polinom Q;
		return Q;
	}
	Polinom Q(*this);
	Node* current = Q.list.GetHead()->next;
	while (current->m.GetPower() != -1)
	{
		current->m.SetCoeff(current->m.GetCoef()*number);
		current = current->next;
	}
	return Q;
}

Polinom Polinom::operator - (Polinom& p)
{
	return *this + p*(-1);

}

Polinom Polinom::operator*(Polinom& p)
{
	Polinom temp;
	Node * current1 = this->list.GetHead()->next;
	while (current1->m.GetPower() != -1)
	{
		Node * current2 = p.list.GetHead()->next;
		while (current2->m.GetPower() != -1)
		{
			temp.AddMonom(current1->m * current2->m);
			current2 = current2->next;
		}
		current1 = current1->next;
	}
	return temp;
}

ostream& operator << (ostream& ostr,  Polinom& p)
{
	Node * current = p.list.GetHead()->next;
	cout << " " << current->m;
	current = current->next;
	while (current->m.GetPower() != -1)
	{
		if (current->m.GetCoef()>0)
			cout << " + " << current->m;
		else
			cout << " " << current->m;
		current = current->next;
	}
	cout << endl;
	return ostr;
}

