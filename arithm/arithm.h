#ifndef __ARITHM_H__
#define __ARITHM_H__

#include "tlist.h"
#include <iostream>
#include <string>

using namespace std;

// type:
// '('=1 , ')'=2 , '+'=3 , '-'=4 , '*'=5 , '/'=6
// �����=0 , ����������='��� ����������', ��� a<'��� ����������'<z
struct Lexeme
{
	char type; // ��� ��������
	double data; // ��������, ���� �����
};

struct Variable
{
	bool name; // ���� ���� �� ���������� � ������ var[i]
	double data; // ��� ����� �� ��������
};

class Arithm
{
protected:
	string Str;
	TList<Lexeme> Lex, Pol;
	Variable var[27];
public:
	Arithm();
	~Arithm();

	void Enter(string strin);	// ���� ������
	bool Translate();			// ����������� �� �������
	double Compute();			// ���������� ���������
};

Arithm::Arithm() 
{
	for(int i=0;i<27;i++) var[i].name=false;
}
Arithm::~Arithm() {}

void Arithm::Enter(string inps)
{
	Str=inps;
}

bool Arithm::Translate()
{
	int i=0; // ������ ������������ �������
	int state=0; // ��������� �������� ��� ������
	int k=0; // ���-�� ����� ������ - ���-�� ������ ������
	Lexeme num;
	char c=Str[0];
	while((i<Str.size())&&(state!=2))
	{
		if(state==0)	// �������� ���� ������ ��� ������ �����
		{
			if(c=='(')
			{
				num.type=1;
				Lex.Put(num);
				k++;
				if(i<Str.size()-1) c=Str[++i]; // ���������� ���������� ��������
			}
			else
				if(c=='-') // ������ �������������� �����
				{
					i++;
					if(i<Str.size()) c=Str[i];
					if((c>='0')&&(c<='9'))
					{
						num.type=0;
						num.data=-(c-48);
						i++;
						while (i<Str.size())
						{
							c=Str[i]; 
							if((Str[i]>='0')&&(Str[i]<='9')) // ���������� �����
							{
								num.data*=10;
								num.data+=c-48;
								i++;
							}
							else break;
						}
						Lex.Put(num);
						state=1;
					}
					else
					if(c=='(')
					{
						num.type=0;
						num.data=0;
						Lex.Put(num);
						num.type=4;
						Lex.Put(num);
					}
					else state=2;
				} // ��������� ������������� �����
				else
					if(c=='+') // ������� ������������� ����� � +
					{
						i++;
						if(i<Str.size()) c=Str[i];
						if((c>='0')&&(c<='9'))
						{
							num.type=0;
							num.data=c-48;
							i++;
							while (i<Str.size())
							{
								c=Str[i]; 
								if((Str[i]>='0')&&(Str[i]<='9')) // ���������� �����
								{
									num.data*=10;
									num.data+=c-48;
									i++;
								}
								else break;
							}
							Lex.Put(num);
							state=1;
						}
						else state=2;
					} // ��������� ������������� ����� � +
					else
						if((c>='0')&&(c<='9')) // ������� ������������� �����
						{
							num.type=0;
							num.data=c-48;
							i++;
							while(i<Str.size())
							{
								c=Str[i]; 
								if((Str[i]>='0')&&(Str[i]<='9')) // ���������� �����
								{
									num.data*=10;
									num.data+=c-48;
									i++;
								}
								else break;
							}
							Lex.Put(num);
							state=1;
						} // ��������� ������������� �����
						else
						if((c>='a')||(c<='z')) // ���������� ����������
						{
							num.type=c;
							Lex.Put(num);
							i++;
							if(i<Str.size()) c=Str[i];
							state=1;
						}
						else state=2;
		}
		else
			if(state==1) // �������� ���� ������ ��� ��������
			{
				if(c==')')
				{
					if(k>0)
					{
						k--;
						num.type=2;
						Lex.Put(num);
						i++;
						if(i<Str.size()) c=Str[i];
					}
					else state=2;
				}
				else
					if((c=='+')||(c=='-')||(c=='*')||(c=='/'))
					{
						switch(c){
						case '+':
							num.type=3; break;
						case '-':
							num.type=4; break;
						case '*':
							num.type=5; break;
						case '/':
							num.type=6; break;
						}				
						state=0;
						i++;
						Lex.Put(num);
						if(i<Str.size()) c=Str[i];
					}
					else state=2;
			}

	}
	
	return (k==0 && state!=2); // ���������� ��� �� ������
}

double Arithm::Compute()
{
	Lexeme temp;
	if(Translate())
	{
		TStack<Lexeme> op;
		while(!Lex.IsEmpty())
		{
			temp=Lex.Get();
			if(temp.type==0) Pol.Put(temp); // ���� �����
			else
				if((temp.type>='a')&&(temp.type<='z')) // ���� ����������
				{
					var[temp.type-97].name=true;
					Pol.Put(temp);
				}
				else
				if(temp.type==1) op.Push(temp); // ���� ������������� ������
				else
					if(temp.type==2) // ���� ������������� ������
					{
						while(op.Top().type!=1) Pol.Put(op.Pop());
						op.Pop();
					}
					else  // ���� ��������
					{
						while(!op.IsEmpty() &&(op.Top().type>=temp.type))
						{
							Pol.Put(op.Pop());
						}
						op.Push(temp);
					}
		}
		while(!op.IsEmpty()) // ���������� ��������
		{
			Pol.Put(op.Pop());
		}
	}
	else throw "not correct";

	
	for(int i=0;i<27;i++) // �������������� ����������
	if(var[i].name)
	{
		char c='a'+i;
		cout<<"Enter "<<c<<'\n';
		
		cin>>var[i].data;
	}

	TStack<double> exe;
	while(!Pol.IsEmpty()) // ����������
	{
		double a,b;
		temp=Pol.Get();
		if(temp.type==0) exe.Push(temp.data); // ���� �����
		else
			if((temp.type>='a')&&(temp.type<='z')) exe.Push(var[temp.type-97].data); // ���� ����������
		else // ���� ��������
		{
			b=exe.Pop();
			a=exe.Pop();
			switch(temp.type)
			{
			case 3:
				{
					exe.Push(a+b);
				}
				break;
			case 4:
				{
					exe.Push(a-b);
				}
				break;
			case 5:
				{
					exe.Push(a*b);
				}
				break;
			case 6:
				{
					exe.Push(a/b);
				}
				break;
			}
		}
	}

	return exe.Pop();
}

double ArithmCompute(string str)
{
	Arithm A;
	A.Enter(str);
	return A.Compute();
}

#endif