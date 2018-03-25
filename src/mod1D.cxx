#include "mod1D.hh"
#include <fstream>
#include <stdexcept>
int modlayers::init(const std::string& filename)  {
	float thickness, vp, vs, rho;
	std::ifstream modfile(filename.c_str());
	float z = 0.0;
	while(modfile >> thickness >> vp >> vs >> rho) {
		d_thickness.push_back(thickness);
		d_vp.push_back(vp);
		d_vs.push_back(vs);
		d_rho.push_back(rho);
		d_zs.push_back(z);
		z += thickness;
	}
	d_zs.push_back(z);
	if(!modfile.eof()) throw std::runtime_error("Invalid data from file: " + filename);
	return 0;
}
int modlayers::outMod(std::ostream& out) {
	out.precision(6);
	char tmpline[128];
	for(int i=0; i<d_vp.size(); ++i) {
		memset(tmpline, 0, 100);
		sprintf(tmpline, "(%d) [%f, %f] %f %f %f %f\n", 
			i+1, d_zs[i], d_zs[i+1], d_thickness[i], d_vp[i], d_vs[i], d_rho[i]);
		out << tmpline;
	}
	return 0;
}

int modlayers::makeLayers() {
	d_layers.resize(d_vp.size());
	for(int i=0; i<d_vp.size(); ++i) {
		d_layers[i].init(d_zs[i], d_zs[i+1], d_vp[i], d_vs[i], d_rho[i]);
	}
	return 0;
}
//int main(int argc, char const *argv[])
//{
//	modlayers mod("test.mod");
//	mod.makeLayers();
//	return 0;
//}