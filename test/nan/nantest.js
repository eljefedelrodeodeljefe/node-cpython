var addon = require('./build/Release/nantest');


describe('Testing that nan works on the system.', function () {
  it('Test Nan at the end', function (done) {
    console.log('something else', addon.nantest()); // 'world'
  });
});
