// ExampleDataClass.h created by Rin Yokoyama on \date September 18, 2019
// This is an example data container with just a single double value.
// This is intended to show how to generate a ROOT dictionary for your own class.

#ifndef ROOT_EXAMPLES_EXAMPLE_DATA_CLASS_H
#define ROOT_EXAMPLES_EXAMPLE_DATA_CLASS_H
#include "TObject.h"

class ExampleDataClass : public TObject {
public:
	// default constructor
	ExampleDataClass() : data_(0) {}
	// copy constructor
	ExampleDataClass(const ExampleDataClass& object) : TObject(object), data_(object.GetData()) {}
	virtual ~ExampleDataClass() {}

	void SetData(const Double_t& data) { data_ = data; }
	Double_t GetData() const { return data_; }

protected:
	// main data value
	Double_t data_;

	ClassDef(ExampleDataClass,1)
};

#endif
