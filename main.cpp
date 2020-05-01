#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <fstream>
#include <ctime>
 
 



#define button 17
#define TRIG 23
#define ECHO 24


using namespace std;

bool flip = false;
bool blnk = false;
bool threadExit = false;
bool debug = false;


void pinCleanUp();
void outLoop();
void datetimeout();
void dataLoop();
int usDistance();
void usOutput();

void ALARMhandler(int sig)
{
	blnk = true;
}


void sigint(int sig)
{
	signal(SIGALRM, SIG_IGN);//pushes back alarm so exiting isnt interrupted
	threadExit = true;
	printf("exiting");
	system("sudo shutdown -h now");

}
int main(void)
{
	int pid = -1;
	wiringPiSetupSys();
	pinMode(button, INPUT);
	//initialize ultrasonic sensor
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	digitalWrite(TRIG, LOW);
	delay(500);
	////

	pid = fork();
	signal(SIGINT, sigint);
	signal(SIGALRM, ALARMhandler);
	alarm(1);
	if (pid == 0)
	{
		printf("Success c");
		outLoop();
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		dataLoop();
		printf("Success p");
	}


	return 0;
}


void datetimeout()
{
	time_t nw;
	struct tm* tinfo;
	char dt[80];
	time(&nw);
	tinfo = localtime(&nw);
	strftime(dt, 80, "%I:%M%p", tinfo);
	ofstream datefile;
	datefile.open("/home/pi/mirrorData/data/date.txt");
	datefile << dt << endl;
	datefile.close();
}


void dataLoop()
{
	while (true)
	{
		if (blnk)
		{
			blnk = false;
			datetimeout();
			usOutput();
			alarm(10);
		}
	}
}

void outLoop()//a loop for the button/hardware inturrupt
{

	for (;;)
	{
		 
		if (digitalRead(button) == HIGH)
		{
			raise(SIGINT);
		}
		 
	}


}
 
void usOutput()
{
	if (debug)
	{
			ofstream usfile;
			usfile.open("/home/pi/mirrorData/data/dist.txt");
			usfile << 1 << endl;
			usfile.close();

		
	}
	else {
		if (usDistance() <= 10)
		{
			ofstream usfile;
			usfile.open("/home/pi/mirrorData/data/dist.txt");
			usfile << 1 << endl;
			usfile.close();

		}
		else
		{
			ofstream usfile;
			usfile.open("/home/pi/mirrorData/data/dist.txt");
			usfile << 0 << endl;
			usfile.close();
		}
	}
}

int usDistance()
{
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);
	while (digitalRead(ECHO) == LOW);
	long start = micros();
	while (digitalRead(ECHO) == HIGH);
	long travel = micros() - start;
	int dist = travel / 58;
	return dist;
}



//function to reset all pins low/high in order to make sure they're returned to their expected initial state(low/output)
//should run at beggining/end of ever thread
void pinCleanUp()
{
	for (int i = 0; i < 30; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
}
