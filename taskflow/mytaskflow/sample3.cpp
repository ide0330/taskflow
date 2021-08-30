#include "../taskflow.hpp"

// For Work B
int mult(int x, int y){
	return x * y;
}
 
// For Work C
int add(int x, int y){
	return x + y;
}
 
// For Work D
int divs(int x, int y){
 	return x / y;
}
 
// For Work main()
int sub(int x, int y){
	return x - y;
}
 
int main(){
	tf::Taskflow tf;
 
	int a, b, c;
	int d, e, f;
	int g;
 
	// Create A~D task
	tf::Task A = tf.emplace([](){}).name("Init a~g");
	tf::Task B = tf.emplace([](){}).name("c = a * b");
	tf::Task C = tf.emplace([](){}).name("f = d + e");
	tf::Task D = tf.emplace([](){}).name("g = c / f");;
 
	// Work of A~D task
	A.work([&a, &b, &c, &d, &e, &f, &g] () {
		std::cout << "==== Task A ====" << std::endl;
		a = 6, b = 8, c = 0;
		d = 3, e = 9, f = 0;
		g = 0;
		std::cout << "Init Param" << std::endl;
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "e = " << e << std::endl;
	});
 
	B.work([&a, &b, &c] () {
		std::cout << "==== Task B ====" << std::endl;
		c = mult(a, b);
		std::cout << "c = a * b" << std::endl;
		std::cout << "c = " << c << std::endl;
	});
 
	C.work([&d, &e, &f] () {
		std::cout << "==== Task C ====" << std::endl;
		f = add(d, e);
		std::cout << "f = d + e" << std::endl;
		std::cout << "f = " << f << std::endl;
	});
 
	D.work([&c, &f, &g] () {
		std::cout << "==== Task D ====" << std::endl;
		g = divs(c, f);
		std::cout << "g = c / f" << std::endl;
		std::cout << "g = " << g << std::endl;
	});
 
	// Precede and gather
	A.precede(B, C);	// A run before B, C (A -> B, A -> C)
	D.gather(B, C);		// D runs after B, C (B -> D, C -> D)
 
	// debug
	tf.dump(std::cout);
 
	// block until finished
	tf.wait_for_all();
 
	// work of main()
	std::cout << "==== main ====" << std::endl;
	std::cout << "g - 2 = " << sub(g, 2) << std::endl;
 
	return 0;
}