#ifndef __MODEL__1D__
#define __MODEL__1D__

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "test.hh"

class layer {
public:
	layer() {}
	layer(float z1, float z2, float vp, float vs, float rho = -12345.0)
	: d_z1(z1), d_z2(z2), d_vp(vp), d_vs(vs), d_rho(rho) {
		d_thickness = z2 - z1;
	}
	int init(float z1, float z2, float vp, float vs, float rho = -12345.0) {
		d_z1 =z1; d_z2 = z2; d_vp = vp; d_vs = vs; d_rho = rho;
		d_thickness = z2 - z1;
		return 0;
	}
	~layer() {}
	int outLayer(std::ostream& out) {
		char tmpline[128];
		memset(tmpline, 0, 128);
		sprintf(tmpline, "Thickness(km) %f [%f, %f] Vp(km/s) %f Vs %f Rho %f\n",
			d_thickness, d_z1, d_z2, d_vp, d_vs, d_rho);
		out << tmpline;
		return 0;
	}
	float getThickness() {return d_thickness;}
	float getVp() {return d_vp;}
	float getVs() {return d_vs;}
	float getRho() {return d_rho;}
private:
	// Downward is the plus direction for Z.
	float d_z1;        // ceil of the layer
	float d_z2;        // floor of the layer
	float d_thickness; // d_thickness = d_z2 - d_z1
	float d_vp;
	float d_vs;
	float d_rho;
};

class modlayers
{
public:
	modlayers() : d_layers(0) {}
	modlayers(const std::string& filename) : d_layers(0) { init(filename); }
	~modlayers() {
		if(!d_thickness.empty()) d_thickness.clear();
		if(!d_vp.empty()) d_vp.clear();
		if(!d_vs.empty()) d_vs.clear();
		if(!d_rho.empty()) d_rho.clear();
		if(!d_zs.empty()) d_zs.clear();
		if(!d_layers.empty()) d_layers.clear();
	}
	int init(const std::string& filename);
	int outMod(std::ostream& out);
	int makeLayers();
	int size() {return d_vp.size(); }
	typedef std::vector<layer>::iterator iterator;
	iterator begin() {return d_layers.begin(); }
	iterator end() {return d_layers.end(); }
private:
	std::vector<float> d_thickness;
	std::vector<float> d_vp;
	std::vector<float> d_vs;
	std::vector<float> d_rho;
	std::vector<float> d_zs;
	std::vector<layer> d_layers;
};

#endif