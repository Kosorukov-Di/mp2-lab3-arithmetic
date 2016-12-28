#include <arithm.h>
#include <conio.h>


void main()
{
	string str;
	cout<<"¬ведите выражение\n";
	cin>>str;
	cout<<'='<<ArithmCompute(str)<<'\n';

	_getch();
}