// ExampleTwoDataClass.h created by Rin Yokoyama on \date April 17, 2023
// These are example data container classes.
// This is intended to demonstrate how to generate a ROOT dictionary for custom classes.

#ifndef ROOT_EXAMPLES_EXAMPLE_TWO_DATA_CLASS_H
#define ROOT_EXAMPLES_EXAMPLE_TWO_DATA_CLASS_H
#include "TObject.h"

// Data container with two values as an example of input data
class ExampleTwoDataClass : public TObject
{
public:
	// Default constructor
	ExampleTwoDataClass() : data1_(0), data2_(0) {}
	// Copy constructor
	ExampleTwoDataClass(const ExampleTwoDataClass &object) : TObject(object), data1_(object.GetData1()), data2_(object.GetData2()) {}
	// Constructor with data values
	ExampleTwoDataClass(const Double_t &data1, const Double_t &data2) : data1_(data1), data2_(data2) {}
	// Destructor
	virtual ~ExampleTwoDataClass() {}

	void SetData(const Double_t &data1, const Double_t &data2)
	{
		data1_ = data1;
		data2_ = data2;
	}
	Double_t GetData1() const { return data1_; }
	Double_t GetData2() const { return data2_; }

protected:
	// Main data values
	Double_t data1_;
	Double_t data2_;

	ClassDef(ExampleTwoDataClass, 1)
};

// Data container with one value as an example of output data
class ExampleOutputDataClass : public TObject
{
public:
	// Default constructor
	ExampleOutputDataClass() : data_(0) {}
	// Copy constructor
	ExampleOutputDataClass(const ExampleOutputDataClass &object) : TObject(object), data_(object.GetData()) {}
	// Constructor with data values
	ExampleOutputDataClass(const Double_t &data) : data_(data) {}
	// Destructor
	virtual ~ExampleOutputDataClass() {}

	Double_t GetData() const { return data_; }
	void SetData(const Double_t &data) { data_ = data; }

protected:
	Double_t data_;

	ClassDef(ExampleOutputDataClass, 1)
};
#endif
