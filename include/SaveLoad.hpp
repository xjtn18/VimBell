#include <jb.hpp>
#include <Rack.hpp>
#include <cajun/json/reader.h>
#include <cajun/json/writer.h>
#include <cajun/json/elements.h>
#include <fstream>

void load_rack(std::shared_ptr<Rack>& rack);
void save_rack(const std::shared_ptr<Rack>& rack);
