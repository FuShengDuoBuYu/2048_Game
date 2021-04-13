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

### 运行程序:

 - 同样是在该源文件目录下,输入

   ```
   main.exe
   ```

   即可进入2048游戏界面

 - 选择测试模式:

   ```dos窗口
   Input '-t' to choose test mode;
   Input other orders to choose normal mode:
   ```

   ​	在该页面下,输入

   ``` 
   -t
   ```

   即可进入测试模式(出现64结束),输入其他任意值进入非测试模式(出现2048结束)

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

- 选择棋盘维度

  ```
  Please enter the number of the corresponding dimension:
  ```

  在该页面下,输入

  ```
  2 //: 进入2 * 2的棋盘
  3 //: 进入3 * 3的棋盘
  4 //: 进入4 * 4的棋盘
  5 //: 进入5 * 5的棋盘
  ```

  - 注:若之前选择双人模式,需要在此时输入双方用户名

- 程序已运行,根据指令进行即可

---

### 注:

- 文件中使用了 windows.h 头文件执行 system("cls");语句以清除屏幕内容,如果在mac上可能无法正常编译运行