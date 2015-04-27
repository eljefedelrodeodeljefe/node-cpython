'use strict'
var expect = require('chai').expect

describe('Test functionality as a module', function () {
  it('Require the module', function (done) {

    let e = require('../../index.js')
    //let d = new e();
    //e.hello()
    class Hello {

    }
    let hello = new Hello()
    done()
  });
  it('another instantiation test', function (done) {
    var e = require('../../index.js')
    e.hello()
    done()
  });
  it('and another instantiation test', function (done) {
    require('../../index.js')()
    var d = new Emscripten()
    d.hello()
    done()
  });

});
