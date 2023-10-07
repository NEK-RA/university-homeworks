import * as readline from 'node:readline/promises';
import { stdin, stdout, stderr } from 'node:process';

/*
readline для чтения
console.log - пишет в stdout
console.error - пишет в stderr
*/
const rl = readline.createInterface({ 
  input: stdin,
  output: stderr
});
// Несколько сокращений
const printout = console.log
const printerr = console.error

// Сама работа

const DEPS_CACHE = new Map()

async function getDeps(pkg) {
  const url = `https://registry.npmjs.org/${pkg}/latest`
  
  let tmp = DEPS_CACHE.get(pkg)
  if(tmp != undefined){
    return tmp
  }
  
  const resp = await fetch(url)
  if(resp.status == 200){
    let data = await resp.json()
    let deps = []
    if (data.dependencies != undefined){
      deps = Array.from(
        new Map(
          Object.entries(
            data.dependencies
          )
        ).keys()
      )
    }
    if(tmp == undefined){
      DEPS_CACHE.set(pkg, deps)
    }
    return deps
  }else{
    if(resp.status == 404){
      printerr(`Пакет ${pkg} не найден!`)
    }else{
      printerr(`Сервер вернул ошибку ${resp.status}: ${resp.statusText}`)
    }
    return []
  }  
}

// Узел графа

class Node{
  name = ""
  parent = undefined
  level = 0
  targetDepth = 1
  deps = []

  constructor(name, parent, depth){
    printerr(`DEBUG: Node: constructor: Creating object for ${name} with depth ${depth}`)
    this.name = name
    this.parent = parent
    this.level = 0
    this.deps = []
    this.targetDepth = depth ?? 1

    if(parent != undefined){
      this.level = parent.level + 1
      parent.deps.push(this)
    }    
  }

  async fillDeps(){
    if(this.level < this.targetDepth){
      let pdeps = await getDeps(this.name)
      pdeps.forEach(dep => {
        new Node(dep, this, this.targetDepth)
      })
      for(let i = 0; i < this.deps.length; i++){
        await this.deps[i].fillDeps()
      }
    }
  }

  toString(){
    return this.name;
  }

  rawGraphviz(){
    let result = ""
    this.deps.forEach(dep => {
      result += `"${this.name}" -> "${dep.name}"\n`
      result += dep.rawGraphviz()
    })

    if(this.parent == undefined){
      return `digraph {\n${result}}`
    }else{
      return result
    }
  }

  graphviz(){
    let raw = this.rawGraphviz().split("\n")
    let clean = []
    for(let i = 0; i < raw.length; i++){
      if(!clean.includes(raw[i])){
        clean.push(raw[i])
      }
    }
    return clean.join("\n")
  }
}

// Запуск и запрос инфы у пользователя
const pname = await rl.question("Укажите название npm пакета: ");
let depth = await rl.question("Глубина сканирования: ")
const lvl = (Number(depth) != NaN) ? Number(depth) : 1

rl.close();

let root = new Node(pname, undefined, lvl)
await root.fillDeps()
printout(root.graphviz())
