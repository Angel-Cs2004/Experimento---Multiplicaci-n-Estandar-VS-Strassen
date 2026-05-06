# Multiplicación Estándar vs Strassen

Estudio comparativo de rendimiento entre la multiplicación de matrices estándar O(n³) y el algoritmo de Strassen O(n^2.807), para el curso de Análisis y Diseño de Algoritmos (ADA) - UNSA.

## Requisitos

- g++ con soporte C++17
- gnuplot (con terminal pngcairo)

## Uso

```bash
make run       # Compila, ejecuta el benchmark y genera el gráfico
make           # Solo compila
make clean     # Elimina binario y objetos
```

El benchmark corre 10 repeticiones por tamaño de matriz (n = 4 hasta 512) y calcula la mediana. Los resultados se guardan en `data/resultados.dat` y el gráfico en `plots/matmul_analysis.png`.

## Estructura

```
├── src/
│   ├── main.cpp        # Sweep de tamaños y salida de resultados
│   ├── matrix.cpp      # Generación, operaciones y padding de matrices
│   ├── multiply.cpp    # Multiplicación estándar y Strassen (BASE=32)
│   └── benchmark.cpp   # Medición por mediana
├── include/            # Headers correspondientes
├── data/               # Resultados del benchmark (generado)
└── plots/              # Gráfico y script gnuplot
```

## Algoritmos

- **Estándar**: triple bucle clásico, O(n³)
- **Strassen**: recursivo con 7 productos en lugar de 8, O(n^2.807). Usa `standardMul` como caso base para n ≤ 32 y padding para matrices de tamaño impar.
