var canvas = document.getElementsByTagName('canvas')[0];
var img = document.createElement('img');
img.src = canvas.toDataURL();
var body = document.getElementsByTagName('body')[0];
body.innerHTML = img;
body.append(img);
