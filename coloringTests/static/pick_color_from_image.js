// create the canvas element, and get it's context
var c = document.getElementById("my_canvas");
var ctx = c.getContext("2d");

// create a rectangle, and fill it with a default color
ctx.beginPath();
ctx.rect(20, 20, 150, 100);
ctx.fillStyle = 'rgba(255, 165, 0, 1)';
ctx.fill();

// get the image's URL
function readURL(input) {
    if (input.files && input.files[0]) {
        var reader = new FileReader();

        reader.onload = function (e) {
            $('#img').attr('src', e.target.result);
        };

        reader.readAsDataURL(input.files[0]);
    }
}

$("#imgInp").change(function () {
    // get the image's URL
    readURL(this);
    $(function () {
        // function to display the picked color, when the image is clicked
        $('body').on('click', 'img', function () {
            var picked_color = document.getElementById("picked_color");
            picked_color.innerHTML = 'Picked Color: rgba(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ', ' + pixelData[3] + ')';
            // TODO - send it to the server!!! prompt first?!
        });

        // function to display the color the mouse hovers above
        $('img').mousemove(function (e) {

            // create a canvas var, if this is the first time
            // you hover over the image
            if (!this.canvas) {
                this.canvas = $('<canvas />')[0];
                this.canvas.width = this.width;
                this.canvas.height = this.height;
                this.canvas.getContext('2d').drawImage(this, 0, 0, this.width, this.height);
            }

            // fill the rectangle with the hovered over color
            pixelData = this.canvas.getContext('2d').getImageData(event.offsetX, event.offsetY, 1, 1).data;

            var c = document.getElementById("my_canvas");
            var ctx = c.getContext("2d");

            ctx.fillStyle = 'rgba(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ', ' + pixelData[3] + ')';
            ctx.fill();

            var current_color = document.getElementById("current_color");

            current_color.innerHTML = 'Current Color: rgba(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ', ' + pixelData[3] + ')';

        });


    });
});