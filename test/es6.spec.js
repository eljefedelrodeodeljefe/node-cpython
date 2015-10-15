'use strict'
var expect = require('chai').expect
var cpython = require('../src/es6/cpython')

describe('CPython class', function () {

  it('Call CPython class', function (done) {
    done()
  });

  it('CPython class does extend EventEmitter', function (done) {
    cpython.on('testevent', function (arg) {
      expect(arg).to.eql('test')
      done()
    })
    cpython.emit('testevent', "test")
  });

  it('Throws errors through EventEmitter if more than 2 args', function (done) {
      cpython.on('error', function(err) {
        expect(err).to.be.an.instanceof(Error)
        done()
      })
      cpython.simpleFile('someargument1', 'someargument2', 'someargument3')
  });

  it('Throws no error with less than 3 args', function (done) {
      cpython.on('error', function(err) {
        expect(err).to.be.undefined;
      })
      cpython.simpleFile('someargument1','some')
      done()
  });

  it('Globbing: return Array with only string as input', function (done) {

      var fn = function(err, files) {
        var ar = []
        ar = files
        expect(ar).to.be.instanceof(Array);
        done()
      }
      cpython._getListOfFiles("src/es6/**/*.js", {silent: true} , fn)
  });

  it('Globbing: return Array with array of strings as input', function (done) {

      var fn2 = function(err, files) {
        var ar = []
        ar = files
        expect(ar).to.be.instanceof(Array);
        done()
      }
      cpython._getListOfFiles(["src/es6/**/*.js", "src/es5/**/*.js"], {silent: true} , fn2)
  });


});
