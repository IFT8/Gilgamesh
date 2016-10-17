var script = document.createElement('script');
script.type = 'text/javascript';
script.text = 'window.g_browser.sendClearHostResolverCache();' 
    + 'window.g_browser.sendFlushSocketPools();';

document.body.appendChild(script);