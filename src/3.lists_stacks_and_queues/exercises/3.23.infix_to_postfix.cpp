#include <stack>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

void infix_to_postfix()
{
    stack<char> symbols;
    string expression;
    getline(cin, expression);
    istringstream expStream(expression);
    while (!expStream.eof())
    {
        char token;
        expStream>>token;
        if (token >= 'a' && token <= 'z')
        {
            cout<<token<<" ";
        }
        else 
        {
            int symbolPriority = 0;
            switch (token)
            {
            case ')':
                while (!symbols.empty() && symbols.top() != '(')
                {
                    cout<<symbols.top()<<" ";
                    symbols.pop(); 
                }
                // pop up '('
                symbols.pop();
                break;
            case '(':
                symbols.push(token);
                break;
            case '^':
                while (!symbols.empty() && !(symbols.top() == '^' || symbols.top() == '('))
                {
                    cout<<symbols.top()<<" ";
                    symbols.pop(); 
                }
                symbols.push(token);
                break;
            case '*':
            case '/':
                while (!symbols.empty() && 
                !(symbols.top() == '+' || symbols.top() == '-' || symbols.top() == '(' ))
                {
                    cout<<symbols.top()<<" ";
                    symbols.pop(); 
                }
                symbols.push(token);
                break; 
            case '+':
            case '-':
                while (!symbols.empty() && !symbols.top() == '(')
                {
                    cout<<symbols.top()<<" ";
                    symbols.pop(); 
                }
                symbols.push(token);
                break;
            default:
                break;
            }            
        }
    }

    while (!symbols.empty() )
    {
        cout<<symbols.top()<<" ";
        symbols.pop();
    }
    cout<<endl;
}

int main()
{
    infix_to_postfix();
    
    return 0;
}