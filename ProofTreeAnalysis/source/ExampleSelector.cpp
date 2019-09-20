// ExampleSelector.h created by Rin Yokoyama on \date September 18, 2019
#include "ExampleSelector.h"

ClassImp(ExampleSelector)

ExampleSelector::ExampleSelector(TTree* tree) :
	tree_reader_(tree),
	data_(tree_reader_, "ExampleData"),
	output_file_name_("default_name"),
	parameter_(0)
{}

ExampleSelector::~ExampleSelector(){
	if (fOutputFile) delete fOutputFile;
}

void ExampleSelector::Begin(TTree* tree) {
	// Begin() is called only in the client process.
	// Get OutputFileName from the list of input objects.
	// This is required when you write a file in the Terminate() method.
	if (fInput) {
		TNamed* named = (TNamed*)fInput->FindObject("OutputFileName");
		if (named)
			output_file_name_ = named->GetTitle();
	}
}

void ExampleSelector::SlaveBegin(TTree* tree) {
	// SlaveBegin() is called only in the worker process when it runs on PROOF.
	// If it's not on PROOF, SlaveBegin() is called after Begin()

	// Create histogram instances.
	if (fHist) delete fHist;
	fHist = new TH1F("h_output_value", "Output Values", 1000, 5, 15);

	// Clear the fOutputList.
	// fOutputList is a list of object which will be merged and sent to the client process.
	GetOutputList()->Clear();

	// Save current TDirectory
	auto savedir = gDirectory;

	if (gProofServ) {
		// If this process is running on a PROOF server, read objects from fInput.
		if (fInput) {
			TNamed* named = (TNamed*)fInput->FindObject("OutputFileName");
			if (named)
				output_file_name_ = named->GetTitle();
			TParameter<Double_t>* parameter = (TParameter<Double_t>*)fInput->FindObject("Parameter");
			if (parameter)
				parameter_ = parameter->GetVal();
			TParameter<Bool_t>* merge_tree = (TParameter<Bool_t>*)fInput->FindObject("MergeTree");
			if (merge_tree)
				merge_tree_ = merge_tree->GetVal();
		}

		// Create a TProofOutputFile
		if (fProofFile) delete fProofFile;
		if (merge_tree_) {
			// Option "M" to merge files from all the workers at the end
			fProofFile = new TProofOutputFile(output_file_name_.c_str(), "M");
		}
		else {
			// Without "M" not to merge output
			fProofFile = new TProofOutputFile(output_file_name_.c_str(), "");
			// Add histograms to the fOutputList to merge them in the client process.
			GetOutputList()->Add(fHist);
		}
			
		// Open an output file for this worker.
		fProofFile->SetOutputFileName(output_file_name_.c_str());
		if (fOutputFile) delete fOutputFile;
		fOutputFile = fProofFile->OpenFile("RECREATE");

		// You can send a message to the client process from workers by using SendAsynMessage()
		const TString msg = TString::Format("SalveBegin() of Ord = %s is called.", gProofServ->GetOrdinal());
		gProofServ->SendAsynMessage(msg);
	}
	else {
		// If it's not on PROOF, just create a new file.
		if (fOutputFile) delete fOutputFile;
		fOutputFile = new TFile(output_file_name_.c_str(), "RECREATE");
	}

	// Create an output tree.
	if (fOutputTree) delete fOutputTree;
	fOutputTree = new TTree("OutputTree", "OutputTree");
	fOutputTree->Branch("output_data",&output_value_,"output_data/D");
	fOutputTree->SetDirectory(fOutputFile);
	fOutputTree->AutoSave();

	// Recover the current directory.
	gDirectory = savedir;
}

void ExampleSelector::Init(TTree* tree) {
	// Init() is called when the selector needs to initialize a new tree
	// According to the ROOT documentation, the tree argument of the Begin() 
	// and SlaveBegin() functions is deprecated.
	// Therefore, SetTree() should be called in this function.
	tree_reader_.SetTree(tree);
}

Bool_t ExampleSelector::Process(Long64_t entry) {
	// Process() is called for each entry in the tree.
	// This function should contain the body of the analysis.

	tree_reader_.SetLocalEntry(entry);

	// "data" is a pointer to the ExampleData branch object.
	auto data = data_.Get();
	if (!data) return kTRUE;

	// Call CalculateOutputValue() function
	CalculateOutputValue(data->GetData());

	// Fill the tree and the histogram
	fOutputTree->Fill();
	fHist->Fill(output_value_);

	return kTRUE;
}

void ExampleSelector::SlaveTerminate() {
	// SlaveTerminate() is called after all entries have been processed.
	// This function is called only in the worker process.
	// If it's not on PROOF, SlaveTerminate() is called before Terminate()

	// Unlink the tree reader from the input tree.
	tree_reader_.SetTree((TTree*)nullptr);

	// Write the tree and the histogram to file.
	auto savedir = gDirectory;
	fOutputFile->cd();
	fOutputTree->Write();
	fHist->Write();

	// If merge_tree_ flag is true, add the file to the fOutput
	// so the files from all the workers will be merged.
	if(merge_tree_)
		fOutput->Add(fProofFile);

	// Close the file.
	fOutputTree->SetDirectory(0);
	fOutputFile->Close();
	gDirectory = savedir;
	delete fOutputFile;
	fOutputFile = nullptr;
}

void ExampleSelector::Terminate() {
	// Terminate() is called only in the client process

	// If there is a histogram in the output list (i.e. merge_tree_ = false),
	// create a file in the client process and write it to the file.
	auto hist = GetOutputList()->FindObject("h_output_value");
	if (hist) {
		fOutputFile = TFile::Open(output_file_name_.c_str(), "UPDATE");
		hist->Write();
		fOutputFile->Close();
	}
}

void ExampleSelector::CalculateOutputValue(const Double_t& input_data) {
	// The function where you define calculations you want to operate on the data
	output_value_ = input_data + parameter_;
}

