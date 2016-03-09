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

  Local<v8::String> result = Nan::MaybeLocal<v8::String>(Nan::New<String>(uuid.str())).ToLocalChecked();

  info.GetReturnValue().Set(result);
}
