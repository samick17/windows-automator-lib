const NodeABI = require('node-abi-version');
const fs = require('fs');
const os = require('os');

module.exports = (function() {
  const abi = NodeABI.getABIVersion();
  const arch = os.arch();
  var srcPath = __dirname+'/dist/Automator'+abi+'_'+arch+'.node';
  var destPath = __dirname+'/dist/Automator.node';
  fs.writeFileSync(destPath, fs.readFileSync(srcPath));
})();

