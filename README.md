# Boid-Wasm
A **boids (flocking) simulation** written in **C++** and compiled to **WebAssembly** using **Emscripten**. The simulation runs entirely in the browser.

# Screenshots
<img width="1871" height="918" alt="image" src="https://github.com/user-attachments/assets/7beb42fc-b570-45fd-9025-711e11329c3d" />

<img width="1896" height="967" alt="image" src="https://github.com/user-attachments/assets/2aee282e-9a46-4887-919a-3407845095ba" />

# Dependencies
1. Emscripten SDK (emsdk) 
2. C++17 compatible compiler
3. Python (for local HTTP server)
4. Modern web browser with WebAssembly support

# Build Instructions
1. Install Emscripten
   ```bash
      git clone https://github.com/emscripten-core/emsdk.git
      cd emsdk
      ./emsdk install latest
      ./emsdk activate latest
   ```    
2. Activate Emscripten
      ```bash
         emsdk_env.bat
      ```
3. Build the provided build script
   ```bash
       build.bat
   ```
4. Run a local python server
  ```Bash
  python -m http.server
  ```

# Notes
1. Performance depends on boid count and browser
2. Compiled with -O3 for best performance
