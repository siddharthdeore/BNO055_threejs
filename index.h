const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <style>
    html, body { margin: 0; padding: 0; overflow: hidden; }
  </style>
<body>
<script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/103/three.min.js"></script>
<script>
var rotX=0;
var rotY=0;
var rotZ=0;

      // Javascript will go here.
      var scene = new THREE.Scene();
      var aspect = window.innerWidth / window.innerHeight;

      var camera = new THREE.PerspectiveCamera( 75, aspect, 0.1, 100 );
      var renderer = new THREE.WebGLRenderer();
      renderer.setSize( window.innerWidth, window.innerHeight );
      document.body.appendChild( renderer.domElement );

      //Lights
      var light = new THREE.DirectionalLight( 0xffffff ,0.5);
      var amblight = new THREE.AmbientLight( 0xffffff ,0.3);

      //Orbit Control
      //var controls = new THREE.OrbitControls( camera );

      var geometry = new THREE.BoxGeometry( 5, 1, 5 );
      var material = new THREE.MeshPhysicalMaterial ( {color: 0x0ffbdd} );
      var cube = new THREE.Mesh( geometry, material );
      scene.add( cube );
      scene.add( amblight );
      scene.add( light );
      camera.position.z = 10;
      light.position.set(10,5,10);

      var render = function () {
        requestAnimationFrame( render );
        //controls.update();
        //|y
        //|___x
        cube.rotation.set(rotX*3.1415/180,rotY*3.1415/180,rotZ*3.1415/180);
        renderer.render( scene, camera );
      };

      render();

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 200); //200 mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var strXYZ = this.responseText;
      var xyzArr = strXYZ.split(',');
      rotY = -parseFloat(xyzArr[0]);
      rotZ = parseFloat(xyzArr[1]);
      rotX = -parseFloat(xyzArr[2]);
    }
  };
  xhttp.open("GET", "readBNO", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
