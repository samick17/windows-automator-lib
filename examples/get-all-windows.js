const Core = require('../core');
//if installed by package, using:
//const Core = require('windows-automator-lib').Core;

var aw = Core.getAllWindows();
for(var i in aw) {
  var a = aw[i];
  console.log(a);
}
