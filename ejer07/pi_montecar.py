import multiprocessing
import random

def monte_carlo_pi_part(n):
    """Función que realiza parte del cálculo de Monte Carlo para PI."""
    count = 0
    for _ in range(n):
        x = random.random()
        y = random.random()
        if x**2 + y**2 <= 1:
            count += 1
    return count

def calculate_pi(num_samples, num_processes):
    """Función principal para calcular PI usando multiprocessing."""
    # Dividir el número total de muestras entre los procesos
    samples_per_process = num_samples // num_processes

    # Crear un Pool de procesos
    with multiprocessing.Pool(processes=num_processes) as pool:
        # Asignar la tarea a cada proceso
        results = pool.map(monte_carlo_pi_part, [samples_per_process] * num_processes)

    # Sumar los resultados de todos los procesos
    total_count = sum(results)

    # Calcular PI
    pi = 4 * total_count / num_samples
    return pi

if __name__ == '__main__':
    num_samples = 10_000_000  # Número total de muestras
    num_processes = multiprocessing.cpu_count()  # Usar el número de CPUs disponibles

    pi_estimate = calculate_pi(num_samples, num_processes)
    print(f'Estimación de PI: {pi_estimate}')
