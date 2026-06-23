import re

with open('software/web-controller/index.html', 'r') as f:
    content = f.read()

# 1. Compact heights
content = re.sub(r'--btn-h-sm:\s*40px;', '--btn-h-sm:      32px;', content)
content = re.sub(r'--btn-h-md:\s*48px;', '--btn-h-md:      40px;', content)
content = re.sub(r'--btn-h-lg:\s*56px;', '--btn-h-lg:      44px;', content)
content = re.sub(r'--btn-h-xl:\s*64px;', '--btn-h-xl:      52px;', content)

# 2. Gradients -> Solid primary color
content = re.sub(r'background:\s*linear-gradient\(145deg,\s*var\(--red\),\s*var\(--red-dark\)\);', 'background: var(--red);', content)
content = re.sub(r'background:\s*linear-gradient\(145deg,\s*var\(--blue\),\s*var\(--blue-dark\)\);', 'background: var(--blue);', content)
content = re.sub(r'background:\s*linear-gradient\(135deg,\s*var\(--red\)\s*0%,\s*var\(--blue\)\s*100%\);', 'background: var(--blue);', content)
content = re.sub(r'background:\s*linear-gradient\(135deg,\s*var\(--red\),\s*var\(--blue\)\);', 'background: var(--blue);', content)

# 3. Add feedback to connectRobot and saveSettings buttons
content = content.replace(
    "function saveSettings(){\n  const fd=document.getElementById('frameDelay').value;",
    """function saveSettings(){
  const btn = document.querySelector('.btn-save');
  const og = btn.innerHTML;
  btn.innerHTML = '✅ &nbsp;Saved!';
  btn.style.opacity = '0.8';
  setTimeout(() => { btn.innerHTML = og; btn.style.opacity = '1'; }, 1500);
  
  const fd=document.getElementById('frameDelay').value;"""
)

content = content.replace(
    "function connectRobot(){\n  const ip=document.getElementById('robotIP').value.trim();\n  if(!ip) return;\n  localStorage.setItem('robotIP', ip);\n  closeSheet();\n  BASE = ip.startsWith('http') ? ip : 'http://'+ip;\n  log('Connecting to '+BASE+' …');\n  fetch(BASE+'/api/status', {signal: AbortSignal.timeout(5000)})\n    .then(r=>r.json())\n    .then(d=>{\n      DEMO=false;\n      const pill=document.getElementById('pill');\n      pill.className='pill live';\n      document.getElementById('pill-txt').textContent='Live';\n      log('✅ Connected  |  Face: '+(d.currentFace||'default'));\n      dismissSheet();\n      fetchSettings();\n    })\n    .catch(()=>{\n      DEMO=true;\n      log('❌ Cannot reach robot — Demo mode active');\n    });",
    """function connectRobot(){
  const btn = document.querySelector('.sheet-connect');
  const og = btn.innerHTML;
  btn.innerHTML = '⏳ &nbsp;Connecting...';
  
  const ip=document.getElementById('robotIP').value.trim();
  if(!ip) { btn.innerHTML = og; return; }
  localStorage.setItem('robotIP', ip);
  
  BASE = ip.startsWith('http') ? ip : 'http://'+ip;
  log('Connecting to '+BASE+' …');
  fetch(BASE+'/api/status', {signal: AbortSignal.timeout(5000)})
    .then(r=>r.json())
    .then(d=>{
      DEMO=false;
      const pill=document.getElementById('pill');
      pill.className='pill live';
      document.getElementById('pill-txt').textContent='Live';
      log('✅ Connected  |  Face: '+(d.currentFace||'default'));
      btn.innerHTML = '✅ &nbsp;Connected!';
      setTimeout(() => { btn.innerHTML = og; closeSheet(); dismissSheet(); fetchSettings(); }, 1000);
    })
    .catch(()=>{
      DEMO=true;
      btn.innerHTML = '❌ &nbsp;Failed';
      log('❌ Cannot reach robot — Demo mode active');
      setTimeout(() => { btn.innerHTML = og; }, 1500);
    });"""
)


with open('software/web-controller/index.html', 'w') as f:
    f.write(content)
