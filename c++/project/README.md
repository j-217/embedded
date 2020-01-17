## 项目介绍

本项目是在linux平台下完成的俄罗斯方块游戏，为了练习在C++语言环境下的面向对象编程思路

作者： 茹今

## 编译&运行方式

```
$cd project
$make
$make clean
$./start
```

## 涉及内容&功能

- Linux 平台下终端光标移动、绘制内容、清除内容
- Linux 平台下的键盘捕获（kbhit）
- 随机生成7种方块
- 方块移动、旋转
- 碰撞检测（移动， 旋转）
- 满行消除
- 游戏结束判定

## 待完善

- 计分系统（当前分数， 历史最高分）
- 多线程进行键盘捕获

## 截图

> 在Windows powershell中显示

<image src="./Resources/win_gaming.png" width="500">
<image src="./Resources/win_gameover.png" width="500">