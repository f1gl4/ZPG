`Studenti se během předmětu seznámí se základními principy 3D počítačové grafiky s využitím jazyka C++ a grafického API OpenGL (případně Vulkan) a prakticky si vyzkouší práci se shadery v jazyce GLSL. 
Postupně projdou jednotlivé kroky od načtení 3D modelu až po jeho vizualizaci, doplněnou o práci s kamerou, transformace objektů a celé scény, nastavování osvětlení, práci s texturami, normálovými mapami, stíny, tvorbu skyboxu a další.`

-

`In this course, students will learn the fundamental principles of 3D computer graphics using C++ and the OpenGL (or potentially Vulkan) graphics API. They will get hands-on experience working with shaders in GLSL. 
Students will progressively work through the entire pipeline, from loading a 3D model to its final visualization, covering camera manipulation, object and scene transformations, lighting, texturing, normal mapping, shadows, skybox creation, and more.`


## Requirements 

Linux (Ubuntu 22.04/24.04 or any distro with X11/XWayland)

Docker



## Linux — build & run with Docker

```
git clone https://github.com/f1gl4/ZPG.git
cd ZPG-main
docker build -t zpg-linux .
```

#### Wayland/Xorg: create an X11 cookie (once per reboot)

```
XAUTH=/tmp/.docker.xauth
touch "$XAUTH"
xauth nlist "$DISPLAY" | sed -e 's/^..../ffff/' | xauth -f "$XAUTH" nmerge -
chmod 644 "$XAUTH"
```

#### Run

```
docker run --rm -it \
  --user $(id -u):$(id -g) \
  --net=host --ipc=host \
  -e DISPLAY=$DISPLAY \
  -e XAUTHORITY=/tmp/.docker.xauth \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v "$XAUTH:/tmp/.docker.xauth:ro" \
  --device /dev/dri \
  zpg-linux
```
