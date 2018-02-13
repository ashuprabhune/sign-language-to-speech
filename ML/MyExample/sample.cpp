#include<GRT/GRT.h>
using namespace std;
using namespace GRT;
int main(){
LabelledTimeSeriesClassificationData trainingData;      //This will store our training data
    GestureRecognitionPipeline pipeline;                    //This is a wrapper for our classifier and any pre/post processing modules 
    UINT trainingClassLabel;                                //This will hold the current label for when we are training the classifier
string infoText = "";
trainingClassLabel = 1;
VectorFloat sample(1);
sample[0]=0;
MatrixFloat matrix;
matrix.loadFromCSVFile("fist.csv",',');
	cout << "Matrix Data: \n";
    for(UINT i=0; i<matrix.getNumRows(); i++){
        for(UINT j=0; j<matrix.getNumCols(); j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
//Initialize the training and info variables




//The input to the training data will be the [x y] from the mouse, so we set the number of dimensions to 2
trainingData.setNumDimensions( 1 );

//Initialize the DTW classifier
DTW dtw;

//Turn on null rejection, this lets the classifier output the predicted class label of 0 when the likelihood of a gesture is low
dtw.enableNullRejection( false);

//Set the null rejection coefficient to 3, this controls the thresholds for the automatic null rejection
//You can increase this value if you find that your real-time gestures are not being recognized
//If you are getting too many false positives then you should decrease this value
//dtw.setNullRejectionCoeff( 3 );

//Turn on the automatic data triming, this will remove any sections of none movement from the start and end of the training samples
//dtw.enableTrimTrainingData(true, 0.1, 90);

//Offset the timeseries data by the first sample, this makes your gestures (more) invariant to the location the gesture is performed
//dtw.setOffsetTimeseriesUsingFirstSample(true);

//Add the classifier to the pipeline (after we do this, we don't need the DTW classifier anymore)
pipeline.setClassifier( dtw );
for(UINT i=0; i<matrix.getNumRows(); i++){
        for(UINT j=0; j<matrix.getNumCols(); j++){
		MatrixFloat matrix1;
		matrix1[i][j]=matrix[i][j];
            trainingData.addSample(1, matrix1);
        }
        cout << endl;
    }

//trainingData.addSample(1, matrix);
cout<<"NUM sample for 1"<<trainingData.getNumSamples()<<endl;
//Clear the timeseries for the next recording
matrix.clear();

matrix.loadFromCSVFile("mid.csv",',');

trainingData.addSample(2,matrix);
cout<<"NUM sample for 2"<<trainingData.getNumSamples()<<endl;
matrix.clear();


matrix.loadFromCSVFile("strt.csv",',');
trainingData.addSample(3,matrix);
cout<<"NUM sample for 3"<<trainingData.getNumSamples()<<endl;
matrix.clear();



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
	sample[0]=82;
	pipeline.predict(sample);
}

}
