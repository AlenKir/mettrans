#include <iostream>
using namespace std;
//вывод правил
//нормальный вывод результата из яка

#define K 'k'
#define M 'm'
#define N 'n'

#define SLAG 'k', 'n', 'm'

#define PLUS '+'
#define MULT '*'
#define END '$' //нужно?

#define ERROR -1

char c;

int amount;

//это вообще так?
int mas[10][3];

int yylex()
{
	cin >> c; //считываем символ
	switch (c)
	{
	case 'k':
	{
		return K;
	}
	case 'm':
	{
		return M;
	}
	case 'n':
	{
		return N;
	}
	case '*':
	{
		return MULT;
	}
	case '+':
	{
		return PLUS;
	}
	case '$':
	{
		return END;
	}
	case '\n':
	{
		return END;
	}
	default:
	{
		return ERROR;
	}
	break;
	}
}

void change(int syn)
{
	if (syn == K)
		mas[amount][0] = mas[amount][0] + 1;
	if (syn == M)
		mas[amount][1] = mas[amount][1] + 1;
	if (syn == N)
		mas[amount][2] = mas[amount][2] + 1;
}

int F(int inh)
{
	int syn;
	if (c == K || c == M || c == N)
	{
		cout << "F::=" << c << endl;
		syn = c;
		if (c == K)
			syn = K;
		if (c == M)
			syn = M;
		if (c == N)
			syn = N;
		return syn;
	}
	else
		return ERROR;
}

int X(int inh)
{
	int syn = 0, syn1 = 0, syn2 = 0;
	if (c != END)
		c = yylex();
	if (c == MULT)
	{
		cout << "X::=*FX;" << endl;
		c = yylex(); //!!!
		syn1 = F(inh);
		syn2 = X(inh); //вычисление данного множителя рекурсивно
		change(syn1);
		change(syn2);
		syn = 0;
	}
	else if (c == PLUS || c == END)
	{
		cout << "X::=_;" << endl;
		syn = 0;
	}
	else
		return ERROR;
	return syn;
}

int T(int inh)
{
	int syn = 0, syn1 = 0, syn2 = 0;
	cout << "T::=FX;" << endl;
	syn1 = F(inh);
	syn2 = X(inh);
	change(syn1);
	change(syn2);
	syn = 0;
	return syn;
}

int Z(int inh)
{
	int syn = 0, syn1 = 0, syn2 = 0;
	if (c != END)
		c = yylex();
	if (c == END)
	{
		cout << "Z::=_;" << endl;
		return 0; //Z()?
	}
	else if (c == K || c == M || c == N)
	{
		cout << "Z::=+TZ;" << endl;
		amount++;
		syn1 = T(inh);
		syn2 = Z(inh);
		change(syn1);
		change(syn2);
		syn = 0;
	}
	else
		syn = ERROR;
	return syn;
}

int E(int inh)
{
	cout << "E::=TZ;" << endl;
	int syn, syn1, syn2;
	syn1 = T(inh);
	syn2 = Z(inh);
	change(syn1);
	change(syn2);
	syn = 0;
	return syn;
}

int S(int inh)
{
	int syn;
	if (c == K || c == M || c == N)
	{
		cout << "S::=E;" << endl;
		syn = E(inh);
		return syn; // S_syn = E_syn
	}
	else
		return ERROR;
}

int main()
{
	amount = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 3; ++j)
			mas[i][j] = 0;
	}
	c = yylex();
	int syn = S(0); //ERROR

	if (syn == ERROR)
	{
		cout << "Wrong string!" << endl;
		system("pause");
		return 0;
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 3; ++j)
			cout << mas[i][j] << " ";
		cout << endl;
	}
	int minK = 100, minM = 100, minN = 100;
	for (int i = 0; i < amount + 1; i++)
	{
		if (mas[i][0] < minK)
			minK = mas[i][0];
		if (mas[i][1] < minM)
			minM = mas[i][1];
		if (mas[i][2] < minN)
			minN = mas[i][2];
	}
	printf("\n minK=%d", minK);
	printf("\n minM=%d", minM);
	printf("\n minN=%d", +minN);

	printf("\n");

	for (int j = 0; j < minK; j++)
		printf("k");
	for (int j = 0; j < minM; j++)
		printf("m");
	for (int j = 0; j < minN; j++)
		printf("n");

	printf("(");
	for (int i = 0; i < amount + 1; i++)
	{
		for (int j = 0; j < mas[i][0] - minK; j++)
			printf("k");

		for (int j = 0; j < mas[i][1] - minM; j++)
		{
			printf("m");
		}

		for (int j = 0; j < mas[i][2] - minN; j++)
			printf("n");

		if ((mas[i][0] - minK == 0) && (mas[i][1] - minM == 0) && (mas[i][2] - minN == 0))
			printf("1");

		if (i != amount)
			printf("+");
	}
	printf(")");

	system("pause");
	return 0;
}