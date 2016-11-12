#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <math.h>
#include <iostream>

//author artbaryl@gmail.com

using namespace std;
double tablica_b[ 5 ]={0,0,0,0,0};
double tablica_c[ 5 ]={0,0,0,0,0};
double srednia_b, srednia_c;

void srednia(double c, double b)
{
	//cout <<" Im in function"<< endl;
	for (int i = 0; i<4; i++)
	{
	
		tablica_b[i]=tablica_b[i+1];
		tablica_c[i]=tablica_c[i+1];
		srednia_b+=tablica_b[i];
		srednia_c+=tablica_c[i];
	}
	tablica_c[4]=c;
	tablica_b[4]=b;
	srednia_b=(b+srednia_b)/5;
	srednia_c=(c+srednia_c)/5;
}

double triangulacja_x(double a, double b, double c)
{
	double x;
	x = - a+ 0.5*sqrt(8.0*pow(a,2)+4.0*pow(b,2)-4.0*pow(c,2));
	return x;
}

double triangulacja_y(double c, double a, double x)
{
	double h;
	h = sqrt(pow(c,2)-pow(a,2)+2*a*x);
	return h;
}

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	printf("Position detection\n\n");

	Serial* SP1 = new Serial("\\\\.\\COM7");    // ANCHOR 1
	Serial* SP2 = new Serial("\\\\.\\COM8");    // ANCHOR 2

	if (SP1->IsConnected())
		printf("Anchor 1 connected\n");
	if (SP2->IsConnected())
		printf("Anchor 2 connected\n");

	char incomingData1[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength1 = 255;
	int readResult1 = 0;
	
	char incomingData2[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength2 = 255;
	int readResult2 = 0;
	double a, b, c, x, y, p;
	a=2.1;
	
	while(SP1->IsConnected()&&SP2->IsConnected())
	{
		
		readResult1 = SP1->ReadData(incomingData1,dataLength2);
		readResult2 = SP2->ReadData(incomingData2,dataLength2);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
             //   incomingData1[readResult1] = 0;
              //  incomingData2[readResult2] = 0;
		//	cout<<"Anchor 1: ";
        //	printf("%s",incomingData1);
        //	cout<<"Anchor 2: ";
		//	printf("%s",incomingData2);
			
		
			
			c= atof(incomingData1);
			cout<<"Anchor 1 "<<c<<" m"<<endl;
			b= atof(incomingData2);
			cout<<"Anchor 2 "<<b<<" m"<<endl;
			if(b< 1000 || c < 1000)
			{
			x = triangulacja_x(a,b,c);
			y = triangulacja_y(c,a,x);
			/*srednia(c,b);
			b=srednia_b;
			c=srednia_c;
			p = (double)(a+b+c)/2;
			x = (2*sqrt(p*(p-a)*(p-b)*(p-c)))/a;
			if(b<c) y=a-((b/c)*a);
			else if(b>c) y=(c/b)*a;			
			*/
			cout<<"Position "<<x<<" "<<y<<endl;
			}
			//cout<<(p*(p-a)*(p-b)*(p-c))<<endl;
		Sleep(500);
	}
	return 0;
}


