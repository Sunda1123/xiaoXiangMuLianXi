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
    // 从剧本数组解析选项（i 指向【选择】的下一行）
    void parse(const vector<string>& lines, int& i)
    {
        options.clear();
        targets.clear();
        const string prefix = "【选项】";

        while (i < (int)lines.size() && lines[i].find(prefix) == 0)
        {
            string opt = lines[i].substr(prefix.length());
            auto p = opt.find("→");
            if (p != string::npos)
            {
                options.push_back(opt.substr(0, p));
                targets.push_back(opt.substr(p + 3));   // "→"是 UTF-8 3字节，跳过整个箭头
            }
            i++;
        }
    }

    int show() const
    {
        cout << endl << "请选择：" << endl;
        for (int i = 0; i < options.size(); ++i)
        {
            cout << i + 1 << ". " << options[i] << endl;
        }
        int choice;
        cin >> choice;
        cin.ignore();   // 清掉输入数字后残留的回车
        return choice;
    }

    string getOption(int index) const
    {
        if (index >= 1 && index <= options.size())
            return options[index - 1];
        return "无效选项";
    }

    string getTarget(int index) const
    {
        if (index >= 1 && index <= targets.size())
            return targets[index - 1];
        return "";
    }

    bool empty() const
    {
        return options.empty();
    }

private:
    vector<string> options;
    vector<string> targets;
};

/* ================= main ================= */
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ifstream fin("script.txt");   // 正式版：读仙侠剧本
    if (!fin)
    {
        cout << "无法打开 script.txt" << endl;
        return 1;
    }
    vector<string> lines;
    string line;
    while (getline(fin, line)) lines.push_back(line);
    fin.close();

    ChoiceScene choice;
    int i = 0;
    while (i < (int)lines.size())
    {
        string cur = lines[i];

        if (cur == "【选择】")
        {
            i++;
            choice.parse(lines, i);
            int c = choice.show();
            cout << "你选择了：" << choice.getOption(c) << endl;
            _getch();

            string target = choice.getTarget(c);
            int j=i;
            while(j<(int)lines.size()&&lines[j].find(target) != 0) j++;
            if (j < (int)lines.size()) i = j;
            else break;
            continue;
        }

        // 【结局】【汇合】都是路标行，不打印直接跳过
        if (cur.find("【结局") == 0 || cur.find("【汇合") == 0) { i++; continue; }

        // 【END】剧本结束标记
        if (cur == "【END】") { break; }

        cout << cur << endl;
        _getch();
        i++;
    }
    return 0;
}