# windows-automator-lib 

## Support the project

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.me/samick17)
[![Donate](https://img.shields.io/badge/Donate-BuyMeCoffee-Blue.svg)](https://www.buymeacoffee.com/samick)

## Installation

Download node at [nodejs.org](http://nodejs.org) and install it, if you haven't already.

```sh
npm install windows-automator-lib --save
```

## Related modules

 - [node-abi-version](https://www.npmjs.com/package/node-abi-version)

##Description
This is the wrapper of windows-OS keyboard/mouse simulator implemented in C++.

## Supported Node Version

<table>
	<tr>
		<th><div>NodeJS Version</div></th>
		<th><div>NODE_MODULE_VERSION</div></th>
	</tr>
	<tbody>
		<tr><td><div>Node.js 10.0.0	 - Node.js 10.8.0</div></td><td><div>64</div></td></tr>
		<tr><td><div>Node.js 9.0.0 - Node.js 9.11.2</div></td><td><div>59</div></td></tr>
		<tr><td><div>Node.js 8.0.0 - Node.js 8.11.2</div></td><td><div>57</div></td></tr>
		<tr><td><div>Node.js 7.0.0 - Node.js 7.10.1</div></td><td><div>51</div></td></tr>
		<tr><td><div>Node.js 6.0.0 - Node.js 6.14.2</div></td><td><div>48</div></td></tr>
		<tr><td><div>Node.js 5.0.0 - Node.js 5.12.0</div></td><td><div>47</div></td></tr>
		<tr><td><div>Node.js 4.0.0 - Node.js 4.9.1</div></td><td><div>46</div></td></tr>
		<tr><td><div>io.js 3.0.0 - io.js 3.3.1</div></td><td><div>45</div></td></tr>
		<tr><td><div>io.js 2.0.0 - io.js 2.5.0</div></td><td><div>44</div></td></tr>
		<tr><td><div>io.js 1.1.0 - io.js 1.8.4</div></td><td><div>43</div></td></tr>
		<tr><td><div>io.js 1.0.0 - io.js 1.0.4</div></td><td><div>42</div></td></tr>
		<tr><td><div>Node.js 0.11.11 - Node.js 0.12.18</div></td><td><div>14</div></td></tr>
	</tbody>
</table>

## Build the package

```shell
node build-all-target.js
```

## ChangeLogs

#### 2023/01/21(1.5.0)
1. update node-abi-version to 1.2.12

#### 2018/08/15(1.4.8)
1. add new function: getWindowProperties(see also examples/get-child-windows.js)
2. update node-abi-version to 1.1.5

#### 2018/06/02(1.4.5)
1. clean bin before build target
2. update node-abi-version to 1.0.16

#### 2018/04/26( - 1.4.2)
1. Update module for x86, x64 arch

#### 2018/04/24(1.4.1)
1.Fix getAllWindows encoding problem, add examples: bot(trigger by global hot keys)

#### 2018/03/28(1.4.0)
1. Update to 1.4.0(support for node abi: 59)

## Usage
[Examples here](https://github.com/samick17/windows-automator-lib/tree/master/examples)

  **Import module**

	const WinAutomatorLib = require('windows-automator-lib');
	const Core = WinAutomatorLib.Core;
	const HotkeyModifiers = WinAutomatorLib.HotkeyModifiers;
	const VK = WinAutomatorLib.VK;

  **window operation**

  *getAllWindows()*

	Core.getAllWindows();

will return like this

>[{ name: 'README.md - MarkdownPad ', hwnd: 721602 },
  { name: 'windows-automator-li', hwnd: 787412 },
  { name: 'Program Manage', hwnd: 65860 } ]

  *getWindowRect(hwnd)*
if hwnd is undefined use DesktopWindow hwnd instead

	Core.getWindowRect();

>{ x: 0, y: 0, w: 1440, h: 900 }

  *getWindowSize(hwnd)*
if hwnd is undefined use DesktopWindow hwnd instead

	Core.getWindowSize();

>{ w: 1440, h: 900 }


  *getActiveWindowRect()*

  *setActivwWindowRect()*

  *setActivwWindowRectByBame()*

	var hwnd = 123456;//you can find window hwnd by "getAllWindows()"
	setActiveWindow(hwnd);
	console.log(getActiveWindow());

>{w: yourWindowWidth, h: yourWindowHeight}


  **mouse/keyboard**

  *sendText(text)*

	Core.sendText('abcde');
	Core.sendText('這是中文');

  *mouseMove(x, y)*
move to position by global screen coord

  *mouseMoveRelative(x, y)*
move to position by "ActivwWindow" coord

  *mouseLeftDown()*

  mouseLeftUp()*

  *mouseLeftClick()*

  *mouseMiddleDown()*
  
  *mouseMiddleUp()*

  *mouseMiddleClick()*

  *mouseRightDown()*

  *mouseRightClick()*

  *mouseRightUp()*

  *mouseWheel(val)*

  **register hot key**

	var keyId = 1;//defined by yourself
	var success = Core.regHotKey(keyId, keyEventConfig.modKey, keyEventConfig.key);
	//TODO if register failed, do something
	var msg = Core.getHotKeyMsg();
	//TODO if msg is blablabla, handle event

## Dependencies

- [node-abi-version](https://github.com/samick17/windows-automator-lib): Get abi version by node/iojs version

## Dev Dependencies


None

## License

MIT

_Generated by [package-json-to-readme](https://github.com/zeke/package-json-to-readme)_
