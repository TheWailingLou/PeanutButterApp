window.AudioContext = window.AudioContext || window.webkitAudioContext;

var context = new AudioContext();
const peanutButter = require('../Sound_Generator/build/Release/peanutButter.node')
const fs = require('fs')
const toWav = require('audiobuffer-to-wav')


process.on('message', function(message) {
  console.log(message);
});

process.send('hello from process ' + process.pid)



function formatBuffer(audioBuffer) {
  var formattedBufferArray = []
  for (var channel=0; channel<audioBuffer.numberOfChannels; channel++) {
    formattedBufferArray.push(audioBuffer.getChannelData(channel))
  }
  return formattedBufferArray
}


function loadSound(url) {
  var request = new XMLHttpRequest()
  request.open('GET', url, true)
  request.responseType = 'arraybuffer';

  let audioPromise = new Promise(function(resolve, reject) {
    request.onload = function() {
      context.decodeAudioData(request.response, function(buffer) {
        soundBuffer = formatBuffer(buffer);
        resolve(soundBuffer);
      })
    }
  })
  request.send()
  return audioPromise
}

Promise.all([
  loadSound('./assets/drum_samples/crash.mp3'),
  loadSound('./assets/drum_samples/crash2.mp3'),
  loadSound('./assets/drum_samples/hi-hat-closed.mp3'),
  loadSound('./assets/drum_samples/hi-hat-open.mp3'),
  loadSound('./assets/drum_samples/kick.mp3'),
  loadSound('./assets/drum_samples/ride.mp3'),
  loadSound('./assets/drum_samples/ride2.mp3'),
  loadSound('./assets/drum_samples/snare.mp3'),
  loadSound('./assets/drum_samples/snareSoft.mp3'),
  loadSound('./assets/drum_samples/tomFloor.mp3'),
  loadSound('./assets/drum_samples/tomFloor2.mp3'),
  loadSound('./assets/drum_samples/tomHigh.mp3'),
  loadSound('./assets/drum_samples/tomMid.mp3'),
  loadSound('./assets/drum_samples/tomMidHigh.mp3')
]).then(function(bufferArray){
  var crash1Buff = bufferArray[0]
  var crash2Buff = bufferArray[1]
  var hiHatClosedBuff = bufferArray[2]
  var hiHatOpenBuff = bufferArray[3]
  var kickBuff = bufferArray[4]
  var ride1Buff = bufferArray[5]
  var ride2Buff = bufferArray[6]
  var snareBuff = bufferArray[7]
  var snareSoftBuff = bufferArray[8]
  var tomFloor1Buff = bufferArray[9]
  var tomFloor2Buff = bufferArray[10]
  var tomHighBuff = bufferArray[11]
  var tomMidBuff = bufferArray[12]
  var tomMidHighBuff = bufferArray[13]

  peanutButter.setCrash1(crash1Buff)
  peanutButter.setCrash2(crash2Buff)
  peanutButter.setHiHatOpen(hiHatOpenBuff)
  peanutButter.setHiHatClosed(hiHatClosedBuff)
  peanutButter.setKick(kickBuff)
  peanutButter.setRide1(ride1Buff)
  peanutButter.setRide2(ride2Buff)
  peanutButter.setSnare(snareBuff)
  peanutButter.setSnareSoft(snareSoftBuff)
  peanutButter.setTomFloor1(tomFloor1Buff)
  peanutButter.setTomFloor2(tomFloor2Buff)
  peanutButter.setTomHigh(tomHighBuff)
  peanutButter.setTomMid(tomMidBuff)
  peanutButter.setTomMidHigh(tomMidHighBuff)

  peanutButter.setSampleRate(44100)
  peanutButter.setTempo(120)

  var bassTrack = peanutButter.getMainBassBuffer();
  var bassBuffer = context.createBuffer(bassTrack.length, bassTrack[0].length, 44100)
  var floatArrayChannels = bassTrack.map(function(channel, j) {
    var buffSize = channel.length
    var float32 = new Float32Array(buffSize)
    for (var i=0; i<buffSize; i++)
    {
      float32[i] = channel[i]
    }
    return float32;
  })
})
