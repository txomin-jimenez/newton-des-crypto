var NetwonDES = require('./build/Release/NetwonDES.node');

module.exports = {
    // Encrypt a Newton key pair with received password.
    // Parameters:
    //      (string) password: the password to encrypt
    //      (string) keys: Newton key pair in HEX string format. ex:
    //            '00783C8C002BB602'
    encrypt: function(password, keys) {
      password || (password = '');
      return NetwonDES.encrypt(password, keys);
    },

    // Decrypt a key pair with received password.
    // Parameters:
    //      (string) password: the password used to encrypt
    //      (string) keys: Newton key pair in HEX string format. ex:
    //            '00783C8C002BB602'
    decrypt: function(password, keys) {
      password || (password = '');
      return NetwonDES.decrypt(password, keys);
    }
};