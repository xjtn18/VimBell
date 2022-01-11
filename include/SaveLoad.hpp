#include <cajun/json/reader.h>
#include <cajun/json/writer.h>
#include <cajun/json/elements.h>


// FD
struct Rack;


void load_rack(std::shared_ptr<Rack>& rack, const std::string& rack_name);
void save_rack(const std::shared_ptr<Rack>& rack);
