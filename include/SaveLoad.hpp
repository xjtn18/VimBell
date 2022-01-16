#include <cajun/json/reader.h>
#include <cajun/json/writer.h>
#include <cajun/json/elements.h>


// FD
struct Rack;
struct Program;


void load_rack(Program &p, const std::string &rack_name);
void save_rack(const std::shared_ptr<Rack>& rack);
