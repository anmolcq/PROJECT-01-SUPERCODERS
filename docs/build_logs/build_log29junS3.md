-Date 29 June 2026 (Sesssion 3)
Duration: 2 hours 30 mins
Goal():
To check about google test suite and implement them for unit testing , And complete the CLI implementation along with it.

What I did():
After i implemented the execute function then the next task is to create a command line interface so that it can be ran direclty from the terminal.

Error 1:
PS D:\CQ> g++ -g clif.cpp -o clif                               
C:\Users\hp\AppData\Local\Temp\ccxsm3fT.o: In function `main':
D:\CQ/clif.cpp:7: undefined reference to `CLI::run()'
collect2.exe: error: ld returned 1 exit status
This error was because i was only running the program for CLI and not running other due to which it was not able to understand all the other headers and due to which it was showing this error.

Written the test cases for the dynamic array for different functions such as insert append remove etc. 

Integrated the test cases in the Cmake list.