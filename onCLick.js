chrome.browserAction.onClicked.addListener(function (tab) {
    chrome.tabs.query({}, function (tabs) {
        var needCreate = true;
        tabs.forEach(function (tab) {
            if (tab.url == 'chrome://net-internals/#dns') {
                chrome.tabs.executeScript(tab.id, { file: "flush.js" }, function () {
                    chrome.tabs.remove(tab.id);
                });
                needCreate = false;
            }
        });

        if (needCreate) {
            chrome.tabs.create({
                url: 'chrome://net-internals/#dns',
                active: false
            }, function (tab) {
                chrome.tabs.executeScript(tab.id, { file: 'flush.js' }, function () {
                    chrome.tabs.remove(tab.id);
                });
            });
        }
    });
});