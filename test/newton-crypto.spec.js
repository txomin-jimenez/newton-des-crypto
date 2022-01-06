const path = require("path");
const NetwonDES = require(path.resolve(path.join(__dirname, "..")));
const expect = require("chai").expect;

describe("Newton DES Crypto Lib", function () {
  describe("with empty password", function () {
    const emptyPassword = "";

    it("should encrypt a key pair", function () {
      const keyPair = "00783C8C002BB602";

      const keyPairEncrypted = NetwonDES.encrypt(emptyPassword, keyPair);

      expect(keyPairEncrypted).to.equal("D3652DD9AC532CEF");
    });

    it("should decrypt a key pair", function () {
      const keyPairEncrypted = "D3652DD9AC532CEF";

      const keyPairDecrypted = NetwonDES.decrypt(emptyPassword, keyPairEncrypted);

      expect(keyPairDecrypted).to.equal("00783C8C002BB602");
    });
  });

  describe("with a given password", function () {
    const password = "a password";

    it("should encrypt a key pair", function () {
      const keyPair = "FFEDA1DA004464B6";

      const keyPairEncrypted = NetwonDES.encrypt(password, keyPair);

      expect(keyPairEncrypted).to.equal("DBE3ED230BC77EFE");
    });

    it("should decrypt a key pair", function () {
      const keyPairEncrypted = "DBE3ED230BC77EFE";

      const keyPairDecrypted = NetwonDES.decrypt(password, keyPairEncrypted);

      expect(keyPairDecrypted).to.equal("FFEDA1DA004464B6");
    });
  });
});
