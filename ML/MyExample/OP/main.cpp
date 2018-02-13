#include "testApp.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>        
#include <stdlib.h> 
#include<unistd.h>
#include <sstream>
#include<stdlib.h>
#include<thread>
#include<chrono>
#define BAUDRATE B9600 
#define MODEMDEVICE "/dev/ttyACM1"/*UART NAME IN PROCESSOR*/
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
void openport(void);
void sendport(void);
void readport(void);
int fd=0, n;
static int cnt, size, s_cnt;
unsigned char *var;
struct termios oldtp, newtp;
char sendcmd1[10]="\0";
FILE *file;
testApp* theApp = NULL;

void  readport(void)
{

       std::cout<<"Read Port"<<"\n";
	//file = fopen( "zname.txt", "w+" );
	int dataInx=0;
	
	while(dataInx<10) 
	{

           
                char buff[100]; 
  		n = read(fd, buff, 100);
//		fcntl(fd,F_SETFL,0);
  	
                //std::cout<<"n="<<n<<std::endl;	
		if (n == -1) 
		switch(errno)
		{
         		case EAGAIN: /* sleep() */ 
            		continue;
          
         		default:
			break;
			 //goto quit;
         	}
  		if (n ==0) continue;

  		std::stringstream ss(buff);
//                std::cout<<buff<<"\n";

  		double d=0.0;
  		while(ss>>d)
  		{
			theApp->vec.push_back(d);
			if( ss.peek()==','|| ss.peek()==' ')
			{
				ss.ignore(1);
			}
  		}

  		if( theApp->vec.size()==7)
 		 {
     			theApp->update();
     			theApp->vec.clear();
 		 }
  		else
 		{
    			theApp->vec.clear();
                        continue;
 		}
  		++dataInx;
  		this_thread::sleep_for(chrono::milliseconds(200));
  		std::cout<<"\n"<<std::endl;

	}
//quit:
//   fclose (file);
}
void openport(void)
{
         
	 fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY |O_NDELAY );
	 printf("oviya :%d\n",fd);
         if (fd <0)
         {
         	perror(MODEMDEVICE);

         }
                                                                                
         fcntl(fd,F_SETFL,0);
         tcgetattr(fd,&oldtp); /* save current serial port settings */
    //     tcgetattr(fd,&newtp); /* save current serial port settings */
         bzero(&newtp, sizeof(newtp));
  //       bzero(&oldtp, sizeof(oldtp));
                                                                                
         newtp.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
                                                                                
         newtp.c_iflag = IGNPAR | ICRNL;
                                                                                
         newtp.c_oflag = 0;                                                                        
         newtp.c_lflag = ICANON;                                                                    
         newtp.c_cc[VINTR]    = 0;     /* Ctrl-c */
         newtp.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
         newtp.c_cc[VERASE]   = 0;     /* del */
         newtp.c_cc[VKILL]    = 0;     /* @ */
        // newtp.c_cc[VEOF]     = 4;     /* Ctrl-d */
         newtp.c_cc[VTIME]    = 0;     /* inter-character timer unused */
         newtp.c_cc[VMIN]     = 0;     /* blocking read until 1 character arrives */
         newtp.c_cc[VSWTC]    = 0;     /* '\0' */
         newtp.c_cc[VSTART]   = 0;     /* Ctrl-q */
         newtp.c_cc[VSTOP]    = 0;     /* Ctrl-s */
         newtp.c_cc[VSUSP]    = 0;     /* Ctrl-z */
         newtp.c_cc[VEOL]     = 0;     /* '\0' */
         newtp.c_cc[VREPRINT] = 0;     /* Ctrl-r */
         newtp.c_cc[VDISCARD] = 0;     /* Ctrl-u */
         newtp.c_cc[VWERASE]  = 0;     /* Ctrl-w */
         newtp.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
         newtp.c_cc[VEOL2]    = 0;     /* '\0' */
   	                                                                                                                                             
//	  tcflush(fd, TCIFLUSH);
//	 tcsetattr(fd,TCSANOW,&newtp);

}


//========================================================================
int main( )
{
       openport();
       theApp=new testApp();
       theApp->setup();
       theApp->record=true;

       while(true)
       {
        std::cin>>theApp->record;
        
	if(theApp->record)
	{
		readport();
        	std::cout<<"Read"<<"\n";
	}
	else
	{
		std::cout<<"Predicting"<<"\n";
                readport();
	}
	while(true)
	{
		char inputChar;
		
		std::cin>>inputChar;
		

		if( inputChar=='c' )
		{
			break;
		}

		theApp->keyPressed( inputChar);
	}
	}

 }
