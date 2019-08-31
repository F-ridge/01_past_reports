import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class ChuaCircuit:
    def __init__(
            self,
            init_y={'v_C_1': 0.01, 'v_C_2': 0.01, 'i_L': 0.01},
            time_stride=0.1,
            param={
                'C_1': 9, 'C_2': 1, 'L': 7,
                'm_0': -0.5, 'm_1': -0.8, 'B_p': 1},
            G=0.1):
        self.init_y = np.array(
            [[init_y['v_C_1']], [init_y['v_C_2']], [init_y['i_L']]])
        self.time_stride = time_stride
        self.C_1 = param['C_1']
        self.C_2 = param['C_2']
        self.L = param['L']
        self.G = G
        self.m_0 = param['m_0']
        self.m_1 = param['m_1']
        self.B_p = param['B_p']

    def g(self, v_C_1):
        return self.m_0 * v_C_1 + (
            (self.m_1 - self.m_0) * abs(v_C_1 + self.B_p) +
            (self.m_0 - self.m_1) * abs(v_C_1 - self.B_p)
            ) / 2

    def differential(
            self, y, time_diff={'v_C_1': 0, 'v_C_2': 0, 'i_L': 0}):
        diff = {}
        diff['v_C_1'] = (
            self.G * (
                (y[1] + time_diff['v_C_2']) -
                (y[0] + time_diff['v_C_1'])
                ) - self.g(y[0] + time_diff['v_C_1'])
            ) * self.C_1
        diff['v_C_2'] = (
            self.G * (
                (y[0] + time_diff['v_C_1']) -
                (y[1] + time_diff['v_C_2'])
                ) + (y[2] + time_diff['i_L'])
            ) * self.C_2
        diff['i_L'] = -(y[1] + time_diff['v_C_2']) * self.L
        return diff

    def runge_kutta(self, n_iter=100):
        result = self.init_y.copy()
        y = self.init_y.copy()
        names = ['v_C_1', 'v_C_2', 'i_L']
        for _ in range(n_iter):
            k_1 = {
                name: self.time_stride * self.differential(y)[
                    name] for name in names}
            k_2 = {
                name: self.time_stride * self.differential(
                    y, time_diff={
                        name_: k_1[name_]/2 for name_ in names
                    })[name] for name in names}
            k_3 = {
                name: self.time_stride * self.differential(
                    y, time_diff={
                        name_: k_2[name_]/2 for name_ in names
                    })[name] for name in names}
            k_4 = {
                name: self.time_stride * self.differential(
                    y, time_diff=k_3)[name] for name in names}
            y += [
                (k_1[name] + 2 * k_2[name] +
                 2 * k_3[name] + k_4[name]) / 6 for name in names]
            result = np.append(result,  y.copy())
        self.result = result.reshape(-1, len(self.init_y))


def plot_track(G, time_stride, n_iter, start=0):
    cc = ChuaCircuit(time_stride=time_stride, G=G)
    cc.runge_kutta(n_iter=n_iter)
    fig = plt.figure(figsize=(4, 4))
    ax = Axes3D(fig)
    ax.plot(
        cc.result[start:, 0],
        cc.result[start:, 1],
        cc.result[start:, 2],
        color='b')
    ax.set_xlabel('$v_{C_1} (V)$', fontsize=15)
    ax.set_ylabel('$v_{C_2} (V)$', fontsize=15)
    ax.set_zlabel('$i_L (A)$', fontsize=15)
    plt.title(
        f'''
        Chua回路のRunge-Kutta法による解軌道
        (反復: {n_iter}回, 時間刻み幅: {time_stride},
        G = {G}, {start}回目以降の反復をプロット)''',
        fontsize=15)
    plt.show()


def compare_plots(
        G_list, time_stride=0.01, n_iter=5000, start=1000, n_cols=4):
    n_plots = len(G_list)
    n_rows = np.ceil(n_plots / n_cols)
    fig = plt.figure(figsize=(n_cols*4.5, n_rows*5))
    for i, G in enumerate(G_list):
        ax = fig.add_subplot(n_rows, n_cols, i+1, projection='3d')
        cc = ChuaCircuit(time_stride=time_stride, G=G)
        cc.runge_kutta(n_iter=n_iter)
        ax.plot(
            cc.result[start:, 0],
            cc.result[start:, 1],
            cc.result[start:, 2],
            color='b')
        ax.set_xlabel('$v_{C_1} (V)$', fontsize=13)
        ax.set_ylabel('$v_{C_2} (V)$', fontsize=13)
        ax.set_zlabel('$i_L (A)$', fontsize=13)
        ax.set_title(
            f'''
            Chua回路のRunge-Kutta法による解軌道
            (反復: {n_iter}回, 時間刻み幅: {time_stride},
            G = {G}, {start}回目以降の反復をプロット)''',
            fontsize=13)
    plt.show()


def compare_plots_2d(
        G_list, time_stride=0.01, n_iter=5000, start=1000, n_cols=4):
    n_plots = len(G_list)
    n_rows = np.ceil(n_plots / n_cols)
    fig = plt.figure(figsize=(n_cols*4.5, n_rows*5))
    for i, G in enumerate(G_list):
        ax = fig.add_subplot(n_rows, n_cols, i+1)
        cc = ChuaCircuit(time_stride=time_stride, G=G)
        cc.runge_kutta(n_iter=n_iter)
        ax.plot(
            cc.result[start:, 0],
            cc.result[start:, 1],
            color='b')
        ax.set_xlabel('$v_{C_1} (V)$', fontsize=13)
        ax.set_ylabel('$v_{C_2} (V)$', fontsize=13)
        ax.set_title(
            f'''
            Chua回路のRunge-Kutta法による解軌道
            (反復: {n_iter}回, 時間刻み幅: {time_stride},
            G = {G}, {start}回目以降の反復をプロット)''',
            fontsize=13)
    plt.show()


def check_result(
        G, time_stride=0.01, n_iter=5000):
    cc = ChuaCircuit(time_stride=time_stride, G=G)
    cc.runge_kutta(n_iter=n_iter)
    return cc.result
