import {SomeClass} from "./math";
import {PyCalls} from "./PyCalls";


export class Emscripten extends PyCalls {
  constructor(opts) {
    super()
    //Emscripten.init.call(this)
    this.opts = opts
    //super()
  }
  hello() {
    console.log('hello from Emscripten')
    super.helloPy()
  }
}

let inst = new Emscripten()
module.exports = inst
