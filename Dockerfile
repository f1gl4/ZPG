FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y build-essential cmake git pkg-config libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxi-dev libxcursor-dev libxinerama-dev libxrandr-dev libglfw3-dev libglew-dev libglm-dev libassimp-dev libstb-dev libsoil-dev zlib1g-dev && rm -rf /var/lib/apt/lists/*

WORKDIR /app/project
COPY project/ /app/project/

RUN rm -rf CMakeFiles CMakeCache.txt Makefile cmake_install.cmake compile_commands.json CMakeScripts CMakeFiles-* build || true

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release
CMD ["./build/zpg"]

