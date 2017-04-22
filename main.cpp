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

#define ERROR 0

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

int F(int inh)
{
	int syn;
	if (c == K || c == M || c == N)
	{
		cout << "F::=" <<  c << endl;
		syn = c;
		if (c == K)
			mas[amount][0]++;
		if (c == M)
			mas[amount][1]++;
		if (c == N)
			mas[amount][2]++;
		return syn;
	}
	else
		return ERROR;
}

int T(int inh)
{
	int syn;
	if (c == K || c == M || c == N)
	{
		cout << "T::=F" << endl;
		syn = F(inh);
		return syn;
	}
	else
		return ERROR;

	//int synthesized;
	//switch (symbol)
	//{
	//case AP_left_KW: {if ((synthesized = A(inherited)) == -1) //Y ::= { Ai = Y i } A )
	//	return -1;
	//				 else if (symbol == AP_right_KW)
	//					 return synthesized; //{Ys = As }
	//				 else return -1; }
	//case AP_right_KW: {symbol = yylex();//Y ::= )
	//	return inherited; }// { Ys = Yi }
	//default: return -1;
	//}
}

int E(int inh)
{
	int syn;
	if (c == K || c == M || c == N)
	{
		cout << "E::=T" << endl;
		syn = T(inh);		
		c = yylex();
		if (c == END)
			return syn; // E_syn = T_syn
	}
	else if (c == PLUS)
	{
		amount++;
		c = yylex();
		syn = T(inh);
	}
	else
		return ERROR;
	//int T(int inherited)
	//{
	//	symbol = yylex();
	//	return Y(inherited + 1);// T ::= ( { Yi = Ti + 1 } Y { Ts = Ys }
	//}
}

int S(int inh)
{
	if (c == K || c == M || c == N)
	{
		cout << "S::=E" << endl;
		int syn = E(inh);
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
	int minK = 0, minM = 0, minN = 0;
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