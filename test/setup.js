/*jshint expr: true*/

var path = require( 'path' );
var newtonCrypto = require( path.resolve( path.join( __dirname, '..' ) ) );
var expect = require( 'chai' ).expect;
var net = require('net');

global.testServer = null;

before(function() {
  // runs before all tests in the test suite
});

after(function() {
  // runs after all test in the test suite
});
