'use strict'var gulp = require("gulp");var babel = require("gulp-babel");var mocha = require('gulp-mocha');var gutil = require('gulp-util');var git = require('gulp-git');var del = require('del');var fs = require("fs");var gulpJsdoc2md = require("gulp-jsdoc-to-markdown");var concat = require("gulp-concat");// =============================================================================// ================================= Build:lib =================================// =============================================================================gulp.task("cpython:2.7:clone", function () {  let opts = { args: '-b 2.7', cwd: 'deps/2.7', quiet: false, branch: '2.7'};  git.clone('https://github.com/python/cpython',opts , function (err) {    if (err) throw err  });});//TODO: clone 3.4 as well// gulp.task("cpython:3.4:clone", function () {//   let opts = { args: '-b 3.4', cwd: 'deps/cpython/3.4', quiet: false};//   git.clone('https://github.com/python/cpython',opts , function (err) {//     if (err) throw err//   });// });//TODO: Del in 3.4 as wellgulp.task('cpython:2.7:clean', function (cb) {  del([    '.hg*',    //'**/*.+(in|ac|sub|m4|guess)',    'Doc',    'Demo',    'Riscos',    // TODO: check whether platform specific files actually can be omitted    // 'Mac',    // 'PC',    // HINT: .git is the biggest chunk since it stores the whole tree data    '.git',    '.bzrignore', '.DS_store', '.gitignore'  ], {cwd: 'deps/2.7/cpython'}, cb);});// =============================================================================// ================================= Compile:JS ================================// =============================================================================/****/gulp.task("babel", function () {  return gulp.src("./src/es6/**/*.js")    .pipe(babel())    .pipe(gulp.dest("./src/es5"));});// =============================================================================// ================================= Tests =====================================// =============================================================================/****/gulp.task('mocha', function() {  require('babel/register');  return gulp.src(['test/**/*.spec.js'], { read: false })    .pipe(mocha({      reporter: 'spec',      compilers: 'js:babel/register'//,      //  globals: {      //   should: require('chai')      //  }    }));});// =============================================================================// ================================= Documentation  ============================// =============================================================================gulp.task("build:docs:md", function() {    return gulp.src("src/es6/cpython.js")        .pipe(concat("API.md"))        .pipe(gulpJsdoc2md())        .on("error", function(err){            gutil.log("jsdoc2md failed:", err.message);        })        .pipe(gulp.dest("doc"));});gulp.task('build:readme', function() {  return gulp.src(['doc/README.md', 'doc/API.md', 'doc/LICENSE.md'])    .pipe(concat('README.md'))    .pipe(gulp.dest('.'));});// =============================================================================// ================================= Gulp  =====================================// =============================================================================/****/gulp.task('watch', function() {  gulp.watch('src/es6/**/*.js', gulp.series('babel'));  gulp.watch('test/**/*.spec.js', gulp.series('mocha'));  gulp.watch().on('error', gutil.log)});gulp.task('default', gulp.series(gulp.series('babel','mocha'), gulp.parallel('watch','babel')));