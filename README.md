# Multiplicación Estándar vs. Strassen

Estudio comparativo de rendimiento entre la multiplicación de matrices estándar O(n³) y el algoritmo de Strassen O(n^2.807), desarrollado para el curso de Análisis y Diseño de Algoritmos (ADA) — Universidad Nacional de San Agustín (UNSA), 2025.

El objetivo del experimento es determinar empíricamente el valor N₀ a partir del cual el algoritmo de Strassen supera en tiempo de ejecución al método estándar, contrastando dicho valor con el umbral teórico de n ≈ 32 sugerido en las diapositivas del MIT.

---

## ¿Qué hace este proyecto?

El benchmark ejecuta ambos algoritmos sobre matrices cuadradas de tamaño n ∈ {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 512, 640, 768, 1024}, midiendo el tiempo de ejecución con `std::chrono::high_resolution_clock`. Para reducir el ruido del sistema operativo, cada tamaño se repite 10 veces y se reporta la **mediana**, lo que elimina el efecto de picos aislados por interrupciones del scheduler.

Las matrices se generan con `std::mt19937` usando semilla fija (42), garantizando que el experimento sea completamente reproducible: cualquier persona que ejecute el código obtendrá exactamente las mismas matrices y, en el mismo hardware, los mismos tiempos.

---

## Algoritmos implementados

**Multiplicación estándar** — Triple bucle clásico ijk con complejidad O(n³). Accede a la memoria de forma secuencial, lo que favorece la localidad de caché y permite al compilador vectorizar el bucle con instrucciones SIMD al compilar con `-O2`.

**Algoritmo de Strassen** — Implementación recursiva que divide cada matriz en 4 subcuadrantes de tamaño n/2 y calcula 7 productos recursivos (P1–P7) en lugar de los 8 del método estándar, reduciendo la complejidad teórica a O(n^2.807). Dos decisiones de implementación clave:

- **Caso base (BASE = 32):** cuando el subproblema llega a n ≤ 32 se invoca directamente la multiplicación estándar. Recursar hasta 1×1 generaría un overhead de alocaciones dinámicas tan grande que destruiría cualquier ventaja del algoritmo.
- **Padding para n impar:** si n no es divisible entre 2, la matriz se expande en 1 fila y columna (rellena con ceros) antes de recursar y se recorta al finalizar, garantizando que la división en cuadrantes siempre sea exacta.

---

## Requisitos

- `g++` con soporte C++17
- `gnuplot` con terminal `pngcairo`

---

## Uso

```bash
make run      # Compila, ejecuta el benchmark y genera el gráfico
make          # Solo compila
make clean    # Elimina binario y objetos
```

Los resultados se guardan en `data/resultados.dat` con el formato:

```
# n  t_standard_ms  t_strassen_ms
4    0.000215       0.000281
...
1024  1031.798862   431.180454
```

El gráfico comparativo se genera en `plots/matmul_analysis.png`.

---

## Estructura del proyecto

```
├── src/
│   ├── main.cpp        # Sweep de tamaños, salida de resultados
│   ├── matrix.cpp      # Generación, operaciones y padding de matrices
│   ├── multiply.cpp    # Multiplicación estándar y Strassen (BASE=32)
│   └── benchmark.cpp   # Medición por mediana sobre 10 repeticiones
├── include/
│   ├── matrix.h
│   ├── multiply.h
│   └── benchmark.h
├── data/
│   └── resultados.dat  # Generado al ejecutar make run
└── plots/
    ├── matmul_analysis.gp   # Script gnuplot
    └── matmul_analysis.png  # Gráfico generado
```

---

## Resultados

| n | Estándar (ms) | Strassen (ms) | Ventaja |
|---|---|---|---|
| 32 | 0.036164 | 0.037446 | Estándar |
| 64 | 0.114055 | 0.152819 | Estándar |
| 128 | 1.014752 | 1.151118 | Estándar |
| 256 | 9.019338 | 8.461906 | **Strassen ✓ (primer cruce)** |
| 320 | 19.696552 | 22.462786 | Estándar (retroceso temporal) |
| 384 | 37.554021 | 31.677285 | **Strassen ✓ (ventaja consolidada)** |
| 512 | 110.189120 | 59.398621 | Strassen ✓ (46% más rápido) |
| 640 | 234.461274 | 160.056181 | Strassen ✓ (32% más rápido) |
| 768 | 412.217170 | 232.357019 | Strassen ✓ (44% más rápido) |
| 1024 | 1031.798862 | 431.180454 | **Strassen ✓ (58% más rápido)** |

El cruce no es abrupto: en n=320 el estándar recupera brevemente la ventaja tras el primer cruce en n=256, confirmando que N₀ ≈ 256 marca el inicio de una transición gradual. A partir de n=384 la ventaja de Strassen se consolida definitivamente, alcanzando un 58% de mejora en n=1024.

---

## Informe

El análisis completo del experimento, incluyendo diseño experimental, identificación de N₀, hipótesis sobre la divergencia teórico-empírica y reflexión crítica, está disponible en el informe académico adjunto al repositorio.
