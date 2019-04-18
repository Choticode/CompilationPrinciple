/*题目： S属性的语法制导定义,基于LR分析器
*文法：（1）E -> E+T    （2）E -> T     （3）T -> T*F
*     （4）T -> F      （5）F -> (E)   （6）F -> id
*     （7）E -> E-T    （8）T -> T/F
*作者：丶
*时间：2018.11.15
*版本：未知
*更新日志：
*/
#include<iostream>
#include<stack>
#include<map>
#include<string>
#include<sstream>
//#include<regex>
using namespace std;

//#define debug

string input;
int ip = 0;
stack<char> sta;
stack<double> sta_num;
double num;
map<char,string> production; 
map<char,map<char,string> > action;  //action table
map<char,map<char,char> > goto_; //goto table

void production_value()
{
    production['1'] = "E -> E+T";
    production['2'] = "E -> T";
    production['3'] = "T -> T*F";
    production['4'] = "T -> F";
    production['5'] = "F -> (E)";
    production['6'] = "F -> i";
    production['7'] = "E -> E-T";//
    production['8'] = "T -> T/F";//
}
void action_value()
{
    /*
    action['0']['0'] = "s5";
    action['4']['0'] = "s5";
    action['6']['0'] = "s5";
    action['7']['0'] = "s5";
    action['e']['0'] = "s5";//
    action['t']['0'] = "s5";//
    action['0']['1'] = "s5";
    action['4']['1'] = "s5";
    action['6']['1'] = "s5";
    action['7']['1'] = "s5";
    action['e']['1'] = "s5";//
    action['t']['1'] = "s5";//
    action['0']['2'] = "s5";
    action['4']['2'] = "s5";
    action['6']['2'] = "s5";
    action['7']['2'] = "s5";
    action['e']['2'] = "s5";//
    action['t']['2'] = "s5";//
    action['0']['3'] = "s5";
    action['4']['3'] = "s5";
    action['6']['3'] = "s5";
    action['7']['3'] = "s5";
    action['e']['3'] = "s5";//
    action['t']['3'] = "s5";//
    action['0']['4'] = "s5";
    action['4']['4'] = "s5";
    action['6']['4'] = "s5";
    action['7']['4'] = "s5";
    action['e']['4'] = "s5";//
    action['t']['4'] = "s5";//
    action['0']['5'] = "s5";
    action['4']['5'] = "s5";
    action['6']['5'] = "s5";
    action['7']['5'] = "s5";
    action['e']['5'] = "s5";//
    action['t']['5'] = "s5";//
    action['0']['6'] = "s5";
    action['4']['6'] = "s5";
    action['6']['6'] = "s5";
    action['7']['6'] = "s5";
    action['e']['6'] = "s5";//
    action['t']['6'] = "s5";//
    action['0']['7'] = "s5";
    action['4']['7'] = "s5";
    action['6']['7'] = "s5";
    action['7']['7'] = "s5";
    action['e']['7'] = "s5";//
    action['t']['7'] = "s5";//
    action['0']['8'] = "s5";
    action['4']['8'] = "s5";
    action['6']['8'] = "s5";
    action['7']['8'] = "s5";
    action['e']['8'] = "s5";//
    action['t']['8'] = "s5";//
    action['0']['9'] = "s5";
    action['4']['9'] = "s5";
    action['6']['9'] = "s5";
    action['7']['9'] = "s5";
    action['e']['9'] = "s5";//
    action['t']['9'] = "s5";//
    */

    action['0']['i'] = "s5";/**/
    action['0']['('] = "s4";

    action['1']['+'] = "s6";
    action['1']['$'] = "acc";
    action['1']['-'] = "se";//

    action['2']['+'] = "r2";
    action['2']['*'] = "s7";
    action['2'][')'] = "r2";
    action['2']['$'] = "r2";
    action['2']['/'] = "st";//
    action['2']['-'] = "r2";//

    action['3']['+'] = "r4";
    action['3']['*'] = "r4";
    action['3'][')'] = "r4";
    action['3']['$'] = "r4";
    action['3']['-'] = "r4";//
    action['3']['/'] = "r4";//

    action['4']['i'] = "s5";/**/
    action['4']['('] = "s4";

    action['5']['+'] = "r6";
    action['5']['*'] = "r6";
    action['5'][')'] = "r6";
    action['5']['$'] = "r6";
    action['5']['-'] = "r6";//
    action['5']['/'] = "r6";//

    action['6']['i'] = "s5";/**/
    action['6']['('] = "s4";

    action['7']['i'] = "s5";/**/
    action['7']['('] = "s4";

    action['8']['+'] = "s6";
    action['8'][')'] = "sw";
    action['8']['-'] = "se";//

    action['9']['+'] = "r1";
    action['9']['*'] = "s7";
    action['9'][')'] = "r1";
    action['9']['$'] = "r1";
    action['9']['/'] = "st";//
    action['9']['-'] = "r1";//

    action['q']['+'] = "r3";
    action['q']['*'] = "r3";
    action['q'][')'] = "r3";
    action['q']['$'] = "r3";
    action['q']['-'] = "r3";//
    action['q']['/'] = "r3";//

    action['w']['+'] = "r5";
    action['w']['*'] = "r5";
    action['w'][')'] = "r5";
    action['w']['$'] = "r5";
    action['w']['-'] = "r5";//
    action['w']['/'] = "r5";//

    action['e']['i'] = "s5";/**/
    action['e']['('] = "s4";//

    action['r']['/'] = "st";//
    action['r']['*'] = "s7";//
    action['r']['+'] = "r7";//
    action['r']['-'] = "r7";//
    action['r'][')'] = "r7";//
    action['r']['$'] = "r7";//

    action['t']['i'] = "s5";/**/
    action['t']['('] = "s4";//

    action['y']['+'] = "r8";//
    action['y']['*'] = "r8";//
    action['y'][')'] = "r8";//
    action['y']['$'] = "r8";//
    action['y']['-'] = "r8";//
    action['y']['/'] = "r8";//
}
void goto_value()
{
    goto_['0']['E'] = '1';
    goto_['0']['T'] = '2';
    goto_['0']['F'] = '3';

    goto_['4']['E'] = '8';
    goto_['4']['T'] = '2';
    goto_['4']['F'] = '3';

    goto_['6']['T'] = '9';
    goto_['6']['F'] = '3';

    goto_['7']['F'] = 'q';

    goto_['e']['T'] = 'r';//
    goto_['e']['F'] = '3';//

    goto_['t']['F'] = 'y';//
}

void init()
{
    production_value();
    action_value();
    goto_value();
}

void yylex()
{
    char digit[256];
	int temp = 0;
    //while (' ' == input[ip])    ip++;   //FIXME: how to skip space?
	while (input[ip] >= '0' && input[ip] <= '9' || '.' == input[ip])
		digit[temp++] = input[ip++];
	if (temp > 0)
    {
		sscanf(digit, "%lf", &num);  //char[]->double buffer: digit->num
        sta_num.push(num);
        #ifdef debug
            cout << "debug: " << sta_num.top() << endl;
        #endif
    }
    else
    {
        sta_num.push(input[ip]);    //no practical significance, just for ...
        ip++;
    }
}
void calcu(int n, char c)
{
    double a, b;
    switch(c)
    {
        case '1':    //reduce:E -> E+T
            a = sta_num.top();
            sta_num.pop();
            sta_num.pop();
            b = sta_num.top();
            sta_num.pop();
            sta_num.push(a + b);
            break;
        case '7':    //reduce:E -> E-T
            a = sta_num.top();
            sta_num.pop();
            sta_num.pop();
            b = sta_num.top();
            sta_num.pop();
            sta_num.push(b - a);
            break;
        case '3':  //reduce:T -> T*F
            a = sta_num.top();
            sta_num.pop();
            sta_num.pop();
            b = sta_num.top();
            sta_num.pop();
            sta_num.push(a * b);
            break;
        case '8':    //reduce:E -> E/T
            a = sta_num.top();
            sta_num.pop();
            sta_num.pop();
            b = sta_num.top();
            sta_num.pop();
            sta_num.push(b / a);
            break;
        case '5':  //reduce:F -> (E)
            sta_num.pop();
            a = sta_num.top();
            sta_num.pop();
            sta_num.pop();
            sta_num.push(a);
            break;
        default:    //others
            break;
    }
}

void LR()
{
    char a, s;
    sta.push('0');
    while(1)
    {
        a = input[ip];
        if ('0' <= a && '9' >= a)
            a = 'i';
        s = sta.top();
        if('s' == action[s][a][0])  //shift t
        {
            sta.push(a);
            sta.push(action[s][a][1]);
            yylex();
        }
        else if('r' == action[s][a][0]) //reduce A->β
        {
            char c = action[s][a][1];
            //........pop 2*|β| times
            int num = 0;
            for(int i = production[c].length()-1; production[c][i] != ' '; i--)
                num += 2;
            calcu(num,c);
            for(; num != 0; num--)
                sta.pop();
            //..........
            char t = sta.top();
            char A = production[c][0];
            sta.push(A);
            sta.push(goto_[t][A]);
        }
        else if("acc" == action[s][a])  //accept
        {
            cout << "Answer: " << sta_num.top() << endl;
            break;
        }
        else    //error routines
        {
            cout << "error, please input again!" << endl;
            cout << "**************************" << endl;
            exit(0);
        }
    }
}

int main()
{
    init();
    cout << "*******************************************************" << endl;
    cout << "arithmetic expression:";
    cin >> input;
    input[input.length()] = '$';
    LR();
    cout << "*******************************************************" << endl;
    return 0;
}