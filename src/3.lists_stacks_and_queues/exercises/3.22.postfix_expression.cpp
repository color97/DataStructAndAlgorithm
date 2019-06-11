#include <stack>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

double evaluate_postfix_expression()
{
    stack<double> items;
    string expression;
    getline(cin, expression);
    istringstream expStream(expression);
    while (!expStream.eof())
    {
        string token;
        expStream>>token;
        double item = atof(token.c_str());
        if (item != 0.0f)
        {
            items.push(item);
        }
        else if(token == "0.0")
        {
            items.push(0.0);
        }
        else 
        {
            switch (token[0])
            {
            case '+':
                {
                    double leftItem = items.top();
                    items.pop();
                    double rightItem = items.top();
                    items.pop();
                    items.push(leftItem + rightItem);
                }
                break;
            case '-':
                {
                    double leftItem = items.top();
                    items.pop();
                    double rightItem = items.top();
                    items.pop();
                    items.push(leftItem - rightItem);
                }
                break;
            case '*':
                {
                    double leftItem = items.top();
                    items.pop();
                    double rightItem = items.top();
                    items.pop();
                    items.push(leftItem * rightItem);
                }
                break;
            case '/':
                {
                    double leftItem = items.top();
                    items.pop();
                    double rightItem = items.top();
                    items.pop();
                    items.push(leftItem / rightItem);
                }
                break;
            
            default:
                break;
            }
        }
    }
    return items.top();
}

int main()
{
    double result = evaluate_postfix_expression();
    cout<<"result = "<<result<<endl;

    return 0;
}