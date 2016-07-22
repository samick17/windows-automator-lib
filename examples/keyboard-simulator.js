var Core = require('../core');
var VK = require('../vk');

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