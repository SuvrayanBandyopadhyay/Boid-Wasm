emcc boid.cpp -O3 ^
-s EXPORTED_FUNCTIONS="['_init','_addBoid','_run','_getXPtr','_getYPtr','_getSize']" ^
-s EXPORTED_RUNTIME_METHODS="['HEAPF32']" ^
-o boid.js
