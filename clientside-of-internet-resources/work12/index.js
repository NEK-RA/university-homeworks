let interval;
let counter = 0;
let lastN = 0;
let fnShown = false;
let fabClicked = 0;

function log(obj){
  let logs = document.querySelector(".console");
  let element = document.createElement("div");
  element.innerHTML = JSON.stringify(obj);
  logs.appendChild(element);
  setTimeout(function(){
    element.remove();
  }, 5000)
}

function showNotification(options){
  let notificationZone = document.querySelector(".top-notifications");
  let newNotification = document.createElement("div");
  newNotification.className = "notification";
  newNotification.innerText = options.text;
  if("tc" in options && options.tc){
    newNotification.style.color = options.tc;
  }
  if("bg" in options && options.bg){
    newNotification.style.backgroundColor = options.bg;
  }
  notificationZone.appendChild(newNotification);
  setTimeout(function(){
    newNotification.remove();
  }, 1500);
}

function makeNotification(){
  let content = prompt("Сообщение для уведомления:");
  if(content){
    let bgcolor = prompt("Цвет фона (hex-код, по умолчанию черный)");
    let color = prompt("Цвет текста (hex-код, по умолчанию белый)");
    showNotification({text: content, bg: bgcolor, tc: color});
  }
}

function clearList(){
  let list = document.querySelector("ul#userlist");
  list.childNodes.forEach(el => {
    setTimeout(function(){
      el.remove();
    }, 100);
  });
}

function makeList(){
  let list = document.querySelector("ul#userlist");
  let text = "tmp";
  while(text){
    text = prompt("Текст нового пункта:");
    if(text){
      let item = document.createElement("li");
      item.innerText = text;
      list.appendChild(item);
    }
  }
}

function showHideFN(){
  fnShown = ~fnShown;
  let fab = document.querySelector(".float-notification");
  let list = document.querySelector(".notify-items");
  try{
    if(fnShown){
      fabClicked = Date.now();
      fab.classList.add("fab-opened");
      list.classList.add("fn-list-shown");
    }else{
      fab.classList.remove("fab-opened");
      list.classList.remove("fn-list-shown");
    }
  }catch(err){
    log(err.message);
  }
}

function removeFnotification(element){
  element.remove();
  document.querySelector(".notify-counter").innerText = --counter;
}

function genNotification(){
  let fb = document.querySelector(".notify-items");
  let cnt = document.querySelector(".notify-counter");
  counter++;
  lastN++;
  let yan = document.createElement("div");
  yan.className = "notify-item";
  yan.innerText = `Уведомление ${lastN}`;
  yan.setAttribute("onclick", "removeFnotification(this)");
  fb.append(yan);
  cnt.innerText = counter;
}

function delayed(f){
  return function(){
    let now = Date.now();
    if(Math.abs(now - fabClicked) < 10000){
      setTimeout(genNotification, 10000);
    }else{
      genNotification();
    }
  }
}

window.onload = function(){
  setInterval(delayed(genNotification), 1500);
}