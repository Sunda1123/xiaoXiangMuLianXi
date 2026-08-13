// milk_tea.cpp — 项目 A:奶茶店叫号系统 🧋
//
// 把你刚学透的 queue 用到真实场景里!
// 你现在是奶茶店店员,用一个"排队队列"管理顾客:
//
//   功能:
//   1. 取号      → 来顾客了,发一个号,排到队尾 完成
//   2. 叫号      → 队头的顾客来取奶茶,出队 
//   3. 看队伍    → 看看现在排到几号、还有几个人
//   4. 过号重排  → 叫号没人应,把这位"过号顾客"挪到队尾(约瑟夫的招!)
//   0. 下班      → 退出
//
// ============================================================
// 【先会用,再讲原理】queue 速查(复习,lesson8 刚学的)
// ============================================================
//   入队       q.push(x);     // x 到队伍最后
//   出队       q.pop();       // 队头离开
//   看队头     q.front();     // 队头是几号(只看不拿走)
//   空不空     q.empty();     // 空 → true
//   有几人     q.size();
//
// ============================================================
// 【新概念:引用 &】(C 语言没有,C++ 才有,今天就顺手学了)
// ============================================================
//   函数参数带 &,意思是"直接操作原来的变量",而不是复制一份。
//   比如:
//     void f(int& x) { x = 100; }   // 改的是原来的 x
//     void f(int  x) { x = 100; }   // 改的是拷贝,原 x 不变
//   我们这个项目要"真的改掉"排队队伍,所以给队伍和号码都用 &。
//   (只有"看队伍"那个函数用传值,为什么?——函数里有说明)

#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

// 打印菜单(这个已经写好,是"说明书",不用改)
void showMenu()
{
    cout << "========= Queue Number System =========" << endl;
    cout << "  1. get number" << endl;
    cout << "  2. call number" << endl;
    cout << "  3. show queue" << endl;
    cout << "  4. requeue" << endl;
    cout << "  0. go home" << endl;
    cout << "=================================" << endl;
}


void takeNumber(queue<int>& q, int& nextNumber)
{
    cout << "welcoming! your number is " << nextNumber << endl;
    q.push(nextNumber);
    nextNumber++;
   
}


void callNext(queue<int>& q)
{
    if (q.empty())
    {
        cout << "there is no one in the queue~" << '\n';
        return;
    }
    else{
        cout <<"the number " << q.front() << " customer,please go to the counter to get milk tea!" << '\n';
        q.pop();
    }
  
}


void showQueue(queue<int> q)
{
    if (q.empty())
    {
        cout << "the queue is empty~" << '\n';
        return;
    }
    else{
        cout << "the current queue is: ";
        while (!q.empty())
        {
            cout << q.front() << "号 ";
            q.pop();
        }
        cout << endl;
    }
  
}


void requeue(queue<int>& q)
{
    if (q.empty())
    {
        cout << "there is no one in the queue,what to requeue?" << '\n';
        return;
    }
    else{
        int man = q.front();
        q.pop();
        q.push(man);
        cout << "the number " << man << " customer is over the queue,has been requeued to the tail!" << '\n';
    }
   
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);   // 让控制台正确显示中文

    queue<int> q;        // 排队队伍(存的是号码)
    int nextNumber = 1;  // 下一个取的号,从 1 开始

    int choice;
    do
    {
        showMenu();
        cout << "请输入操作(0~4): ";
        cin >> choice;

        switch (choice)
        {
            case 1: takeNumber(q, nextNumber); break;   // 取号
            case 2: callNext(q); break;                 // 叫号
            case 3: showQueue(q); break;                // 看队伍
            case 4: requeue(q); break;                  // 过号重排
            case 0: cout << "it`s time to go home!" << endl; break;
            default: cout << "invalid option, please try again!" << endl; break;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}
