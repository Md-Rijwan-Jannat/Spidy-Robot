#pragma once

#include <Arduino.h>

// ======================================================================
// --- WEB INTERFACE HTML ---
// ======================================================================

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Spidy Robot Controller</title>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
  <meta charset="UTF-8">
  <style>
    @import url('https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;500;600;700&display=swap');
    
    :root {
      --content-color: #ff7a00;
      --content-color-dark: #e06000;
      --content-color-darker: #b34a00;
      --content-color-glow: rgba(255, 122, 0, 0.25);
      --bg-gradient: linear-gradient(135deg, #090a10, #141624);
      --panel-bg: rgba(20, 22, 39, 0.65);
      --panel-border: rgba(255, 255, 255, 0.07);
      --font-family: 'Outfit', sans-serif;
    }
    
    * {
      user-select: none;
      -webkit-user-select: none;
      -webkit-touch-callout: none;
      box-sizing: border-box;
    }
    
    body { 
      font-family: var(--font-family); 
      text-align: center; 
      background: var(--bg-gradient);
      color: #f0f0f5; 
      touch-action: manipulation; 
      margin: 0;
      padding: 15px;
      overflow-x: hidden;
      min-height: 100vh;
    }

    /* Header & Logo styling */
    .header {
      display: flex;
      flex-direction: column;
      align-items: center;
      margin: 15px auto 25px auto;
      max-width: 500px;
    }
    .logo-container {
      width: 90px;
      height: 90px;
      border-radius: 50%;
      background: #111;
      padding: 4px;
      box-shadow: 0 4px 20px rgba(0, 0, 0, 0.5), 0 0 15px var(--content-color-glow);
      border: 2px solid var(--content-color);
      display: flex;
      justify-content: center;
      align-items: center;
      overflow: hidden;
      margin-bottom: 12px;
      transition: transform 0.3s ease;
    }
    .logo-container:hover {
      transform: scale(1.05);
    }
    .logo-container img {
      width: 100%;
      height: auto;
      object-fit: cover;
    }
    h1 {
      font-size: 26px;
      font-weight: 700;
      margin: 0;
      color: #ffffff;
      letter-spacing: 0.5px;
      text-shadow: 0 2px 10px rgba(0,0,0,0.5);
    }
    .subtitle {
      font-size: 13px;
      color: #8f92a1;
      margin: 4px 0 0 0;
      text-transform: uppercase;
      letter-spacing: 1.5px;
    }

    .command-queue {
      font-size: 11px;
      color: #888;
      background: rgba(0, 0, 0, 0.3);
      padding: 6px 14px;
      border-radius: 20px;
      display: inline-block;
      margin-bottom: 25px;
      border: 1px solid rgba(255,255,255,0.03);
    }
    .command-queue.full {
      color: #ff4a4a;
      font-weight: bold;
      border-color: rgba(255, 74, 74, 0.2);
      box-shadow: 0 0 10px rgba(255, 74, 74, 0.1);
    }
    
    /* Section Layout */
    .sections-container {
      display: flex;
      flex-direction: column;
      gap: 20px;
      max-width: 1100px;
      margin: 0 auto;
    }
    
    .section {
      background: var(--panel-bg);
      border: 1px solid var(--panel-border);
      border-radius: 24px;
      padding: 20px;
      box-shadow: 0 12px 40px rgba(0,0,0,0.4);
      backdrop-filter: blur(16px);
      -webkit-backdrop-filter: blur(16px);
      transition: border-color 0.3s ease;
    }
    .section:hover {
      border-color: rgba(255, 122, 0, 0.15);
    }
    
    .section-title {
      font-size: 14px;
      font-weight: 700;
      color: var(--content-color);
      margin: 0 0 18px 0;
      text-transform: uppercase;
      letter-spacing: 2px;
      opacity: 0.9;
    }
    
    /* Premium 3x3 D-Pad */
    .dpad-container { 
      display: flex; 
      flex-direction: column;
      align-items: center;
      width: 100%;
    }
    .dpad { 
      display: grid; 
      grid-template-columns: repeat(3, 1fr); 
      grid-template-rows: repeat(3, 1fr); 
      gap: 12px;
      width: 250px;
      height: 250px;
      margin-bottom: 20px;
    }
    .dpad-btn { 
      background: linear-gradient(145deg, #1b1c2b, #12131f);
      border: 1px solid rgba(255,255,255,0.06); 
      color: #fff;
      font-size: 24px; 
      border-radius: 18px; 
      cursor: pointer; 
      box-shadow: 0 6px 15px rgba(0,0,0,0.4);
      transition: all 0.15s ease;
      display: flex;
      justify-content: center;
      align-items: center;
      touch-action: none;
    }
    .dpad-btn:active { 
      background: linear-gradient(145deg, #12131f, #0a0b12);
      transform: translateY(2px);
      box-shadow: 0 2px 6px rgba(0,0,0,0.4);
      border-color: var(--content-color);
    }
    .dpad-btn.stop-btn {
      background: linear-gradient(145deg, #e63946, #c92a35);
      border-color: #ff6b6b;
      box-shadow: 0 6px 15px rgba(230, 57, 70, 0.3);
    }
    .dpad-btn.stop-btn:active {
      background: linear-gradient(145deg, #c92a35, #a8222c);
      box-shadow: 0 2px 6px rgba(230, 57, 70, 0.2);
    }
    .spacer { 
      visibility: hidden; 
    }
    
    .btn-stop-all { 
      background: linear-gradient(145deg, #e63946, #c92a35);
      width: 100%; 
      max-width: 250px;
      font-size: 16px; 
      padding: 14px; 
      border-radius: 15px;
      border: 1px solid #ff6b6b;
      color: #fff;
      text-transform: uppercase;
      letter-spacing: 2px;
      font-weight: 700;
      cursor: pointer;
      box-shadow: 0 6px 15px rgba(230, 57, 70, 0.25);
      transition: all 0.15s;
    }
    .btn-stop-all:active { 
      transform: translateY(2px);
      box-shadow: 0 2px 6px rgba(230, 57, 70, 0.2);
    }
    
    /* Pose Cards Grid */
    .grid { 
      display: grid; 
      grid-template-columns: repeat(auto-fill, minmax(110px, 1fr)); 
      gap: 12px; 
    }
    .btn-pose { 
      background: rgba(27, 28, 43, 0.8);
      border: 1px solid rgba(255,255,255,0.06);
      border-radius: 16px;
      padding: 12px 6px;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      cursor: pointer;
      transition: all 0.2s cubic-bezier(0.4, 0, 0.2, 1);
    }
    .btn-pose:hover {
      border-color: rgba(255, 122, 0, 0.3);
      background: rgba(255, 122, 0, 0.04);
      transform: translateY(-2px);
    }
    .btn-pose:active { 
      transform: scale(0.95);
      border-color: var(--content-color);
      background: rgba(255, 122, 0, 0.1);
    }
    .pose-thumb {
      width: 64px;
      height: 32px;
      image-rendering: pixelated;
      image-rendering: crisp-edges;
      margin-bottom: 8px;
      border-radius: 6px;
      background: #050508;
      border: 1px solid rgba(255, 255, 255, 0.05);
      padding: 2px;
      box-shadow: 0 4px 10px rgba(0,0,0,0.3);
    }
    .pose-label {
      font-size: 13px;
      font-weight: 500;
      color: #dfdfe6;
    }
    
    /* Action & System Buttons */
    .btn-system { 
      background: linear-gradient(145deg, #2c2d3d, #20212e);
      border: 1px solid rgba(255,255,255,0.05);
      color: #e0e0e0; 
      padding: 14px 28px;
      font-size: 15px;
      border-radius: 14px; 
      cursor: pointer; 
      font-weight: 600;
      box-shadow: 0 4px 10px rgba(0,0,0,0.3);
      transition: all 0.15s;
    }
    .btn-system:active { 
      transform: translateY(2px); 
    }
    
    /* Motor Controls styling */
    .lock-indicator {
      font-size: 12px;
      color: #ff6b6b;
      font-weight: 600;
      text-align: center;
      margin-bottom: 15px;
      display: none;
      background: rgba(255, 107, 107, 0.1);
      padding: 6px;
      border-radius: 8px;
      border: 1px solid rgba(255, 107, 107, 0.2);
    }
    .lock-indicator.active {
      display: block;
      animation: pulse 1.5s infinite alternate;
    }
    
    @keyframes pulse {
      from { opacity: 0.6; }
      to { opacity: 1; }
    }
    
    .motor-slider {
      margin: 18px 0;
      background: rgba(0, 0, 0, 0.2);
      padding: 10px 14px;
      border-radius: 14px;
      border: 1px solid rgba(255,255,255,0.02);
    }
    .motor-slider label {
      display: flex;
      justify-content: space-between;
      font-size: 12px;
      color: #aaa;
      margin-bottom: 8px;
      font-weight: 600;
    }
    .motor-slider input[type="range"] {
      width: 100%;
      height: 6px;
      background: #252636;
      border-radius: 5px;
      outline: none;
      -webkit-appearance: none;
    }
    .motor-slider input[type="range"]::-webkit-slider-thumb {
      -webkit-appearance: none;
      width: 20px;
      height: 20px;
      background: var(--content-color);
      border-radius: 50%;
      cursor: pointer;
      box-shadow: 0 0 10px var(--content-color);
      transition: background 0.15s;
    }
    .motor-slider input[type="range"]::-moz-range-thumb {
      width: 20px;
      height: 20px;
      background: var(--content-color);
      border-radius: 50%;
      cursor: pointer;
      border: none;
      box-shadow: 0 0 10px var(--content-color);
    }
    .motor-slider input[type="range"]:disabled {
      opacity: 0.4;
    }
    
    /* Gamepad Status Badge */
    .gamepad-status {
      font-size: 12px;
      padding: 8px 16px;
      border-radius: 20px;
      border: 1px solid rgba(255,255,255,0.1);
      color: #888;
      background: rgba(0, 0, 0, 0.2);
      display: inline-block;
      font-weight: 500;
    }
    .gamepad-status.connected {
      border-color: #2ecc71;
      color: #2ecc71;
      background: rgba(46, 204, 113, 0.08);
      box-shadow: 0 0 15px rgba(46, 204, 113, 0.15);
    }
    
    /* Panels */
    .settings-panel { 
      display: none; 
      position: fixed; 
      top: 0; 
      left: 0; 
      width: 100%; 
      height: 100%; 
      background: rgba(5, 5, 8, 0.85); 
      z-index: 100; 
      backdrop-filter: blur(12px);
      -webkit-backdrop-filter: blur(12px);
      overflow-y: auto;
    }
    .settings-content { 
      background: linear-gradient(145deg, #121320, #1c1e30);
      border: 1px solid rgba(255,255,255,0.08); 
      max-width: 440px; 
      margin: 40px auto; 
      padding: 25px; 
      border-radius: 24px; 
      text-align: left; 
      box-shadow: 0 20px 50px rgba(0,0,0,0.6); 
    }
    .settings-content h3 { 
      color: #fff; 
      margin-top: 0; 
      text-align: center;
      font-size: 22px;
      font-weight: 700;
      border-bottom: 1px solid rgba(255,255,255,0.05);
      padding-bottom: 15px;
    }
    .settings-section {
      margin: 18px 0;
      padding: 15px;
      background: rgba(0,0,0,0.25);
      border-radius: 16px;
      border: 1px solid rgba(255,255,255,0.02);
    }
    .settings-section h4 {
      color: var(--content-color);
      margin: 0 0 12px 0;
      font-size: 13px;
      text-transform: uppercase;
      letter-spacing: 1.5px;
    }
    .settings-content label { 
      display: block; 
      margin-top: 10px; 
      font-weight: 600; 
      color: #a0a0ab;
      font-size: 12px;
    }
    .settings-content input, 
    .settings-content select { 
      width: 100%; 
      padding: 12px; 
      margin-top: 6px; 
      background: #0d0e17; 
      color: #fff; 
      border: 1px solid rgba(255,255,255,0.06); 
      border-radius: 10px; 
      box-sizing: border-box;
      font-size: 14px;
      font-family: var(--font-family);
    }
    .btn-save { 
      background: linear-gradient(145deg, #2ecc71, #27ae60);
      box-shadow: 0 4px 15px rgba(46, 204, 113, 0.25);
      width: 100%; 
      margin-top: 20px; 
      color: #fff; 
      border: none;
      padding: 14px;
      font-weight: 700;
      border-radius: 12px;
      cursor: pointer;
    }
    .btn-close { 
      background: linear-gradient(145deg, #e74c3c, #c0392b);
      box-shadow: 0 4px 15px rgba(231, 76, 60, 0.2);
      width: 100%; 
      margin-top: 10px; 
      color: #fff; 
      border: none;
      padding: 12px;
      font-weight: 700;
      border-radius: 12px;
      cursor: pointer;
    }
    
    /* Desktop side-by-side layout */
    @media (min-width: 1024px) {
      .sections-container {
        flex-direction: row;
        justify-content: center;
        align-items: flex-start;
        gap: 30px;
      }
      .section-column {
        flex: 1;
        max-width: 500px;
        display: flex;
        flex-direction: column;
        gap: 25px;
      }
    }
  </style>
</head>
<body>
  
  <div class="header">
    <div class="logo-container">
      <img src="data:image/jpeg;base64,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" alt="Spidy Logo" />
    </div>
    <h1>Spidy Controller</h1>
    <div class="subtitle">Access Point Dashboard</div>
  </div>

  <div class="command-queue" id="queueStatus">Command Queue: 0/3</div>
  
  <div class="sections-container">
    <div class="section-column">
      <!-- Movement Control Section -->
      <div class="section">
        <div class="section-title">Movement Control</div>
        <div class="dpad-container">
          <div class="dpad">
            <div class="spacer"></div>
            <button class="dpad-btn up" onpointerdown="move('forward'); event.preventDefault();" onpointerup="stop(); event.preventDefault();" onpointercancel="stop(); event.preventDefault();">&#9650;</button>
            <div class="spacer"></div>
            
            <button class="dpad-btn left" onpointerdown="move('left'); event.preventDefault();" onpointerup="stop(); event.preventDefault();" onpointercancel="stop(); event.preventDefault();">&#9664;</button>
            <button class="dpad-btn stop-btn" onpointerdown="stop(); event.preventDefault();">&#9632;</button>
            <button class="dpad-btn right" onpointerdown="move('right'); event.preventDefault();" onpointerup="stop(); event.preventDefault();" onpointercancel="stop(); event.preventDefault();">&#9654;</button>
            
            <div class="spacer"></div>
            <button class="dpad-btn down" onpointerdown="move('backward'); event.preventDefault();" onpointerup="stop(); event.preventDefault();" onpointercancel="stop(); event.preventDefault();">&#9660;</button>
            <div class="spacer"></div>
          </div>
          <button class="btn-stop-all" onpointerdown="stop(); event.preventDefault();">STOP ALL</button>
        </div>
      </div>

      <!-- Poses & Animations Section -->
      <div class="section">
        <div class="section-title">Poses & Animations</div>
        <div class="grid">
          <button class="btn-pose" onclick="pose('rest')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAYklEQVR4nK3NsQmAMBCF4d8kSAoJKSwsLHQDS0tHcyx7V3GA1GIhLxgnyMHBx8G7B7XHf2si4IQBuIUEPCOYDWgSmJzoClzBJZzMu1JY9ArDQdCFaSVYYcHTCpE+d/3tteYFR0gJFCGDlVoAAAAASUVORK5CYII=" class="pose-thumb" alt="Rest Face" />
            <span class="pose-label">Rest</span>
          </button>
          <button class="btn-pose" onclick="pose('stand')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAYklEQVR4nK3NsQmAMBCF4d8kSAoJKSwsLHQDS0tHcyx7V3GA1GIhLxgnyMHBx8G7B7XHf2si4IQBuIUEPCOYDWgSmJzoClzBJZzMu1JY9ArDQdCFaSVYYcHTCpE+d/3tteYFR0gJFCGDlVoAAAAASUVORK5CYII=" class="pose-thumb" alt="Stand Face" />
            <span class="pose-label">Stand</span>
          </button>
          <button class="btn-pose" onclick="pose('wave')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAfElEQVR4nK2PsQmDUABE37+vgiBoIeQXFo7gCL9MkcIBUmSCkBGsMoejOEpm0CYQ5Ms3juAVxzV3j4PTNUUzg8xE+SUgIK/BY8EVCV7QgKMVLHAHkc6v9Toi9CZ0PQm/y7O61RUWl3UFj1i3n7hjDpAY/knB79AdHcNpbza+SRMANzGHAwAAAABJRU5ErkJggg==" class="pose-thumb" alt="Wave Face" />
            <span class="pose-label">Wave</span>
          </button>
          <button class="btn-pose" onclick="pose('dance')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAZUlEQVR4nK3NwQnCYBCE0cf4Izl4yFF7EGzEXmzMIiwlFYgiSA4ShQ2xgnyHYZadnWV1UtpHO3DWxfbN0YOuVrvobYYlOjDmycQruePnKie+XLCvqzb3Fv+eVuYT4/J0KjOPK/AD5W8Qmh6hn1EAAAAASUVORK5CYII=" class="pose-thumb" alt="Dance Face" />
            <span class="pose-label">Dance</span>
          </button>
          <button class="btn-pose" onclick="pose('swim')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAgUlEQVR4nK3PvQ2CUBiF4ZePLxdJDPUtTKDSxsKEAUQnYRNv5RbuwAQE4yLMYIXmBgg/I3Cq05wnObB1DCU8AeVouAN7Tj0fEH996aOGwHKu03Jwgm1JC4PwFVUXV7Igv4uQ+N67LhPa2y5rAHt4d3kwgREk4SwDIch/Lcx73e7OCAM/GDIekjAJAAAAAElFTkSuQmCC" class="pose-thumb" alt="Swim Face" />
            <span class="pose-label">Swim</span>
          </button>
          <button class="btn-pose" onclick="pose('point')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAW0lEQVR4nL3OMQ3DQBQD0Pe/MnS8MeNBCISDcgiKoZAKoVACI0OG6G5pAVSx7MGSLZu7sAxuegQPtVYvWcpub+QxMx/paYs3yorWpIJOOolhhmb42/pZIf53+wIJhQtqcR7ZSAAAAABJRU5ErkJggg==" class="pose-thumb" alt="Point Face" />
            <span class="pose-label">Point</span>
          </button>
          <button class="btn-pose" onclick="pose('pushup')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAa0lEQVR4nGNgoDZgg1AHmKB8BQYehgMg4QQmBgYLBgYJBgYmBgY1BolLDAJMAgwvGSQvMDAwyNTw2z98kGMPwvBB96C/zx8HBhmGBwwCfAwFLB8YFjB8YGL4wMADMTCBCWY0wi5GMA0hqQoAfnsSqRpc9MQAAAAASUVORK5CYII=" class="pose-thumb" alt="Pushup Face" />
            <span class="pose-label">Pushup</span>
          </button>
          <button class="btn-pose" onclick="pose('bow')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAe0lEQVR4nK2PsQ3CMBBFny+WWSBSJHSFRcUUKGQSKmZIx43CCIxwo7igQExAERxksUJ++d5rPmw/pTOQYEodg4nYkTUD3d+7RBRmIHGQkB4BMMNsUNJoEKEOj5YnZVa8CHte73Av7A6AZJelB9YzwrWVF4/12cj03erMD3iDGwWk5bRtAAAAAElFTkSuQmCC" class="pose-thumb" alt="Bow Face" />
            <span class="pose-label">Bow</span>
          </button>
          <button class="btn-pose" onclick="pose('cute')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAbElEQVR4nGNgoDbggVAHmKB8BQYJxgYGBjaGBCYGhgIGBgkGBiaG/z4MDJcYBJgUGC79/3sBJPJDgF1AIecAE8ODqL/cc/44MFgwHmD+wMdQwCDByABSkMDE8J+BgeEfAwMTC4ZdEMtACqkMANLoFKtD4ut9AAAAAElFTkSuQmCC" class="pose-thumb" alt="Cute Face" />
            <span class="pose-label">Cute</span>
          </button>
          <button class="btn-pose" onclick="pose('freaky')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAXklEQVR4nGNgoBJgbgBTBxiYIfwEJhYIQ4CBDcIwYIKpZeJgYP/B8J+BgYmhDsTP4WBh2PFTuY/FmImJ4SlI5CkDAx8Dg+Q9ZgYDkHbGP1Dt/2tAsuwwK/5Qy/U4AQBatg6pcbpVzAAAAABJRU5ErkJggg==" class="pose-thumb" alt="Freaky Face" />
            <span class="pose-label">Freaky</span>
          </button>
          <button class="btn-pose" onclick="pose('worm')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAeUlEQVR4nK3PsQnCUBhF4c8/EiwEU4qIOIBFwAXeKBnBETJKhrCwfANYZArBLmUQA4I6Qm5zmgOHy9wrf8jBcTOsdFHaUhM8pnRTBc+26L/OKy0TUSmvp4y9g2ZUx2BHwvrcyYv7JaSmyPohYqBFjEzi3Sr+0dnffAB+bRq+kIKPhQAAAABJRU5ErkJggg==" class="pose-thumb" alt="Worm Face" />
            <span class="pose-label">Worm</span>
          </button>
          <button class="btn-pose" onclick="pose('shake')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAZElEQVR4nK2PsRGAMAwD36KhSMFRUcIODMAYlIyS0Rgl9AxAwSVcMCPgQtKdJfkMf0/zokW5YJFzQe1nUXYeheW6gcAKMxvB8jQUkigCgxrvIyQJzrXGLzi6Ksxv7bq99/dneADCZRB/5b6Q9QAAAABJRU5ErkJggg==" class="pose-thumb" alt="Shake Face" />
            <span class="pose-label">Shake</span>
          </button>
          <button class="btn-pose" onclick="pose('shrug')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAXElEQVR4nGNgoBJgg1AHmDggjAVM/6AyTAIQWoDpzw2oGgYJqBQDVI6Jgfn/b77//xiYQLwGsMhfRg4/RiYGJhYGhn8KIJEPDAz/vzAwOIDVCDAwfIBbSi1PYAIA04MRS0ozsRwAAAAASUVORK5CYII=" class="pose-thumb" alt="Shrug Face" />
            <span class="pose-label">Shrug</span>
          </button>
          <button class="btn-pose" onclick="pose('dead')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAATUlEQVR4nK2KgQ2AQAgDj2qcwwUcwcTRfjQX8/lUZYNvCLRXYLpurw196UHxEorQftNRobqISA8iD/IE9fqIZrMgLjLNEiJYEbsrs8kapq8Oa7lMK10AAAAASUVORK5CYII=" class="pose-thumb" alt="Dead Face" />
            <span class="pose-label">Dead</span>
          </button>
          <button class="btn-pose" onclick="pose('crab')">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAQAAAACK5kMpAAAAcUlEQVR4nLWPMQ5AQBREn0+i2awtVbR0WyodSalbeodwFEfR6pQkiPw7MNWbTCaTgd9kIHtgEWjVz2Lwt4sHyCmMtXTkxJPt8TRkxhZ4gVrYBgQqnhOFcnQBbZEe0AlwHgCnCSFyIVp1S7WKZgpfvXgBmKsUgdjh9QkAAAAASUVORK5CYII=" class="pose-thumb" alt="Crab Face" />
            <span class="pose-label">Crab</span>
          </button>
        </div>
      </div>
    </div>

    <div class="section-column">
      <!-- Settings & Status Section -->
      <div class="section">
        <div class="section-title">System</div>
        <button class="btn-system" onclick="openSettings()">Settings</button>
        <div style="margin-top: 15px;">
          <div id="gamepadStatus" class="gamepad-status">Gamepad disconnected</div>
        </div>
      </div>
    </div>
  </div>

  <div id="settingsPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Settings</h3>
      
      <div class="settings-section">
        <h4>Animation Parameters</h4>
        <label>Frame Delay (ms):</label>
        <input type="number" id="frameDelay" min="1" max="1000" step="1">
        <label>Walk Cycles:</label>
        <input type="number" id="walkCycles" min="1" max="50" step="1">
      </div>

      <div class="settings-section">
        <h4>Motor Settings</h4>
        <label>Motor Current Delay (ms):</label>
        <input type="number" id="motorCurrentDelay" min="0" max="500" step="1">
        <label>Motor Speed:</label>
        <select id="motorSpeed">
          <option value="slow">Slow</option>
          <option value="medium" selected>Medium</option>
          <option value="fast">Fast</option>
        </select>
      </div>

      <div class="settings-section">
        <h4>Theme</h4>
        <label>Accent Color:</label>
        <select id="themeColor">
          <option value="#ff7a00">Orange (Default)</option>
          <option value="#66d9ef">Cyan</option>
          <option value="#a8dadc">Light Blue</option>
          <option value="#2ecc71">Green</option>
          <option value="#e74c3c">Red</option>
          <option value="#9b59b6">Purple</option>
          <option value="#f39c12">Yellow</option>
          <option value="#e91e63">Pink</option>
          <option value="custom">Custom</option>
        </select>
        <input type="color" id="customColor" value="#ff7a00" style="margin-top: 10px; display: none;">
      </div>

      <button class="btn-system" style="width: 100%; margin-top: 20px;" onclick="openMotorControl()">Manual Motor Control</button>

      <button class="btn-save" onclick="saveSettings()">Save Settings</button>
      <button class="btn-close" onclick="closeSettings()">Close</button>
    </div>
  </div>

  <div id="motorControlPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Manual Motor Control</h3>
      <div class="lock-indicator" id="lockIndicator">Locked during animations</div>
      
      <div class="settings-section">
        <div class="motor-controls">
          <div class="motor-slider">
            <label><span>S0 R1</span><span id="m1val">90&deg;</span></label>
            <input type="range" id="motor1" min="0" max="180" value="90" oninput="updateMotor(1, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S1 R2</span><span id="m2val">90&deg;</span></label>
            <input type="range" id="motor2" min="0" max="180" value="90" oninput="updateMotor(2, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S2 L1</span><span id="m3val">90&deg;</span></label>
            <input type="range" id="motor3" min="0" max="180" value="90" oninput="updateMotor(3, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S3 L2</span><span id="m4val">90&deg;</span></label>
            <input type="range" id="motor4" min="0" max="180" value="90" oninput="updateMotor(4, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S4 R4</span><span id="m5val">90&deg;</span></label>
            <input type="range" id="motor5" min="0" max="180" value="90" oninput="updateMotor(5, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S5 R3</span><span id="m6val">90&deg;</span></label>
            <input type="range" id="motor6" min="0" max="180" value="90" oninput="updateMotor(6, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S6 L3</span><span id="m7val">90&deg;</span></label>
            <input type="range" id="motor7" min="0" max="180" value="90" oninput="updateMotor(7, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S7 L4</span><span id="m8val">90&deg;</span></label>
            <input type="range" id="motor8" min="0" max="180" value="90" oninput="updateMotor(8, this.value)">
          </div>
        </div>
      </div>

      <button class="btn-close" onclick="closeMotorControl()">Close</button>
    </div>
  </div>

<script>
// Command queue management - max 3 commands
let commandQueue = 0;
const MAX_COMMANDS = 3;
let motorsLocked = false;

// Load theme on page load
document.addEventListener('DOMContentLoaded', () => {
  loadTheme();
});

function loadTheme() {
  const savedColor = localStorage.getItem('themeColor');
  if (savedColor) {
    applyTheme(savedColor);
  }
}

function applyTheme(color) {
  const root = document.documentElement;
  root.style.setProperty('--content-color', color);
  
  // Calculate darker shades
  const rgb = hexToRgb(color);
  if (rgb) {
    const dark = `rgb(${Math.max(0, rgb.r - 20)}, ${Math.max(0, rgb.g - 20)}, ${Math.max(0, rgb.b - 20)})`;
    const darker = `rgb(${Math.max(0, rgb.r - 40)}, ${Math.max(0, rgb.g - 40)}, ${Math.max(0, rgb.b - 40)})`;
    const glow = `rgba(${rgb.r}, ${rgb.g}, ${rgb.b}, 0.25)`;
    
    root.style.setProperty('--content-color-dark', dark);
    root.style.setProperty('--content-color-darker', darker);
    root.style.setProperty('--content-color-glow', glow);
  }
}

function hexToRgb(hex) {
  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}

function updateQueueStatus() {
  const queueEl = document.getElementById('queueStatus');
  queueEl.textContent = `Command Queue: ${commandQueue}/${MAX_COMMANDS}`;
  if (commandQueue >= MAX_COMMANDS) {
    queueEl.classList.add('full');
  } else {
    queueEl.classList.remove('full');
  }
}

function canSendCommand() {
  return commandQueue < MAX_COMMANDS;
}

function incrementQueue() {
  commandQueue++;
  updateQueueStatus();
  setTimeout(() => {
    if (commandQueue > 0) {
      commandQueue--;
    }
    updateQueueStatus();
  }, 1000);
}

function lockMotors(duration = 3000) {
  motorsLocked = true;
  document.getElementById('lockIndicator').classList.add('active');
  for (let i = 1; i <= 8; i++) {
    const slider = document.getElementById('motor' + i);
    if (slider) slider.disabled = true;
  }
  setTimeout(() => {
    motorsLocked = false;
    document.getElementById('lockIndicator').classList.remove('active');
    for (let i = 1; i <= 8; i++) {
      const slider = document.getElementById('motor' + i);
      if (slider) slider.disabled = false;
    }
  }, duration);
}

function move(dir) { 
  if (!canSendCommand()) return;
  incrementQueue();
  fetch('/cmd?go=' + dir).catch(console.log); 
}

function stop() { 
  commandQueue = 0;
  updateQueueStatus();
  fetch('/cmd?stop=1').catch(console.log); 
}

function pose(name) { 
  if (!canSendCommand()) return;
  incrementQueue();
  lockMotors(3000);
  fetch('/cmd?pose=' + name).catch(console.log); 
}

function updateMotor(motorNum, value) {
  if (motorsLocked) return;
  document.getElementById('m' + motorNum + 'val').textContent = value + '\u00B0';
  if (!canSendCommand()) return;
  incrementQueue();
  fetch('/cmd?motor=' + motorNum + '&value=' + value).catch(console.log);
}

function openSettings() {
  fetch('/getSettings').then(r => r.json()).then(data => {
    document.getElementById('frameDelay').value = data.frameDelay || 100;
    document.getElementById('walkCycles').value = data.walkCycles || 10;
    document.getElementById('motorCurrentDelay').value = data.motorCurrentDelay || 20;
    document.getElementById('motorSpeed').value = data.motorSpeed || 'medium';
    
    // Load theme settings
    const savedColor = localStorage.getItem('themeColor') || '#ff7a00';
    const colorSelect = document.getElementById('themeColor');
    const customColorInput = document.getElementById('customColor');
    
    // Check if saved color matches a preset
    let matchFound = false;
    for (let option of colorSelect.options) {
      if (option.value === savedColor) {
        colorSelect.value = savedColor;
        matchFound = true;
        break;
      }
    }
    
    if (!matchFound) {
      colorSelect.value = 'custom';
      customColorInput.value = savedColor;
      customColorInput.style.display = 'block';
    }
    
    document.getElementById('settingsPanel').style.display = 'block';
  }).catch(() => {
    // Fallback if settings endpoint doesn't exist yet
    document.getElementById('frameDelay').value = 100;
    document.getElementById('walkCycles').value = 10;
    document.getElementById('motorCurrentDelay').value = 20;
    
    const savedColor = localStorage.getItem('themeColor') || '#ff7a00';
    document.getElementById('themeColor').value = savedColor;
    
    document.getElementById('settingsPanel').style.display = 'block';
  });
  
  // Add event listener for theme color change
  document.getElementById('themeColor').addEventListener('change', function() {
    const customColorInput = document.getElementById('customColor');
    if (this.value === 'custom') {
      customColorInput.style.display = 'block';
    } else {
      customColorInput.style.display = 'none';
      applyTheme(this.value);
    }
  });
  
  document.getElementById('customColor').addEventListener('input', function() {
    applyTheme(this.value);
  });
}

function closeSettings() { 
  document.getElementById('settingsPanel').style.display = 'none'; 
}

function openMotorControl() {
  document.getElementById('motorControlPanel').style.display = 'block';
}

function closeMotorControl() {
  document.getElementById('motorControlPanel').style.display = 'none';
}

function saveSettings() {
  const fd = document.getElementById('frameDelay').value;
  const wc = document.getElementById('walkCycles').value;
  const mcd = document.getElementById('motorCurrentDelay').value;
  const ms = document.getElementById('motorSpeed').value;
  
  // Save theme color
  const colorSelect = document.getElementById('themeColor');
  const customColorInput = document.getElementById('customColor');
  const themeColor = colorSelect.value === 'custom' ? customColorInput.value : colorSelect.value;
  localStorage.setItem('themeColor', themeColor);
  applyTheme(themeColor);
  
  fetch(`/setSettings?frameDelay=${fd}&walkCycles=${wc}&motorCurrentDelay=${mcd}&motorSpeed=${ms}`)
    .then(() => closeSettings())
    .catch(() => closeSettings());
}

let activeGamepadIndex = null;
let gamepadPollId = null;
let lastButtonStates = [];
let lastAxisDir = { x: 0, y: 0 };
const axisThreshold = 0.5;
const pollIntervalMs = 80;

const buttonBindings = {
  0: () => pose('stand'),   // A / Cross
  1: () => pose('wave'),    // B / Circle
  2: () => pose('dance'),   // X / Square
  3: () => pose('swim'),    // Y / Triangle
  4: () => pose('point'),   // LB / L1
  5: () => pose('pushup'),  // RB / R1
  6: () => pose('bow'),     // LT / L2
  7: () => pose('shake'),   // RT / R2
  8: () => stop(),          // Back / Share
  9: () => pose('rest'),    // Start / Options
  10: () => pose('cute'),   // L3
  11: () => pose('freaky'), // R3
  12: () => move('forward'),// D-pad up
  13: () => move('backward'),// D-pad down
  14: () => move('left'),   // D-pad left
  15: () => move('right'),  // D-pad right
  16: () => stop(),         // Home / PS
  17: () => pose('worm')    // Touchpad / extra
};

const buttonReleaseStop = new Set([12, 13, 14, 15]);

function updateGamepadStatus(connected) {
  const status = document.getElementById('gamepadStatus');
  if (!status) return;
  if (connected) {
    status.textContent = 'Gamepad connected';
    status.classList.add('connected');
  } else {
    status.textContent = 'Gamepad disconnected';
    status.classList.remove('connected');
  }
}

function handleButtonChange(index, pressed) {
  if (pressed) {
    const action = buttonBindings[index];
    if (action) action();
  } else if (buttonReleaseStop.has(index)) {
    stop();
  }
}

function getAxisDirection(x, y) {
  if (Math.abs(x) < axisThreshold && Math.abs(y) < axisThreshold) return { x: 0, y: 0 };
  if (Math.abs(x) > Math.abs(y)) {
    return { x: x > 0 ? 1 : -1, y: 0 };
  }
  return { x: 0, y: y > 0 ? 1 : -1 };
}

function applyAxisDirection(dir) {
  if (dir.x === 1) move('right');
  else if (dir.x === -1) move('left');
  else if (dir.y === 1) move('backward');
  else if (dir.y === -1) move('forward');
  else stop();
}

function pollGamepad() {
  const pads = navigator.getGamepads ? navigator.getGamepads() : [];
  const pad = pads && activeGamepadIndex !== null ? pads[activeGamepadIndex] : null;
  if (!pad) {
    updateGamepadStatus(false);
    return;
  }
  updateGamepadStatus(true);

  if (!lastButtonStates.length) {
    lastButtonStates = pad.buttons.map(b => !!b.pressed);
  }
  pad.buttons.forEach((btn, i) => {
    const pressed = !!btn.pressed;
    if (pressed !== lastButtonStates[i]) {
      handleButtonChange(i, pressed);
      lastButtonStates[i] = pressed;
    }
  });

  const x = pad.axes[0] || 0;
  const y = pad.axes[1] || 0;
  const dir = getAxisDirection(x, y);
  if (dir.x !== lastAxisDir.x || dir.y !== lastAxisDir.y) {
    applyAxisDirection(dir);
    lastAxisDir = dir;
  }
}

window.addEventListener('gamepadconnected', (e) => {
  activeGamepadIndex = e.gamepad.index;
  lastButtonStates = [];
  lastAxisDir = { x: 0, y: 0 };
  updateGamepadStatus(true);
  if (!gamepadPollId) {
    gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
  }
});

window.addEventListener('gamepaddisconnected', (e) => {
  if (activeGamepadIndex === e.gamepad.index) {
    activeGamepadIndex = null;
    lastButtonStates = [];
    lastAxisDir = { x: 0, y: 0 };
    updateGamepadStatus(false);
  }
});

if (navigator.getGamepads) {
  setInterval(() => {
    if (activeGamepadIndex !== null) return;
    const pads = navigator.getGamepads();
    if (!pads) return;
    for (let i = 0; i < pads.length; i++) {
      if (pads[i]) {
        activeGamepadIndex = pads[i].index;
        updateGamepadStatus(true);
        if (!gamepadPollId) {
          gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
        }
        break;
      }
    }
  }, 1000);
}
</script>
</body>
</html>
)rawliteral";
