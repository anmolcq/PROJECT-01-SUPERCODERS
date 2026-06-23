
- Date: 22 June 2026 (Session 1)
Duration: 2 Hours 30 mins 
Goal():
To implement 2 methods of the dynamic array been listed in the design proposal.


Problem():
There were some errors encountered during the coding the errors were caused due to the misplacement missing the keywords etc. The errors are:
**Error 1:**
PS D:\GITN\PROJECT-01-SUPERCODERS\DynamicArray> g++ -g DynamicArray.cpp -o Dynamicarray
c:/mingw/bin/../lib/gcc/mingw32/6.3.0/../../../libmingw32.a(main.o):(.text.startup+0xa0): undefined reference to `WinMain@16'
collect2.exe: error: ld returned 1 exit status

- Explaination :I have not defined the iostream due to which this error occured. It meant that compiler is check and cannot fint the standard int function.

What I tried:
I have created class for the dynamic array and tried implementing the constructor and destructor then tried some basic ones like size and check if empty.When i get this errors i regain visited the code and understood which is missing in the code due to which the errors are encountered.


Outcome:
Implemented constructors destructors and grow funtion for Dynamic array.
