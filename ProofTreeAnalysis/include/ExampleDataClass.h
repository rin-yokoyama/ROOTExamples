#ifndef ROOT_EXAMPLES_EXAMPLE_DATA_CLASS_H
#define ROOT_EXAMPLES_EXAMPLE_DATA_CLASS_H
#include "TObject.h"

class ExampleDataClass : public TObject {
public:
	ExampleDataClass() : data_(0) {}
	ExampleDataClass(const ExampleDataClass& object) : TObject(object), data_(object.GetData()) {}
	virtual ~ExampleDataClass() {}

	void SetData(const Double_t& data) { data_ = data; }
	Double_t GetData() const { return data_; }

protected:
	Double_t data_;

	ClassDef(ExampleDataClass,1)
};

#endif
