# Longest english word chain
This is the pair programming code repo for BHU 2023 software eng.

## 项目目结构

`src`/ 目录下存放的是主程序和Core计算模块的源代码。

`bin`/ 目录下保存的是Wordlist.exe以及 core.dll和Argparser.dll, IOUtil.dll。等依赖

`gui`/ 目录下保存的是gui界面的源码，采用qt，作为子目录编译。

`guibin`/ 目录下保存的是gui.exe及其依赖，包括Core.dll，IOUtil.dll。

## DLL介绍

**Core.dll**: 核心计算模块。

**IOUtill.dll**：负责文件读入和输出的模块。

**ArgParser.dll**：负责参数解析的模块。

## 使用方法

**CLI**：依照作业要求，在`bin`文件夹下使用命令行调用Wordlist.exe。

CLI在面对错误输入时，有一定的提醒功能：

```
D:\Cpp\Wordlist\bin>Wordlist.exe
You must specify a function
D:\Cpp\Wordlist\bin>Wordlist.exe -c
You must specify a file
D:\Cpp\Wordlist\bin>Wordlist.exe -c -j
Miss option for -j.

D:\Cpp\Wordlist\bin>Wordlist.exe -c -j c
You must specify a file
D:\Cpp\Wordlist\bin>Wordlist.exe -c -j c ..\testt.txt
No such file ..\testt.txt
```

**GUI**：在`guibin`文件夹下打开gui.exe即可使用

## 注意！

`libgcc_s_seh-1.dll`和`libstdc++-6.dll`为必要依赖，**请勿删除**！
