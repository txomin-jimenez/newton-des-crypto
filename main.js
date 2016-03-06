var uDesCryptoNative = require('./build/Release/uDesCrypto.node');
var uDesCrypto;

module.exports = {
    // Encrypt a Newton key pair with received password. 
    // Parameters:
    //      (string) password: the password to encrypt
    //      (string) data: Newton key pair in HEX string format. ex: 
    //            '00783C8C002BB602'
    encryptBlock: function(password, data) {
      password || (password = '');
      return uDesCryptoNative.encryptBlock(password, data);
    },

    // Decrypt a key pair with received password. 
    // Parameters:
    //      (string) password: the password used to encrypt
    //      (string) data: Newton key pair in HEX string format. ex: 
    //            '00783C8C002BB602'
    decryptBlock: function(password, data) {
      password || (password = '');
      return uDesCryptoNative.decryptBlock(password, data);
    
    }

};
