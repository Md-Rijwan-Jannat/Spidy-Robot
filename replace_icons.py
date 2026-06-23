import re

with open("software/web-controller/index.html", "r") as f:
    html = f.read()

if '<script src="https://unpkg.com/@phosphor-icons/web"></script>' not in html:
    html = html.replace("</head>", '  <script src="https://unpkg.com/@phosphor-icons/web"></script>\n</head>')

# Replace emojis
replacements = {
    '🕹️': '<i class="ph ph-gamepad"></i>',
    '⛔': '<i class="ph ph-octagon"></i>',
    '⚡': '<i class="ph ph-lightning"></i>',
    '😴': '<i class="ph ph-moon"></i>',
    '👋': '<i class="ph ph-hand-waving"></i>',
    '💃': '<i class="ph ph-music-notes"></i>',
    '🙇': '<i class="ph ph-user-minus"></i>',
    '🏊': '<i class="ph ph-waves"></i>',
    '📡': '<i class="ph ph-broadcast"></i>',
    '🎮': '<i class="ph ph-gamepad"></i>',
    '😊': '<i class="ph ph-smiley"></i>',
    '🗣️': '<i class="ph ph-chats"></i>',
    '😢': '<i class="ph ph-smiley-sad"></i>',
    '😠': '<i class="ph ph-smiley-angry"></i>',
    '😲': '<i class="ph ph-smiley-x-eyes"></i>',
    '😍': '<i class="ph ph-heart"></i>',
    '😕': '<i class="ph ph-confused"></i>',
    '🎚️': '<i class="ph ph-sliders-horizontal"></i>',
    '⚙️': '<i class="ph ph-gear"></i>',
    '🎨': '<i class="ph ph-palette"></i>',
    '💾': '<i class="ph ph-floppy-disk"></i>',
    '🔗': '<i class="ph ph-link"></i>',
    '✅': '<i class="ph ph-check-circle"></i>',
    '❌': '<i class="ph ph-x-circle"></i>',
    '✓': '<i class="ph ph-check"></i>'
}

for emoji, icon in replacements.items():
    html = html.replace(emoji, icon)

with open("software/web-controller/index.html", "w") as f:
    f.write(html)
