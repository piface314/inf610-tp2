from sys import argv
import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd

if len(argv) <= 2:
    print(f"Usage:\n\t$ python {argv[0]} <output-folder> <input> ...")
    exit(1)

out_fp = argv[1]
os.makedirs(out_fp, exist_ok=True)

df = pd.concat([pd.read_csv(fp) for fp in argv[2:]], axis=0)

def plot_euler_chk(df: pd.DataFrame):
    rep_info = {
        "IncMatrix": (lambda v, e: v*e, "$c_{IM} \cdot (?)$", "#FF5500"),
        "AdjMatrix": (lambda v, e: 2*v+e, "$c_{AM} \cdot (?)$", "#00CC22"),
        "AdjList":   (lambda v, e: v+e, "$c_{AL} \cdot (?)$", "#0055FF"),
    }
    df = df[df["problem"] == "euler"]
    fig, ax = plt.subplots(figsize=(10,6), dpi=300)
    for rep, (fn, label, color) in rep_info.items():
        df_ = df[df["rep"] == rep]
        x = df_["n_vertices"]
        y = df_["chk_op"]
        plt.plot(x, y, color=color, marker='o', linestyle='-', label=f"T(n) medido para {rep}")
        x_o = np.linspace(x.min(), x.max(), 1000)
        y_o = fn(x_o, 2*x_o)
        plt.plot(x_o, y_o, color=color, linestyle='--', label=label)
    plt.legend()
    plt.xlabel("Quantidade de vértices, $|V|$")
    plt.ylabel("Quantidade de operações")
    plt.grid(alpha=0.3)
    plt.savefig(os.path.join(out_fp, "eulerian-chk.png"), bbox_inches='tight', pad_inches = 0.1)
    plt.close()

def plot_euler(df: pd.DataFrame):
    rep_info = {
        "IncMatrix": (lambda v, e: v*e, "$c_{IM} \cdot (?)$", "#FF5500"),
        "AdjMatrix": (lambda v, e: 2*v+e, "$c_{AM} \cdot (?)$", "#00CC22"),
        "AdjList":   (lambda v, e: 6*e, "$6_{AL} \cdot |E|$", "#0055FF"),
    }
    df = df[df["problem"] == "euler"]
    fig, ax = plt.subplots(figsize=(10,6), dpi=300)
    for rep, (fn, label, color) in rep_info.items():
        df_ = df[df["rep"] == rep]
        x = df_["n_vertices"]
        y = df_["op"]
        plt.plot(x, y, color=color, marker='o', linestyle='-', label=f"T(n) medido para {rep}")
        x_o = np.linspace(x.min(), x.max(), 1000)
        y_o = fn(x_o, 2*x_o)
        plt.plot(x_o, y_o, color=color, linestyle='--', label=label)
    plt.legend()
    plt.xlabel("Quantidade de vértices, $|V|$")
    plt.ylabel("Quantidade de operações")
    plt.grid(alpha=0.3)
    plt.savefig(os.path.join(out_fp, "eulerian.png"), bbox_inches='tight', pad_inches = 0.1)
    plt.close()

def plot_hamilton(df: pd.DataFrame):
    fn = lambda v, e: 2 ** v * v
    df = df[df["problem"] == "hamilton"]
    fig, ax = plt.subplots(figsize=(10,6), dpi=300)
    x = df["n_vertices"]
    y = df["op"]
    plt.plot(x, y, color="#0055FF", marker='o', linestyle='-', label=f"T(n) medido")
    x_o = np.linspace(x.min(), x.max(), 1000)
    y_o = fn(x_o, 2*x_o)
    plt.plot(x_o, y_o, color="#0055FF", linestyle='--', label="$c \cdot (2^{|V|} \cdot |V|)$")
    plt.legend()
    plt.yscale("log")
    plt.xlabel("Quantidade de vértices, $|V|$")
    plt.ylabel("Quantidade de operações")
    plt.grid(alpha=0.3)
    plt.savefig(os.path.join(out_fp, "hamiltonian.png"), bbox_inches='tight', pad_inches = 0.1)
    plt.close()

plot_euler_chk(df)
plot_euler(df)
plot_hamilton(df)