# <center>操作系统实验二 Shell脚本编程</center>
#### <center>518021910879 陈瀚嵩</center>
## 1 实验题目
### 1.1 *myfind*
&emsp;&emsp;编写一个 Shell 脚本 `myfind.sh` ，接受**两个**参数 *path* 和 *pattern* ，实现如下功能：
* 搜索 *path* 目录树下的所有 `.c` 和 `.h` 文件，如果文件中的某一行中包含 *pattern* 指定的字符串，则将该行内容和相应的文件名打印出来。
* 如果 *path* 参数缺省，则在**当前目录**中执行上述针对 *pattern* 的搜索和打印任务。
### 1.2 *mytree*
&emsp;&emsp;编写一个 Shell 脚本 `mytree.sh` ，实现如下功能：
* 按层次结构输出当前目录树中的所有目录和文件名，每层**缩进 4 个空格**。
## 2 算法思想及概要设计
### 2.1 *myfind*
&emsp;&emsp;首先判断接受参数的个数，若接受一个参数，在当前目录下搜索，若接受两个参数，在第一个参数指定的目录下搜索，若接受其他数量参数，返回报错。

&emsp;&emsp;根据上述参数个数判断结果，在指定目录下查找符合要求的文件，在其中搜索符合要求的字符串并打印出来。
### 2.2 *mytree*
&emsp;&emsp;使用函数递归调用自身的算法，遍历目录树，打印遍历到的文件或文件夹名称，并在递归调用自身的同时传入缩进空格数的参数。
## 3 重要模块的功能、详细设计以及接口说明
### 3.1 *myfind*
&emsp;&emsp;使用 `case` 语句判断接受参数个数，按判断的结果指定搜索目录 *path* 和字符串模式 *pattern* 。

&emsp;&emsp;搜索时，先用 `find` 命令查找指定路径下后缀为 `.c` 和 `.h` 的文件，然后在找到的文件中使用 `grep` 命令打印包含 *pattern* 所指定字符串的文件和相应行号。

### 3.2 *mytree*
&emsp;&emsp;定义函数 `mytree()` ，使用递归法遍历指定目录树的所有层次。其中，遍历的目录传入函数的第一个参数，行首缩进的空格数传入函数的第二个参数。

&emsp;&emsp;函数每次被调用时，遍历其第一个参数指定的目录下所有文件夹及文件，同时打印名称，其中当遍历到文件夹时，函数递归调用自己，再从被遍历到的文件夹开始遍历，且缩进空格数按预设增长。

## 4 重要数据结构及变量说明
### 4.1 数据结构
&emsp;&emsp;*mytree* 中，遍历的目录树为树状结构，对其的递归遍历采用了类似于前序遍历的方式。
### 4.2 变量
&emsp;&emsp;*myfind* 中，变量 `path` 和 `pattern` 的含义如题目所指定。
## 5 测试方法及结果
### 5.1 测试方法
&emsp;&emsp;在 Linux 环境下，使用交互式测试方法，以 `bash myfind.sh` 、 `bash mytree.sh` 运行程序，其中对于 `myfind` ，用户指定搜索的 *path* 和 *pattern* 。
### 5.2 测试结果
&emsp;&emsp;构造特定的文件目录结构，对 *myfind* 和 *mytree* 的一次具体测试的控制台输入、输出实例测试结果如下：

```
$ bash myfind.sh
Parameter number wrong!
$ bash myfind.sh hello
./test/test1/1.c:1:hello
./test/test2/test21/2.h:1:hello 
./test/test2/test21/2.h:4: hellooohe
./test/test2/test21/2.h:5:ahahahahhello
$ bash myfind.sh ./test/test1 hello
./test/test1/1.c:1:hello
$ bash mytree.sh
myfind.sh
mytree.sh
test
    test1
        1.c
        test11
            test111
    test2
        test21
            2.h
```
## 6 结果及错误的分析
### 6.1 结果分析
&emsp;&emsp;本次实验我实现了简单 Shell 脚本的编写。在实验过程中，我初步掌握了 Shell 脚本简单命令的使用、函数的编写等操作。在完成实验后，我编写 Shell 脚本的能力有了很大提升。

### 6.2 错误分析
&emsp;&emsp;本次实验过程中主要需考虑到错误输入带来的问题，尤其是参数个数错误需要特别处理，才能使程序得到正确执行。