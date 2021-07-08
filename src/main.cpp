#include <Program.hpp>



int main(int argc, char* argv[]){
	// Start the program

	char* exec_path = argv[0];
	// set root path
	jb::rootPath = jb::rtrim(exec_path, strlen(exec_path), '/'); // does not work, returns only relative path

	Program p;
	p.mainloop();
	p.quit();

	return 0;
}


