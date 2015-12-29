localStorage.clear();

var socket = new WebSocket('ws://127.0.0.1:9059/')
socket.onopen = function() {
    socket.send('need new circuit')
    console.log('socket opened')
}
socket.onmessage = function(evt) {
    console.log(evt.data);
    if (evt.data.indexOf('new circuit created') != -1) {
        ip = evt.data.substring(24)
        setTimeout(f, 0)
    }
}


var startTime = new Date();
var total = 0;
var success = 0;
var failure = 0;
var ip = null;

var run = true;
var f = function () {
    if (!run) {
        return;
    }
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://innoawards.geekpark.net/ranks/408cdd6a-4588-4bcb-af71-cad63a904b24/vote', true);
    xhr.setRequestHeader('X-CSRF-Token',
            'su199SchyX8Gi89Mfli6TPGyxYKTOXwUW9A9c3RM1OJsI7Ry6FwhGuK1qjITzk6xFRqiidzlAhfSgpw7UrkekA==');
    xhr.timeout = 11 * 1000;
    xhr.ontimeout = function() {
        console.error('time out');
        socket.send('time out. ip:' + ip)
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

