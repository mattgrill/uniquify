#include <nan.h>
#include "functions.h"  // NOLINT(build/include)

using v8::FunctionTemplate;
using v8::Handle;

using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

// Expose synchronous and asynchronous access to our
// Estimate() function
NAN_MODULE_INIT(InitAll) {
  Set(target, New<String>("generate").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(Generate)).ToLocalChecked());

  Set(target, New<String>("generateSync").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(GenerateSync)).ToLocalChecked());
}

NODE_MODULE(uniquify, InitAll)
