var Core = require('../core');

var aw = Core.getAllWindows();
for(var i in aw) {
  var a = aw[i];
  console.log(a);
}
