## 运行环境:

​	 windows10

### **gcc版本:**

​	gcc version 9.2.0

---

## 编译方式:

​	进入到dos命令窗口并达到源文件目录下后,输入以下命令:

```dos窗口
  	g++ main.cpp -o main.exe
```

​	即可获得main.exe这个编译后的可执行文件

---

**注:由于使用了一些过时的时间函数,因此在编译时会出现警告,警告内容如下:**

```
In file included from lab2048.cpp:11,
                 from main.cpp:1:
bonus.cpp: In function 'long long unsigned int currentTimeMillisec()':
bonus.cpp:14:15: warning: 'timeb' is deprecated [-Wdeprecated-declarations]
   14 |  struct timeb tb;
      |               ^~
In file included from bonus.cpp:6,
                 from lab2048.cpp:11,
                 from main.cpp:1:
c:\mingw\include\sys\timeb.h:57:32: note: declared here
   57 | struct __POSIX_2001_DEPRECATED timeb
      |                                ^~~~~
In file included from lab2048.cpp:11,
                 from main.cpp:1:
bonus.cpp:15:11: warning: 'void ftime(timeb*)' is deprecated [-Wdeprecated-declarations]
   15 |  ftime(&tb);
      |           ^
In file included from bonus.cpp:6,
                 from lab2048.cpp:11,
                 from main.cpp:1:
c:\mingw\include\sys\timeb.h:169:6: note: declared here
  169 | void ftime (struct timeb *__t) {_ftime ((struct _timeb *)(__t)); }
      |      ^~~~~
In file included from lab2048.cpp:11,
                 from main.cpp:1:
bonus.cpp:15:11: warning: 'void ftime(timeb*)' is deprecated [-Wdeprecated-declarations]
   15 |  ftime(&tb);
      |           ^
In file included from bonus.cpp:6,
                 from lab2048.cpp:11,
                 from main.cpp:1:
c:\mingw\include\sys\timeb.h:169:6: note: declared here
  169 | void ftime (struct timeb *__t) {_ftime ((struct _timeb *)(__t)); }
```

**但是这些警告并不影响程序的正常运行**,忽略即可

---

​	编译成功后如果使用如下命令行参数,则会读取input.in文件中的内容并将处理后的内容放置于output.out文件中

```
main.exe -i input.in -o output.out
```

​	编译成功后如果使用如下命令行参数,则会将终止条件改为出现值为64的方块

```
main.exe -t
```

​	编译成功后如果使用如下命令行参数,则会将棋盘设置为长和宽为n的正方棋盘

```
main.exe -s n
```

​	编译成功后如果使用如下命令行参数,则会将移动得分输出日志到该目录下的 log.txt文件中

```
main.exe -log
```

​	编译成功后如果使用如下命令行参数,则会将移动得分和奖励得分输出日志到该目录下的 log.txt文件中

```
main.exe -log -p
```

---

### 运行程序:

 - 同样是在该源文件目录下,输入

   ```
   main.exe
   ```

   即可进入2048游戏界面

- 选择单双人模式:

  ```
  --------------Game Start--------------
  
  Please choose your game mode:
  1: Single player mode
  2: Double player mode
  Please enter the number of the corresponding mode:
  ```

  在该页面下,输入

  ```
  1 //: 进入单人模式
  2 //: 进入双人模式
  ```

  - 注:若之前选择双人模式,需要在此时输入双方用户名

- 程序已运行,根据指令进行即可

---

