// Variable Initialization
let previousTime = performance.now();
let t_e_array = [];
let button_clicked = false;
let clear_fields = false;
let timer_event = {
  name: "",
  interval: 0,
  n_times: 0,
  time_created: 0,
  time_alive: 0,
  print_times_remaining: 0,
  should_print: false
};

function MakeNewTimeEventAndPush(elapsedTime){
  if(button_clicked) {
    let name = document.getElementById("da_name").value;
    let interval = document.getElementById("the_interval").value;
    let n_times = document.getElementById("the_n_times").value;
    let new_data = Object.create(timer_event);
    new_data.name = name;
    new_data.interval = interval;
    new_data.n_times = n_times;
    new_data.time_created = performance.now();
    new_data.time_alive = performance.now() - new_data.time_created;
    new_data.print_times_remaining = n_times;
    t_e_array.push(new_data);    
    button_clicked = false;
    clear_fields = true;
  }
}

function removeOutdatedEntries(){
  // This must be done in reverse order as was mentioned in class.
  // for (var i = 0; i < t_e_array.length; i++) {
  //   if(t_e_array[i].print_times_remaining == 0) {
  //     t_e_array.splice(i,1);
  //   }
  // }
  for (var i = t_e_array.length - 1; i >= 0 ; i--) {
    if(t_e_array[i].print_times_remaining == 0) {
      t_e_array.splice(i,1);
    }
  }
}

function resetPrintBools(){
  for (var i = 0; i < t_e_array.length; i++) {
    t_e_array[i].should_print = false;
  }
}

function processAndSetPrintBool(elapsedTime){
  for (var i = 0; i < t_e_array.length; i++) {
    t_e_array[i].time_alive = t_e_array[i].time_alive + elapsedTime;
    // Here time since creation is actually counting the timing between printings.
    if(t_e_array[i].time_alive % t_e_array[i].interval > 0) {
      t_e_array[i].should_print = true;
      t_e_array[i].time_alive = t_e_array[i].time_alive - t_e_array[i].interval;
      t_e_array[i].print_times_remaining = t_e_array[i].print_times_remaining - 1;
    }
  }
}

function clearTheFields(){
  if(clear_fields) {
    let name = document.getElementById("da_name");
    let interval = document.getElementById("the_interval");
    let n_times = document.getElementById("the_n_times");
    name.value = "";
    interval.value = "";
    n_times.value = "";
    clear_fields = false;
  }
}

function printTheOutput(){
  for (var i = 0; i < t_e_array.length; i++) {
    if(t_e_array[i].should_print) {
      let printthis = ("Event: " + t_e_array[i].name + " (" + t_e_array[i].print_times_remaining + " remaining)");
      document.getElementById("output_log").innerHTML += ("<br>" + printthis);
      let objdiv = document.getElementById("output_log");
      objdiv.scrollTop = objdiv.scrollHeight;
    }
  }
}

function processInput(elapsedTime) {
  MakeNewTimeEventAndPush(elapsedTime);
}

function update(elapsedTime) {
  removeOutdatedEntries();
  resetPrintBools();
  processAndSetPrintBool(elapsedTime);  
}

function render(elapsedTime) {
  clearTheFields();
  printTheOutput();
}

function gameLoop() {
	let currentTime = performance.now();
	let elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	processInput(elapsedTime);
	update(elapsedTime);
	render(elapsedTime);
	requestAnimationFrame(gameLoop);
}

window.onload = function() {
  // Call the Game Loop
  gameLoop();

  // Grab the button and form.
  let jsbutton = document.getElementById("the_button");
  let jsform = document.getElementById("form1");

  // Make sure that the onsubmit for the form returns false.
  jsform.onsubmit = function() {
    return false;
  };

  // Everytime the button is clicked, set a bool.
  jsbutton.onclick = function runthis22(){
    button_clicked = true;
  };
}