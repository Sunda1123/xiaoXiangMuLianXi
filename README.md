# xiaoXiangMuLianXi · 小项目练习

> C++ 小项目合集，记录从零写代码的成长过程 🚀
> 每个项目都是独立小工程，练手 + 简历素材两用。

---

## 📁 项目列表

### 1. calculator · 模板计算器

一个支持**分数运算**的控制台计算器，把 C++ 的模板、运算符重载、两栈求值全部用上了。

**功能亮点：**
- 表达式求值：`2 + 3 * 4` → `14`，支持括号 `( ) [ ] { }` 三种
- 同一套代码同时支持 `int` / `double` / `Fraction`（分数）三种类型
- `Fraction` 类自动约分，输出 `5/6` 这样的真分数
- 支持负数输入（如 `-3 + 5`）

**编译运行：**
```bash
g++ calculator/calculator.cpp -o calculator
./calculator          # Windows 下运行 calculator.exe
```

**示例：**
```
>>> 1/2 + 1/3
[Fraction] = 5/6
```

---

### 2. mini_engine · 迷你文字游戏引擎

一个**剧情引擎**——游戏内容写在 `script.txt` 里，引擎负责读文件、逐行显示、给选项。**改剧情不用改代码**，体会"引擎与内容分离"的思想。

**玩法：**
- 剧情文件里的普通行 = 对话/旁白，按任意键翻页
- 遇到 `【选择】` 标记，读取下面的 `【选项】xxx` 作为分支选项

**编译运行：**
```bash
g++ mini_engine/mini_engine.cpp -o mini_engine
# 在 mini_engine 目录下准备 script.txt（剧情文件），然后运行
./mini_engine
```

**剧情文件 `script.txt` 示例：**
```
你好，欢迎来到文字世界！
【选择】
【选项】向左走
【选项】向右走
```

---

### 3. tanchishe · 贪吃蛇

Windows 控制台版贪吃蛇，用 `vector` + 面向对象实现。

**功能：**
- 方向键控制移动，蛇不能掉头/撞墙/咬自己
- 吃食物加 10 分，越吃越快
- 空格暂停/继续，R 重新开始，Q 退出

**编译运行：**
```bash
g++ tanchishe/snake.cpp -o snake
./snake               # Windows 下运行 snake.exe
```

---

## 🛠 环境要求

- 编译器：`g++`（MinGW）或 VS 2022
- 平台：Windows（用到了 `windows.h` / `conio.h` 控制台 API）
- 编码：源码为 UTF-8，程序内已调用 `SetConsoleOutputCP(CP_UTF8)` 保证中文正常显示

## 📌 说明

- 仓库只放源码，`.exe` 等编译产物已通过 `.gitignore` 忽略，需要自己编译
- 学习顺序推荐：贪吃蛇 → 计算器 → 迷你引擎（由易到难）
