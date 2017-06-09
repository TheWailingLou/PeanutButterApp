window.AudioContext = window.AudioContext || window.webkitAudioContext;

var context = new AudioContext();
const peanutButter = require('../Sound_Generator/build/Release/peanutButter.node')

peanutButter.setSampleRate(44100)
peanutButter.setTempo(120)

var bassTrack = peanutButter.getMainBassBuffer()
var bassBuffer = context.createBuffer(bassTrack.length, bassTrack[0].length, 44100)
bassTrack.forEach(function(channel, j) {
  var buffSize = channel.length
  var float32 = new Float32Array(buffSize)
  for (var i=0; i<buffSize; i++)
  {
    float32[i] = channel[i]
  }
  bassBuffer.copyToChannel(float32, j)
})
var source = context.createBufferSource()
source.buffer = bassBuffer
source.connect(context.destination);
source.start()
