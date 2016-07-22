const Core = require('../core');
const VK = require('../vk');
const HotkeyModifier = require('../hotkey-modifiers');
const Utils = require('util');

/*
example of register hotkey
*/

function registerHotkey(id, keyEventConfig) {
  var keyId = parseInt(id);
  var success = Core.regHotKey(keyId, keyEventConfig.modKey, keyEventConfig.key);
  if(!success) {
    throw Utils.format('register key :%s failed', keyId);
  }
}

var keyEventMap = {
  1: {
    modKey: HotkeyModifier.CONTROL|HotkeyModifier.SHIFT,
    key: VK.H,
    handler: function() {
      console.log('handle event 1');
    }
  },
  2: {
    modKey: HotkeyModifier.CONTROL,
    key: VK.G,
    handler: function() {
      console.log('handle event 2');
    }
  }
};

function onKey() {
  var keyId = Core.getHotKeyMsg();
  if(keyId in keyEventMap) {
    keyEventMap[keyId].handler();
  }
}

try {
  for(var key in keyEventMap) {
    registerHotkey(key, keyEventMap[key]);
  }
  onKey();
}
catch(e) {
  console.log(e);
}