import re

with open("software/web-controller/index.html", "r") as f:
    html = f.read()

# Replace Phosphor script with FontAwesome CSS
html = html.replace(
    '<script src="https://unpkg.com/@phosphor-icons/web"></script>',
    '<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css">'
)

fa_mapping = {
    'ph-gamepad': 'fa-solid fa-gamepad',
    'ph-octagon': 'fa-solid fa-stop',
    'ph-lightning': 'fa-solid fa-bolt',
    'ph-moon': 'fa-solid fa-moon',
    'ph-hand-waving': 'fa-solid fa-hand',
    'ph-music-notes': 'fa-solid fa-music',
    'ph-user-minus': 'fa-solid fa-person-praying',
    'ph-waves': 'fa-solid fa-water',
    'ph-broadcast': 'fa-solid fa-satellite-dish',
    'ph-smiley': 'fa-solid fa-face-smile',
    'ph-chats': 'fa-solid fa-comments',
    'ph-smiley-sad': 'fa-solid fa-face-frown',
    'ph-smiley-angry': 'fa-solid fa-face-angry',
    'ph-smiley-x-eyes': 'fa-solid fa-face-dizzy',
    'ph-heart': 'fa-solid fa-heart',
    'ph-confused': 'fa-solid fa-face-meh',
    'ph-sliders-horizontal': 'fa-solid fa-sliders',
    'ph-gear': 'fa-solid fa-gear',
    'ph-palette': 'fa-solid fa-palette',
    'ph-floppy-disk': 'fa-solid fa-floppy-disk',
    'ph-link': 'fa-solid fa-link',
    'ph-check-circle': 'fa-solid fa-circle-check',
    'ph-x-circle': 'fa-solid fa-circle-xmark',
    'ph-check': 'fa-solid fa-check',
    'ph-person-simple-walk': 'fa-solid fa-person-walking',
    'ph-person-simple': 'fa-solid fa-person',
    'ph-person-arms-spread': 'fa-solid fa-person-rays',
    'ph-heart-straight': 'fa-solid fa-heart',
    'ph-question': 'fa-solid fa-question',
    'ph-star': 'fa-solid fa-star',
    'ph-hourglass': 'fa-solid fa-hourglass-half',
    'ph-caret-right': 'fa-solid fa-caret-right',
    'ph-caret-left': 'fa-solid fa-caret-left',
    'ph-caret-up': 'fa-solid fa-caret-up',
    'ph-caret-down': 'fa-solid fa-caret-down'
}

for ph, fa in fa_mapping.items():
    html = html.replace(f'ph {ph}', fa)

with open("software/web-controller/index.html", "w") as f:
    f.write(html)
