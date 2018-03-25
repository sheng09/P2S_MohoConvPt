#include "ray1d.hh"

int ray1d::initMod(modlayers *mod) {
	d_mod = mod;
	d_raySegments.resize(mod->size());
	int i =0;
	for(modlayers::iterator it = mod->begin(); it != mod->end(); ++it)
		d_raySegments[i++].init(it);
	return 0;
}

int ray1d::rayTrace() {
	for(std::vector<rayseg>::iterator it = d_raySegments.begin(); it != d_raySegments.end(); ++it) {
		it->makeSeg(d_raypara, d_rayType);
		it->backTrace(d_baz);
	}
	return 0;
}

int ray1d::conversionPoint(GeoPoint *convPt) {
	GeoPoint& pt = *convPt;
	pt.assign(0.0, 0.0);
	for(std::vector<rayseg>::iterator it = d_raySegments.begin(); it != d_raySegments.end(); ++it) {
		pt.incre(it->getEW(), it->getNS() );
	}
	pt.km2deg();
	pt.incre(d_stlo, d_stla);
	return 0;
}