#include <bits/stdc++.h>
using namespace std;
class calc
{
public:
    int Add(int a, int b) { return a + b; }
    double Add(double a, double b) { return a + b; }
    int Sub(int a, int b) { return a - b; }
    double Sub(double a, double b) { return a - b; }
    int Multi(int a, int b) { return a * b; }
    double Multi(double a, double b) { return a * b; }
    int Div(int a, int b) { return a / b; }
    double Div(double a, double b) { return a / b; }
};
int main()
{
    //  printf("Enter the operation you want to do\n(+ For
    // addition,- For Subtraction,* For Multiplication and / for
    // division): ");
    calc *ob = new calc();
    char op;
    cin >> op;
    printf("Enter first Value for The Operation: ");
    double a, b;
    cin >> a;
    printf("Enter second Value for The Operation: ");
    cin >> b;
    if (b != 0 || op != '/')

    {
        cout << "The Answer After the operation is: ";
        if (op == '+')

        {
            cout << ob->Add(a, b) << endl;
        }
        else if (op == '-')

        {
            cout << ob->Sub(a, b) << endl;
        }
        else if (op == '*')

        {
            cout << ob->Multi(a, b) << endl;
        }
        else if (op == '/')
            cout << ob->Div(a, b) << endl;
    }
    else
        cout << "Operation is not Possible.\n";
    return 0;
}