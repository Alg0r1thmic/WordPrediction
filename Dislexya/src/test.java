import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;
import weka.core.FastVector;
import weka.core.Instances;
import weka.core.OptionHandler;
import weka.core.Utils;
import weka.filters.Filter;
import weka.classifiers.meta.FilteredClassifier;
import weka.classifiers.evaluation.Prediction;
import weka.classifiers.functions.*;
import weka.classifiers.trees.*;
import weka.filters.unsupervised.attribute.AddID;
import weka.filters.unsupervised.attribute.Remove;
import weka.classifiers.Evaluation;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Vector;
import java.util.Random;

public class test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(
			new FileReader("/home/mmayo/code/learning_words/sets/full_difficult_unique_easy_p10_words_down2.arff"));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//Instances data = null;
		Instances newData = null;
		try {
			newData = new Instances(reader);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			reader.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// setting class attribute
		newData.setClassIndex(newData.numAttributes() - 1);
		
		//System.out.println(data.numInstances() + " " + data.numAttributes());
		
		/*AddID addi = new weka.filters.unsupervised.attribute.AddID();                         // new instance of filter
		addi.setIDIndex("1");                         // set options
		try {
			addi.setInputFormat(data);
		} catch (Exception e4) {
			// TODO Auto-generated catch block
			e4.printStackTrace();
		}                          // inform filter about dataset **AFTER** setting options
		try {
			newData = Filter.useFilter(data, addi);
		} catch (Exception e3) {
			// TODO Auto-generated catch block
			e3.printStackTrace();
		}*/
		
		System.out.println(newData.numInstances() + " " + newData.numAttributes());
		
		SimpleLogistic simpleLogistic = new SimpleLogistic();
		simpleLogistic.setDebug(false);
		simpleLogistic.setErrorOnProbabilities(false);
		simpleLogistic.setHeuristicStop(50);
		simpleLogistic.setMaxBoostingIterations(500);
		simpleLogistic.setNumBoostingIterations(0);
		simpleLogistic.setUseAIC(false);
		simpleLogistic.setUseCrossValidation(true);
		simpleLogistic.setWeightTrimBeta(0.0);
		
		SMO smo = new SMO();
		
		J48 j48 = new J48();
		
		Remove rm = new Remove();
		//rm.setAttributeIndices("1,3,4,6,8,10,11,12,13,14,15,17,18,19,22,23,24");  // remove 1st attribute
		rm.setAttributeIndices("1");  // remove 1st attribute
		// meta-classifier
		FilteredClassifier fc = new FilteredClassifier();
		fc.setFilter(rm);
		//fc.setClassifier(simpleLogistic);
		fc.setClassifier(j48);
		
		Evaluation eval = null;
		try {
			eval = new Evaluation(newData);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		StringBuffer forPredictionsPrinting = new StringBuffer();
	    weka.core.Range attsToOutput = new weka.core.Range("1");
	    Boolean outputDistribution = new Boolean(true);
	    try {
			eval.crossValidateModel(fc, newData, 10, new Random(1), 
			forPredictionsPrinting, attsToOutput, outputDistribution);
		} catch (Exception e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
		}
		
	    /*try {
			eval.crossValidateModel(simpleLogistic, data, 10, new Random(1));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
	    System.out.println(eval.toSummaryString());
	    try {
			System.out.println(eval.toClassDetailsString());
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	    try {
			System.out.println(eval.toMatrixString());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    
	    System.out.println(forPredictionsPrinting);
	    	    
	    /*for (int i=0; i<fv.size(); i++) {
	    	System.out.print("ID: " + data.instance(i).value(0));
			System.out.print(", actual: " + );
			System.out.println(", predicted: " + data.classAttribute().value((int) pred));
	    }*/
		
		/*for (int i = 0; i < data.numInstances(); i++) {
			   double pred = e.classifyInstance(data.instance(i));
			   System.out.print("ID: " + data.instance(i).value(0));
			   System.out.print(", actual: " + data.classAttribute().value((int) data.instance(i).classValue()));
			   System.out.println(", predicted: " + data.classAttribute().value((int) pred));
			}*/

	}

}
