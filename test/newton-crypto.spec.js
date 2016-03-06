/*jshint expr: true*/

var path = require( 'path' );
var NewtonUDesCrypto = require( path.resolve( path.join( __dirname, '..' ) ) );
var expect = require( 'chai' ).expect;
var net = require('net');


describe('Newton Crypto Lib', function( done ) {

    //before(function() {
      //// runs before all tests in this block
    //});
    
    it('should encrypt a block with empty password', function() {
     global.data = '00783C8C002BB602'; 
     global.pwd = '';
     global.dataEncrypted = NewtonUDesCrypto.encryptBlock(pwd, data); 
     expect(global.dataEncrypted).to.equal('D3652DD9AC532CEF');
    });
    
    it('should decrypt a block with empty password', function() {
      decryptedData = NewtonUDesCrypto.decryptBlock(pwd,dataEncrypted);
      expect(decryptedData).to.equal(data);
    });

    it('should encrypt a block', function() {
     global.data = 'FFEDA1DA004464B6'; 
     global.pwd = 'tjd';
     global.dataEncrypted = NewtonUDesCrypto.encryptBlock(pwd, data); 
     expect(global.dataEncrypted).to.equal('C5D6849E47034D2F');
    });
    
    it('should decrypt a block', function() {
      decryptedData = NewtonUDesCrypto.decryptBlock(pwd,dataEncrypted);
      expect(decryptedData).to.equal(data);
    });

    //after(function() {
    //});
});
