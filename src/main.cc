#include <nan.h>
#include "UDES.h"
#include "UTInt64.h"
#include "UUTF16CStr.h"

// -------------------------------------------------------------------- //
// Encrypt a Newton key pair with received password. 
// Parameters:
//      (string) password: the password to encrypt
//      (string) data: Newton key pair in HEX string format. ex: 
//            '00783C8C002BB602'
// -------------------------------------------------------------------- //
void EncryptBlock(const Nan::FunctionCallbackInfo<v8::Value>& args) {
    
    // get input password
    v8::String::Utf8Value cmd(args[0]);
    std::string s = std::string(*cmd); 
    const char *thePassword = s.c_str();
   
    // generate UDES key for encryption 
    KUInt16 theUTF16Password[16];
    KUInt64 theKey;
    UUTF16CStr::FromASCII( (const KUInt8*) thePassword, theUTF16Password, 16 );
    UDES::CreateNewtonKey( theUTF16Password, &theKey );

    // process input key pair received as HEX String
    KUInt64 theBlock;
    v8::String::Utf8Value cmd2(args[1]);
    std::string s2 = std::string(*cmd2); 
    unsigned int key1 = std::stoul (s2.substr(0,8),nullptr,16);
    unsigned int key2 = std::stoul (s2.substr(8,8),nullptr,16);
    
    //(void) ::printf("input key1 -> %s\n", s2.substr(0,8).c_str());
    //(void) ::printf("input key2 -> %s\n", s2.substr(8,8).c_str());
    //(void) ::printf("input key -> %.8X%.8X\n", key1, key2);
    
    //UTInt64::Set( &theBlock, 0x000f1f6b, 0xff82ddcb );
    //UTInt64::Set( &theBlock, 0x06622230, 0x05804779 );
    //UTInt64::Set( &theBlock, 0xFF8A5C97, 0x006DD480 );
    //UTInt64::Set( &theBlock, 0xFFEDA1DA, 0x004464B6 );
    //UTInt64::Set( &theBlock, 0x00783C8C, 0x002BB602 );
    UTInt64::Set( &theBlock, key1, key2);
    
    UDES::NewtonEncodeBlock( theKey, &theBlock );
    
    //(void) ::printf(
          //"encrypted key -> %.8X%.8X\n",
          //(unsigned int) UTInt64::GetHi(theBlock),
          //(unsigned int) UTInt64::GetLo(theBlock) );
    
    char encryptedKeys[16];
    std::sprintf(encryptedKeys, "%.8X%.8X",
          (unsigned int) UTInt64::GetHi(theBlock),
          (unsigned int) UTInt64::GetLo(theBlock) );

    std::string returnValue(encryptedKeys);
    //args.GetReturnValue().Set(Nan::New("world").ToLocalChecked());
    args.GetReturnValue().Set(Nan::New(returnValue).ToLocalChecked());
    
}

// -------------------------------------------------------------------- //
// Decrypt a key pair with received password. 
// Parameters:
//      (string) password: the password used to encrypt
//      (string) data: Newton key pair in HEX string format. ex: 
//            '00783C8C002BB602'
// -------------------------------------------------------------------- //
void DecryptBlock(const Nan::FunctionCallbackInfo<v8::Value>& args) {
    
    // get input password
    v8::String::Utf8Value cmd(args[0]);
    std::string s = std::string(*cmd); 
    const char *thePassword = s.c_str();
   
    // generate UDES key for decryption 
    KUInt16 theUTF16Password[16];
    KUInt64 theKey;
    UUTF16CStr::FromASCII( (const KUInt8*) thePassword, theUTF16Password, 16 );
    UDES::CreateNewtonKey( theUTF16Password, &theKey );

    // process input key pair received as HEX String
    KUInt64 theBlock;
    v8::String::Utf8Value cmd2(args[1]);
    std::string s2 = std::string(*cmd2); 
    unsigned int key1 = std::stoul (s2.substr(0,8),nullptr,16);
    unsigned int key2 = std::stoul (s2.substr(8,8),nullptr,16);
    
    //(void) ::printf("input key -> %.8X%.8X\n", key1, key2);
    
    UTInt64::Set( &theBlock, key1, key2);
    
    UDES::NewtonDecodeBlock( theKey, &theBlock );
    
    //(void) ::printf(
          //"decrypted key -> %.8X%.8X\n",
          //(unsigned int) UTInt64::GetHi(theBlock),
          //(unsigned int) UTInt64::GetLo(theBlock) );
    
    char decryptedKeys[16];
    std::sprintf(decryptedKeys, "%.8X%.8X",
          (unsigned int) UTInt64::GetHi(theBlock),
          (unsigned int) UTInt64::GetLo(theBlock) );

    std::string returnValue(decryptedKeys);
    args.GetReturnValue().Set(Nan::New(returnValue).ToLocalChecked());
    
}

// -------------------------------------------------------------------- //
//   Init Node Module export functions
// -------------------------------------------------------------------- //
void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("encryptBlock").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(EncryptBlock)->GetFunction());
    exports->Set(Nan::New("decryptBlock").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DecryptBlock)->GetFunction());
}

NODE_MODULE(uDesCrypto, Init)
