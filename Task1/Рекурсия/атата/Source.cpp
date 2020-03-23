#include <iostream>

void f(int mas[], const int size, int i = 0)
{
	if (i != size)
	{
		std::cout <<mas[i] << std::endl;
		f(mas, size, i + 1);
	}
}

int main()
{
	int mas[] = { 1, 2, 3, 4, 5 };
	f(mas, 5);
	system("pause");
	return 0;
}