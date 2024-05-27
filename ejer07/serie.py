import multiprocessing
from math import sqrt
import multiprocessing


def f(ini, fin):
    """Funcion para cacular la sumatoria 1/n^2 por partes"""
    sum = 0 
    for i in range(ini,fin):
        sum += 1 / (i * i) 
    return sum

def calculo_pi(nt, np):
    """Calculo de pi usando multiprocesing con la serie del problema de Basilea"""
    # Calcular el rango para cada proceso
    num_tramos = nt // np
    rangos = [(i * num_tramos + 1, (i + 1) * num_tramos + 1) for i in range(np)]
    
    # Crear el pool 
    with multiprocessing.Pool(np) as pool:
        resultados = pool.starmap(f, rangos)
    
    # Sumas los resultados de todos los procesos 
    suma_total = sum(resultados)

    #Calculo de
    pi = sqrt(6 * suma_total)

    return pi

if __name__ == '__main__':
    num_terminos = 10_000_000  # Número total de términos
    num_procesos = multiprocessing.cpu_count()  # Usar el número de CPUs disponibles

    pi = calculo_pi(num_terminos, num_procesos)
    print(f'Estimación de PI: {pi}')   