#include <Program.hpp>



std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect){
	os << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << std::endl;
	return os;
}



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


