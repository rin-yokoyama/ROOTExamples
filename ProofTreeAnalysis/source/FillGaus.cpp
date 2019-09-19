// FillGaus.cpp created by Rin Yokoyama on \date September 17, 2019
// This program generates root files with a tree containing a branch of the ExampleDataClass.
// named "ExampleData". ExampleData.data_ will be filled with random Gaussian events.
#include <iostream>
#include <vector>
#include <thread>
#include "TROOT.h"
#include "ROOT/TSeq.hxx"
#include "TFile.h"
#include "TRandom3.h"
#include "TTree.h"
#include "ExampleDataClass.h"

// Total number of entries to fill
const UInt_t kNumbers = 1000000U;
// The number of workers
const UInt_t kNWorkers = 2U;
// Number of entries to fill per worker
const auto kWorkSize = kNumbers / kNWorkers;

// An example function to fill data to the tree with random Gaussian events.
void FillData(TTree& tree, TRandom3& rand, ExampleDataClass &data, const UInt_t n) {
	for (auto i : ROOT::TSeqI(n)) {
		data.SetData(rand.Gaus());
		tree.Fill();
	}
}

// main function
int main(int argc, char** argv) {
	// Switch to the batch mode.
	gROOT->SetBatch();
	// Make ROOT thread-aware.
	ROOT::EnableThreadSafety();

	// Definition of the work item
	// Open a file, fill data to a tree, and write it to the file.
	auto work_item = [](UInt_t worker_id) {
		TRandom3 random(worker_id);
		TFile output_file(Form("example_tree_%u.root", worker_id), "RECREATE");
		TTree tree("ExampleTree", "example tree");
		ExampleDataClass data;
		tree.Branch("ExampleData", "ExampleDataClass", &data);
		FillData(tree, random, data, kWorkSize);
		tree.Write();
		output_file.Close();
		return 0;
	};

	// Create a pool and fill it with workers.
	std::vector<std::thread> workers;
	for (auto worker_id : ROOT::TSeqI(kNWorkers)) {
		workers.emplace_back(work_item, worker_id);
	}

	// Start working!
	for (auto&& worker : workers) {
		worker.join();
	}

	return 0;
}
