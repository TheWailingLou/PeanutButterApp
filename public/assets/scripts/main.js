window.AudioContext = window.AudioContext || window.webkitAudioContext;

var context = new AudioContext();

// var child = require('child_process').fork('./public/assets/scripts/cppIO.js');

const peanutButter = require('../Sound_Generator/build/Release/peanutButter.node')

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
})
$(document).ready(function(){
  $('.create_tracks').click(function(){
    console.log("clicked!")

    var startProgress = new Promise(function(resolve, reject) {
      $('.progress_bar').toggle();
      $('.progress_text').toggle();
      $('.progress_bar').val(10)
      $('.create_tracks').addClass('create_tracks-progress')
      $('.generate_sound').text('BUILDING..')
      // $('.logo').attr('src', './assets/images/logo1red.png')
      $('.logo').toggle()
      $('.logo-spin').toggle()
      setTimeout(function(){
        resolve()
      }, 0)
    })
    startProgress.then(function(){
      var loadTrack = new Promise(function(resolve, reject) {
        var bassTrack = peanutButter.getMainBassBuffer();
        resolve(bassTrack);
      })

      loadTrack.then(function(bassTrack){
        var update_progress = new Promise(function(resolve, reject) {
          $('.progress_bar').val(30)
          // .addClass('logo-spin');
          setTimeout(function(){
            resolve(bassTrack)
          }, 0)
        })
        update_progress.then(function(bassTrack) {
          var setUpBassBuff = new Promise(function(resolve, reject) {
            var bassBuffer = context.createBuffer(bassTrack.length, bassTrack[0].length, 44100)
            resolve([bassTrack, bassBuffer])
          })
          setUpBassBuff.then(function(trackAndBuff) {
            var update_progress_again = new Promise(function(resolve, reject) {
              $('.progress_bar').val(55)
              setTimeout(function(){
                resolve(trackAndBuff)
              }, 0)
            })
            update_progress_again.then(function(trackAndBuff) {
              var bassBuff = trackAndBuff[1];
              var bassTrk = trackAndBuff[0];
              var floatArrayChannels = bassTrk.map(function(channel, j) {
                var buffSize = channel.length
                var float32 = new Float32Array(buffSize)
                for (var i=0; i<buffSize; i++)
                {
                  float32[i] = channel[i]
                }
                bassBuff.copyToChannel(float32, j);
              })
              $('.progress_bar').val(100)
              $('.logo').toggle()
              $('.logo-spin').toggle()
              $('.create_tracks').removeClass('create_tracks-progress')
              $('.generate_sound').text('CREATE')
              $('.progress_bar').toggle();
              $('.progress_text').toggle();
              // $('.logo').removeClass('logo-spin')
            })
          })
        })
      })
    })
  })

  $('.toggle_modes').click(function() {
    $('.advanced_mode').toggle();
  })

  $('.toggle_voices').click(function() {
    $('.basic_voice').toggle();
  })
})


// Promise.all([
//   loadSound('./assets/drum_samples/crash.mp3'),
//   loadSound('./assets/drum_samples/crash2.mp3'),
//   loadSound('./assets/drum_samples/hi-hat-closed.mp3'),
//   loadSound('./assets/drum_samples/hi-hat-open.mp3'),
//   loadSound('./assets/drum_samples/kick.mp3'),
//   loadSound('./assets/drum_samples/ride.mp3'),
//   loadSound('./assets/drum_samples/ride2.mp3'),
//   loadSound('./assets/drum_samples/snare.mp3'),
//   loadSound('./assets/drum_samples/snareSoft.mp3'),
//   loadSound('./assets/drum_samples/tomFloor.mp3'),
//   loadSound('./assets/drum_samples/tomFloor2.mp3'),
//   loadSound('./assets/drum_samples/tomHigh.mp3'),
//   loadSound('./assets/drum_samples/tomMid.mp3'),
//   loadSound('./assets/drum_samples/tomMidHigh.mp3')
// ]).then(function(bufferArray){
//   var crash1Buff = bufferArray[0]
//   var crash2Buff = bufferArray[1]
//   var hiHatClosedBuff = bufferArray[2]
//   var hiHatOpenBuff = bufferArray[3]
//   var kickBuff = bufferArray[4]
//   var ride1Buff = bufferArray[5]
//   var ride2Buff = bufferArray[6]
//   var snareBuff = bufferArray[7]
//   var snareSoftBuff = bufferArray[8]
//   var tomFloor1Buff = bufferArray[9]
//   var tomFloor2Buff = bufferArray[10]
//   var tomHighBuff = bufferArray[11]
//   var tomMidBuff = bufferArray[12]
//   var tomMidHighBuff = bufferArray[13]


  // child.send({message:"setCrash1", data:crash1Buff})
  // child.send({message:"setCrash2", data:crash2Buff})
  // child.send({message:"setHiHatOpen", data:hiHatOpenBuff})
  // child.send({message:"setHiHatClosed", data:hiHatClosedBuff})
  // child.send({message:"setKick", data:kickBuff})
  // child.send({message:"setRide1", data:ride1Buff})
  // child.send({message:"setRide2", data:ride2Buff})
  // child.send({message:"setSnare", data:snareBuff})
  // child.send({message:"setSnareSoft", data:snareSoftBuff})
  // child.send({message:"setTomFloor1", data:tomFloor1Buff})
  // child.send({message:"setTomFloor2", data:tomFloor2Buff})
  // child.send({message:"setTomHigh", data:tomHighBuff})
  // child.send({message:"setTomMid", data:tomMidBuff})
  // child.send({message:"setTomMidHigh", data:tomMidHighBuff})

//   child.send({message:'setSampleRate', sampleRate:44100})
//   child.send({message:'setTempo', tempo:120})
//   // child.send({message:'generateTrack'});
//
// }).catch(function(err) {
//   console.log(err);
//   console.log("WE GOTS PROBLEMS")
// })



// child.send({message: 'setUpContext', context:context})
// child.send({message:'sendDrums'})



// child.send('sayhello');
// child.send('exit');

// child.on('message', function(data) {
//   if (data.message != "progress" && data.message)
//   {
//     console.log(data.message);
//   } else {
//     console.log("got something back")
//     if (data.buffer){
//       console.log("got data back")
//     }
//   }
// })
