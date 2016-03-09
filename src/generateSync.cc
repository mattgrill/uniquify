#include <nan.h>
#include "lib/sole/sole.hpp"
#include "functions.h"  // NOLINT(build/include)

using namespace Nan;
using namespace v8;
using namespace std;

NAN_METHOD(GenerateSync) {
  // Expect a number as the first argument
  int version = To<int>(info[0]).FromJust();

  sole::uuid uuid;
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

  v8::Isolate* isolate_ = v8::Isolate::GetCurrent();
  v8::Isolate::Scope isolate_scope(isolate_);

  Local<Object> obj = Object::New(isolate_);
  obj->Set(String::NewFromUtf8(isolate_, "uuid"),
                          String::NewFromUtf8(isolate_, uuid.str().c_str()));

  info.GetReturnValue().Set(obj);
}
