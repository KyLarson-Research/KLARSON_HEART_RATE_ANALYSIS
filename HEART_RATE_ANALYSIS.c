//
// FileName: HEART_RATE_ANALYSIS.c 
// Author: Kyle C Larson
// License: Proprietary
// Statement: By using this software the user agrees 
// 	not to copy, modify nor redistribute the work without written permission from the Author.
#include <stdio.h>
#include <string.h>
#include <math.h>
#define TEST_FILE_NUMBER_OF_LINES 2757
int main(void)
{
    FILE *fp;
	
    //FILE *fq;
    //Open .CSV
	const char *inp_filename = "HR_data.csv";
		//const char *out_filename = "HR_VARIABILITY_ANALYSIS.";
	float HR_buffer[30];
	HR_buffer[0]=0;
	double Time_Buffer[30];
	Time_Buffer[0]=0;
	double Time[30];
	Time[0]=0;
	float Running_Average_HR=0;
	int Running_Sum_HR=0;
	float mean_HR =0;
	float Total_HR = 0;
	float stdev_HR[TEST_FILE_NUMBER_OF_LINES];
	float sum_of_variance=0;
	int i=0;
	float k =0;
	float j=0;
	int l=0;
    fp = fopen(inp_filename, "r");
		//fq = fopen(out_filename, "w");
	if (fp == NULL) { // Check that the input file exists
        printf("Could not open file %s", inp_filename);
        return 1;
    }
	while (fscanf (fp, "%f,%lf", &HR_buffer[i], &Time_Buffer[i]) != EOF ){//Start of second do while. the reason is to get strings
		//
	//Loop import 30 lines calculate 
		//printf("%d\n",HR_buffer[i]);
		
		//Time Conversion to minutes
		Time[i]=((Time_Buffer[i]-Time_Buffer[0])/1000)*60+((Time_Buffer[i]-Time_Buffer[0])-(Time_Buffer[i]-Time_Buffer[0])/1000)/100+(fmod(Time_Buffer[i]-Time_Buffer[0], 100))/60;//
		
		//-Root Mean Square Successive Differences
		if(i>0){
			Running_Sum_HR=Running_Sum_HR+((HR_buffer[i]-HR_buffer[i-1])*(HR_buffer[i]-HR_buffer[i-1]));
		}
		if(i==29){Running_Average_HR = Running_Sum_HR/Time[i];
			printf("%lf,%lf\n", sqrt(Running_Average_HR), Time[i]);
		
			
		}
		//-Sum for Mean HR
			Total_HR=Total_HR + HR_buffer[i];
		//-Storage for the Standard Deviation HR
			stdev_HR[l] = HR_buffer[i];
		
		i++;
		k++;
		l++;
		if(i==30){i=0;}
		
	}
	//calculate mean
	mean_HR = Total_HR/k;
	//calculate stdev
	for(i=0;i<TEST_FILE_NUMBER_OF_LINES; i++){
		sum_of_variance = sum_of_variance  + (stdev_HR[i]-mean_HR)*(stdev_HR[i]-mean_HR);
	}
	printf("\n\n Number of HR Samples: %d\n\n Mean HR: %f bpm\n\n St Dev: %f", l,mean_HR,sqrt(sum_of_variance/k));
	fclose(fp);//fclose(fq);
    return 0;


}