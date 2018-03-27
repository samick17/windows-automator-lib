const NodeABI = require('node-abi-version');
const fs = require('fs');

module.exports = function() {
  const abi = NodeABI.getABIVersion();
  var srcPath = __dirname+'/dist/Automator'+abi+'.node';
  var destPath = __dirname+'/dist/Automator.node';
  fs.writeFileSync(destPath, fs.readFileSync(srcPath));
}();