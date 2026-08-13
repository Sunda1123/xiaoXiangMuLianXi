#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

/* ================= 选择场景类 ================= */
class ChoiceScene
    {
    public:
        // 从当前文件流中解析选项
        void parse(ifstream& fin)
        {
            options.clear();   // 防止重复添加
            string opt;
        const string prefix = "【选项】";

        while (getline(fin, opt) && opt.find(prefix) == 0)
        {
            options.push_back(opt.substr(prefix.length()));
        }
    }

    // 展示选项并获取玩家选择
    int show() const
    {
        cout << endl << "请选择：" << endl;
        for (int i = 0; i < options.size(); ++i)
        {
            cout << i + 1 << ". " << options[i] << endl;
        }

        int choice;
        cin >> choice;
        return choice;
    }

    // 获取选项内容
    string getOption(int index) const
    {
        if (index >= 1 && index <= options.size())
            return options[index - 1];
        return "无效选项";
    }

    bool empty() const
    {
        return options.empty();
    }

private:
    vector<string> options;
};

/* ================= main ================= */
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ifstream fin("script.txt");
    if (!fin)
    {
        cout << "无法打开 script.txt" << endl;
        return 1;
    }

    string line;
    ChoiceScene choice;

    while (getline(fin, line))
    {
        if (line == "【选择】")
        {
            choice.parse(fin);   // 解析选项
            int c = choice.show(); // 展示并选择
            cout << "你选择了：" << choice.getOption(c) << endl;
            _getch();
            continue;
        }

        cout << line << endl;
        _getch();
    }

    fin.close();
    return 0;
}