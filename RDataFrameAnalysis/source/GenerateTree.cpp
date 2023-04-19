// GenerateTree.cpp created by Rin Yokoyama on \date April 18, 2019
// This program generates ROOT files with a tree containing a branch of the ExampleTwoDataClass.
// named "ExampleData". ExampleData.data1_ and data2_ will be filled with random Gaussian events.
#include <iostream>
#include "TROOT.h"
#include "TRandom3.h"
#include "ROOT/RDataFrame.hxx"
#include "ExampleTwoDataClass.h"

// Total number of entries to fill
const UInt_t kNumbers = 1000000U;
// Number of workers
const UInt_t kNWorkers = 10U;

// Main function
int main(int argc, char **argv)
{
	ROOT::EnableImplicitMT(kNWorkers);
	// Create random number generators with random seeds.
	TRandom3 rand1(0); // explicitly set 0 for a random seed.
	TRandom3 rand2(0);
	// Create an RDataFrame object with kNumbers entries.
	ROOT::RDataFrame d(kNumbers);
	// Define ExampleData branch by filling it with random Gaussian events using the
	// lambda function.
	d.Define("ExampleData", [&rand1, &rand2]()
			 { return ExampleTwoDataClass(rand1.Gaus(), rand2.Gaus()); })
		// Save the tree with the generated data to "example.root" file.
		.Snapshot("exampleTree", "example.root");
	return 0;
}
