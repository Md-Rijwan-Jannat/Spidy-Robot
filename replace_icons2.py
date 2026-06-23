import re

with open("software/web-controller/index.html", "r") as f:
    html = f.read()

# Replace remaining emojis
replacements = {
    '🤸': '<i class="ph ph-person-simple-walk"></i>',
    '🧍': '<i class="ph ph-person-simple"></i>',
    '🤷': '<i class="ph ph-person-arms-spread"></i>',
    '🥰': '<i class="ph ph-heart-straight"></i>',
    '🤔': '<i class="ph ph-question"></i>',
    '🤩': '<i class="ph ph-star"></i>',
    '⏳': '<i class="ph ph-hourglass"></i>',
    '▶': '<i class="ph ph-caret-right"></i>',
    '◀': '<i class="ph ph-caret-left"></i>',
    '▲': '<i class="ph ph-caret-up"></i>',
    '▼': '<i class="ph ph-caret-down"></i>'
}

for emoji, icon in replacements.items():
    html = html.replace(emoji, icon)

with open("software/web-controller/index.html", "w") as f:
    f.write(html)
