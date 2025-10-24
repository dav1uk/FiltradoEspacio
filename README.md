<div align="center">
  <img 
    src="https://raw.githubusercontent.com/JeisonAlexis/FiltradoEspacio/main/assets/filtroespacial.svg"
    alt="Banner animado"
    style="width: 50%; max-width: 350px; height: auto; border-radius: 10px;" />
</div>

## <picture><img src = "https://github.com/7oSkaaa/7oSkaaa/blob/main/Images/about_me.gif?raw=true" width = 50px></picture> Paso a Paso Practica Filtrado de Espacio


<div style="padding:10px;border-radius:8px;margin-bottom:8px;background:#f7f7f7;">
      <strong>1️⃣ Paso 1:</strong>
      <p style="margin:.25rem 0 0 0;">Descargar las imágenes de la ruta <strong>/images/imagenes.zip</strong> en este <strong>Repositorio</strong>.</p>
</div>

<div style="padding:10px;border-radius:8px;background:#f7f7f7;">
      <strong>2️⃣ Paso 2:</strong>
      <p style="margin:.25rem 0 0 0;">Cambiar las imágenes a <strong>escala de grises</strong> de la siguiente manera:</p>
</div>

```python
img = cv2.imread(ruta_imagen, cv2.IMREAD_GRAYSCALE)
if img is None:
    raise FileNotFoundError("No se pudo cargar la imagen. Verifica la ruta o la descarga.")

plt.imshow(img, cmap='gray')
plt.axis('off')
plt.title('Imagen Original')
plt.show()
```

<div style="padding:10px;border-radius:8px;background:#f7f7f7;">
      <strong>3️⃣ Paso 3:</strong>
      <p style="margin:.25rem 0 0 0;">Aplicar el filtro promedio (lineal) de la siguiente manera:</p>
</div>

```python
@njit(parallel=True)
def filtro_promedio(img, ksize=3):
    filas, columnas = img.shape
    salida = np.zeros_like(img)
    offset = ksize // 2

    for i in prange(offset, filas - offset):
        for j in range(offset, columnas - offset):
            suma = 0
            for m in range(-offset, offset + 1):
                for n in range(-offset, offset + 1):
                    suma += img[i + m, j + n]
            salida[i, j] = suma // (ksize * ksize)
    return salida
```


<p align="center">
  <a href="https://git.io/typing-svg">
    <img src="https://readme-typing-svg.herokuapp.com?font=Bitcount+Grid+Single&weight=500&duration=3000&pause=1000&color=F5FF29&background=000000&center=true&vCenter=true&width=451&lines=Filtrado+en+espacio;Transformaciones+de+suavizado;Promedio+del+entorno+de+la+vecindad;Filtros+no+lineales;Filtrado+espacial+paso+alto" alt="Typing SVG" />
  </a>
</p>


## <picture><img src = "https://raw.githubusercontent.com/JeisonAlexis/FiltradoEspacio/main/assets/equipo.gif" width = 50px></picture> Presentado Por:

<div style="padding:10px;border-radius:8px;margin-bottom:8px;background:#f7f7f7;">
      <li>Jeison Alexis Rodriguez Angarita</li>
</div>

<div style="padding:10px;border-radius:8px;background:#f7f7f7;">
      <li>Leyder Stiven Jaimes Castellanos</li>
</div>

<div style="padding:10px;border-radius:8px;background:#f7f7f7;">
      <li>Daniel Eduardo Davila Quintero</li>
</div>

<div style="padding:10px;border-radius:8px;background:#f7f7f7;">
      <br>
      <strong>Fundamentos de la Computación Paralela y Distribuida</strong>
</div>



