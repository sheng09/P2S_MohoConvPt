#include "mod1D.hh"
#include <cmath>

#ifndef __RAY__1D__
#define __RAY__1D__
class GeoPoint {
public:
	GeoPoint() {}
	~GeoPoint() {}
	GeoPoint(const GeoPoint& pt) { assign(pt.longitude, pt.latitude);}
	GeoPoint(float lo, float la) { assign(lo, la); }
	float longitude;
	float latitude;
	void assign(float lo, float la)  { latitude = la; longitude = lo; }
	GeoPoint& incre(float dlo, float dla) { latitude+=dla; longitude+=dlo; return *this;}
	GeoPoint& incre( GeoPoint dpt) { incre(dpt.longitude, dpt.latitude); return *this; }
	GeoPoint& km2deg() { latitude /= 111.1949266414; longitude /= 111.1949266414; return *this; }
	GeoPoint& deg2km() { latitude *= 111.1949266414; longitude *= 111.1949266414; return *this; }
};

class rayseg
{
public:
	rayseg() {};
	rayseg(modlayers::iterator l) {init(l);}
	~rayseg() {}
	int init(modlayers::iterator l) {d_layer = l;}
	int makeSeg(float raypara, char wave) {
		float vel = (wave == 'P' ? d_layer->getVp() : d_layer->getVs());
		d_dz = d_layer->getThickness();
		float sina = raypara*vel;
		float cosa = sqrtf(1.0-sina*sina);
		d_dx = d_dz*(sina/cosa);
		return 0;
	}
	int backTrace(float baz) {
		float angle = (90.0-baz)/180.0*3.1415926535;
		d_ew = cosf(angle)*d_dx;
		d_ns = sinf(angle)*d_dx;
		return 0;
	}
	float getDistance() {return d_dx; }
	float getNS() {return d_ns; }
	float getEW() {return d_ew; }
private:
	float d_dz;
	float d_dx;
	float d_ns;
	float d_ew;
	modlayers::iterator d_layer;
};

class ray1d
{
public:
	ray1d() : d_raySegments(0) {};
	ray1d(float raypara, float baz, char raytype, GeoPoint station, modlayers* mod) {
		initMod(mod);
		initGeo(raypara, baz, raytype, station);
	}
	~ray1d() {
		if(!d_raySegments.empty()) d_raySegments.clear();
	}
	int initMod(modlayers *mod);
	int initGeo(float raypara, float baz, char raytype, GeoPoint sta) {
		DPRINT("entering ray1d::init %p", this);
		d_raypara = raypara; d_baz = baz; d_rayType = raytype; d_station = sta;
		return 0;
	}
	int rayTrace();
	int conversionPoint(GeoPoint *convPt);
private:
	//float d_stlo, d_stla;
	GeoPoint d_station;
	float d_raypara;  // s/km
	float d_baz;      // Degree
	char  d_rayType;  // 'P' or 'S'
	modlayers *d_mod;
	std::vector<rayseg> d_raySegments;
};
#endif