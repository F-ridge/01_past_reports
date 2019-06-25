# optimization_report_01.py

import numpy as np
import matplotlib.pyplot as plt


def objective_func(x):
    return 100 * (x[1] - x[0] ** 2) ** 2 + (1 - x[0]) ** 2


def gradient_vector(x):
    return np.array([
        (-400) * x[0] * (x[1] - x[0] ** 2) - 2 * (1 - x[0]),
        200 * (x[1] - x[0] ** 2)])


def hessian(x):
    return np.array([
        [(-400) * (x[1] - x[0] ** 2) +
         800 * x[0] ** 2 + 2, (-400) * x[0]],
        [(-400) * x[0], 200]])


def gradient_decent(
        x_0, objective_func, gradient_vector,
        alpha_0=1, c_1=0.0001, c_2=0.9, rho=0.5, n_iter=100):
    x_k = x_0.copy()
    result = [x_0]
    for i in range(n_iter):
        direction = gradient_vector(x_k) * (-1)
        alpha = backtrack_alpha(
            x_k, direction, alpha_0, c_1, c_2, rho,
            objective_func, gradient_vector)
        x_k += alpha * direction
        result.append(x_k.copy())
    return np.array(result)


def newton(x_0, hessian, gradient_vector, n_iter=100):
    x_k = x_0.copy()
    result = [x_0]
    for i in range(n_iter):
        direction = np.linalg.solve(
            hessian(x_k), gradient_vector(x_k) * (-1))
        x_k += direction
        result.append(x_k.copy())
    return np.array(result)


def quasi_newton(
        x_0, objective_func, gradient_vector, hessian,
        alpha_0=1, c_1=0.0001, c_2=0.9, rho=0.5, n_iter=100):
    x_prev = x_0.copy()
    H_k = np.linalg.inv(hessian(x_0))
    result = [x_0]
    for i in range(n_iter):
        grad_prev = gradient_vector(x_prev)
        direction = np.dot(H_k, grad_prev) * (-1)
        alpha = backtrack_alpha(
            x_prev, direction, alpha_0, c_1, c_2, rho,
            objective_func, gradient_vector)
        x_next = x_prev + alpha * direction
        s_k = x_next - x_prev
        y_k = gradient_vector(x_next) - grad_prev
        H_k = H_matrix(H_k, s_k, y_k)
        result.append(x_next.copy())
        x_prev = x_next
    return np.array(result)


def backtrack_alpha(
        x_k, direction,
        alpha_0, c_1, c_2, rho,
        objective_func, gradient_vector):
    if armijo(
            x_k, direction, alpha_0, c_1,
            objective_func, gradient_vector)\
            and wolfe(x_k, direction, alpha_0, c_2, gradient_vector):
        return alpha_0
    else:
        return backtrack_alpha(
            x_k, direction, alpha_0 * rho, c_1, c_2, rho,
            objective_func, gradient_vector)


def H_matrix(H_k, s_k, y_k):
    s = s_k.reshape(-1, 1)
    s_t = s_k.reshape(1, -1)
    y = s_k.reshape(-1, 1)
    y_t = s_k.reshape(1, -1)
    return np.dot(
        np.dot(
            (np.array([[1, 0], [0, 1]]) - np.dot(s, y_t) /
             np.dot(y_t, s)), H_k),
        (np.array([[1, 0], [0, 1]]) - np.dot(y, s_t) /
         np.dot(y_t, s))) +\
        np.dot(s, s_t) / np.dot(s_t, y)


def armijo(
        x_k, direction, alpha, c_1,
        objective_func, gradient_vector):
    return objective_func(x_k + alpha * direction) <=\
        objective_func(x_k) + c_1 * alpha * np.dot(
            gradient_vector(x_k), direction)


def wolfe(x_k, direction, alpha, c_2, gradient_vector):
    return np.dot(
        gradient_vector(x_k + alpha * direction), direction) >=\
        c_2 * np.dot(gradient_vector(x_k), direction)


def plot_result(
        result, x_range, y_range,
        levels_contour, levels_contourf,
        objective_func, method, x_0):
    X, Y = np.meshgrid(
        np.linspace(x_range[0], x_range[1], num=100),
        np.linspace(y_range[0], y_range[1], num=100))
    Z = objective_func([X, Y])
    fig = plt.figure(figsize=(16, 8))
    ax_1 = fig.add_subplot(121)
    ax_1.contourf(
        X, Y, Z, levels=levels_contourf, cmap='Greys')
    ax_1.contour(
        X, Y, Z, levels=levels_contour,
        colors='black', alpha=0.5).clabel(fmt='%.0f')
    ax_1.scatter(
        1, 1, color='red', marker='*', s=150, label='真の解', zorder=2)
    ax_1.plot(
        result.T[0], result.T[1],
        linestyle='--', color='blue', marker='.',
        markersize=10, label='各反復での解', zorder=1)
    ax_1.legend()
    ax_1.set_title(
        f'解の挙動({method}, 初期ベクトル: {x_0}$^T$)')
    ax_1.set_xlabel('$x_1$', fontsize=15)
    ax_1.set_ylabel('$x_2$', fontsize=15)
    ax_2 = ax_1 = fig.add_subplot(122)
    ax_2.plot(
        np.arange(min(50, len(result))), objective_func(result[:50].T),
        linestyle='--', color='blue', marker='.',
        markersize=10, label='解に対する関数値')
    ax_2.set_title(
        f'反復50回未満での、解に対する関数値の推移\n' +
        f'({method}, 初期ベクトル: {x_0}$^T$)')
    ax_2.set_xlabel('反復回数', fontsize=15)
    ax_2.set_ylabel('$f(x_1, x_2)$', fontsize=15)
    ax_2.legend()
    plt.show()
