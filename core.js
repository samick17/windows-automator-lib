const binding = require('./dist/Automator');

module.exports = binding;
module.exports.sendText = function(text) {
  for(var i in text) {
    var ch = text[i];
    binding.sendCharByScanCode(ch.charCodeAt());
  }
};
module.exports.pressLeftArrow = function() {
  binding.combinationKey(['shift', 'left']);
};
module.exports.pressRightArrow = function() {
  binding.combinationKey(['shift', 'right']);
};
module.exports.pressUpArrow = function() {
  binding.combinationKey(['shift', 'up']);
};
module.exports.pressDownArrow = function() {
  binding.combinationKey(['shift', 'down']);
};