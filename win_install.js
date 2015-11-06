var spawn = require('child_process').spawn;
var os = require('os').type();
var cp = spawn('CMD', ['/S','/C', 'node', "test.js"]);

if (os === 'Windows_NT') {
  console.log('Hellow Windows_NT');
}

cp.stdout.on("data", function(data) {
    console.log(data.toString());
});

cp.stderr.on("data", function(data) {
    console.error(data.toString());
});
