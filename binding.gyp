{
  "targets": [
    {
      "target_name": "uniquify",
      "sources": [
        "src/main.cc",
        "src/generate.cc"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "conditions": [
        [
          'OS=="mac"',
          {
            'xcode_settings': {
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
              'OTHER_CPLUSPLUSFLAGS' : [
                '-std=c++11',
                '-stdlib=libc++',
                '-Wno-mismatched-tags'
              ],
              'OTHER_LDFLAGS': ['-stdlib=libc++'],
              'MACOSX_DEPLOYMENT_TARGET': '10.7',
              'LIBTOOLIZE': 'glibtoolize'
            }
          }
        ]
      ]
    }
  ]
}
