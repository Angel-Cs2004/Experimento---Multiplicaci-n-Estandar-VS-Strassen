# Multiplicación Estándar vs. Strassen

Estudio comparativo de rendimiento entre la multiplicación de matrices estándar O(n³) y el algoritmo de Strassen O(n^2.807), desarrollado para el curso de Análisis y Diseño de Algoritmos (ADA) — Universidad Nacional de San Agustín (UNSA), 2025.

El objetivo del experimento es determinar empíricamente el valor N₀ a partir del cual el algoritmo de Strassen supera en tiempo de ejecución al método estándar, contrastando dicho valor con el umbral teórico de n ≈ 32 sugerido en las diapositivas del MIT.

---

## ¿Qué hace este proyecto?

El benchmark ejecuta ambos algoritmos sobre matrices cuadradas de tamaño n ∈ {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 512}, midiendo el tiempo de ejecución con `std::chrono::high_resolution_clock`. Para reducir el ruido del sistema operativo, cada tamaño se repite 10 veces y se reporta la **mediana** (no la media), lo que elimina el efecto de picos aislados por interrupciones del scheduler.

Las matrices de entrada se generan con `std::mt19937` usando semilla fija (42), garantizando que el experimento sea completamente reproducible: cualquier persona que ejecute el código obtendrá exactamente las mismas matrices y, en el mismo hardware, los mismos tiempos.

Los resultados obtenidos muestran que el N₀ empírico de esta implementación es aproximadamente **n = 256**, significativamente mayor que el valor teórico, debido principalmente al overhead de alocaciones dinámicas y la pérdida de localidad de caché en la recursión de Strassen.

---

## Algoritmos implementados

**Multiplicación estándar** — Triple bucle clásico ijk con complejidad O(n³). Accede a la memoria de forma secuencial, lo que favorece la localidad de caché y permite al compilador vectorizar el bucle automáticamente con instrucciones SIMD cuando se compila con `-O2`.

**Algoritmo de Strassen** — Implementación recursiva que divide cada matriz en 4 subcuadrantes de tamaño n/2 y calcula 7 productos recursivos (P1–P7) en lugar de los 8 del método estándar, reduciendo la complejidad teórica a O(n^2.807). Dos decisiones de implementación importantes:

- **Caso base (BASE = 32):** cuando el subproblema llega a n ≤ 32, se invoca directamente la multiplicación estándar en lugar de continuar recursando. Esto evita el overhead de decenas de niveles de recursión adicionales sobre matrices pequeñas donde el triple bucle es más eficiente.
- **Padding para n impar:** si n no es divisible entre 2, la matriz se expande en 1 fila y columna (rellena con ceros) antes de recursar, y se recorta al tamaño original al finalizar. Esto garantiza que la división en cuadrantes siempre sea exacta.

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
4    0.000167       0.000166
8    0.000803       0.000736
...
512  112.193867     62.148612
```

El gráfico comparativo se genera automáticamente en `plots/matmul_analysis.png`.

---

## Estructura del proyecto

```
├── src/
│   ├── main.cpp        # Sweep de tamaños, salida de resultados a stdout y stderr
│   ├── matrix.cpp      # Generación de matrices, operaciones (add, sub, get, set, pad, unpad)
│   ├── multiply.cpp    # Multiplicación estándar y Strassen con caso base y padding
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
| 32 | 0.025804 | 0.024056 | Strassen ✓ (caso base activo) |
| 64 | 0.125275 | 0.166518 | Estándar |
| 128 | 1.008653 | 1.145424 | Estándar |
| 256 | 9.937449 | 8.497127 | **Strassen ✓ (primer cruce real)** |
| 384 | 39.212694 | 33.006082 | Strassen ✓ |
| 512 | 112.193867 | 62.148612 | **Strassen ✓ (~44% más rápido)** |

El cruce no es abrupto: en n = 320 el estándar recupera brevemente la ventaja, confirmando que N₀ ≈ 256 es el inicio de una transición gradual, no un punto de quiebre instantáneo.

---

## Informe

El análisis completo del experimento, incluyendo diseño experimental, identificación de N₀, hipótesis sobre la divergencia teórico-empírica y reflexión crítica, está disponible en el informe académico adjunto al repositorio.
