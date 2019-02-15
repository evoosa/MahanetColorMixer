var c = document.getElementById("my_canvas");
var ctx = c.getContext("2d");

ctx.beginPath();
ctx.rect(20, 20, 150, 100);
ctx.fillStyle = 'rgba(255, 165, 0, 1)';
ctx.fill();

function readURL(input) {
    if (input.files && input.files[0]) {
        var reader = new FileReader();

        reader.onload = function (e) {
            $('#img').attr('src', e.target.result);
            //var img = document.getElementById('img');
            //var canvas = document.getElementById('canvas');
            //canvas.width = img.width;
            //canvas.height = img.height;
            //canvas.getContext('2d').drawImage(img, 0, 0, img.width, img.height);
        }

        reader.readAsDataURL(input.files[0]);
    }
}

$("#imgInp").change(function () {
    readURL(this);
    $(function () {

        $('body').on('click', 'img', function () {
            var h1 = document.getElementById("head1");
            h1.innerHTML = 'rgba(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ', ' + pixelData[3] + ')';
            ;
        })

        $('img').mousemove(function (e) {

            if (!this.canvas) {
                this.canvas = $('<canvas />')[0];
                this.canvas.width = this.width;
                this.canvas.height = this.height;
                this.canvas.getContext('2d').drawImage(this, 0, 0, this.width, this.height);
            }

            pixelData = this.canvas.getContext('2d').getImageData(event.offsetX, event.offsetY, 1, 1).data;

            var c = document.getElementById("my_canvas");
            var ctx = c.getContext("2d");

            ctx.fillStyle = 'rgba(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ', ' + pixelData[3] + ')';
            ctx.fill();

            var h = document.getElementById("head");

            h.innerHTML = 'rgba(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ', ' + pixelData[3] + ')';

        });


    });
});