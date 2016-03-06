{
  "targets": [
    {
      "target_name": "uDesCrypto",
      "sources": [ 
        "src/KDefinitions.cc",
        "src/main.cc",
        "src/TInt64.cc",
        "src/TSInt64.cc",
        "src/TUInt64.cc",
        "src/UTInt64.cc",
        "src/UDES.cc",
        "src/UDESTables.cc",
        "src/UUTF16CStr.cc",
        "src/UUTF16Conv.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags": ["-std=c++11", "-DTARGET_OS_OPENSTEP=1"],
      "conditions": [
        [ 'OS!="win"', {
          "cflags+": [ "-std=c++11" , "-DTARGET_OS_OPENSTEP=1"],
          "cflags_c+": [ "-std=c++11" , "-DTARGET_OS_OPENSTEP=1"],
          "cflags_cc+": [ "-std=c++11" , "-DTARGET_OS_OPENSTEP=1"],
        }],
        [ 'OS=="mac"', {
          "xcode_settings": {
            "OTHER_CPLUSPLUSFLAGS" : [ "-std=c++11", "-stdlib=libc++" , "-DTARGET_OS_OPENSTEP=1"],
            "OTHER_LDFLAGS": [ "-stdlib=libc++" , "-DTARGET_OS_OPENSTEP=1"],
            "MACOSX_DEPLOYMENT_TARGET": "10.7"
          },
        }],
      ]
    }
  ]
}
