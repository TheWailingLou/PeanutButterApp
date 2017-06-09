// var cluster = require('cluster');
// var dependency = {message: 'hello there'};
// var args = [JSON.stringify(dependency)];


var cppIO = require('child_process').fork('./public/assets/scripts/testChild.js');
child.send('sayhello');
child.send('exit');

child.on('message', function(message) {
  console.log(message);
})

// if (cluster.isMaster) {
  // var worker = cluster.fork({WorkerName: "worker1"});


  // cluster.on('online', function(worker) {
  //   console.log('Worker ' + worker.process.pid + ' is online');
  // })
  // cluster.on('exit', function(worker, code, signal) {
  //   console.log('Worker ' + worker.process.pid + ' died with code ' + code);
  //   cluster.fork();
  // })

  // $('.create_tracks').click(function() {
  // })
  // $('.download').click(function(){
  //   var wav = toWav(drumBuffer)
  //   var wavBuff = new Uint8Array(wav)
  //   var blob = new window.Blob([ new DataView(wav) ], {
  //     type: 'audio/wav'
  //   })
  //   var url = window.URL.createObjectURL(blob)
  //   var anchor = document.createElement('a')
  //   document.body.appendChild(anchor)
  //   anchor.style = 'display: none'
  //   anchor.href = url
  //   anchor.download = 'Bass and drum test.wav'
  //   anchor.click()
  //   window.URL.revokeObjectURL(url)
  // })

  // worker.on('message', function(message) {
  //   console.log(message)
  // })
  // worker.send('hello from the master!');

  // console.log("getting here?")
// } else {
//   console.log("Getting to the worker?")
//   //
// }








    // Worker worker = new Worker('./createTrack.js');
    // worker.onmessage = function(event) {
    //   console.log(event.data);
    // }
    // startProgress.then(function(){
    //   var createBufferPromise = new Promise(function(resolve, reject) {
    //     // console.log("promise created");
    //     resolve();
    //   })
      // console.log("between promise creation and promise doing stuff.")
      // createBufferPromise.then(function(bassTrack) {
      //   console.log("promise.thened");
      //   var update_progress = new Promise (function(resolve, reject) {
      //     $('.progress_bar').val('20');
      //     resolve(bassTrack);
      //   })
      //   update_progress.then(function(bassTrack){
      //     var bassBuffer = context.createBuffer(bassTrack.length, bassTrack[0].length, 44100)
      //     bassTrack.map(function(channel, j) {
      //       var buffSize = channel.length
      //       var float32 = new Float32Array(buffSize)
      //       for (var i=0; i<buffSize; i++)
      //       {
      //         float32[i] = channel[i]
      //       }
      //       return float32;
      //       // bassBuffer.copyToChannel(float32, j)
      //     })
      //   })
      //
      // })

    // })

    // console.log("this should happen first");


    // var drumTrack = peanutButter.getMainBassBuffer()



    // var source;
    // var started = false;
    // $(".clickMe").click(function(){
    //   if (started)
    //   {
    //     source.stop();
    //     started = false;
    //   } else {
    //     source = context.createBufferSource()
    //     source.buffer = drumBuffer
    //     source.connect(context.destination);
    //     source.start()
    //     started = true;
    //   }
    //
    // })



  // $(".clickMe").attr('class', 'clickMe ready')
  // $(".clickMe").text('Sound Ready')
  // $(".download").attr('class', 'download ready')
  // $(".download").text('Save Wav File')


  // $(".clickMe").hover(function(){
  //   if (started)
  //   {
  //     $(this).text('Click To Stop.')
  //   }
  // }, function(){
  //   if (started)
  //   {
  //     $(this).text('Sound Playing')
  //   } else {
  //     $(this).text('Sound Ready')
  //   }
  // })
// })
