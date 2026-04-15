
> Proyecto académico enfocado en modelado de sistemas y eficiencia en tiempo de ejecución.

---

## Descripción

Este proyecto fue desarrollado en el marco de la facultad como parte de mi formación en programación. Consiste en un sistema de gestión de exposiciones para una galería de arte, implementado en C++, con el objetivo de modelar y organizar obras, exposiciones y visitantes de manera estructurada.

El sistema permite representar exposiciones compuestas por múltiples obras, cada una con un identificador único que garantiza su correcta gestión dentro del programa. A su vez, las exposiciones están planificadas en función de horarios de inicio y fin, lo que permite organizarlas dentro de un calendario y evitar superposiciones.

---

## Funcionalidades

- Gestión de obras con identificadores únicos  
- Planificación de exposiciones mediante horarios (inicio y fin)  
- Organización dentro de un calendario  
- Gestión de visitantes mediante un Árbol Binario de Búsqueda (ABB)  
- Sistema de reservas y control de asistencia  

---

## Estructuras de datos

Para la gestión de visitantes se utiliza un **Árbol Binario de Búsqueda (ABB)**, lo que permite mantener operaciones eficientes incluso con mayor volumen de datos.

```cpp
// Estructura base de ABB utilizada para visitantes
struct Nodo {
    Visitante dato;
    Nodo* izq;
    Nodo* der;
};
```

---

## Enfoque de desarrollo

Se buscó que cada componente del sistema no solo cumpliera su función, sino que lo hiciera de forma eficiente. Las decisiones de diseño estuvieron orientadas a minimizar el tiempo de ejecución y mantener una estructura clara del código.

Este enfoque apunta a que el sistema pueda escalar sin comprometer su rendimiento, considerando desde el inicio el impacto de cada operación en el comportamiento general del programa.

---

## Tecnologías y conceptos utilizados

```diff
+ C++
+ Programación orientada a objetos
+ Estructuras de datos (ABB)
+ Modelado de sistemas
+ Lógica de negocio
```
Aplicar conceptos vistos en la facultad en un caso práctico, con foco en el diseño de sistemas, el uso de estructuras de datos y la resolución eficiente de problemas.
