#pragma once

#include <string>
#include <vector>

struct DataShape {
public:
  DataShape()
    : has_output_field(true),
      output_field_name("") {
  }
public:
  bool has_output_field;
  std::vector<std::string> input_field_names;
  std::vector<std::string> input_types;
  std::string output_field_name;
  std::string output_type;
};

struct Value {
protected:
  Value()
    : type("") {
  }
public:
  virtual ~Value() {};
public:
  std::string type;
};

template<typename T>
struct ValueImpl : public Value {
  T v;
};

struct DataEntry {
public:
  DataEntry()
    : data_shape(nullptr),
      output_value(nullptr) {
  }
  virtual ~DataEntry() {
    // CAUTION: Do not delete shape. Data entry is not shape owner.
    for (uint32_t i = 0; i < input_values.size(); i++) {
      delete input_values[i];
    }
    input_values.clear();
    if (output_value) {
      delete output_value;
    }
  }
public:
  DataShape *data_shape;
  std::vector<Value *> input_values;
  Value *output_value;
};

struct DataSet {
public:
  DataSet()
    : data_shape(nullptr) {
  }
  virtual ~DataSet() {
    if (data_shape) {
      delete data_shape;
    }
    for (uint32_t i = 0; i < data_entries.size(); i++) {
      delete data_entries[i];
    }
    data_entries.clear();
  }
public:
  DataShape *data_shape;
  std::vector<DataEntry *> data_entries;
};