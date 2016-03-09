#include <nan.h>
#include "lib/sole/sole.hpp"
#include "functions.h"

// bring in the required namespaces
using namespace Nan;
using namespace v8;
using namespace std;

class UUIDWorker : public AsyncWorker {
 public:
  UUIDWorker(Callback *callback, int version)
    : AsyncWorker(callback), version(version) {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute () {
    switch (version) {
    case 0:
      uuid = sole::uuid0();
      break;
    case 1:
      uuid = sole::uuid1();
      break;
    case 4:
      uuid = sole::uuid4();
      break;
    default:
      uuid = sole::uuid4();
      break;
    }
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    Local<v8::String> result = Nan::MaybeLocal<v8::String>(Nan::New<String>(uuid.str())).ToLocalChecked();

    Local<Value> argv[] = {
      Null(),
      result
    };

    callback->Call(2, argv);

  }

 private:
  int version;
  sole::uuid uuid;
};

// Asynchronous access to the `UUIDWorker()` function
NAN_METHOD(Generate) {
  int version = To<int>(info[0]).FromJust();
  Callback *callback = new Callback(info[1].As<Function>());

  AsyncQueueWorker(new UUIDWorker(callback, version));
}
