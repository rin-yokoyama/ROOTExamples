// FillGaus.cpp created by Rin Yokoyama on \date September 17, 2019
// This program generates root files with a tree containing a branch of the ExampleTwoDataClass.
// named "ExampleData". ExampleData.data1_ and data2_ will be filled with random Gaussian events.
#include <iostream>
#include "TROOT.h"
#include "TRandom3.h"
#include "ROOT/RDataFrame.hxx"
#include "ExampleTwoDataClass.h"

// Total number of entries to fill
const UInt_t kNumbers = 1000000U;
// The number of workers
const UInt_t kNWorkers = 10U;

// main function
int main(int argc, char **argv)
{
	ROOT::EnableImplicitMT(kNWorkers);
	TRandom3 rand1(0); // explicitly set 0 for a random seed.
	TRandom3 rand2(0);
	ROOT::RDataFrame d(kNumbers);
	d.Define("ExampleData", [&rand1, &rand2]()
			 { return ExampleTwoDataClass(rand1.Gaus(), rand2.Gaus()); })
		.Snapshot("exampleTree", "example.root");
	return 0;
}
