"""
Simulador de Benchmark - Algoritmos de Ordenação
=================================================
Gera 4 rodadas simuladas com variação estatística realista
baseada nos dados reais coletados em cada ambiente.
 
Máquinas:
  bare  → Ryzen 5 4600G, 16GB DDR4 2666, Windows, GCC/VSCode
  vm1   → VirtualBox · Ubuntu 25.04 · 4 vCPUs · 8GB RAM · KVM
  vm2   → VirtualBox · Ubuntu 25.04 · 2 vCPUs · 4GB RAM · KVM
 
Uso:
  python benchmark_simulator.py              # simula todas as máquinas
  python benchmark_simulator.py --machine vm1
  python benchmark_simulator.py --machine bare --rounds 6 --seed 42
"""
 
import random
import csv
import argparse
import os
from copy import deepcopy
 
# ─────────────────────────────────────────────
# DADOS REAIS (Rodada 1)
# ─────────────────────────────────────────────
 
REAL_DATA = {
    "bare": {
        "label": "Bare Metal (Ryzen 5 4600G · 16GB DDR4 2666 · Windows · GCC)",
        "data": [
            {"tamanho": 300000,  "algoritmo": "Bubble Sort",    "tempo": 286.142000},
            {"tamanho": 300000,  "algoritmo": "Insertion Sort", "tempo": 41.774000},
            {"tamanho": 300000,  "algoritmo": "Quick Sort",     "tempo": 0.029000},
            {"tamanho": 300000,  "algoritmo": "Heap Sort",      "tempo": 0.038000},
            {"tamanho": 600000,  "algoritmo": "Bubble Sort",    "tempo": 1139.927000},
            {"tamanho": 600000,  "algoritmo": "Insertion Sort", "tempo": 168.882000},
            {"tamanho": 600000,  "algoritmo": "Quick Sort",     "tempo": 0.065000},
            {"tamanho": 600000,  "algoritmo": "Heap Sort",      "tempo": 0.086000},
            {"tamanho": 900000,  "algoritmo": "Bubble Sort",    "tempo": 2570.301000},
            {"tamanho": 900000,  "algoritmo": "Insertion Sort", "tempo": 385.754000},
            {"tamanho": 900000,  "algoritmo": "Quick Sort",     "tempo": 0.103000},
            {"tamanho": 900000,  "algoritmo": "Heap Sort",      "tempo": 0.143000},
            {"tamanho": 1200000, "algoritmo": "Bubble Sort",    "tempo": 4577.284000},
            {"tamanho": 1200000, "algoritmo": "Insertion Sort", "tempo": 684.579000},
            {"tamanho": 1200000, "algoritmo": "Quick Sort",     "tempo": 0.147000},
            {"tamanho": 1200000, "algoritmo": "Heap Sort",      "tempo": 0.202000},
            {"tamanho": 1500000, "algoritmo": "Bubble Sort",    "tempo": 7225.017000},
            {"tamanho": 1500000, "algoritmo": "Insertion Sort", "tempo": 1103.000000},
            {"tamanho": 1500000, "algoritmo": "Quick Sort",     "tempo": 0.184000},
            {"tamanho": 1500000, "algoritmo": "Heap Sort",      "tempo": 0.299000},
        ],
    },
    "vm1": {
        "label": "VM1 (VirtualBox · Ubuntu 25.04 · 4 vCPUs · 8GB RAM · KVM)",
        "data": [
            {"tamanho": 300000,  "algoritmo": "Bubble Sort",    "tempo": 336.032177},
            {"tamanho": 300000,  "algoritmo": "Insertion Sort", "tempo": 44.710741},
            {"tamanho": 300000,  "algoritmo": "Quick Sort",     "tempo": 0.036845},
            {"tamanho": 300000,  "algoritmo": "Heap Sort",      "tempo": 0.047815},
            {"tamanho": 600000,  "algoritmo": "Bubble Sort",    "tempo": 1330.960427},
            {"tamanho": 600000,  "algoritmo": "Insertion Sort", "tempo": 179.457353},
            {"tamanho": 600000,  "algoritmo": "Quick Sort",     "tempo": 0.077210},
            {"tamanho": 600000,  "algoritmo": "Heap Sort",      "tempo": 0.120379},
            {"tamanho": 900000,  "algoritmo": "Bubble Sort",    "tempo": 3031.100790},
            {"tamanho": 900000,  "algoritmo": "Insertion Sort", "tempo": 410.281010},
            {"tamanho": 900000,  "algoritmo": "Quick Sort",     "tempo": 0.114849},
            {"tamanho": 900000,  "algoritmo": "Heap Sort",      "tempo": 0.228723},
            {"tamanho": 1200000, "algoritmo": "Bubble Sort",    "tempo": 5400.623215},
            {"tamanho": 1200000, "algoritmo": "Insertion Sort", "tempo": 717.867189},
            {"tamanho": 1200000, "algoritmo": "Quick Sort",     "tempo": 0.160784},
            {"tamanho": 1200000, "algoritmo": "Heap Sort",      "tempo": 0.314518},
            {"tamanho": 1500000, "algoritmo": "Bubble Sort",    "tempo": 8371.744289},
            {"tamanho": 1500000, "algoritmo": "Insertion Sort", "tempo": 1088.700624},
            {"tamanho": 1500000, "algoritmo": "Quick Sort",     "tempo": 0.196623},
            {"tamanho": 1500000, "algoritmo": "Heap Sort",      "tempo": 0.383897},
        ],
    },
    "vm2": {
        "label": "VM2 (VirtualBox · Ubuntu 25.04 · 2 vCPUs · 4GB RAM · KVM)",
        "data": [
            {"tamanho": 300000,  "algoritmo": "Bubble Sort",    "tempo": 339.689138},
            {"tamanho": 300000,  "algoritmo": "Insertion Sort", "tempo": 42.207236},
            {"tamanho": 300000,  "algoritmo": "Quick Sort",     "tempo": 0.038545},
            {"tamanho": 300000,  "algoritmo": "Heap Sort",      "tempo": 0.046647},
            {"tamanho": 600000,  "algoritmo": "Bubble Sort",    "tempo": 1339.834346},
            {"tamanho": 600000,  "algoritmo": "Insertion Sort", "tempo": 176.849619},
            {"tamanho": 600000,  "algoritmo": "Quick Sort",     "tempo": 0.075451},
            {"tamanho": 600000,  "algoritmo": "Heap Sort",      "tempo": 0.125919},
            {"tamanho": 900000,  "algoritmo": "Bubble Sort",    "tempo": 3005.703713},
            {"tamanho": 900000,  "algoritmo": "Insertion Sort", "tempo": 387.136344},
            {"tamanho": 900000,  "algoritmo": "Quick Sort",     "tempo": 0.115541},
            {"tamanho": 900000,  "algoritmo": "Heap Sort",      "tempo": 0.206243},
            {"tamanho": 1200000, "algoritmo": "Bubble Sort",    "tempo": 5328.400933},
            {"tamanho": 1200000, "algoritmo": "Insertion Sort", "tempo": 686.842561},
            {"tamanho": 1200000, "algoritmo": "Quick Sort",     "tempo": 0.154095},
            {"tamanho": 1200000, "algoritmo": "Heap Sort",      "tempo": 0.283325},
            {"tamanho": 1500000, "algoritmo": "Bubble Sort",    "tempo": 8331.894524},
            {"tamanho": 1500000, "algoritmo": "Insertion Sort", "tempo": 1081.072673},
            {"tamanho": 1500000, "algoritmo": "Quick Sort",     "tempo": 0.194461},
            {"tamanho": 1500000, "algoritmo": "Heap Sort",      "tempo": 0.394701},
        ],
    },
}
 
# ─────────────────────────────────────────────
# PERFIS DE VARIAÇÃO POR AMBIENTE
# ─────────────────────────────────────────────
 
NOISE_PROFILES = {
    # (min_pct, max_pct) de variação por classe de algoritmo
    "bare": {
        "fast":  (0.005, 0.030),   # Quick Sort, Heap Sort
        "slow":  (0.002, 0.015),   # Bubble Sort, Insertion Sort
        "spike_chance": 0.05,       # probabilidade de pico de latência
        "spike_factor": (1.02, 1.05),
        "warmup_rounds": [3, 4],    # rodadas com leve aquecimento
        "warmup_factor": (1.003, 1.010),
    },
    "vm1": {
        "fast":  (0.010, 0.050),
        "slow":  (0.005, 0.025),
        "spike_chance": 0.10,
        "spike_factor": (1.03, 1.08),
        "warmup_rounds": [3, 4],
        "warmup_factor": (1.005, 1.015),
    },
    "vm2": {
        "fast":  (0.020, 0.070),
        "slow":  (0.010, 0.035),
        "spike_chance": 0.15,
        "spike_factor": (1.05, 1.12),
        "warmup_rounds": [3, 4],
        "warmup_factor": (1.008, 1.020),
    },
}
 
FAST_ALGOS = {"Quick Sort", "Heap Sort"}
 
 
def simulate_value(base: float, rodada: int, profile: dict, algoritmo: str, rng: random.Random) -> float:
    """Aplica variação estatística realista a um tempo base."""
    is_fast = algoritmo in FAST_ALGOS
    lo, hi = profile["fast"] if is_fast else profile["slow"]
 
    # ruído gaussiano dentro do intervalo [lo, hi]
    sigma = (hi - lo) / 4
    noise = rng.gauss(0, sigma)
    noise = max(-hi, min(hi, noise))          # clamp
    direction = rng.choice([-1, 1])
    factor = 1 + direction * abs(noise)
 
    # pico de hypervisor/SO (spike)
    if rng.random() < profile["spike_chance"]:
        sf_lo, sf_hi = profile["spike_factor"]
        factor *= rng.uniform(sf_lo, sf_hi)
 
    # aquecimento de CPU nas rodadas do meio
    if rodada in profile["warmup_rounds"]:
        wf_lo, wf_hi = profile["warmup_factor"]
        factor *= rng.uniform(wf_lo, wf_hi)
 
    return round(base * factor, 6)
 
 
def simulate_rounds(machine_key: str, n_rounds: int, rng: random.Random) -> list[dict]:
    """Retorna lista de rodadas simuladas (começando em rodada 2)."""
    profile = NOISE_PROFILES[machine_key]
    base_data = REAL_DATA[machine_key]["data"]
    rounds = []
 
    for r in range(2, 2 + n_rounds):
        rodada = {"rodada": r, "dados": []}
        for entry in base_data:
            simulated_tempo = simulate_value(
                base=entry["tempo"],
                rodada=r,
                profile=profile,
                algoritmo=entry["algoritmo"],
                rng=rng,
            )
            rodada["dados"].append({
                "tamanho": entry["tamanho"],
                "algoritmo": entry["algoritmo"],
                "tempo": simulated_tempo,
            })
        rounds.append(rodada)
 
    return rounds
 
 
def format_time(v: float) -> str:
    if v >= 100:
        return f"{v:.3f}s"
    if v >= 1:
        return f"{v:.4f}s"
    return f"{v:.6f}s"
 
 
def print_table(machine_key: str, all_rounds: list[dict]):
    """Imprime tabela comparativa no terminal."""
    algos  = ["Bubble Sort", "Insertion Sort", "Quick Sort", "Heap Sort"]
    sizes  = [300000, 600000, 900000, 1200000, 1500000]
    cols = []
    for r in all_rounds:
        lbl = "Real" if r["rodada"] == 1 else "Sim." + str(r["rodada"] - 1)
        cols.append(f"  {lbl:>12}")
    header = f"{'Tamanho':>10}  {'Algoritmo':<16}" + "".join(cols)
    print(header)
    print("─" * len(header))
 
    for sz in sizes:
        for alg in algos:
            row = f"{sz:>10}  {alg:<16}"
            for r in all_rounds:
                val = next((d["tempo"] for d in r["dados"]
                            if d["tamanho"] == sz and d["algoritmo"] == alg), None)
                row += f"  {format_time(val):>12}" if val else f"  {'—':>12}"
            print(row)
        print()
 
 
def print_stats(all_rounds: list[dict]):
    """Imprime média, desvio padrão e CV% de todas as rodadas combinadas."""
    algos = ["Bubble Sort", "Insertion Sort", "Quick Sort", "Heap Sort"]
    sizes = [300000, 600000, 900000, 1200000, 1500000]
    print(f"{'Tamanho':>10}  {'Algoritmo':<16}  {'Média':>12}  {'Desvio':>12}  {'CV%':>6}")
    print("─" * 66)
 
    for sz in sizes:
        for alg in algos:
            vals = [d["tempo"] for r in all_rounds
                    for d in r["dados"]
                    if d["tamanho"] == sz and d["algoritmo"] == alg]
            if not vals:
                continue
            media = sum(vals) / len(vals)
            desvio = (sum((v - media) ** 2 for v in vals) / len(vals)) ** 0.5
            cv = (desvio / media * 100) if media else 0
            flag = " ⚠" if cv > 2 else ""
            print(f"{sz:>10}  {alg:<16}  {format_time(media):>12}  {format_time(desvio):>12}  {cv:>5.2f}%{flag}")
        print()
 
 
def save_csv(machine_key: str, all_rounds: list[dict], output_dir: str):
    """Salva todas as rodadas em um CSV por máquina."""
    filename = os.path.join(output_dir, f"simulado_{machine_key}.csv")
    with open(filename, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f, delimiter="|")
        writer.writerow(["rodada", "tamanho", "algoritmo", "tempo(s)"])
        for r in all_rounds:
            for d in r["dados"]:
                writer.writerow([r["rodada"], d["tamanho"], d["algoritmo"], f"{d['tempo']:.6f}"])
    return filename
 
 
# ─────────────────────────────────────────────
# MAIN
# ─────────────────────────────────────────────
 
def main():
    parser = argparse.ArgumentParser(description="Simulador de benchmark de algoritmos de ordenação")
    parser.add_argument("--machine", choices=["bare", "vm1", "vm2", "all"], default="all",
                        help="Máquina a simular (padrão: all)")
    parser.add_argument("--rounds", type=int, default=4,
                        help="Número de rodadas simuladas (padrão: 4)")
    parser.add_argument("--seed", type=int, default=None,
                        help="Seed para reprodutibilidade (padrão: aleatório)")
    parser.add_argument("--csv", action="store_true",
                        help="Salvar resultados em CSV")
    parser.add_argument("--output-dir", default=".", metavar="DIR",
                        help="Diretório de saída dos CSVs (padrão: diretório atual)")
    parser.add_argument("--stats", action="store_true",
                        help="Exibir estatísticas (média, desvio, CV%%)")
    args = parser.parse_args()
 
    seed = args.seed if args.seed is not None else random.randint(0, 99999)
    rng = random.Random(seed)
    print(f"Seed: {seed}  |  Rodadas simuladas: {args.rounds}\n")
 
    machines = ["bare", "vm1", "vm2"] if args.machine == "all" else [args.machine]
 
    for machine_key in machines:
        info = REAL_DATA[machine_key]
        print("=" * 70)
        print(f"  {info['label']}")
        print("=" * 70)
 
        simulated = simulate_rounds(machine_key, args.rounds, rng)
        rodada_real = {"rodada": 1, "dados": deepcopy(info["data"])}
        all_rounds = [rodada_real] + simulated
 
        print_table(machine_key, all_rounds)
 
        if args.stats:
            print("  ── Estatísticas ──")
            print_stats(all_rounds)
 
        if args.csv:
            os.makedirs(args.output_dir, exist_ok=True)
            path = save_csv(machine_key, all_rounds, args.output_dir)
            print(f"  CSV salvo em: {path}\n")
        else:
            print()
 
 
if __name__ == "__main__":
    main()