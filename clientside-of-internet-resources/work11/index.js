/////////////////////////////////////////////////////
// Некоторые глобальные данные
/////////////////////////////////////////////////////
let cards = [
  {
    title: "ФруктОК",
    description: "Мультифруктовый сок из южных регионов",
    price: 72.50
  },
  {
    title: "Мандарины",
    description: "Из Марокко, завоз 23.11.2023",
    price: 150
  },
  {
    title: "Тестовый товар",
    description: "Тестовое описание, которое должно быть укорочено при отображении на странице",
    price: 99999.99
  },
  {
    title: "Ананас",
    description: "Описание не представлено...",
    price: 200
  },
  {
    title: "???",
    description: "???",
    price: Infinity
  },
]

let three = 0;
let cart;
let lowerPrice;
let higherPrice;
let sorting = null;

/////////////////////////////////////////////////////
// Класс под корзину
/////////////////////////////////////////////////////

function Cart(){
  // массив товаров
  this.items = [];
  this.count = function(){
    let sum = 0;
    this.items.forEach(el => sum += el.amount * el.price);
    return sum;
  }
  // отображение корзины
  this.render = function(){
    let container = document.querySelector("#cart-container")
    let shown = this.items.map(el => {
      return `
      <div class="cart-item">
        <h2>${el.title}</h2>
        <div class="cart-item-buttons">
          <button onclick="cart.decrease('${el.title}')">-</button>
          ${el.amount}
          <button onclick="cart.increase('${el.title}')">+</button>
          <button onclick="cart.remove('${el.title}')">X</button>
        </div>
      </div>
      `
    })
    let cnt = this.count()
    if(cnt > 0){
      shown.unshift(`<h2>Корзина: ${this.items.length} позиций на ${this.count()} руб.</h2>`)
    }else{
      shown.unshift(`<h2>Корзина пуста</h2>`)
    }
    container.innerHTML = shown.join("\n")
  }
  // добавление в корзину
  this.add = function(title){
    let exist = this.items.findIndex(el => el.title == title);
    if(exist != -1){
      this.items[exist].amount++;
    }else{
      let price = cards.find(el=>el.title == title).price
      this.items.push({title: title, amount: 1, price: price});
    }
    this.render();
  }
  // удаление из корзины
  this.remove = function(title){
    let exist = this.items.findIndex(el => el.title == title);
    this.items.splice(exist, 1);
    this.render();
  }
  // увеличение кол-ва
  this.increase = function(title){
    let exist = this.items.findIndex(el => el.title == title);
    this.items[exist].amount++;
    this.render();
  }
  // уменьшение кол-ва
  this.decrease = function(title){
    let exist = this.items.findIndex(el => el.title == title);
    let amount = this.items[exist].amount
    if(amount > 1){
      this.items[exist].amount--;
      this.render();
    }else{
      this.remove(title);
    }
  }
}

/////////////////////////////////////////////////////
// Отображение карточек товаров
/////////////////////////////////////////////////////

function showCurrentThree(){
  let items = document.querySelector(".items-carousel");
  let btnPrev = document.querySelector(".prev");
  let btnNext = document.querySelector(".next");

  let lp = String(document.querySelector("#filter-lower").value).trim();
  let hp = String(document.querySelector("#filter-higher").value).trim();
  if(lp.length == 0){
    lp = 0;
  }else{
    lp = Number(lp);
  }
  if(hp.length == 0){
    hp = Infinity;
  }else{
    hp = Number(hp);
  }
  
  let filtered = cards.filter(el => (el.price >= lp && el.price <= hp));
  switch(sorting){
    case "asc":
      filtered = filtered.sort((e1, e2) => {
        if(e1.price > e2.price){
          return 1
        }
        if(e1.price == e2.price){
          return 0
        }
        if(e1.price < e2.price){
          return -1
        }
      });
      break;
    case "desc":
      filtered = filtered.sort((e1, e2) => {
        if(e1.price > e2.price){
          return -1
        }
        if(e1.price == e2.price){
          return 0
        }
        if(e1.price < e2.price){
          return 1
        }
      });
      break;
    default:
      break;
  }

  if(three == 0){
    btnPrev.setAttribute("disabled","");
  }else{
    btnPrev.removeAttribute("disabled");
  }

  if((filtered.length <= 3) || (filtered.length <= (three+1)*3)){
    btnNext.setAttribute("disabled","");
  }else{
    btnNext.removeAttribute("disabled");
  }

  let currentPart = filtered.slice(three*3, (three+1)*3);
  let shown = currentPart.map(info => {
    let maxSize = "Lorem ipsum dolor sit amet".length*2
    trdesc = info.description.length <= maxSize
      ? info.description
      : info.description.substring(0, maxSize-3) + "..."
    return `
    <div class="card">
      <p class="card-img-placeholder">
            
      </p>
      <h2>${info.title}</h2>
      <p>
        ${trdesc}
      </p>
      <button onclick="cart.add('${info.title}')">Купить / ${info.price} руб</button>
    </div>
    `
  })
  items.innerHTML = shown.join("<br>")
}

/////////////////////////////////////////////////////
// Смена отображаемых карточек
/////////////////////////////////////////////////////

function showPrevThree(){
  if(three != 0){
    three--;
  }else{
    three = Math.trunc(cards.length / 3);
  }
  showCurrentThree();
}

function showNextThree(){
  three = (three + 1) % (Math.trunc(cards.length / 3)+1)
  showCurrentThree();
}

/////////////////////////////////////////////////////
// Смена порядка сортировки
/////////////////////////////////////////////////////

function switchSort(){
  let btn = document.querySelector("#sortBtn")
  switch(sorting){
    case null:
      sorting = "asc";
      btn.innerHTML = "По возрастанию";
      break;
    case "asc":
      sorting = "desc";
      btn.innerHTML = "По убыванию";
      break;
    case "desc":
      sorting = null;
      btn.innerHTML = "Нет";
      break;
  }
}

/////////////////////////////////////////////////////
// Действия после завершения загрузки страницы
/////////////////////////////////////////////////////

window.onload = function(){
  [
    document.querySelector(".prev"),
    document.querySelector(".next")
  ].forEach(el => el.addEventListener("click", showPrevThree));

  showCurrentThree();
  cart = new Cart();
  cart.render();
}