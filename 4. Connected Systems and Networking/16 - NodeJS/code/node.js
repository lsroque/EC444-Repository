/* Author: Lesbeth Roque
Cluster 2, Skill 16
10-07-2020
Team 15*/

// api-serialport; SOURCE: https://github.com/serialport/website/blob/master/docs/api-serialport.md
// api-parser-readline source: https://serialport.io/docs/api-parser-readline

const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const port = new SerialPort('/dev/cu.SLAB_USBtoUART', { baudRate: 115200}) //Serial port event

const parser = new Readline()
port.pipe(parser)

parser.on('data',line => console.log(`>${line}`))
port.write('ROBOT POWER ON\n')
//> ROBOT ONLINE
