///////////////////////////////////////////////////////////////////////////

function randomInt(min, max){
  if(min > max){
    return 0;
  }
  // верхняя граница включительно
  max++;
  return Math.trunc(Math.random() * (max - min) + min);
}

///////////////////////////////////////////////////////////////////////////

function randomString(length=6){
  let min = "a".charCodeAt(0);
  let max = "z".charCodeAt(0);
  let result = "";
  let upper;
  let char;
  for(let i = 0; i < length; i++){
    upper = randomInt(0,1);
    char = String.fromCharCode(randomInt(min, max));
    result += upper ? char.toUpperCase() : char;
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////

function randomNumber(length=3){
  if(length < 1){
    return 0;
  }
  return randomInt(0, Number.MAX_SAFE_INTEGER) % (10**length);
}

///////////////////////////////////////////////////////////////////////////

function prepareCaptcha(text=true, length=10){
  let captchaText = document.querySelector("#captcha-task");
  let captchaInput = document.querySelector("#captcha-input");
  let button = document.querySelector("#captcha-protected");
  if(text){
    captchaText.innerHTML = randomString()
  }else{
    captchaText.innerHTML = `${randomNumber()} + ${randomNumber()}`;
  }
  captchaInput.removeAttribute("disabled");
  button.setAttribute("disabled", "");
}

///////////////////////////////////////////////////////////////////////////

function checkCaptcha(){
  let captchaText = document.querySelector("#captcha-task").innerHTML;
  let captchaInput = document.querySelector("#captcha-input").value;
  let button = document.querySelector("#captcha-protected");

  let solution = String(captchaInput).trim();
  let textTask = !captchaText.includes("+") && (solution == captchaText);
  let numTask = captchaText.includes("+");
  if(numTask){
    let nums = captchaText.split(" + ").map((el) => Number(el));
    numTask = (nums[0] + nums[1]) == Number(solution);
  }
  if(textTask || numTask){
    button.removeAttribute("disabled");
  }else{
    button.setAttribute("disabled", "");
  }
}

///////////////////////////////////////////////////////////////////////////

function changeCaptcha(){
  prepareCaptcha(false);
}

///////////////////////////////////////////////////////////////////////////

function Accumulator(startingValue){
  this.value = startingValue;
  this.content = {};
  this.read = function(name){
    let amount = Number(prompt(`Какое количество товара ${name} добавить?`));
    if(typeof(amount) == "number"){
      this.value += amount;
      let exist = this.content.hasOwnProperty(name);
      if(exist){
        this.content[name] += amount;
      }else{
        this.content[name] = amount;
      }
    }
  }
}

let state;

function addToCart(name){
  if(!state){
    state = new Accumulator(0);
  }
  state.read(name);
}

function alertCart(){
  if(!state){
    state = new Accumulator(0);
  }
  alert(`Всего товаров: ${state.value}, из них добавлено вручную: ${JSON.stringify(state.content)}`);
}

function clearCart(){
  if(state){
    state = new Accumulator(0);
  }
}

///////////////////////////////////////////////////////////////////////////

function truncateCards(){
  let cards = document.querySelectorAll(".simple-card");
  let length = Number(prompt("Сколько символов оставить?"));
  let original;
  let truncated;
  if(typeof(length) == "number"){
    if(length < 1){
      alert("Слишком маленькая длина строки!");
      return;
    }
    for(card of cards){
      original = card.querySelector(".card-text");
      truncated = card.querySelector(".truncated-text");
      truncated.innerHTML = String(original.innerHTML).substring(0, length) + "...";
      truncated.style.display = "block";
      original.style.display = "none";
    }
  }
}

///////////////////////////////////////////////////////////////////////////

window.onload = function(){
  let captchaText = document.querySelector("#captcha-task");
  let captchaInput = document.querySelector("#captcha-input");
  if(!captchaText || !captchaInput){
    alert("Что-то пошло не так при загрузке страницы");
  }else{
    prepareCaptcha();
    captchaInput.addEventListener("input", checkCaptcha);
  }
  document.querySelector("form").addEventListener("submit", (event) => {
    event.preventDefault();
    return false;
  }, true);
}

///////////////////////////////////////////////////////////////////////////
