import multiprocessing
import itertools

def f(inicio, fin):
    """Funcion para el calculo de pares por partes"""
    v = []
    for i in range(inicio, fin):
        v.append(2 * i)
    return v

def generador_de_serie(nt, np):
    """Funcion genaradora de la serie de pares"""
    # Calculo de los rangos por proceso
    rango = nt // np
    mod = nt % np
    rangos = []
    for i in range(np):
        if i < mod:
            ini = i * rango + i
            fin = (i + 1) * rango + i
            rangos.append((ini,fin))
        else:
            ini = i * rango + mod
            fin = (i + 1) * rango + mod
            rangos.append((ini,fin))

    # Creamos el pool
    with multiprocessing.Pool(np) as pool:
        resultados = pool.starmap(f, rangos)
    
    # Aplanar la lista de listas
    serie = list(itertools.chain(*resultados))
    return serie

if __name__ == '__main__':
    num_terminos = 100
    num_procesos = multiprocessing.cpu_count()

    # Generar la serie
    serie = generador_de_serie(num_terminos, num_procesos)
    print(f'La serie es: {serie}')
