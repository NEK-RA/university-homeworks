// window.onload = function(){
//   alert("Hi")
// }

let liked = false;
let drawing = false;
let imgCounter = 0;
let lastImg = {x: null, y: null};

function switchlike(){
  let likebox = document.querySelector(".likebox");
  let lcount = document.querySelector(".like-counter")
  let like = document.querySelector(".like")

  num = Number(lcount.innerText)
  if(!liked){
    liked = true;
    num++;
    lcount.innerText = num;
    like.innerText = "favorite";
    likebox.classList.add("likebox-active");
    like.classList.add("like-active");
  }else{
    liked = false;
    num--;
    lcount.innerText = num;
    like.innerText = "favorite_border";
    likebox.classList.remove("likebox-active");
    like.classList.remove("like-active");
  }
}

function adminLogin(){
  let login = prompt("Имя пользователя администратора");
  if(!login){
    alert("Отменено");
    return;
  }
  if(login == "Админ"){
    let password = prompt("Ваш пароль");
    if(!password){
      alert("Отменено");
    }
    if(password == "Я главный"){
      alert("Здравствуйте!");
    }else{
      alert("Неверный пароль")
    }
  }else{
    alert("Я вас не знаю!");
  }
}

function showUserLogin(){
  let form = document.querySelector(".ulogin-form");
  if(form){
    if(form.style.display && form.style.display != "none"){
      form.style.opacity = 0;
      setTimeout(function(){
        form.style.display = "none";
      }, 500);
    }else{
      form.style.display = "block";
      for(let i = 1; i <= 10; i++){
        setTimeout(function(){
          form.style.opacity = 0.1 * i;
        }, 50);
      }
    }
  }else{
    alert("Проблемы при загрузке страницы, попробуйте позже...")
  }
}

function loginIfExist(){
  let login = userLogin.value;
  let password = userPass.value;
  if(login=="Админ" && password == "Я главный"){
    alert("Здравствуйте!")
  }else{
    let agree = confirm("Пользователь не найден. Желаете пройти регистрацию?")
    if(agree){
      alert("Круто!");
    }else{
      alert("Попробуйте еще раз...")
    }
  }
}

function makePictures(event){
  borderLeft = 16;
  borderRight = event.target.clientWidth - 16;
  borderTop = 16 + 50;
  borderBottom = event.target.clientHeight - 16 + 50;
  x = event.clientX
  y = event.clientY
  mouseXok = x > (borderLeft) && x < borderRight;
  mouseYok = y > borderTop && y < borderBottom;
  // let text = `
  //   left=${borderLeft}px
  //   right=${borderRight}px
  //   top=${borderTop}px
  //   bottom=${borderBottom}px

  //   xOk = ${mouseXok}
  //   yOk = ${mouseYok}

  //   cursor-pointer = {${x}, ${y}}
  //   images added: ${imgCounter}
  // `;
  // event.target.innerText = text;
  if(mouseXok && mouseYok){
    let frequencyCondition;
    const diff = 16; // distance in pixels
    frequencyCondition = (Math.abs(x - lastImg.x) > diff) || (Math.abs(y - lastImg.y) > diff);
    event.target.innerText = `
      cursor: {x=${x}, y=${y}}
      last img: ${JSON.stringify(lastImg)}
      dx = ${Math.abs(x - lastImg.x)}
      dy = ${Math.abs(y - lastImg.y)}
      ${frequencyCondition ? "allowed":"not allowed"}
    `;
    let layout = document.querySelector(".layout");
    if(frequencyCondition && layout){
      let image = document.createElement("img");
      image.id = `img-draw-${imgCounter}`;
      image.style.position = "absolute";
      image.style.top = `${y - borderTop}px`;
      image.style.left = `${x - borderLeft}px`;
      image.src="html5.png";
      image.zIndex = 0;
      layout.appendChild(image);
      imgCounter++;
      lastImg.x = x;
      lastImg.y = y;
    }
  }
}

function draw(){
  let main = document.querySelector("main")
  if(drawing){
    drawing = false;
    main.removeEventListener("mousemove", makePictures);

  }else{
    drawing = true;
    main.addEventListener("mousemove", makePictures);
  }
}

function clearLayout(){
  console.log("clicked");
  let layout = document.querySelector(".layout");
  layout.innerHTML = "";
}