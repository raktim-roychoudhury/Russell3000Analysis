#include <stdio.h>
#include <stdlib.h>
#include <math.h>

namespace fre{

    void plotResults(double* xData, double* Beat, double* Meet, double* Miss, int dataSize, const char* title, const char* yLabel) {
       
        FILE *gnuplotPipe,*tempDataFile;
        
        const char *tempDataFileName1 = "Beat";
        const char *tempDataFileName2 = "Meet";
        const char *tempDataFileName3 = "Miss";
        
        double x,y, x2, y2, x3, y3;
        int i;
        
        //set up the gnu plot
        gnuplotPipe = popen("gnuplot -persist", "w");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set title '%s'\n", title);
        fprintf(gnuplotPipe, "set arrow from 0,graph(0,0) to 0,graph(1,1) nohead lc rgb 'red'\n");
        fprintf(gnuplotPipe, "set xlabel 'Announcement Date'\nset ylabel '%s'\n", yLabel);
        
        if (gnuplotPipe) 
        {
            
            fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n",tempDataFileName1, tempDataFileName2, tempDataFileName3);
            fflush(gnuplotPipe);
            
            //plot figure 1
            tempDataFile = fopen(tempDataFileName1,"w");
            for (i=0; i <= dataSize; i++) {
                x = xData[i];
                y = Beat[i];
                fprintf(tempDataFile,"%lf %lf\n",x,y);
            }
            fclose(tempDataFile);
            
            //plot figure 2
            tempDataFile = fopen(tempDataFileName2,"w");
            for (i=0; i <= dataSize; i++) {
                x2 = xData[i];
                y2 = Meet[i];
                fprintf(tempDataFile,"%lf %lf\n",x2,y2);
            }
            fclose(tempDataFile);
            
            //plot figure 3
            tempDataFile = fopen(tempDataFileName3,"w");
            for (i=0; i <= dataSize; i++) {
                x3 = -xData[i];
                y3 = Meet[i];
                fprintf(tempDataFile,"%lf %lf\n",x3,y3);
            }
            fclose(tempDataFile);
            
            printf("press enter to continue...");
            getchar();
            remove(tempDataFileName1);
            remove(tempDataFileName2);
            remove(tempDataFileName3);
            fprintf(gnuplotPipe,"exit \n");
        } 
        else 
        {        
            printf("gnuplot not found...");    
        }
    } 
}