(function() {
	const Lib = require('windows-automator-lib');
	const Core = Lib.Core;
	module.exports = {
		getHotKey: function() {
			return new Promise((resolve) => {
				var keyId = Core.getHotKeyMsg();
				resolve(keyId);
			});
		}
	};
})();