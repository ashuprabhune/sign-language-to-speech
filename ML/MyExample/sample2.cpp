#include<GRT/GRT.h>
#include<iostream>
#include<fstream>
using namespace std;
using namespace GRT;
int main(){
LabelledTimeSeriesClassificationData trainingData;      //This will store our training data
LabelledTimeSeriesClassificationData testData;
    GestureRecognitionPipeline pipeline;                    //This is a wrapper for our classifier and any pre/post processing modules 
    UINT trainingClassLabel;                                //This will hold the current label for when we are training the classifier
string infoText = "";
trainingClassLabel = 1;
VectorFloat sample(7);
//sample[0]=0;
//sample[1]=0;
trainingData.setNumDimensions( 7 );
MatrixFloat timeseries;
string line;
  
  
  
  
  
  
  

  
  
  
  
  
  
  
  
  
  

  
  
  



//Initialize the DTW classifier
DTW dtw;

//Turn on null rejection, this lets the classifier output the predicted class label of 0 when the likelihood of a gesture is low
//dtw.enableNullRejection( true);

//Set the null rejection coefficient to 3, this controls the thresholds for the automatic null rejection
//You can increase this value if you find that your real-time gestures are not being recognized
//If you are getting too many false positives then you should decrease this value
//dtw.setNullRejectionCoeff( 3 );

//Turn on the automatic data triming, this will remove any sections of none movement from the start and end of the training samples
//dtw.enableTrimTrainingData(true, 0.1, 90);

//Offset the timeseries data by the first sample, this makes your gestures (more) invariant to the location the gesture is performed
dtw.setOffsetTimeseriesUsingFirstSample(true);

//Add the classifier to the pipeline (after we do this, we don't need the DTW classifier anymore)
pipeline.setClassifier( dtw );

trainingData.loadDatasetFromCSVFile("bent.csv");
//testData=trainingData.split(80);
//testData.saveDatasetToFile("testData.txt");
testData.load("bent_test_.csv");
if( pipeline.train( trainingData ) ){
                infoText = "Pipeline Trained";
            }else infoText = "WARNING: Failed to train pipeline";


if( trainingData.saveDatasetToFile("TrainingData.txt") ){
                infoText = "Training data saved to file";
            }else infoText = "WARNING: Failed to save training data to file";

cout<<pipeline.getTrained()<<endl;
cout<<pipeline.getMaximumLikelihood()<<endl;
cout<<pipeline.getPredictedClassLabel()<<endl;
if(pipeline.getTrained())
{
//	sample[0]=62;
//	sample[1]=62;
//	cout<<sample[0]<<endl;
//	cout<<pipeline.predict(sample);
}

double accuracy = 0;
       for(UINT i=0; i<testData.getNumSamples(); i++){
               //Get the i'th test sample - this is a timeseries
               UINT classLabel = testData[i].getClassLabel();
               MatrixDouble timeseries = testData[i].getData();
       	timeseries.print();

               //Perform a prediction using the classifier
               if( !pipeline.predict( timeseries ) ){
                       cout << "Failed to perform prediction for test sampel: " << i <<"\n";
                       return EXIT_FAILURE;
               }

               //Get the predicted class label
               UINT predictedClassLabel = pipeline.getPredictedClassLabel();
               double maximumLikelihood = pipeline.getMaximumLikelihood();
               VectorDouble classLikelihoods = pipeline.getClassLikelihoods();
               VectorDouble classDistances = pipeline.getClassDistances();

               //Update the accuracy
               if( classLabel == predictedClassLabel ) accuracy++;

       cout << "TestSample: " << i <<  "\tClassLabel: " << classLabel << "\tPredictedClassLabel: " << predictedClassLabel << "\tMaximumLikelihood: " << maximumLikelihood << endl;
       }

//ifstream myfile ("straight_test.csv");
//if (myfile.is_open())
//{
//  while ( getline (myfile,line) )
//  {
//      	std::stringstream ss(line);
//                                                           
//              double d=0.0;
//              while(ss>>d)
//              {
//      		cout<<"Value of d:"<<d<<endl;
//                      sample.push_back(d);
//                      if( ss.peek()==','|| ss.peek()==' ')
//                      {
//                              ss.ignore(1);
//                      }
//              }
//
//	cout<<"prediction succed?"<<pipeline.predict(sample);
//	
//	cout<<pipeline.getMaximumLikelihood()<<endl;
//	cout<<pipeline.getPredictedClassLabel()<<endl;
//
//                                                           
//  }
//  myfile.close();
//}

cout<<pipeline.getMaximumLikelihood()<<endl;
cout<<pipeline.getPredictedClassLabel()<<endl;
}

