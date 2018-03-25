#include "jobConvPt.hh"

char HMSG[] = "\
%s -Mmodfile -Iinput [-H]\n\
Calculate the conversion point of P-to-S wave at Moho for teleseismic Receiver Functions.\n\
\n\
-M modfile: Model filename. Each line should be:\n\
            \"Thickness(km) Vp(km/s) Vs(km/s) rho(kg/m^3)\"\n\
-I input:   The file that containing station and ray information.\n\
            Each line should be:\n\
            \"stlo stla baz rayParaMeter\"\n\
[-H] :      Show this message.\n\
";

int jobConvPt::init(int ac, char **av) {
	d_ac = ac; d_av = av;
	if(ac <= 1) {
		outHelpMessage();
		exit(0);
	}
	for(int i =1; i<d_ac; ++i) {
		if(d_av[i][0] == '-') {
			if(d_av[i][1] == 'M') {
				d_mod.init(std::string(&(d_av[i][2])));
			} else if (d_av[i][1] == 'I') {
				d_geoFilename = std::string( &(d_av[i][2]) );
			} else if (d_av[i][1] == 'H') {
				outHelpMessage();
				exit(0);
			} else {
				std::cerr << "Unrecognized argument: " << d_av[i] << "\n";
				exit(-1);
			}
		}
	}
	return 0;
}
int jobConvPt::run() {
	d_mod.makeLayers();
	d_backTrace.initMod(&d_mod);
	std::ifstream input(d_geoFilename.c_str() );
	GeoPoint station, conversion;
	float baz, raypara;
	while(input >> station.longitude >> station.latitude >> baz >> raypara) {
		d_backTrace.initGeo(raypara, baz, 'S', station);
		d_backTrace.rayTrace();
		d_backTrace.conversionPoint(&conversion);
		std::cout << conversion.longitude << ' ' << conversion.latitude << "\n";
	}
	return 0;
}
int jobConvPt::outHelpMessage() {
	printf(HMSG, d_av[0]);
	return 0;
}

int main(int ac, char **av)
{
	jobConvPt job(ac, av);
	job.run();
	return 0;
}