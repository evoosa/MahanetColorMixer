// displays the photo, without the need of a <canvas> tag
function displayAsImage(file) {
  var imgURL = URL.createObjectURL(file),
      img = document.createElement('img');

  img.onload = function() {
    URL.revokeObjectURL(imgURL);
  };

  img.src = imgURL;
  document.body.appendChild(img);
}

// Inserts the file to a canvas
function drawOnCanvas(file) {
  var reader = new FileReader();

  reader.onload = function (e) {
    var dataURL = e.target.result,
        c = document.querySelector('canvas'), // see Example 4
        ctx = c.getContext('2d'),
        img = new Image();

    img.onload = function() {
      c.width = img.width;
      c.height = img.height;
      ctx.drawImage(img, 0, 0);
    };

    img.src = dataURL;
  };

  reader.readAsDataURL(file);
}

// gets the file from the user, by saving the element which has 'file-input' as it's ID
const fileInput = document.getElementById('file-input');

// and eventListener - when the user will upload a photo, it will call the diplay function
//fileInput.addEventListener('change', (e) => drawOnCanvas(e.target.files[0]));
fileInput.addEventListener('change', (e) => displayAsImage(e.target.files[0]));