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
    v8::Isolate* isolate_ = v8::Isolate::GetCurrent();
    v8::Isolate::Scope isolate_scope(isolate_);

    Local<Object> obj = Object::New(isolate_);
    obj->Set(String::NewFromUtf8(isolate_, "uuid"),
                            String::NewFromUtf8(isolate_, uuid.str().c_str()));
    obj->Set(String::NewFromUtf8(isolate_, "base62"),
                            String::NewFromUtf8(isolate_, uuid.base62().c_str()));
    obj->Set(String::NewFromUtf8(isolate_, "uuidPretty"),
                            String::NewFromUtf8(isolate_, uuid.pretty().c_str()));

    Local<Value> argv[] = {
      Null(),
      obj
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
