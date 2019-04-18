/*题目：LR分析器
*文法：（1）E -> E+T    （2）E -> T     （3）T -> T*F
*     （4）T -> F      （5）F -> (E)   （6）F -> id
*作者：
*时间：2018.11.06
*版本：未知
*更新日志：错误例程
*/
#include<iostream>
#include<stack>
#include<map>
#include<string>
using namespace std;

string input;
int ip = 0;
stack<char> sta;
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
    production['6'] = "F -> id";
}
void action_value()
{
    //FIXME: 表中某些error条目可能存在填写问题

    action['0']['i'] = "s5";
    action['0']['('] = "s4";
    action['0']['+'] = "e1";
    action['0']['*'] = "e1";
    action['0']['$'] = "e1";
    action['0'][')'] = "e2";

    action['1']['+'] = "s6";
    action['1']['$'] = "acc";
    action['1']['i'] = "e3";
    action['1']['('] = "e3";
    action['1'][')'] = "e2"; 

    action['2']['+'] = "r2";
    action['2']['*'] = "s7";
    action['2'][')'] = "r2";
    action['2']['$'] = "r2";
    action['2']['i'] = "e3";
    action['2']['('] = "e3";

    action['3']['+'] = "r4";
    action['3']['*'] = "r4";
    action['3'][')'] = "r4";
    action['3']['$'] = "r4";
    action['3']['i'] = "e3";
    action['3']['('] = "e3";

    action['4']['i'] = "s5";
    action['4']['('] = "s4";
    action['4']['+'] = "e1";
    action['4']['*'] = "e1";
    action['4']['$'] = "e1";
    action['4'][')'] = "e2";

    action['5']['+'] = "r6";
    action['5']['*'] = "r6";
    action['5'][')'] = "r6";
    action['5']['$'] = "r6";
    action['5']['i'] = "e3";
    action['5']['('] = "e3";

    action['6']['i'] = "s5";
    action['6']['('] = "s4";
    action['6']['+'] = "e1";
    action['6']['*'] = "e1";
    action['6']['$'] = "e1";
    action['6'][')'] = "e2";

    action['7']['i'] = "s5";
    action['7']['('] = "s4";
    action['7']['+'] = "e1";
    action['7']['*'] = "e1";
    action['7']['$'] = "e1";
    action['7'][')'] = "e2";

    action['8']['+'] = "s6";
    action['8'][')'] = "sw";
    action['8']['i'] = "e3";
    action['8']['('] = "e3";
    action['8']['$'] = "e4";

    action['9']['+'] = "r1";
    action['9']['*'] = "s7";
    action['9'][')'] = "r1";
    action['9']['$'] = "r1";
    action['9']['i'] = "e3";
    action['9']['('] = "e3";

    action['q']['+'] = "r3";
    action['q']['*'] = "r3";
    action['q'][')'] = "r3";
    action['q']['$'] = "r3";
    action['q']['i'] = "e3";
    action['q']['('] = "e3";

    action['w']['+'] = "r5";
    action['w']['*'] = "r5";
    action['w'][')'] = "r5";
    action['w']['$'] = "r5";
    action['w']['i'] = "e3";
    action['w']['('] = "e3";
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
}

void init()
{
    production_value();
    action_value();
    goto_value();
}

void LR()
{
    char a, s;
    sta.push('0');
    while(1)
    {
        
        a = input[ip];
        s = sta.top();
        if('s' == action[s][a][0])  //shift t
        {
            sta.push(a);
            sta.push(action[s][a][1]);
            if (a != 'i')
				ip++;
			else
				ip += 2;
            cout << "shift" << endl;
        }
        else if('r' == action[s][a][0]) //reduce A->β
        {
            char c = action[s][a][1];
            //........pop 2*|β| times
            int num = 0;    
            if (c != '6')   // (6) F -> id
			{
                for(int i = production[c].length()-1; production[c][i] != ' '; i--)
                    num += 2;
                for(; num != 0; num--)
                    sta.pop();
            }
			else
            {
				sta.pop();
                sta.pop();
            }
            //..........
            char t = sta.top();
            char A = production[c][0];
            sta.push(A);
            sta.push(goto_[t][A]);
            cout << "reduce: " << production[c] << endl;
        }
        else if("acc" == action[s][a])  //accept
        {
            cout << "accept!" << endl;
            break;
        }
        else    //error recovery routines
        {
            /*短语级错误恢复：
            *发现错误时，分析器对剩余输入作局部纠正
            *FIXME: 该错误例程逻辑内蕴于action_table的错误条目中，因而其‘正确性’基于action_table的正确
            */
            switch(action[s][a][1])
            {
                case '1': 
                    cout << "error, missing arithmetic objects" << endl;
                    ip -= 2;
                    input[ip] = 'i';
                    input[ip+1] = 'd';
                    break;
                case '2':
                    cout << "error, non-paired right parentheses" <<endl;
                    ip++;
                    break;
                case '3':
                    cout << "error, missing operator" << endl;
                    ip--;
                    input[ip] = '+';
                    break;
                case '4':
                    cout << "error, missing right parentheses" << endl;
                    ip--;
                    input[ip] = ')';
                    break;
                default:
                    cout << "error, undefined tokens" << endl;
                    ip++;
                    break;
                    //exit(0);
            }

            
            /*紧急方式的错误恢复：
            *从栈顶开始退栈，直至出现状态s，它有预先确定的非终结符A的转移；
            *然后抛弃若干个输入符号，直至找到符号a，它能合法的跟随A；    follow(A)
            *分析器再把A和状态goto[s,A]压进栈，恢复正常分析。
            */      
            /*FIXME: ???
            while('0' != sta.top() && '4' != sta.top()
                    && '6' != sta.top() && '7' != sta.top() )
                sta.pop();
            s = sta.top();
            while(input[ip] != '*' && input[ip] != '+' 
                    && input[ip] != ')' && input[ip] != '$')
                ip++;
            sta.push('F');
            sta.push(goto_[s]['F']);*/
        }
    }
}

int main()
{
    init();
    cout << "input the string:" << endl;
    cin >> input;
    cout << "**************************" << endl;
    input[input.length()] = '$';
    LR();
    cout << "**************************" << endl;
    return 0;
}