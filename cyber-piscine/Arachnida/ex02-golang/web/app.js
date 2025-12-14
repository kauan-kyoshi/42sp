import {htmlEscape} from './utils.js'

const $ = (id) => document.getElementById(id)
let files = []
let current = null

function toast(msg, timeout=3000){
  const t = $('toast')
  t.classList.remove('hidden')
  t.textContent = msg
  setTimeout(()=> t.classList.add('hidden'), timeout)
}

function showTopProgress(){
  const bar = document.getElementById('topProgress')
  const fill = bar.querySelector('.fill')
  bar.classList.remove('hidden')
  fill.style.width = '6%'
  let pct = 6
  const t = setInterval(()=>{
    pct = Math.min(98, pct + Math.random()*12)
    fill.style.width = pct + '%'
    if(pct>=98) clearInterval(t)
  }, 220)
  return ()=>{
    clearInterval(t)
    fill.style.width = '100%'
    setTimeout(()=>{bar.classList.add('hidden'); fill.style.width='0%'}, 220)
  }
}

async function listFiles(){
  const stop = showTopProgress()
  const res = await fetch('/api/files')
  files = await res.json()
  stop()
  renderFileList(files)
}

function renderFileList(list){
  const container = $('fileList')
  container.innerHTML = ''
  list.forEach(name => {
    const el = document.createElement('div')
    el.className = 'file-item'
    el.innerHTML = `<div class="file-name">${htmlEscape(name)}</div><div class="file-meta">&nbsp;</div>`
    el.onclick = ()=> selectFile(name, el)
    container.appendChild(el)
  })
}

async function selectFile(name, el){
  try{
    current = name
    $('currentFile').textContent = name
    document.querySelectorAll('.file-item').forEach(n=>n.classList.remove('active'))
    if(el) el.classList.add('active')
    const sk = $('metaSkeleton')
    if(sk) sk.classList.remove('hidden')
    $('metaInfo').textContent = ''
    $('raw').textContent = ''
    const stop = showTopProgress()
    const res = await fetch('/api/metadata?file='+encodeURIComponent(name))
    const md = await res.json()
    stop()
    if(sk) sk.classList.add('hidden')
    $('metaInfo').textContent = JSON.stringify(md, null, 2)
    $('raw').textContent = md.raw || ''
    const preview = $('preview')
    preview.innerHTML = ''
    if(md.preview){
      const img = document.createElement('img')
      img.src = '/data/'+encodeURIComponent(name)
      img.alt = name
      img.onload = ()=>{ preview.appendChild(img); preview.classList.add('has-image') }
      img.onerror = ()=>{ preview.innerHTML = `<div class="placeholder">Preview não disponível</div>` }
    }
  }catch(e){
    toast('Erro ao carregar metadata')
  }
}

$('refresh').onclick = ()=> listFiles()

async function postAction(path, body=null){
  const btns = Array.from(document.querySelectorAll('.btn'))
  btns.forEach(b=>b.classList.add('loading'))
  const stop = showTopProgress()
  try{
    const opts = {method:'POST'}
    if(body){ opts.headers={'Content-Type':'application/json'}; opts.body=JSON.stringify(body) }
    const res = await fetch(path, opts)
    let txt
    try{ txt = await res.json(); $('raw').textContent = JSON.stringify(txt, null,2); toast(txt.message || 'ok') }
    catch(_){ txt = await res.text(); $('raw').textContent = txt; toast('OK') }
  }catch(e){ toast('Request failed') }
  finally{ stop(); btns.forEach(b=>b.classList.remove('loading')); listFiles() }
}

$('btnClear').onclick = async ()=>{
  if(!current) return toast('Selecione um arquivo')
  if(!confirm('Remover EXIF de '+current+'?')) return
  await postAction('/api/clear?file='+encodeURIComponent(current))
}

$('btnUndo').onclick = async ()=>{
  if(!current) return toast('Selecione um arquivo')
  await postAction('/api/undo?file='+encodeURIComponent(current))
}

$('btnSet').onclick = async ()=>{
  if(!current) return toast('Selecione um arquivo')
  const tag = $('tagName').value.trim()
  const val = $('tagVal').value.trim()
  if(!tag || !val) return toast('TAG e VALOR necessários')
  const body = {file:current, set:[tag+'='+val]}
  await postAction('/api/edit', body)
}

$('btnRemove').onclick = async ()=>{
  if(!current) return toast('Selecione um arquivo')
  const tag = $('tagName').value.trim()
  if(!tag) return toast('TAG necessária')
  const body = {file:current, remove:[tag]}
  await postAction('/api/edit', body)
}

// search
$('search').oninput = (e)=>{
  const q = e.target.value.toLowerCase()
  renderFileList(files.filter(f=>f.toLowerCase().includes(q)))
}

listFiles()
