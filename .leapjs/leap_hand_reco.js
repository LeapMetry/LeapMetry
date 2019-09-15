
function main(){
  var controller = new Leap.Controller({enableGestures: true});

  controller.loop(function(frame) {
    if(frame.gestures.length > 0){
      state = 'paused'
      document.getElementById('last_gesture').innerHTML = "<p>"+frame.gestures+"<p>";
    }
    
    // if(last_gesture != frame)
    if (haveLoggedFrame == false && frame.hands[0]){
      console.log(frame);
      haveLoggedFrame = true;
    }
  });
};