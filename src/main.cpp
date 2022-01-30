#include <Program.hpp>



int main(int argc, char* argv[]){
	// Start the program

	char* exec_path = argv[0];
	// set root path
	vb::rootPath = vb::rtrim(exec_path, strlen(exec_path), '/'); // does not work, returns only relative path

	Program p; // instantiate program
	p.mainloop();
	p.quit();

	return 0;
}


