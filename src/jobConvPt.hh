#ifndef __JOB__CONV__POINT__
#define __JOB__CONV__POINT__


#include "mod1D.hh"
#include "ray1d.hh"
#include <string>
#include <fstream>

class jobConvPt
{
public:
	jobConvPt();
	jobConvPt(int ac, char **av) {init(ac, av); }
	~jobConvPt() {d_av = NULL;}
	int init(int ac, char **av);
	int run();
	int outHelpMessage();
private:
	modlayers   d_mod;
	ray1d       d_backTrace;
	std::string d_geoFilename; // stlo stla baz raypara
	int d_ac;
	char **d_av;
};

#endif