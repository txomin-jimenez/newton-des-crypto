{
  "targets": [
    {
      "target_name": "NetwonDES",
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
      "cflags": ["-std=c++11", "-DTARGET_OS_LINUX=1"],
      "conditions": [
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
