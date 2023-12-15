function pick(selector){
  return document.querySelector(selector);
}

let prevScrollTop = 0;

////////////////////////////////////////////////////////////////////

function updateImgPosition(boxsize){
  let pic = pick(".imgbox > img");
  let picsize = pic.getBoundingClientRect();
  // console.log(picsize);
  pic.style.marginLeft = `${(boxsize.width - picsize.width)/2}px`;
  pic.style.marginTop = `${(boxsize.height - picsize.height)/2}px`;
}

function windowResizeImgBoxListener(event){
  // console.log(event)
  let box = pick(".imgbox");
  let boxsize = box.getBoundingClientRect();
  // console.log(boxsize);
  let winWidth = document.documentElement.clientWidth;
  let winHeight = document.documentElement.clientHeight;
  // console.log(`Window size: ${winWidth} x ${winHeight}`);
  box.style.marginLeft = `${(winWidth - boxsize.width)/2}px`;
  box.style.marginTop = `${(winHeight - boxsize.height)/2}px`;
  boxsize = box.getBoundingClientRect();
  updateImgPosition(boxsize);
}

function showCoords(event){
  pick("#clickoords").innerText = `Точка клика (WxH): ${event.pageX}x${event.pageY}`;
}

////////////////////////////////////////////////////////////////////

let fnShown = false;

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

function genNotification(title){
  let fb = document.querySelector(".notify-items");
  let cnt = document.querySelector(".notify-counter");
  let count = Number(cnt.innerText);
  let yan = document.createElement("div");
  yan.className = "notify-item";
  yan.innerText = title;
  fb.append(yan);
  count++;
  cnt.innerText = count;

  let closeBtn = document.createElement("button");
  closeBtn.innerText = "X";
  closeBtn.style.marginLeft = "20px";
  closeBtn.className = "close-notification-button";
  yan.append(closeBtn);
}

function tempRemoveNotification(event){
  if(event.target.className == "close-notification-button"){
    let parent = event.target.parentNode;
    setTimeout(()=>{
      genNotification(parent.innerText + " again!")
    }, 3000 + (Date.now() % 100)*30);
    parent.remove();
    let cnt = document.querySelector(".notify-counter");
    let count = Number(cnt.innerText);
    count--;
    cnt.innerText = count;
  }
  event.stopPropagation();
}

////////////////////////////////////////////////////////////////////

function firstParalaxListener(event){
  // if(paralaxEnabled){
    let img = pick("#paralax1");
    let curScroll = window.scrollY;
    img.style.marginTop = `${curScroll/2}px`;
  // }
}

function secondParalaxListener(event){
  // if(paralaxEnabled){
    let img = pick("#paralax2");
    let curScroll = window.scrollY;
    // img.style.marginTop = `${curScroll/0.4}px`;
    img.style.top = `${curScroll + (curScroll % 500)}px`;
  // }
}

////////////////////////////////////////////////////////////////////

let lorem;

function expLoremIpsum(event){
  let lipsum = pick("#lorem-ipsum");
  let curScroll = window.scrollY;
  if(curScroll % 2 == 0){
    console.log(`current=${curScroll} <---> prev=${prevScrollTop}`);
    if(curScroll - 50 >= prevScrollTop && curScroll < 1000){
      lipsum.innerText += lorem;
      prevScrollTop = curScroll;
      console.log("Добавляем еще абзац");
    }else if(curScroll == 0){
      lipsum.innerText = lorem;
      prevScrollTop = curScroll;
      console.log("Возвращаем изначальное содержимое");
      genNotification("Спасибо что полистали!")
    }
  }
}

////////////////////////////////////////////////////////////////////

window.onload = function(){
  lorem = pick("#lorem-ipsum").innerText;
  pick(".imgbox").addEventListener("click", showCoords);
  addEventListener("resize", windowResizeImgBoxListener);
  windowResizeImgBoxListener();
  pick(".notify-items").addEventListener("click", tempRemoveNotification);
  genNotification("First");
  genNotification("Second");
  genNotification("Third");
  addEventListener("scroll", expLoremIpsum);
  addEventListener("scroll", firstParalaxListener);
  addEventListener("scroll", secondParalaxListener);
}