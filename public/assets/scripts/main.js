window.AudioContext = window.AudioContext || window.webkitAudioContext;

var context = new AudioContext();

const peanutButter = require('../Sound_Generator/build/Release/peanutButter.node')

const toWav = require('audiobuffer-to-wav')

function formatBuffer(audioBuffer) {
  var formattedBufferArray = []
  for (var channel=0; channel<audioBuffer.numberOfChannels; channel++) {
    formattedBufferArray.push(audioBuffer.getChannelData(channel))
  }
  return formattedBufferArray
}

var completeMainBuffer;
var completeMainTrack;
var completeBassBuffer;
var completeBassTrack;
var completeDrumBuffer;
var completeDrumTrack;

var bassGain = context.createGain();
var drumGain = context.createGain();
bassGain.connect(context.destination);
drumGain.connect(context.destination);

bassGain.gain.value = 1;
drumGain.gain.value = 1;

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

var creatingTrack = false;
$(document).ready(function(){
  $('.create_tracks').click(function(){
    if (!creatingTrack)
    {
      creatingTrack = true;
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
        var setKeyTempoModeVoice = new Promise(function(resolve, reject) {
          var key = $('.selectKey').val();
          if (key === "random") {
            key = Math.floor(Math.random()*12);
          }
          key = parseInt(key);

          var mode = $('.selectMode').val()
          if (mode === "random") {
            if (document.getElementById("toggle_modes").checked) {
              mode = Math.floor(Math.random()*7);
            } else {
              mode = Math.floor(Math.random()*2)*5;
            }
          }
          mode = parseInt(mode);

          var voice = $('.selectBassVoice').val()
          if (voice === "random") {
            if (document.getElementById('toggle_voices').checked) {
              voice = Math.floor(Math.random()*7);
            } else {
              voice = Math.floor(Math.random()*3)
            }
          }
          voice = parseInt(voice);

          var tempo = parseInt($('.setTempo').val())

          peanutButter.setKey(key);
          peanutButter.setMode(mode);
          peanutButter.setTempo(tempo);
          console.log("key ", key);
          console.log("mode ", mode);
          console.log("voice ", voice);
          console.log("tempo ", tempo);
          setTimeout(function() {
            resolve()
          }, 0)
        })
        setKeyTempoModeVoice.then(function() {
          var first_progress_update = new Promise(function(resolve, reject) {
            $('.progress_bar').val(15)
            setTimeout(function(){
              resolve()
            }, 0)
          })
          first_progress_update.then(function(){
            var createTracks = new Promise(function(resolve, reject) {
              peanutButter.createAllTracks();
              setTimeout(function(){
                resolve()
              }, 0)
            })
            createTracks.then(function(){
              var secondProgressUpdate = new Promise(function(resolve, reject) {
                $('.progress_bar').val(45)
                setTimeout(function(){
                  resolve()
                }, 0)
              })
              secondProgressUpdate.then(function() {
                var loadTrack = new Promise(function(resolve, reject) {
                  completeMainTrack = peanutButter.getMainBuffer();
                  setTimeout(function(){
                    resolve(); //mainTrack
                  }, 0)
                })
                loadTrack.then(function(mainTrack){
                  peanutButter.freeMainTrackMemory();
                  var update_progress = new Promise(function(resolve, reject) {
                    $('.progress_bar').val(60)
                    setTimeout(function(){
                      resolve() //mainTrack
                    }, 0)
                  })
                  update_progress.then(function() { //mainTrack
                    var loadBassTrack = new Promise(function(resolve, reject) {
                      completeBassTrack = peanutButter.getMainBassBuffer();
                      setTimeout(function(){
                        resolve(); //[mainTrack, bassTrack]
                      }, 0)
                    })

                    loadBassTrack.then(function() { //mainAndBass
                      peanutButter.freeBassMemory();
                      var update_progress4 = new Promise(function(resolve, reject) {
                        // console.log("main and bass Len:", mainAndBass[0].length);
                        $('.progress_bar').val(70);
                        setTimeout(function() {
                          resolve() //mainAndBass
                        }, 0)
                      })

                      update_progress4.then(function() { //mainAndBass
                        var loadDrumTrack = new Promise(function(resolve, reject) {
                          completeDrumTrack = peanutButter.getMainDrumBuffer();
                          setTimeout(function(){
                            resolve() // [mainAndBass[0], mainAndBass[1], drumTrack]
                          }, 0)
                        })
                        loadDrumTrack.then(function() { //mainBassDrums
                          peanutButter.freeDrumMemory();
                          var update_progress5 = new Promise(function(resolve, reject) {
                            $('.progress_bar').val(80);
                            setTimeout(function() {
                              resolve() //mainBassDrums
                            }, 0)
                          })
                          update_progress5.then(function(){ //mainBassDrums
                            var setUpAllBuffers = new Promise(function(resolve, reject) {

                              // var mainTrack = mainBassDrums[0];
                              console.log("Main Track");
                              // var bassTrack = mainBassDrums[1];
                              // var drumTrack = mainBassDrums[2];
                              completeMainBuffer = context.createBuffer(completeMainTrack.length, completeMainTrack[0].length, 44100)
                              completeBassBuffer = context.createBuffer(completeBassTrack.length, completeBassTrack[0].length, 44100)
                              completeDrumBuffer = context.createBuffer(completeDrumTrack.length, completeDrumTrack[0].length, 44100)

                              resolve()//[[mainTrack, mainBuffer], [bassTrack, bassBuffer], [drumTrack, drumBuffer]]
                            })
                            setUpAllBuffers.then(function() { //tracksAndBuffs
                              var update_progress_again = new Promise(function(resolve, reject) {
                                $('.progress_bar').val(90)
                                setTimeout(function(){
                                  resolve() //tracksAndBuffs
                                }, 0)
                              })
                              update_progress_again.then(function() { //tracksAndBuffs
                                // completeMainBuffer = tracksAndBuffs[0][1];
                                // completeMainTrack = tracksAndBuffs[0][0];

                                completeMainTrack.forEach(function(channel, j) {
                                  var buffSize = channel.length
                                  var float32 = new Float32Array(buffSize)
                                  for (var i=0; i<buffSize; i++)
                                  {
                                    float32[i] = channel[i]
                                  }
                                  completeMainBuffer.copyToChannel(float32, j);
                                })

                                // completeBassBuffer = tracksAndBuffs[1][1];
                                // completeBassTrack = tracksAndBuffs[1][0];
                                completeBassTrack.forEach(function(channel, j) {
                                  var buffSize = channel.length
                                  var float32 = new Float32Array(buffSize)
                                  for (var i=0; i<buffSize; i++)
                                  {
                                    float32[i] = channel[i]
                                  }
                                  completeBassBuffer.copyToChannel(float32, j);
                                })

                                // completeDrumBuffer = tracksAndBuffs[2][1];
                                // completeDrumTrack = tracksAndBuffs[2][0];
                                completeDrumTrack.forEach(function(channel, j) {
                                  var buffSize = channel.length
                                  var float32 = new Float32Array(buffSize)
                                  for (var i=0; i<buffSize; i++)
                                  {
                                    float32[i] = channel[i]
                                  }
                                  completeDrumBuffer.copyToChannel(float32, j);
                                })

                                // peanutButter.freeAllMemory();
                                $('.progress_bar').val(100)
                                $('.logo').toggle()
                                $('.logo-spin').toggle()
                                $('.create_tracks').removeClass('create_tracks-progress')
                                $('.generate_sound').text('CREATE')
                                $('.progress_bar').toggle();
                                $('.progress_text').toggle();
                                $('.play_button_div').css('opacity', '1');
                                creatingTrack = false;
                              })
                            })
                          })
                        })
                      })
                    })
                  })
                })
              })
            })
          })
        })
      })
    }
  })

  $('.toggle_modes').click(function() {
    $('.advanced_mode').toggle();
  })

  $('.toggle_voices').click(function() {
    $('.basic_voice').toggle();
  })

  $('#toggle_random_tempo').click(function() {
    var boxChecked = document.getElementById('toggle_random_tempo').checked
    if (boxChecked)
    {
      var randomTempo = Math.floor(Math.random()*80) + 80;
      $('.setTempo').val(randomTempo)
    } else {
      $('.setTempo').val(120)
    }
  })
  $('.setTempo').click(function(){
    document.getElementById('toggle_random_tempo').checked = false;
  })
  var source1;
  var source2;
  var started = false;
  $('.play_button').click(function() {
    $('.play_button').toggleClass('stop_button');
    $('.unloaded_track').toggleClass('loaded-track');
    if ($('.play_button').hasClass('stop_button')) {
      $('.play_button h2').text('STOP')
    } else {
      $('.play_button h2').text('PLAY')
    }
    if (started) {
      source1.stop();
      source2.stop();
      started = false;
    } else {
      source1 = context.createBufferSource();
      source2 = context.createBufferSource();
      source1.buffer = completeBassBuffer;
      source2.buffer = completeDrumBuffer;
      source1.connect(bassGain);
      source2.connect(drumGain);
      source1.start();
      source2.start();
      started = true;
    }
  })

  $('.muteBass').click(function(){
    if (bassGain.gain.value == 1) {
      bassGain.gain.value = 0;
    } else {
      bassGain.gain.value = 1;
    }
  })
  $('.muteDrums').click(function(){
    if (drumGain.gain.value == 1) {
      drumGain.gain.value = 0;
    } else {
      drumGain.gain.value = 1;
    }
  })

  $('.saveMain').click(function(){
      var wav = toWav(completeMainBuffer);
      var wavBuff = new Uint8Array(wav)
      var blob = new window.Blob([ new DataView(wav) ], {
        type: 'audio/wav'
      })
      var url = window.URL.createObjectURL(blob)
      var anchor = document.createElement('a')
      document.body.appendChild(anchor)
      anchor.style = 'display: none'
      anchor.href = url
      anchor.download = 'CompleteBufferTest.wav'
      anchor.click()
      window.URL.revokeObjectURL(url)
  })

  $('.saveBass').click(function(){
      var wav = toWav(completeBassBuffer);
      var wavBuff = new Uint8Array(wav)
      var blob = new window.Blob([ new DataView(wav) ], {
        type: 'audio/wav'
      })
      var url = window.URL.createObjectURL(blob)
      var anchor = document.createElement('a')
      document.body.appendChild(anchor)
      anchor.style = 'display: none'
      anchor.href = url
      anchor.download = 'CompleteBufferTest.wav'
      anchor.click()
      window.URL.revokeObjectURL(url)
  })

  $('.saveDrums').click(function(){
      var wav = toWav(completeDrumBuffer);
      var wavBuff = new Uint8Array(wav)
      var blob = new window.Blob([ new DataView(wav) ], {
        type: 'audio/wav'
      })
      var url = window.URL.createObjectURL(blob)
      var anchor = document.createElement('a')
      document.body.appendChild(anchor)
      anchor.style = 'display: none'
      anchor.href = url
      anchor.download = 'CompleteBufferTest.wav'
      anchor.click()
      window.URL.revokeObjectURL(url)
  })
})
