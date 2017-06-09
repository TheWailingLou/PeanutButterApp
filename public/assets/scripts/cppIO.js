const path = require('path')
const pathToPB = path.join(__dirname, '../../../Sound_Generator/build/Release/peanutButter.node')
const peanutButter = require(pathToPB)
const fs = require('fs')
const toWav = require('audiobuffer-to-wav')
const wavEncode = require('node-wav');

const XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;

// var window;

process.on('message', function(data){
  console.log(data.message)
  if(data.message == 'sendDrums') {
    // sendDrums().then(function(){
    process.send({message: 'drums sent to cpp'})
  } else if(data.message == 'setTempo') {
    setTempo(data.tempo)
    process.send({message: `tempo has been set to ${data.tempo}`})
  } else if(data.message == 'setSampleRate') {
    setSampleRate(data.sampleRate);
    process.send({message: `sample rate has been set to ${data.sampleRate}`})
  } else if(data.message == 'generateTrack') {
    generateTrack();
  } else if (data.message == 'exit') {
    process.exit(0);
  } else if (data.message == "setCrash1") {
    console.log(typeof data.data)
    // peanutButter.setCrash1(data.data);
    process.send("crash1 set.")
  } else if (data.mesage == "setCrash2") {
    peanutButter.setCrash2(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setHiHatOpen") {
    peanutButter.setHiHatOpen(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setHiHatClosed") {
    peanutButter.setHiHatClosed(data.data)
  } else if (data.message == "setKick") {
    peanutButter.setKick(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setRide1") {
    peanutButter.setRide1(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setRide2") {
    peanutButter.setRide2(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setSnare") {
    peanutButter.setSnare(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setSnareSoft") {
    peanutButter.setSnareSoft(data.data)
  } else if (data.message == "setTomFloor1") {
    peanutButter.setTomFloor1(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setTomFloor2") {
    peanutButter.setTomFloor2(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setTomHigh") {
    peanutButter.setTomHigh(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setTomMid") {
    peanutButter.setTomMid(data.data)
    process.send("crash1 set.")
  } else if (data.message == "setTomMidHigh") {
    peanutButter.setTomMidHigh(data.data)
    process.send("crash1 set.")
  }
});








//   child.send({message:, data:crash1Buff})
// child.send({message:, data:crash2Buff})
// child.send({message:, data:hiHatOpenBuff})
// child.send({message:, data:hiHatClosedBuff})
// child.send({message:, data:kickBuff})
// child.send({message:, data:ride1Buff})
// child.send({message:, data:ride2Buff})
// child.send({message:, data:snareBuff})
// child.send({message:, data:snareSoftBuff})
// child.send({message:, data:tomFloor1})
// child.send({message:, data:tomFloor2})
// child.send({message:, data:tomHigh})
// child.send({message:, data:tomMid})
// child.send({message:, data:tomMidHigh}))



// const pathToAssets = path.join(__dirname, '../');
// console.log(pathToAssets+'drum_samples/crash.mp3')



function setSampleRate(sampleRate) {
  peanutButter.setSampleRate(sampleRate);
}

function setTempo(tempo) {
  peanutButter.setTempo(tempo)
}

function generateTrack() {
  process.send({message: `generation process begun.`});
  var bassTrack = peanutButter.getMainBassBuffer();
  process.send({message: `got buffer back from cpp.`});
  // var bassBuffer = context.createBuffer(bassTrack.length, bassTrack[0].length, 44100)
  process.send({message: `created buffer, now copying data to channels`});
  var floatArrayChannels = bassTrack.map(function(channel, j) {
    var buffSize = channel.length
    var float32 = new Float32Array(buffSize)
    for (var i=0; i<buffSize; i++)
    {
      float32[i] = channel[i]
    }
    process.send({message: `copied channel ${j}`});
    console.log("typeof", typeof float32)
    return float32;
  })
  console.log(typeof floatArrayChannels[0])
  var pathToTemp = path.join(__dirname, '../tempFiles/tempMAIN.wav')
  // var wav = toWav(floatArrayChannels[0]);
  var wav = wavEncode.encode(floatArrayChannels, { sampleRate: 44100, float: true, bitDepth: 32 });
  fs.writeFileSync(pathToTemp, wav); //Buffer.from(new Uint8Array(wav))
  // process.send({message:"progress", buffer:floatArrayChannels})
  process.send({message: `Done! ready to play.`});
}




















//
