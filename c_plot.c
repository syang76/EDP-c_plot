// Siyang Yang
// 09/14/2024
// links to iri.so to create executable iri which uses gnuplot to plot EDP parameters
// icc -c c_plot.c
// icc -o iri ~/MY_LD/lib_iri.so c_plot.o -lifcore

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void iritest_main_();

int main() {
    //float xlat = 10.0; // lati/deg
    //float xlon = 110.0; // long/deg
    //int iy = 2012; // year(yyyy)
    //int imd = 211; // mmdd(or -ddd)
    //float hour = 10.0; // hour
    //float hx = 300.0; // height/km
    printf("Assign parameters for EDP below:\n");
    int jm = 0; // 0/1,geog/geom
    float xlat = 37.8; // lati/deg Lat 37.8N
    float xlon = -75.4; // long/deg Lon 75.4W
    int iy = 2019; // year(yyyy) 2021
    int imd = 201; // mmdd(or -ddd) Mar 3
    int iut = 1; // 0/1,LT/UT) UT
    float hour = 12.0; // hour 23:00:00
    float hx = 600.0; // height/km  600km
    int ivar = 1; // (1/2/../8 for height/lat/long/year/month/day/day of year/hour)
    float vbeg = 0.0; 
    float vend = 2000.0; 
    float vstp = 10.0; // begin, end, and stepsize for the selected variable
    int piktab = 0; // output-option (if variable=height then choose 0, 3, 4, or 5)
                    // (enter 0 for standard table of IRI parameters)
                    // (enter 1 for list of peak heights and densities)
                    // (enter 2 for plasma frequencies, B0, M3000, valley, width and depth,)
                    // (enter 3 for 6 parameters of your choice)
                    // (enter 4 for D-region models at 60,65,..,110 km)
                    // (enter 5 special test output)
    float htec_max = 2000; // upper height [km] for TEC integration (0 for no TEC)
    int jchoice = 0; // Options: t(rue) or f(alse)
                     // Enter 0 to use standard or 1 to enter your own

    // call fortran subroutine in iritest.for to generate EDP and save in fort.70
    iritest_main_(&jm,&xlat,&xlon,&iy,&imd,&iut,&hour,&hx,&ivar,&vbeg,&vend,&vstp,
                  &piktab,&htec_max,&jchoice);

    // Create Gnuplot script to plot data in fort.70
    printf("Starting gnuplot.\n");
    FILE *script_file;
    script_file = fopen("plot_script.gp", "w");
    if (script_file == NULL) {
        perror("Error opening script file");
        return 1;
    }
    printf("generate gnuplot script.\n");
    fprintf(script_file,
            "set terminal pngcairo size 800,600\n"
            "set output 'EDP.png'\n"
            "set title 'EDP'\n"
            "set xlabel 'Plasma frequency (MHz)'\n"
            "set ylabel 'Altitude (km)'\n"
            "set xrange [0:12]\n"
            "set yrange [0:600]\n"
            "plot 'fort.70' using 2:1 with lines\n");
    fclose(script_file);
    // Call Gnuplot
    printf("call gnuplot\n");
    system("gnuplot plot_script.gp");
    printf("All done\n");

    return 0;
}

