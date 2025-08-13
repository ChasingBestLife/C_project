/*

	声明函数，只需要在调用之前声明就不会报错，
	有三种声明方式
	void swap(int a, int b)
	extern void swap(int a, int b)
	void swap(int , int )

	没有函数体（代码块）就是声明，有函数体就是定义

*/

// return 与 exit区别
// return 是结束当前函数运行，即在子函数运行return就会结束调用子函数，在main函数运行就会结束整个程序

// exit 是一个库函数，结束整个程序运行，无论在子函数还是main函数
// exit（0）;