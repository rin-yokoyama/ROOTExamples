// ExampleTwoDataClass.h created by Rin Yokoyama on \date April 117, 2023
// This is an example data container classes.
// This is intended to show how to generate a ROOT dictionary for your own class.

#ifndef ROOT_EXAMPLES_EXAMPLE_TWO_DATA_CLASS_H
#define ROOT_EXAMPLES_EXAMPLE_TWO_DATA_CLASS_H
#include "TObject.h"

// data container with two values as an example of input data
class ExampleTwoDataClass : public TObject
{
public:
	// default constructor
	ExampleTwoDataClass() : data1_(0), data2_(0) {}
	// copy constructor
	ExampleTwoDataClass(const ExampleTwoDataClass &object) : TObject(object), data1_(object.GetData1()), data2_(object.GetData2()) {}
	// constructor with data values
	ExampleTwoDataClass(const Double_t &data1, const Double_t &data2) : data1_(data1), data2_(data2) {}
	// destractor
	virtual ~ExampleTwoDataClass() {}

	void SetData(const Double_t &data1, const Double_t &data2)
	{
		data1_ = data1;
		data2_ = data2;
	}
	Double_t GetData1() const { return data1_; }
	Double_t GetData2() const { return data2_; }

protected:
	// main data values
	Double_t data1_;
	Double_t data2_;

	ClassDef(ExampleTwoDataClass, 1)
};

// data container with one value as an example output data
class ExampleOutputDataClass : public TObject
{
public:
	// default constructor
	ExampleOutputDataClass() : data_(0) {}
	// copy constructor
	ExampleOutputDataClass(const ExampleOutputDataClass &object) : TObject(object), data_(object.GetData()) {}
	// constructor with data values
	ExampleOutputDataClass(const Double_t &data) : data_(data) {}
	// destractor
	virtual ~ExampleOutputDataClass() {}

	Double_t GetData() const { return data_; }

protected:
	Double_t data_;

	ClassDef(ExampleOutputDataClass, 1)
};
#endif
