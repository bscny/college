// NOTICE: To test this code, please use npm to create a package.json, and make it `"type": "module"`
// I am not using commonJS here
import dgram from 'node:dgram';

const server = dgram.createSocket('udp4');

server.on('message', (msg, rinfo) => {
    console.log(msg.toString());

    server.send(rinfo.port.toString()+ ":" + msg.toString(), rinfo.port, rinfo.address, (err) => {
        if (err) {
            console.error(`Failed to send response: ${err}`);
        } else {
            server.close();
        }
    });
});

server.bind(20213);