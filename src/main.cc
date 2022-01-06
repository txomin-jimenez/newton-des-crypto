#include <nan.h>
#include "UDES.h"
#include "UTInt64.h"
#include "UUTF16CStr.h"

// -------------------------------------------------------------------- //
// Encrypt a Newton key pair with received password.
// Parameters:
//      (string) password: the password to encrypt
//      (string) keys: Newton key pair in HEX string format. ex:
//            '00783C8C002BB602'
// -------------------------------------------------------------------- //
void Encrypt(const Nan::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate* isolate = args.GetIsolate();

  // get input password
  v8::String::Utf8Value passwordArg(isolate, args[0]);
  const char *password = std::string(*passwordArg).c_str();

  // generate UDES key for encryption
  KUInt16 passwordUTF16[16];
  KUInt64 encryptionKey;
  UUTF16CStr::FromASCII((const KUInt8*) password, passwordUTF16, 16);
  UDES::CreateNewtonKey(passwordUTF16, &encryptionKey);

  // process input key pair received as HEX String
  KUInt64 keysBlock;
  v8::String::Utf8Value keysArg(isolate, args[1]);
  std::string keysStr = std::string(*keysArg);
  unsigned int key1 = std::stoul (keysStr.substr(0,8),nullptr,16);
  unsigned int key2 = std::stoul (keysStr.substr(8,8),nullptr,16);
  UTInt64::Set(&keysBlock, key1, key2);

  // (void) ::printf("input key1 -> %s\n", s2.substr(0,8).c_str());
  // (void) ::printf("input key2 -> %s\n", s2.substr(8,8).c_str());
  // (void) ::printf("input key -> %.8X%.8X\n", key1, key2);

  UDES::NewtonEncodeBlock(encryptionKey, &keysBlock);

  // (void) ::printf(
  //       "encrypted key -> '%.8X%.8X'\n",
  //       (unsigned int) UTInt64::GetHi(theBlock),
  //       (unsigned int) UTInt64::GetLo(theBlock) );

  char encryptedKeysChar[17];
  std::sprintf(encryptedKeysChar, "%.8X%.8X",
        (unsigned int) UTInt64::GetHi(keysBlock),
        (unsigned int) UTInt64::GetLo(keysBlock) );

  std::string encryptedKeys(encryptedKeysChar);
  args.GetReturnValue().Set(Nan::New(encryptedKeys).ToLocalChecked());
}

// -------------------------------------------------------------------- //
// Decrypt a key pair with received password.
// Parameters:
//      (string) password: the password used to encrypt
//      (string) keys: Newton key pair in HEX string format. ex:
//            '00783C8C002BB602'
// -------------------------------------------------------------------- //
void Decrypt(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  // get input password
  v8::String::Utf8Value passwordArg(isolate, args[0]);
  const char *password = std::string(*passwordArg).c_str();

  // generate UDES key for decryption
  KUInt16 passwordUTF16[16];
  KUInt64 decryptionKey;
  UUTF16CStr::FromASCII((const KUInt8*) password, passwordUTF16, 16);
  UDES::CreateNewtonKey(passwordUTF16, &decryptionKey);

  // process input key pair received as HEX String
  KUInt64 keysBlock;
  v8::String::Utf8Value keysArg(isolate, args[1]);
  std::string keysStr = std::string(*keysArg);
  unsigned int key1 = std::stoul (keysStr.substr(0,8),nullptr,16);
  unsigned int key2 = std::stoul (keysStr.substr(8,8),nullptr,16);

  UTInt64::Set(&keysBlock, key1, key2);
  //(void) ::printf("input key -> %.8X%.8X\n", key1, key2);

  UDES::NewtonDecodeBlock(decryptionKey, &keysBlock);

  //(void) ::printf(
        //"decrypted key -> %.8X%.8X\n",
        //(unsigned int) UTInt64::GetHi(theBlock),
        //(unsigned int) UTInt64::GetLo(theBlock) );

  char decryptedKeysChar[17];
  std::sprintf(decryptedKeysChar, "%.8X%.8X",
        (unsigned int) UTInt64::GetHi(keysBlock),
        (unsigned int) UTInt64::GetLo(keysBlock) );

  std::string decryptedKeys(decryptedKeysChar);
  args.GetReturnValue().Set(Nan::New(decryptedKeys).ToLocalChecked());
}

// -------------------------------------------------------------------- //
//   Init Node Module export functions
// -------------------------------------------------------------------- //
void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = exports->CreationContext();
  exports->Set(context,
               Nan::New("encrypt").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Encrypt)
                   ->GetFunction(context)
                   .ToLocalChecked());
  exports->Set(context,
               Nan::New("decrypt").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Decrypt)
                   ->GetFunction(context)
                   .ToLocalChecked());
}

NODE_MODULE(NetwonDES, Init)