// RDataFrameAnalysis.cpp created by Rin Yokoyama on \date April 18, 2023
// This program generates root files with a tree containing a branch of the ExampleTwoDataClass.
// named "ExampleData". ExampleData.data1_ and data2_ will be filled with random Gaussian events.
#include <iostream>
#include "TROOT.h"
#include "ROOT/RDataFrame.hxx"
#include "ExampleTwoDataClass.h"

// The number of workers
const UInt_t kNWorkers = 4U;

// main function
int main(int argc, char **argv)
{
	// Set multithreading
	ROOT::EnableImplicitMT(kNWorkers);
	// Create RDataFrame from a tree, "exampleTree" in the "example.root" file.
	ROOT::RDataFrame d("exampleTree", "example.root");

	// Definition of an output data object
	ExampleOutputDataClass outputData;

	// Your custom function to process input data and return modified outputData.
	// Both inputs and outputs are defined as your own class named
	// ExampleTwoDataClass and ExampleOutputDataClass
	const auto exampleFunction = [&outputData](const ExampleTwoDataClass &input)
	{
		// This example just fills the sum of data1 and data2 to the output object.
		outputData.SetData(input.GetData1() + input.GetData2());
		return outputData;
	};

	// Process tree
	auto output = d.Define("output", exampleFunction, {"ExampleData"});

	// Filling to a histogram
	// If you want to plot a value in your class, you need to first Define()
	// a column with the value then Histo1D().
	// A lambda function is used to return Double_t value of the output branch.
	// Histogram definition is {"name","title",nbin,low,up} or simply "name"
	// for auto filling.
	auto hist = output.Define(
						  "value", [](const ExampleOutputDataClass &output)
						  { return output.GetData(); },
						  {"output"})
					.Histo1D({"hist", "title", 300, -3, 3}, "value");
	// Fit histogram with gaussian
	hist->Fit("gaus");
	std::cout << "\n Fit result of the sum of data1 and data2.\nThe sigma should be ~sqrt(2).\n"
			  << std::endl;

	// Save outputTree to a file
	output.Snapshot("outputTree", "output.root");

	// Your custom cut function
	// It returns true if data1 is grater than 1.
	const auto exampleCut = [](const ExampleTwoDataClass &input)
	{
		return input.GetData1() > 1;
	};

	// Count total number of events processed
	auto total = d.Count();
	// Count number of events filtered by your cut
	auto c = d.Filter(exampleCut, {"ExampleData"}).Count();
	// Print counts (total/c are not numbers. use *total/*c)
	std::cout << *c << "/" << *total << " (should be ~16%, ratio over 1sigma on one side)" << std::endl;

	return 0;
}
