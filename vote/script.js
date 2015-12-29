localStorage.clear();

var socket = new WebSocket('ws://127.0.0.1:9059/')
socket.onopen = function() {
    socket.send('need new circuit')
    console.log('socket opened')
}
socket.onmessage = function(evt) {
    console.log(evt.data);
    switch(evt.data) {
        case 'new circuit created':
            setTimeout(f, 0)
            break;
    }
}


var startTime = new Date();
var total = 0;
var success = 0;
var failure = 0;

var run = true;
var f = function () {
    if (!run) {
        return;
    }
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://innoawards.geekpark.net/ranks/408cdd6a-4588-4bcb-af71-cad63a904b24/vote', true);
    xhr.setRequestHeader('X-CSRF-Token',
            'ws7CCyZ+n7mHM/WzjzD0T0iNZoZqg0PDBF/+6Srp3ylQCnRMXOxAWrLAgZhZLX1kgL7UcF1Pggse9Ur+c+BKTg==');
    xhr.timeout = 11 * 1000;
    xhr.ontimeout = function() {
        console.error('time out');
        xhr.abort();
    }
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
            total++;
            if (xhr.status === 200) {
                success++;
                f();
            } else {
                failure++;
                socket.send('need new circuit');
            }
            console.log('Total time:' + ((new Date() - startTime) / 1000) + ' seconds');
            console.log('total:' + total + '   '
                    + 'success:' + success + '   '
                    + 'failure:' + failure);
            xhr.responseText && console.log(xhr.responseText);
        }
    }

    xhr.send();
};

