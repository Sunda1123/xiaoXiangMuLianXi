#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

class Fraction {
public:
    int up;    // 分子
    int down;  // 分母

    Fraction() : up(0), down(1) { normalize(); }           // 默认构造：0/1
    Fraction(int u) : up(u), down(1) { normalize(); }      // 单参构造：整数当分子
    Fraction(int u, int d) : up(u), down(d) {
        normalize();
    }
private:
    int gcd(int a,int b){
        return b==0?abs(a) : gcd(b,a%b);
    }

    void normalize(){
        if(down==0){
            throw invalid_argument("分母不能为0");
        }
        else if(down<0){
            up = -up;
            down = -down;
        }

        int g =gcd(up,down);
        up /= g;
        down /= g;
    }
public:
    bool operator==(const Fraction& other) {
        return up * other.down == other.up * down;
    }

    Fraction operator+(const Fraction& other) {
      
        int newUp = up * other.down + other.up * down;
        int newDown = down * other.down;
        return Fraction(newUp, newDown);
    }
    Fraction operator-(const Fraction& other) {
      
        int newUp = up * other.down - other.up * down;
        int newDown = down * other.down;
        return Fraction(newUp, newDown);
    }
    Fraction operator*(const Fraction& other) {
     
        int newUp = up* other.up;
        int newDown = down * other.down;
        return Fraction(newUp, newDown);
    }
        Fraction operator/(const Fraction& other) {
        
        int newUp =up * other.down;
        int newDown = down * other.up;
        return Fraction(newUp, newDown);
    }
    friend ostream& operator<<(ostream& os, const Fraction& f) {
        if(f.down == 1)
        {
            os << f.up;
        }
        else{
        os << f.up << "/" << f.down;
        }   
        return os;  
    };
};

template<typename T>
T apply(T a,T b,char op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return T(); 
}

int priority(char op)
{
    if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
   return 0;
}

template<typename T>
T calculate(string s)
{
    stack<T> nums;    // 数字栈
    stack<char> ops;    // 符号栈

    int i = 0;
    while (i < s.length())
    {
        char c = s[i];

        if (c == ' ')
        {
            i++;
            continue;
        }
        else if (isdigit(c))
        {
            int num = 0;
            while (i < s.length() && isdigit(s[i]))
            {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            nums.push(T(num));
        }
        else                    // 是运算符或括号 ( ) [ ] { }
        {
            if (c == '(' || c == '[' || c == '{')   // 任意左括号,直接压栈
            {
                ops.push(c);
                i++;
            }
            else if (c == ')' || c == ']' || c == '}')   // 任意右括号:弹栈算到对应的左括号
            {
                char left;                    // 先找出右括号对应的左括号
                if (c == ')') left = '(';
                else if (c == ']') left = '[';
                else if (c == '}') left = '{';             
                while (!ops.empty() && ops.top() != left)   // 一直算到左括号
                {
                    T b = nums.top(); nums.pop();
                    T a = nums.top(); nums.pop();
                    char op = ops.top(); ops.pop();
                    nums.push(apply(a, b, op));
                }
                ops.pop();   // 弹出左括号
                i++;
            }
            else                 // + - * / 普通运算符:优先级循环
            {
            if (c == '-' && (i == 0 || s[i-1] == '(' || s[i-1] == '[' || s[i-1] == '{' || s[i-1] == '+' || s[i-1] == '-' || s[i-1] == '*' || s[i-1] == '/'))
                {
                    i++;
                    int num = 0;
                    while(i < s.length() && isdigit(s[i]))
                    {
                        num = num *10 + (s[i] - '0');
                        i++;
                    }
                    nums.push(T(-num));
                    continue;
                }
                while (!ops.empty() && priority(ops.top()) >= priority(c))
                {
                    T b = nums.top(); nums.pop();
                    T a = nums.top(); nums.pop();
                    char op = ops.top(); ops.pop();
                    nums.push(apply(a, b, op));
                }
                ops.push(c);     // 当前符号压栈
                i++;
            }
        }
    }
    while (!ops.empty())   // 扫描完,清空符号栈算完
    {
        T b = nums.top(); nums.pop();
        T a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        nums.push(apply(a, b, op));
    }

    return nums.top();   // 数字栈顶 = 最终答案
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "模板计算器(int / Fraction)输入 q 退出" << endl;

    string expr;
    while (true) {
        cout << ">>> ";
        getline(cin, expr);
        if (expr == "q") break;
        cout << "[double]   = " << calculate<double>(expr) << endl;
        cout << "[int]      = " << calculate<int>(expr) << endl;
        cout << "[Fraction] = " << calculate<Fraction>(expr) << endl;
    }
}