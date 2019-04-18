#include<iostream>
#include<stack>
#include<map>
#include<string>
#include<windows.h>
using namespace std;

//#define 

stack<char> sta;	/*变量声明*/
map<char, map<char, string> > M;
map<char, map<char, string> > m;
string input;
int ip;
char X;

void error(int i)
{
	cout << "error_" << i << endl;
    cout << "**********************************" << endl;
	system("pause");
	exit(0);
}
void M_value()		/*使用A代替E'、B代替T’、e代替ε*/
{
	M['E']['i'] = "E -> TA";
	M['E']['+'] = "error";
	M['E']['*'] = "error";
	M['E']['('] = "E -> TA";
	M['E'][')'] = "synch";
	M['E']['$'] = "synch";
	M['A']['i'] = "error";
	M['A']['+'] = "A -> +TA";
	M['A']['*'] = "error";
	M['A']['('] = "error";
	M['A'][')'] = "A -> e";
	M['A']['$'] = "A -> e";
	M['T']['i'] = "T -> FB";
	M['T']['+'] = "synch";
	M['T']['*'] = "error";
	M['T']['('] = "T -> FB";
	M['T'][')'] = "synch";
	M['T']['$'] = "synch";
	M['B']['i'] = "error";
	M['B']['+'] = "B -> e";
	M['B']['*'] = "B -> *FB";
	M['B']['('] = "error";
	M['B'][')'] = "B -> e";
	M['B']['$'] = "B -> e";
	M['F']['i'] = "F -> id";
	M['F']['+'] = "synch";
	M['F']['*'] = "synch";
	M['F']['('] = "F -> (E)";
	M['F'][')'] = "synch";
	M['F']['$'] = "synch";
}
void m_value()
{
	m['E']['i'] = "E -> TE'";
	m['E']['+'] = "skip input[ip], missing op!";
	m['E']['*'] = "skip input[ip], missing op!";
	m['E']['('] = "E -> TE'";
	m['E'][')'] = "synch";
	m['E']['$'] = "synch";
	m['A']['i'] = "skip input[ip], missing op!";
	m['A']['+'] = "E' -> +TE'";
	m['A']['*'] = "skip input[ip], missing op!";
	m['A']['('] = "skip input[ip], missing op!";
	m['A'][')'] = "E' -> ε";
	m['A']['$'] = "E' -> ε";
	m['T']['i'] = "T -> FT’";
	m['T']['+'] = "pop stack, missing id!";
	m['T']['*'] = "skip input[ip], missing op!";
	m['T']['('] = "T -> FT’";
	m['T'][')'] = "synch";
	m['T']['$'] = "synch";
	m['B']['i'] = "skip input[ip], missing op!";
	m['B']['+'] = "T’ -> ε";
	m['B']['*'] = "T’ -> *FT’";
	m['B']['('] = "skip input[ip], missing op!";
	m['B'][')'] = "T’ -> ε";
	m['B']['$'] = "T’ -> ε";
	m['F']['i'] = "F -> id";
	m['F']['+'] = "pop stack, missing id!";
	m['F']['*'] = "pop stack, missing id!";
	m['F']['('] = "F -> (E)";
	m['F'][')'] = "synch";
	m['F']['$'] = "synch";
}
void analy()
{
	while (X != '$')
	{
		if (X == input[ip])
		{
			sta.pop();
			if (input[ip] != 'i')
				ip++;
			else
				ip += 2;
		}
		else if ('i' == X || '*' == X || '+' == X || '(' == X || ')' == X)
		{
            cout << "missing '(' or ')'!" << endl;
            sta.pop();
        }
        else if(M[X][input[ip]] == "error")
        {
            cout << m[X][input[ip]] << endl;
            if (input[ip] != 'i')
				ip++;
			else
				ip += 2;
        }
		else if (M[X][input[ip]] == "synch") 
		{    
            cout << m[X][input[ip]] << endl;
            sta.pop();
        }
		else if (M[X][input[ip]] != "error" && M[X][input[ip]] != "synch")
		{
			cout << m[X][input[ip]] << endl;
			sta.pop();
			for (int i = M[X][input[ip]].length() - 1; i > 4; i--)
				if (M[X][input[ip]][i] != 'd' && M[X][input[ip]][i] != 'e')
					sta.push(M[X][input[ip]][i]);
		}
		X = sta.top();
	}
    //if(input[ip] != '$')
        //error(1);
}

int main()
{
    system("chcp 65001");
	sta.push('$');		/*初始化变量*/
	sta.push('E');
	ip = 0;
	X = sta.top();
	M_value();
	m_value();
    cout << "**********************************" << endl;
	cout << "INPUT string:" << endl;
	cin >> input;
    input[input.length()] = '$';
	cout << "OUTPUT:" << endl;
	analy();
    cout << "**********************************" << endl;
	system("pause");
	return 0;
}