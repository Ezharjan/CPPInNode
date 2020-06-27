# CPP Utilization In Node.js Project

### Tutorial

1. npm install node-addon-api --save

<br>

2. add the code below into the packake.json file:
{
  "name": "test-cpp-module",
  "version": "0.1.0",
  "private": true,
  "gypfile": true
}


<br>


3. Create 'binding.gyp' file in the project folder and add the contents below:
{
     "targets": [
    {
      "target_name": "democpp",
      "sources": [
        "democpp.cc"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": ["NAPI_CPP_EXCEPTIONS"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
      }
    }
  ]
}


<br>

4. Create a CPP file and add the functions and methods you want, for example:

```C++

#include <napi.h>

using namespace Napi;

String Hello(const CallbackInfo& info) {
  return String::New(info.Env(), "world");
}
Napi::Object  Init(Env env, Object exports) {
  exports.Set("hello", Function::New(env, Hello));
  return exports;
}
NODE_API_MODULE(addon, Init)

```

<br>

5. npm install

<br>

6. Create a file called 'test.js' to call your functions in it, for example:

const democpp = require("./build/Release/democpp.node");
console.log(democpp.hello());

<br><br><br>

[Reference](https://www.cnblogs.com/andrewwang/p/9409876.html)

------

<p align="right">by Alexander Ezharjan</p>
<p align="right">2020/6/27</p>