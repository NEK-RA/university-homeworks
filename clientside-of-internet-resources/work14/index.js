// зона переменных
let selection = [];
let sliderMoving = false;

function DND(){
  this.current = null;
  this.dragPoint = {
    x: null,
    y: null
  };
  this.dropzone = null;
  this.source = {
    parent: null,
    before: null
  };
  this.reset = function(){
    this.current = null;
    this.dragPoint.x = null;
    this.dragPoint.y = null;
    this.dropzone = null;
    this.source.parent = null;
    this.source.before = null;
  }
}
let dragAndDrop = new DND();

let currentlyHighlighted = null;
let timer;

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

function contentsClickChecker(event){
  event.preventDefault();
  let link;
  let current = event.target;
  while(current != this){
    if(current.tagName == "A"){
      link = current;
      break;
    }else{
      current = current.parentNode;
    }
  }

  // let path = event.path.slice(0, event.path.indexOf(this));
  // let link;
  // for(let i = path.length - 1; i >= 0; i--){
  //   if(path[i].tagName == "A"){
  //     link = path[i];
  //     break;
  //   }
  // }

  if(link){
    let sure = confirm(`Вы действительно хотите перейти по ссылке "${link.innerText}"?\nЕе адрес: ${link.href}`);
    if(sure){
      let target;
      if(event.ctrlKey || event.metaKey){
        target = "_blank";
      }else{
        target = link.getAttribute("target") ?? "_self";
      }
      window.open(link.href, target);
    }
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

function imagesSwitcher(event){
  if(event.target.tagName == "IMG"){
    let viewbox = document.querySelector("#viewbox");
    let viewimg = document.querySelector(".viewimg");
    let {width, height} = viewbox.getBoundingClientRect();
    let viewboxRatio = width / height;
    let size = event.target.getBoundingClientRect();
    let imgRatio = size.width / size.height;
    viewimg.style.opacity = 0;
    setTimeout(()=>{
      viewimg.setAttribute("src", event.target.getAttribute("src"));
      if(imgRatio > viewboxRatio){
        viewimg.classList.add("full-width");
        viewimg.classList.remove("full-height");
      }else{
        viewimg.classList.add("full-height");
        viewimg.classList.remove("full-width");
      }
      viewimg.style.opacity = 1;
    }, 300);
  }
}

function viewimgAdapt(event){
  let viewimg = document.querySelector(".viewimg");
  if(viewimg.getAttribute("src")){
    let viewbox = document.querySelector("#viewbox");
    let {width, height} = viewbox.getBoundingClientRect();
    let viewboxRatio = width / height;
    let size = viewimg.getBoundingClientRect();
    let imgRatio = size.width / size.height;
    if(imgRatio > viewboxRatio){
      viewimg.classList.add("full-width");
      viewimg.classList.remove("full-height");
    }else{
      viewimg.classList.add("full-height");
      viewimg.classList.remove("full-width");
    }
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

function select(event){
  let target;
  let current = event.target;
  while(current != this){
    if(current.classList.contains("selectable")){
      target = current;
      break;
    }
    current = current.parentNode;
  }
  if(target){
    if(event.ctrlKey || event.metaKey){
      let index = selection.indexOf(target);
      if(index == -1){
        selection.push(target);
        target.classList.add("selected");
      }else{
        selection.splice(index,1);
        target.classList.remove("selected");
      }
    }else{
      for(let node of selection){
        node.classList.remove("selected");
      }
      selection = [target];
      target.classList.add("selected");
    }
  }else{
    for(let node of selection){
      node.classList.remove("selected");
    }
    selection = [];
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

function enableSliderMove(event){
  event.preventDefault();
  sliderMoving = true;
}

function disableSliderMove(event){
  sliderMoving = false;
}

function moveSlider(event){
  if(sliderMoving){
    let bar = document.querySelector(".slider-bar");
    bar.size = bar.getBoundingClientRect();
    let runner = document.querySelector(".slider-runner");
    let pos = event.clientX - bar.size.left;
    if(pos >= 0 && pos <= bar.size.width){
      runner.style.left = `${pos - 10}px`;
    }
  }
}

function placeSlider(event){
  let bar = document.querySelector(".slider-bar");
  bar.size = bar.getBoundingClientRect();
  let pos = event.clientX - bar.size.left;
  if(pos >= 0 && pos <= bar.size.width){
    document.querySelector(".slider-runner").style.left = `${pos - 10}px`;
  }
}

function addSliderListeners(){
  let bar = document.querySelector(".slider-bar");
  let runner = document.querySelector(".slider-runner");
  runner.addEventListener("mousedown", enableSliderMove);
  addEventListener("mouseup", disableSliderMove);
  addEventListener("mousemove", moveSlider);
  bar.addEventListener("click", placeSlider);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

function startDND(event){
  let product;
  let current = event.target;
  while(current != this){
    if(current.classList.contains("product")){
      product = current;
      break;
    }
    current = current.parentNode;
  }
  if(product){
    let bcr = product.getBoundingClientRect();
    let dragPoint = {
      x: event.clientX - bcr.left,
      y: event.clientY - bcr.top
    };

    dragAndDrop.current = product;
    dragAndDrop.dragPoint = dragPoint;
    dragAndDrop.source.parent = product.parentNode;
    dragAndDrop.source.before = product.nextSibling;

    product.style.position = "absolute";
    product.style.zIndex = 100;
    product.style.left = `${event.pageX - dragPoint.x}px`;
    product.style.top = `${event.pageY - dragPoint.y}px`;
    product.style.width = `${document.querySelector(".store").getBoundingClientRect().width}px`;
    product.style.transform = "scale(1.1)";
    product.classList.add("highlight");
    document.body.append(product);

    addEventListener("mousemove", moveDND);
    addEventListener("mouseup", endDND);
    product.addEventListener("dragstart", event => event.preventDefault());

    document.querySelector(".dropzone").classList.add("highlight");
  }
}

function moveDND(event){
  if(dragAndDrop.current){
    let {current, dragPoint} = dragAndDrop;
    current.style.left = `${event.pageX - dragPoint.x}px`;
    current.style.top = `${event.pageY - dragPoint.y}px`;

    current.style.display = "none";
    let dropzone = document.elementFromPoint(event.clientX, event.clientY).closest(".dropzone");
    current.style.display = "flex";

    if(dropzone){
      dropzone.classList.add("release-highlight");
      current.classList.add("release-highlight");
      dragAndDrop.dropzone = dropzone;
    }else{
      current.classList.remove("release-highlight");
      document.querySelectorAll(".dropzone").forEach(el => el.classList.remove("release-highlight"));
      dragAndDrop.dropzone = null;
    }
  }
}

function endDND(event){
  if(dragAndDrop.current){
    let {current, dropzone, source} = dragAndDrop;
    if(dropzone){
      dropzone.append(current);
      dropzone.classList.remove("release-highlight");
      recalculateCart();
    }else{
      source.parent.insertBefore(current, source.before);
    }

    current.removeAttribute("style");
    current.classList.remove("highlight");
    current.classList.remove("release-highlight");

    dragAndDrop.reset();
    removeEventListener("mousemove", moveDND);
    removeEventListener("mouseup", endDND);

    document.querySelectorAll(".dropzone").forEach(el => el.classList.remove("highlight"));
  }
}

async function recalculateCart(){
  let cart = document.querySelector(".cart");
  let items = cart.querySelectorAll(".product");
  let total = cart.querySelector(".total");
  let sum = 0.0;
  items.forEach(el => {
    sum += Number(el.children[1].innerText.substring(1));
  });
  total.innerHTML = `Total billing: $${sum}`;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

function noticeHovered(event){
  if(currentlyHighlighted){
    currentlyHighlighted.style.boxShadow = "none";
  }
  currentlyHighlighted = document.elementFromPoint(event.clientX, event.clientY);
}

function animate({timing, draw, duration}) {

  let start = performance.now();

  requestAnimationFrame(function animate(time) {
    // timeFraction изменяется от 0 до 1
    let timeFraction = (time - start) / duration;
    if (timeFraction > 1) timeFraction = timeFraction % 1;

    // вычисление текущего состояния анимации
    let progress = timing(timeFraction);

    draw(progress); // отрисовать её

    if (timeFraction < 1) {
      requestAnimationFrame(animate);
    }

  });
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

addEventListener("load", (event) => {
  // к заданию 1
  document.querySelector("#contents").addEventListener("click", contentsClickChecker);
  // к заданию 2
  document.querySelector(".thumbnails").addEventListener("click", imagesSwitcher);
  addEventListener("resize", viewimgAdapt);
  // к заданию 3
  document.querySelector(".selection-zone").addEventListener("click", select);
  document.querySelector(".selection-zone").addEventListener("mousedown", event => event.preventDefault());
  // к заданию 4
  addSliderListeners();
  // к заданию 5
  document.querySelector(".store").addEventListener("mousedown", startDND);
  // к заданию 6
  addEventListener("mousemove", noticeHovered);

  animate({
    duration: 1000,
    timing(time){ return time},
    draw(frame){
      document.querySelector(".progress-bar").style.width = `${frame * 100}%`;
    }
  });

  animate({
    duration: 3000,
    timing(time){return time},
    draw(frame){
      if(currentlyHighlighted){
        currentlyHighlighted.style.boxShadow = `0px 0px ${frame*15}px ${frame*5}px darkred`;
      }
    }
  });
})