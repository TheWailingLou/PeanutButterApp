// var dependency = JSON.parse(process.argv[2]);
process.on('message', function(m){
    if(m == 'sayhello') {
      console.log(dependency.message);
      process.send({message: "hello_back"})
    }
    else if(m == 'exit') process.exit();
});
