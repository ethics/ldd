Let us see an example to understand how compilers interpret volatile keyword. Consider the below code. 
We are changing the value of a const object using a pointer and we are compiling code without optimization option. 
Hence the compiler won’t do any optimization and will change the value of the const object.

When we compile code with “–save-temps” option of gcc, it generates 3 output files:
1) preprocessed code (having .i extension) 
2) assembly code (having .s extension) and 
3) object code (having .o extension). 

We compiled code without optimization, that’s why the size of assembly code will be larger.

Let us compile the same code with optimization option (i.e. -O option). 
In the below code, “local” is declared as const (and non-volatile). 
The GCC compiler does optimization and ignores the instructions which try to change the value of the const object. Hence the value of the const object remains same.   

For the above code, the compiler does optimization, that’s why the size of assembly code will reduce.

Let us declare the const object as volatile and compile code with optimization option.
Although we compile code with optimization option, the value of the const object will change because the variable is declared as volatile which means, don’t do any optimization. 
