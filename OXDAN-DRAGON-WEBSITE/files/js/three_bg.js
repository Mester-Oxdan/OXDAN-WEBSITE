// three_bg.js - Enhanced with shapes and particles

let scene, camera, renderer, particles, shapes = [];
let mouseX = 0, mouseY = 0;
let windowHalfX = window.innerWidth / 2;
let windowHalfY = window.innerHeight / 2;

function init() {
    const container = document.getElementById('canvas-container');
    if (!container) return;

    scene = new THREE.Scene();
    scene.fog = new THREE.FogExp2(0x000000, 0.0005);

    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 1, 3000);
    camera.position.z = 1000;

    renderer = new THREE.WebGLRenderer({ alpha: true, antialias: true });
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.setSize(window.innerWidth, window.innerHeight);
    container.appendChild(renderer.domElement);

    // Particle Cloud
    const geometry = new THREE.BufferGeometry();
    const particleCount = 500;
    const positions = [];
    const colors = [];

    const color1 = new THREE.Color(0x2997ff);
    const color2 = new THREE.Color(0xffffff);

    for (let i = 0; i < particleCount; i++) {
        const x = (Math.random() * 2 - 1) * 1500;
        const y = (Math.random() * 2 - 1) * 1500;
        const z = (Math.random() * 2 - 1) * 1500;
        positions.push(x, y, z);

        const mixedColor = color1.clone().lerp(color2, Math.random());
        colors.push(mixedColor.r, mixedColor.g, mixedColor.b);
    }

    geometry.setAttribute('position', new THREE.Float32BufferAttribute(positions, 3));
    geometry.setAttribute('color', new THREE.Float32BufferAttribute(colors, 3));

    const material = new THREE.PointsMaterial({
        size: 3,
        vertexColors: true,
        transparent: true,
        opacity: 0.8,
        sizeAttenuation: true
    });

    particles = new THREE.Points(geometry, material);
    scene.add(particles);

    // Add floating geometric shapes (Dragon-inspired patterns)
    createFloatingShapes();

    document.addEventListener('mousemove', onDocumentMouseMove, false);
    window.addEventListener('resize', onWindowResize, false);

    animate();
}

function createFloatingShapes() {
    // Create dragon-wing-like triangular patterns
    const triangleGeometry = new THREE.BufferGeometry();
    const vertices = new Float32Array([
        -50, 0, 0,
        50, 0, 0,
        0, 100, 0
    ]);
    triangleGeometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));

    for (let i = 0; i < 5; i++) {
        const material = new THREE.MeshBasicMaterial({
            color: 0x2997ff,
            transparent: true,
            opacity: 0.1,
            side: THREE.DoubleSide,
            wireframe: true
        });

        const mesh = new THREE.Mesh(triangleGeometry, material);
        mesh.position.set(
            (Math.random() - 0.5) * 2000,
            (Math.random() - 0.5) * 2000,
            (Math.random() - 0.5) * 2000
        );
        mesh.rotation.set(
            Math.random() * Math.PI,
            Math.random() * Math.PI,
            Math.random() * Math.PI
        );

        shapes.push({ mesh, speed: 0.0005 + Math.random() * 0.001 });
        scene.add(mesh);
    }

    // Add some torus shapes (abstract patterns)
    const torusGeometry = new THREE.TorusGeometry(80, 20, 16, 100);
    for (let i = 0; i < 3; i++) {
        const material = new THREE.MeshBasicMaterial({
            color: 0xffffff,
            transparent: true,
            opacity: 0.05,
            wireframe: true
        });

        const mesh = new THREE.Mesh(torusGeometry, material);
        mesh.position.set(
            (Math.random() - 0.5) * 2000,
            (Math.random() - 0.5) * 2000,
            (Math.random() - 0.5) * 2000
        );

        shapes.push({ mesh, speed: 0.0003 + Math.random() * 0.0005 });
        scene.add(mesh);
    }
}

function onWindowResize() {
    windowHalfX = window.innerWidth / 2;
    windowHalfY = window.innerHeight / 2;
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

function onDocumentMouseMove(event) {
    mouseX = event.clientX - windowHalfX;
    mouseY = event.clientY - windowHalfY;
}

function animate() {
    requestAnimationFrame(animate);
    render();
}

function render() {
    const time = Date.now() * 0.00005;

    camera.position.x += (mouseX * 0.5 - camera.position.x) * 0.05;
    camera.position.y += (-mouseY * 0.5 - camera.position.y) * 0.05;
    camera.lookAt(scene.position);

    particles.rotation.y = time * 0.5;
    particles.rotation.z = time * 0.2;

    // Animate floating shapes
    shapes.forEach(shape => {
        shape.mesh.rotation.x += shape.speed;
        shape.mesh.rotation.y += shape.speed * 1.5;
        shape.mesh.position.y += Math.sin(time * 10 + shape.mesh.position.x) * 0.5;
    });

    renderer.render(scene, camera);
}

document.addEventListener('DOMContentLoaded', init);
