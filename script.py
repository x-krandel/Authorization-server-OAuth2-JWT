import matplotlib.pyplot as plt
import numpy as np

# Dane pomiarowe (Hz, dB)
data = np.array([
    [10, 16.95145318],
    [20, 19.71750715],
    [50, 21.13809703],
    [100, 21.28915978],
    [1000, 21.58362492],
    [2000, 21.28915978],
    [5000, 21.28915978],
    [10000, 21.28915978],
    [20000, 21.28915978],
    [50000, 20.8278537],
    [100000, 18.4855857],
    [500000, 9.77101433]
])

# Rozdzielenie na X i Y
freq = data[:, 0]
gain = data[:, 1]

# Poziom -3 dB
reference = 21.58362492  # wartość @ 1 kHz
minus_3db = reference - 3

# Tworzenie wykresu
plt.figure(figsize=(10, 6))
plt.semilogx(freq, gain, color='blue', linewidth=2, label='Charakterystyka K(f)')
plt.axhline(minus_3db, color='orange', linestyle='--', linewidth=2, label='Poziom -3 dB')

# Opisy osi i tytuł
plt.title('Charakterystyka amplitudowo-częstotliwościowa wzmacniacza', fontsize=14)
plt.xlabel('Częstotliwość [Hz]', fontsize=12)
plt.ylabel('Wzmocnienie K [dB]', fontsize=12)

# Siatka techniczna
plt.grid(True, which='both', linestyle=':', linewidth=0.7)

# Legenda
plt.legend()

# Wyświetlenie
plt.show()
