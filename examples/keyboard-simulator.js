const Core = require('../core');
const VK = require('../vk');
//if installed by package, using:
//const Lib = require('windows-automator-lib');
//const Core = Lib.Core;
//const VK = Lib.VK;

//simualte enter by character
for(var i = 0; i < 10;i++)
  Core.sendKey('z');

//simulate enter text
Core.sendText('Hahaha');
Core.sendText('這是中文');


//simulate enter combokeys
Core.combinationKeyByVKValue([VK.CONTROL, VK.A]);
/*or
Core.combinationKey(['control', 'a']);
*/