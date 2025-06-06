
# 🍽️ Proyecto Philosophers – Problema de los Filósofos Comensales

Una implementación del clásico **problema de los filósofos comensales** en C, desarrollado en el contexto de la Escuela 42. El fin es practicar **programación concurrente**, **sincronización** y manejo de **hilos y mutexes**.

---

## 🧠 ¿Qué es el problema?

Cinco filósofos se sientan alrededor de una mesa. Cada uno alterna entre **pensar**, **comer** y **dormir**, pero para comer debe tomar **dos tenedores** (a la izquierda y a la derecha) :contentReference[oaicite:0]{index=0}.  
El desafío consiste en evitar:

- **Interbloqueo** (deadlock), cuando todos toman un tenedor y quedan esperando al otro.
- **Hambre indefinida** (starvation), si algún filósofo nunca consigue comer :contentReference[oaicite:1]{index=1}.

---

## ⚙️ Componentes Técnicos

- Filosofía implementada con **hilos (threads)** y **mutexes** o **semáforos** para controlar el acceso a recursos compartidos :contentReference[oaicite:2]{index=2}.
- Cada filósofo es un hilo que busca comer y debe proteger recursos compartidos.
- El número de filósofos, tiempos de sueño, comida o muerte se pasan por argumentos y se gestionan concurrentemente :contentReference[oaicite:3]{index=3}.

---

## 🎯 Objetivos del Proyecto

- Implementar una solución que permita sincronizar múltiples procesos reales (filósofos).
- Aprender a utilizar:
  - **Mutexes o semáforos** para evitar interbloqueos.
  - **Bloqueo por tiempo** y detección de fallo por inanición (no comer antes de `time_to_die`) :contentReference[oaicite:4]{index=4}.
- Asegurar:
  - Exclusión mutua para acceder a los tenedores.
  - Ausencia de interbloqueos.
  - Justicia para que todos los filósofos coman.

---

## 🛠️ Uso

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [times_each_philosopher_must_eat]
```

### Ejemplo:

```bash
./philo 5 800 200 200 5
```

---

## 🧾 Argumentos

Al ejecutar el programa, se deben pasar los siguientes argumentos en este orden:

- `number_of_philosophers`: número de filósofos 🧠
- `time_to_die`: tiempo en milisegundos que un filósofo puede estar sin comer antes de morir ⚰️
- `time_to_eat`: tiempo en milisegundos que tarda en comer 🍽️
- `time_to_sleep`: tiempo en milisegundos que tarda en dormir 😴
- `times_each_philosopher_must_eat` *(opcional)*: número mínimo de veces que cada filósofo debe comer 🍜

---

## 🧩 Estrategias Comunes

Para resolver el problema sin caer en errores clásicos como el **deadlock**, algunas estrategias habituales incluyen:

- 🔄 **Ordenar adquisición de mutexes**: Cada filósofo toma primero el tenedor con menor ID (por ejemplo, siempre el de la izquierda primero). Así se evita el interbloqueo.
- 🚷 **Limitar acceso simultáneo**: Se permite que sólo un número determinado de filósofos intente tomar tenedores al mismo tiempo.
- 🕴️ **Arbitraje**: Un sistema central decide cuándo un filósofo puede comer, evitando conflictos de acceso a los tenedores.

---

## 🎓 Beneficios Educativos

Este proyecto es excelente para aprender y practicar:

- 🔁 Sincronización entre múltiples hilos.
- ⏱️ Gestión temporal con `sleep` y contadores de tiempo.
- 🚫 Prevención de condiciones de carrera, interbloqueo y inanición.
- 💡 Diseño robusto en C para entornos concurrentes y controlados.

---

## 📚 Recursos Útiles

Aquí algunos enlaces que me han ayudado durante el proyecto:

- 📘 [Artículo en GeeksforGeeks: Dining Philosophers Problem](https://www.geeksforgeeks.org/dining-philosophers-problem/)
- 📗 [Guía de solución para Philosophers – 42](https://github.com/)
- 📙 [Wikipedia – Threads, Mutexes y Sincronización](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- 📒 [AlgoMonster – Concurrencia y planificación](https://algo.monster)

---

## 📌 Conclusión

El proyecto **Philosophers** es una oportunidad ideal para dominar los fundamentos de la **programación concurrente**, el uso de **mutexes y semáforos**, y garantizar la **coherencia y eficiencia** en soluciones multihilo. ¡Un reto a la vez clásico y educativo! 🧵🔐🚀


---

# 📝 Créditos

- 💻 **Proyecto:** Minishell – Escuela 42  
- ✍️ **Autor original:** Miriam Fernández Pérez  

---
