import datetime
from stem import Signal
from stem.process import launch_tor
from stem.control import Controller
from websocket_server import WebsocketServer
from time import sleep

import stem
import atexit

ip_set = open('ip_set', 'r').readlines()

class Tor:
    tor = None
    controller = None
    def launch(self):
        def init_msg(message):
            print(message)

        self.tor = launch_tor(tor_cmd='D:\\Program Files (x86)\\Tor Browser\\Browser\\TorBrowser\\Tor\\tor.exe',
                torrc_path='D:\\Program Files (x86)\\Tor Browser\\Browser\\TorBrowser\\Data\\Tor\\torrc',
                init_msg_handler=init_msg)
        self.controller = Controller.from_port(port = 9151)
        self.controller.authenticate()
        print('Tor is running, version %s' % self.controller.get_version())
    def terminate(self):
        if self.tor != None:
            self.controller.reset_conf('__LeaveStreamsUnattached')
            self.tor.kill()
            open('ip_set', 'w').writelines(ip_set)
            print('Tor is terminated')

tor = Tor()
tor.launch()
atexit.register(tor.terminate) # kill tor when python process is terminated

pre_listener = None
ip_count = 100
# websocket server
def message_received(client, server, message):
    if 'need new circuit' in message:
        global pre_listener 
        controller = tor.controller
        controller.set_conf('__LeaveStreamsUnattached', '1')
        controller.remove_event_listener(pre_listener)

        for s in controller.get_streams():
            controller.close_stream(s.id)
            if s.circ_id:
                controller.close_circuit(s.circ_id, 'ifUnused')
            print('Stream %s on circuit %s is closed' % (s.id, s.circ_id if s.circ_id else 'unknown'))

        print('Wait for creating new circuit')

        while True:
            try:
                new_circuit_id = controller.new_circuit(await_build = True)
                new_circuit = controller.get_circuit(new_circuit_id)
                exit_fp, exit_nickname = new_circuit.path[-1]
                exit_desc = controller.get_network_status(exit_fp, None)
                exit_address = exit_desc.address if exit_desc else 'unknown'
                if exit_address in ip_set:
                    continue

                ip_set.append(exit_address + '\n')
                print('New circuit %s created. Exit relay address: %s' % (new_circuit.id, exit_address)) 

                break
            except stem.CircuitExtensionFailed:
                continue

        def attach_stream(stream):
            if stream.status == stem.StreamStatus.NEW:
                try:
                    print('Attach stream ' + stream.id + ' to ' + new_circuit_id)
                    controller.attach_stream(stream.id, new_circuit_id)
                except stem.UnsatisfiableRequest:
                    print('Unexpect exception')
                except stem.InvalidRequest:
                    print('Unexpect Exception')
            elif stream.status == stem.StreamStatus.SUCCEEDED:
                print('SUCCESS:' + stream.id + ':' + stream.circ_id)

        controller.add_event_listener(attach_stream, stem.control.EventType.STREAM)
        pre_listener = attach_stream
        ip_count += 1
        if ip_count > 100:
            ip_count = 0
            now = datetime.now()
            ip_set.append(now.strftime('%c'))

        server.send_message(client, 'new circuit created')

server = WebsocketServer(9059)
server.set_fn_message_received(message_received)
server.run_forever()


