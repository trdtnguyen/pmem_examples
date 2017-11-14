Transaction operations test 

Usage
./rect tempfile 3 4

The program will do following:
+ allocate a struct rect in persistent memory 
+ calculate the perimeter from w and h (input) and print w * h to the screen

./reader tempfile
The tempfile is store in NVDIMM, this program read it and print out the values inside struct rect


