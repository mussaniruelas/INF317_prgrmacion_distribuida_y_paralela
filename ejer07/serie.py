import multiprocessing
from math import sqrt
import multiprocessing

def f(ini, fin):
    sum = 0 
    for i in range(ini,fin):
        sum += 1 / (i * i) 
    return sum

def calculo_pi(nt, np):

    num_tramos = nt // np
    rangos = [(i * num_tramos + 1, (i + 1) * num_tramos + 1) for i in range(np)]
    
    with multiprocessing.Pool(np) as pool:
        resultados = pool.starmap(f, rangos)
    
    suma_total = sum(resultados)
    pi = sqrt(6 * suma_total)

    return pi

if __name__ == '__main__':
    num_terminos = 10_000_000  # Número total de términos
    num_procesos = multiprocessing.cpu_count()  # Usar el número de CPUs disponibles

    pi = calculo_pi(num_terminos, num_procesos)
    print(f'Estimación de PI: {pi}')   