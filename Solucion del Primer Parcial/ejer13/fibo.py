import multiprocessing
import itertools
from math import sqrt

def f(inicio, fin):
    """Funcion para el calculo de pares por partes"""
    v = []
    # Calculo del numero aureo
    a = (1 + sqrt(5)) / 2

    # Calculo del primer termino de fibonacci en el rango 
    f1 = int((a**inicio - (-1/a) ** inicio) / sqrt(5))
    inicio += 1

    # Calculo del segundo termino de fibonacci en el rango
    f2 = int((a**inicio - (-1/a) ** inicio) / sqrt(5))
    inicio += 1

    # Añade a la lista
    v.append(f1)
    v.append(f2)

    for i in range(inicio, fin):
        f1, f2 = f2, f1 + f2
        v.append(f2)
    
    return v

def generador_de_serie(nt, np):
    """Funcion genaradora de la serie de fibonaci"""
    # Calculo de los rangos por proceso
    rango = nt // np
    mod = nt % np
    rangos = []
    for i in range(np):
        if i < mod:
            inicio = i * rango + i
            fin = (i + 1) * rango + i
            rangos.append((inicio, fin))
        else:
            inicio = i * rango + mod
            fin = (i + 1) * rango + mod
            rangos.append((inicio, fin))

    #rangos = [(i * rango, (i + 1) * rango) for i in range(np)]

    #Creamos el pool
    with multiprocessing.Pool(np) as pool:
        resultados = pool.starmap(f, rangos)
    
    # Aplanar la lista de listas
    serie = list(itertools.chain(*resultados))
    return serie



if __name__ == '__main__':
    num_terminos = 50
    num_procesos = multiprocessing.cpu_count()

    # Generar la serie
    serie = generador_de_serie(num_terminos, num_procesos)
    print(f'La serie es: {serie}')
