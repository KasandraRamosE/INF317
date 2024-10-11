#5. Con multiprocessing calculo pi hasta el término 1 millón, utilice al menos 3 procesadores.
import multiprocessing

def leibniz(inicio, fin):
    suma= 0.0
    for k in range(inicio, fin):
        termino= (-1)**k / (2 * k + 1)
        suma += termino
    return suma

def main():
    num_terminos= 1000000
    num_procesos= 3
    tamaño_segmento= num_terminos // num_procesos

    with multiprocessing.Pool(processes=num_procesos) as pool:
        rangos= [(i, i + tamaño_segmento) for i in range(0, num_terminos, tamaño_segmento)]
        resultados= pool.starmap(leibniz, rangos)

    pi= 4 * sum(resultados)
    print(f"Valor de pi con {num_terminos} términos: {pi:.15f}")

if __name__ == "__main__":
    main()
