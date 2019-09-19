// ExampleSelector.h created by Rin Yokoyama on \date September 18, 2019
// This is an example class for analyzing a TTree data using TSelector class.
// It fills a histogram and a new output Tree with the output_value_
// which is input_value + parameter_
// It can be run either on PROOF or as a local process.
// This example shows how to output histograms and trees when it runs on PROOF
// and how to receive arguments from the client session.
#ifndef ROOT_EXAMPLES_EXAMPLE_SELECTOR_H
#define ROOT_EXAMPLES_EXAMPLE_SELECTOR_H
#include <iostream>
#include <string>
#include "TSelector.h"
#include "TTree.h"
#include "TProofServ.h"
#include "TProofOutputFile.h"
#include "TFile.h"
#include "TParameter.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TH1.h"
#include "ExampleDataClass.h"

class ExampleSelector : public TSelector {
public:
	ExampleSelector(TTree* tree = 0);
	virtual ~ExampleSelector();

	// Overloaded from TSelector
	virtual Int_t   Version() const { return 1; }
	virtual void    Init(TTree* tree);
	virtual void    Begin(TTree* tree);
	virtual void    SlaveBegin(TTree* tree);
	virtual Bool_t  Notify() {std::cout << "Notify() called." << std::endl;  return kTRUE; }
	virtual Bool_t  Process(Long64_t entry);
	virtual void    SetOption(const char* option) { fOption = option; }
	virtual void    SetObject(TObject* obj) { fObject = obj; }
	virtual void    SetInputList(TList* input) { fInput = input; }
	virtual TList*	 GetOutputList() const { return fOutput; }
	virtual void    SlaveTerminate();
	virtual void    Terminate();

	// Set methods
	void SetOutputFileName(const std::string& name) { output_file_name_ = name; }
	void SetParameter(const Double_t& parameter) { parameter_ = parameter; }

protected:
	TTreeReader tree_reader_; // TTreeReader for the input tree
	TTreeReaderValue<ExampleDataClass> data_; // TTreeReaderValue for the input data branch
	Double_t output_value_; // The output value that will be filled to the output tree.
	TTree* fOutputTree = nullptr; // A pointer to the output tree object
	TFile* fOutputFile = nullptr; // A pointer to the output file object
	TProofOutputFile* fProofFile = nullptr; // A pointer to the ProofOutputFile object
	TH1F* fHist = nullptr; // A pointer to the output histogram
	std::string output_file_name_; // The output file name
	Double_t parameter_; // An example parameter to process data
	Bool_t merge_tree_ = false; // A flag whether to merge tree output at the end when use PROOF.

	// A function defining the calculation to obtain output values from the input value.
	virtual void CalculateOutputValue(const Double_t &input_value);

	ClassDef(ExampleSelector, 1)
};

#endif
