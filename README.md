# README
<h1>Implementing a Memory Allocation Library</h1>
<h2>To Compile and Run</h2>
Library: <br >
make <br  >

Tests: <br >
After compiling and linking the library together <br >
gcc -o test_name test_name.c -L. -lmem (the userthread library must be in the same directory as the test for this line to work) <br >
./test_name

<h2>Introduction</h2>
This Memory Allocation Library uses mmap() to request the operating system for a set amount of writable data in pages and bytes that can then be allocated (split) and/or freed.

<h3>Data Structures Implemented</h3>
The primary data structure implemented was a doubly linked list to keep track of the free blocks. 


<h2>Features</h2>

<h3>Fully Implemented</h3>
<h4>Mem_Init()</h4>
<h4>Mem_Alloc()</h4>
<h4>Mem_Free()</h4>
<h4>Mem_Dump()</h4>


<h3>Not Implemented</h3>
Extra Credit is not implemented.

<h3>Tests Performed</h3>
Small tests at each step of building the code were performed. When near completion, the test were made using the suggestions on hw5.pdf.
