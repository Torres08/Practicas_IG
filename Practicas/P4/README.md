# Practica 4: Materiales, fuentes de luz y Texturas

## Ejemplo Visual
Dentro de la Carpeta P4 hacer este comando para limpiar todos los .o, compilar y ejecutar el archivo.
```bash
make total
```
![p4_v2](Entrega/P4_v2.gif)


## Implementado 
- Añadido en la clase MiMalla las propiedades `DiffuseReflectivity`, `SpecularReflectivity`, `AmbientReflectivity`, y como extra `Shininess`
- He implementado, jugando con las propiedades anteriores, 3 modelos con las siguientes texturas (tres objetos con diferentes materiales)
  - Beethoven de Vidrio Verde
  - Vaca de Oro
  - Tetera de plástico Azul

- He creado la clase dado, donde le asigno la textura dado, las coordenadas de la textura se las paso a mano (dado)

- he hecho el tutorial de `Creación de cajas AABB (bounding box) y normalización de coordenadas` implementada en la funcion de MiMalla `processVertices()` 

- He creado la funcion `drawConTexturaCilindrica()` para, cuando le asigno una textura como madera.jpg o marmol.jpg , calcule las coordenadas de textura de una forma cilindrica de la forma:  
  
```c++
float u1 = atan2(v1.z - centerZ, v1.x - centerX) / (2 * M_PI) + 0.5f;
float v1_tex = (v1.y - minY) / (maxY - minY); // Normalizar la coordenada y
float u2 = atan2(v2.z - centerZ, v2.x - centerX) / (2 * M_PI) + 0.5f;
float v2_tex = (v2.y - minY) / (maxY - minY); // Normalizar la coordenada y
float u3 = atan2(v3.z - centerZ, v3.x - centerX) / (2 * M_PI) + 0.5f;
float v3_tex = (v3.y - minY) / (maxY - minY); // Normalizar la coordenada y
```

- Con `d` podemos intercambiar el tipo de textura entre madera y marmol y con `g` cambiamos ese modelo entre una taza y el lobo para probar el texturizado automatico de MiMalla. (malla con textura)

- clases mas modularizadas (MiCubo, MiDado, MiPiramide, MiBrazoMecánico, etc).

- Arreglado problema clase en el que el coche de la practica 2 se veia más brilloso

