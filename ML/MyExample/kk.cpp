#include <gtk/gtk.h>
#include <unistd.h>
#include <GRT/GRT.h>
#include <vector>
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
void readport(void);
void openport(void);

using namespace GRT;
using namespace std;
bool record=false;
void setup();
int fd=0, n;
static int cnt, size, s_cnt;
unsigned char *var;
struct termios oldtp, newtp;
char sendcmd1[10]="\0";
FILE *file;
LabelledTimeSeriesClassificationData trainingData;      //This will store our training data
    MatrixDouble timeseries;                                //This will store a single training sample
    GestureRecognitionPipeline pipeline;                    //This is a wrapper for our classifier and any pre/post processing modules 
    UINT trainingClassLabel;                                //This will hold the current label for when we are training the classifier
    string infoText;                                        //This string will be used to draw some info messages to the main app window
    
    VectorDouble vec;
void  readport(void)
{

       std::cout<<"Read Port"<<"\n";
	//file = fopen( "zname.txt", "w+" );

                char buff[100]; 
  		n = read(fd, buff, 100);
//		fcntl(fd,F_SETFL,0);
  	
                //std::cout<<"n="<<n<<std::endl;	
		if (n == -1) 
		switch(errno)
		{
         		case EAGAIN: /* sleep() */ 
          
         		default:
			break;
			 //goto quit;
         	}
  		if (n ==0) ;

  		std::stringstream ss(buff);
//                std::cout<<buff<<"\n";

  		double d=0.0;
  		while(ss>>d && vec.size()<7)
  		{
			vec.push_back(d);
			if( ss.peek()==','|| ss.peek()==' ')
			{
				ss.ignore(1);
			}
  		}

  		//if( vec.size()==7)
 		// {
     		//	update();
     		//	vec.clear();
 		// }
  		//else
 		//{
    		//	theApp->vec.clear();
                //        continue;
 		//}
  		//this_thread::sleep_for(chrono::milliseconds(200));
  		std::cout<<"n:"<<std::endl;

	
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

void setup()
{
	//ofSetFrameRate(30);
    
    //Initialize the training and info variables
    infoText = "";
    trainingClassLabel = 1;
    record = false;
    
    //The input to the training data will be the [x y] from the mouse, so we set the number of dimensions to 2
    trainingData.setNumDimensions( 7 );
    
    //Initialize the DTW classifier
    DTW dtw;
    
    //Turn on null rejection, this lets the classifier output the predicted class label of 0 when the likelihood of a gesture is low
    dtw.enableNullRejection( true );
    
    //Set the null rejection coefficient to 3, this controls the thresholds for the automatic null rejection
    //You can increase this value if you find that your real-time gestures are not being recognized
    //If you are getting too many false positives then you should decrease this value
    dtw.setNullRejectionCoeff( 3 );
    
    //Turn on the automatic data triming, this will remove any sections of none movement from the start and end of the training samples
    dtw.enableTrimTrainingData(true, 0.1, 90);
    
    //Offset the timeseries data by the first sample, this makes your gestures (more) invariant to the location the gesture is performed
    dtw.setOffsetTimeseriesUsingFirstSample(true);
    
    //Add the classifier to the pipeline (after we do this, we don't need the DTW classifier anymore)
    pipeline.setClassifier( dtw );

}
/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void recordData( GtkWidget *widget,
                   gpointer   data )
{
	record=!record;
	if( !record ){
		cout<<"stopped recording"<<endl;
		cout<<"adding sample"<<endl;
		timeseries.print(" ");
                trainingData.addSample(trainingClassLabel, timeseries);
                //Clear the timeseries for the next recording
                timeseries.clear();
            }
	else{
		cout<<"started Recording;";
}
}

//static void trainData(GtkWidget *widget,
//                   gpointer   data )
//{
//
//	if( pipeline.train( trainingData ) ){
//                infoText = "Pipeline Trained";
//            }else infoText = "WARNING: Failed to train pipeline";		
//
//}



static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

}
/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}
gboolean getArduinoData(gpointer data)
{ 
   // readport();
   //    std::cout<<"Read Port"<<"\n";
	//file = fopen( "zname.txt", "w+" );

                char buff[100]; 
  		n = read(fd, buff, 100);
//		fcntl(fd,F_SETFL,0);
  	
                //std::cout<<"n="<<n<<std::endl;	
		if (n == -1) 
		switch(errno)
		{
         		case EAGAIN: /* sleep() */ 
          
         		default:
			break;
			 //goto quit;
         	}
  		if (n ==0) ;

  		std::stringstream ss(buff);
//                std::cout<<buff<<"\n";

  		double d=0.0;
  		while(ss>>d)
  		{       cout<<d;
			vec.push_back(d);
			if( ss.peek()==','|| ss.peek()==' ')
			{
				ss.ignore(1);
			}
  		}

  		if( vec.size()==7 && record)
 		 {
     			timeseries.push_back( vec );
     			vec.clear();
 		 }
		else if( vec.size()==7 && pipeline.getTrained()&& timeseries.getNumRows())
		{
			pipeline.predict( vec );
			std::cout<<pipeline.getPredictedClassLabel()<<std::endl;

		}
		
  		//this_thread::sleep_for(chrono::milliseconds(200));
  		//std::cout<<"n:"<<std::endl;

 //   std::cout<<"In Update"<<std::endl;
    VectorDouble sample(7);
    //sample[0] = vec[0];
    //sample[1] = vec[1];
    //sample[2] = vec[2];
    //sample[3] = vec[3];
    //sample[4] = vec[4];
    //sample[5] = vec[5];
    //sample[6] = vec[6];

for( auto& a : vec)
{
//   std::cout<<a<<std::endl;
}
    
    //If we are recording training data, then add the current sample to the training data set
    //if( record ){
    //    timeseries.push_back( vec );
    //}
    //
    ////If the pipeline has been trained, then run the prediction
    //if( pipeline.getTrained()&& timeseries.getNumRows()==10 ){
    //    pipeline.predict( vec );
    //    std::cout<<pipeline.getPredictedClassLabel()<<std::endl;
    //}		
	return true;
}
int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *stop;
    GtkWidget *box;
    GtkWidget *button1;
    box = gtk_hbox_new (FALSE, 0);
    setup();
    openport();
    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);
    
    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    /* When the window is given the "delete-event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    
    /* Here we connect the "destroy" event to a signal handler.  
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete-event" callback. */
    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);
    
    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    /* Creates a new button with the label "Hello World". */
    button = gtk_button_new_with_label ("Record");
    
    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
    g_signal_connect (button, "clicked",
		      G_CALLBACK (recordData), NULL);
	gint ref = g_timeout_add (1, getArduinoData, NULL );

    /* This will cause the window to be destroyed by calling
     * gtk_widget_destroy(window) when "clicked".  Again, the destroy
     * signal could come from here, or the window manager. */
//    g_signal_connect_swapped (button, "clicked",
//			      G_CALLBACK (gtk_widget_destroy),
//                              window);
    
    /* This packs the button into the window (a gtk container). */
    stop =gtk_button_new_with_label ("STOP");

 
	g_signal_connect (stop, "clicked",
                      G_CALLBACK (destroy), NULL);
 //   gtk_box_pack_start (GTK_BOX (box),
   //                     button1, FALSE, FALSE, 3);
   // gtk_box_pack_start (GTK_BOX (box),
   //                     stop, FALSE, FALSE, 3);

//gtk_widget_show(button);

gtk_widget_show(stop);
gtk_container_add (GTK_CONTAINER (box), stop);
gtk_container_add (GTK_CONTAINER (box),button);
    gtk_container_add (GTK_CONTAINER (window), box);
    /* The final step is to display this newly created widget. */
    gtk_widget_show (stop);
    gtk_widget_show(button);
    gtk_widget_show(box); 
    /* and the window */
    gtk_widget_show (window);
    
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */




    gtk_main ();
    return 0;
}
