# NewtonDESCrypto

Newton variant of DES encrpytion algorithm for NodeJS. [As it has been found](http://newtontalk.newtontalk.narkive.com/U6dNGqJw/newton-dock-password), Newton OS has it's own implementation of DES encryption, so any try to implement Dock password exchange using standard DES will fail.

This module uses a C++ implementation from Paul Guyot ( [Kallisys](http://www.kallisys.com) )  with small modifications in order to compile a node native addon.


## Installation

```
$ npm install --save newton-des-crypto
```

## Usage

```js
NewtonDesCrypto = require('newton-des-crypto');
pwd = "apassword";
dataEncrypted = NewtonDesCrypto.encryptBlock(pwd, '00783C8C002BB602'); 
decryptedData = NewtonDesCrypto.decryptBlock(pwd, dataEncrypted);
```

## Tests

Unit test available via:
```
$ grunt test
```

## License

Portions of C++ code for Int64 manipulation, UniCode Strings, and DES Encryption created by original author are Copyright (C) 2001-2004, Paul Guyot. All Rights Reserved.

Main C++ module class and NodeJs module are 
Copyright (c) 2016, Txomin Jimenez

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
