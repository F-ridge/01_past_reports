import random
import numpy as np
from copy import deepcopy


class GNN:
    def __init__(
            self, n_iter=2, dim_feature_vectors=8,
            alpha_sgd=0.0001, momentum_sgd=0.9,
            alpha_adam=0.001, momentum_adam=[0.9, 0.999], eps_adam=1e-8,
            eps=0.001, parameters='normal_dist',
            path_to_datasets='datasets'):
        random.seed(20190506)
        np.random.seed(20190506)
        self.n_iter = n_iter
        self.dim_feature_vectors = dim_feature_vectors
        self.alpha_sgd = alpha_sgd
        self.momentum_sgd = momentum_sgd
        self.alpha_adam = alpha_adam
        self.momentum_adam = momentum_adam
        self.eps_adam = eps_adam
        self.eps = eps
        self.path_to_datasets = path_to_datasets
        self.initialize_parameters(parameters)

    def initialize_parameters(self, parameters):
        if parameters == 'normal_dist':
            self.parameters = {
                'W': np.random.normal(
                    0, 0.4, [self.dim_feature_vectors,
                             self.dim_feature_vectors]),
                'A': np.random.normal(0, 0.4, self.dim_feature_vectors),
                'b': 0}
        elif parameters == 'test':
            self.parameters = {
                'W': np.diag(np.ones(self.dim_feature_vectors)),
                'A': np.ones(self.dim_feature_vectors),
                'b': 0}
        else:
            self.parameters = parameters

    def load_graph(self, n_nodes, graph, label=None):
        self.n_nodes = n_nodes
        self.graph = graph
        self.label = label

    def initialize_feature_vectors(self):
        init_feature_vectors = np.zeros(
            [self.n_nodes, self.dim_feature_vectors])
        for i in range(self.n_nodes):
            init_feature_vectors[i, i % self.dim_feature_vectors] = 1
        self.feature_vectors = init_feature_vectors
        self.prev_feature_vectors = deepcopy(self.feature_vectors)

    def initialize_avg_grad(self):
        avg_grad = {
                'W': np.zeros([self.dim_feature_vectors,
                               self.dim_feature_vectors]),
                'A': np.zeros(self.dim_feature_vectors),
                'b': 0}
        return avg_grad

    def train(
            self, ids, batch_size=20,
            test_ratio=0.3, n_epochs=10, how='SGD'):
        graphs = {
            data_id: np.loadtxt(
                f'{self.path_to_datasets}/train/{data_id}_graph.txt',
                skiprows=1)
            for data_id in ids}
        labels = {
            data_id: np.loadtxt(
                f'{self.path_to_datasets}/train/{data_id}_label.txt')
            for data_id in ids}
        self.avg_loss = {'train': [], 'test': []}
        self.accuracy = {'train': [], 'test': []}
        ids_copy = deepcopy(ids)
        random.shuffle(ids_copy)
        border = int(np.ceil(len(ids) * test_ratio))
        train_ids = ids_copy[border:]
        test_ids = ids_copy[:border]
        self.append_avg_loss_and_accuracy(
            graphs, labels, train_ids, 'train')
        self.append_avg_loss_and_accuracy(
            graphs, labels, test_ids, 'test')
        for i in range(n_epochs):
            print(f'\repoch {i+1} / {n_epochs} ({how}) ... ', end='')
            self.epoch(graphs, labels, train_ids, batch_size, how)
            self.append_avg_loss_and_accuracy(
                graphs, labels, train_ids, 'train')
            self.append_avg_loss_and_accuracy(
                graphs, labels, test_ids, 'test')
        print('done.')

    def epoch(self, graphs, labels, train_ids, batch_size, how):
        train_ids_copy = deepcopy(train_ids)
        random.shuffle(train_ids_copy)
        while len(train_ids_copy) > 0:
            n_graphs = 0
            avg_grad = self.initialize_avg_grad()
            self.total_grad = {
                'W': np.zeros([self.dim_feature_vectors,
                               self.dim_feature_vectors]),
                'A': np.zeros(self.dim_feature_vectors),
                'b': 0}
            batch_ids = train_ids_copy[:batch_size]
            del train_ids_copy[:batch_size]
            for data_id in batch_ids:
                n_graphs += 1
                graph = graphs[data_id]
                self.load_graph(len(graph), graph, labels[data_id])
                self.fit()
                avg_grad = self.update_average_grad(
                    avg_grad, self.calc_grad(), n_graphs)
            self.update_paramters(self.calc_update(avg_grad, how))

    def fit(self):
        self.initialize_feature_vectors()
        for _ in range(self.n_iter):
            self.aggregate()
        self.readout()

    def aggregate(self):
        for i in range(self.n_nodes):
            node = self.graph[i]
            a = np.zeros(self.dim_feature_vectors)
            for j in range(self.n_nodes):
                if i != j and node[j] == 1:
                    a += self.prev_feature_vectors[j]
            self.feature_vectors[i] = self.update_feature_vector(self.relu, a)
        self.prev_feature_vectors = deepcopy(self.feature_vectors)

    def calc_update(self, avg_grad, how):
        if how == 'SGD':
            update = {key: avg_grad[key] * (-self.alpha_sgd)
                      for key in avg_grad.keys()}
        if how == 'momentumSGD':
            if not hasattr(self, 'prev_grad_update'):
                self.prev_grad_update = {
                    'W': np.zeros([self.dim_feature_vectors,
                                   self.dim_feature_vectors]),
                    'A': np.zeros(self.dim_feature_vectors),
                    'b': 0}
            update = {
                key: (avg_grad[key] * (-self.alpha_sgd) +
                      self.prev_grad_update[key] * self.momentum_sgd)
                for key in avg_grad.keys()}
            self.prev_grad_update = deepcopy(update)
        if how == 'Adam':
            if not hasattr(self, 'm_adam'):
                self.m_adam = {
                    'W': np.zeros([self.dim_feature_vectors,
                                   self.dim_feature_vectors]),
                    'A': np.zeros(self.dim_feature_vectors),
                    'b': 0}
            if not hasattr(self, 'v_adam'):
                self.v_adam = {
                    'W': np.zeros([self.dim_feature_vectors,
                                   self.dim_feature_vectors]),
                    'A': np.zeros(self.dim_feature_vectors),
                    'b': 0}
            if not hasattr(self, 'n_updates_adam'):
                self.n_updates_adam = 0
            self.n_updates_adam += 1
            self.m_adam = {
                key: (self.momentum_adam[0] * self.m_adam[key] +
                      (1 - self.momentum_adam[0]) * avg_grad[key])
                for key in self.m_adam.keys()}
            self.v_adam = {
                key: (self.momentum_adam[1] * self.v_adam[key] +
                      (1 - self.momentum_adam[1]) * avg_grad[key] ** 2)
                for key in self.v_adam.keys()}
            bias_corrected_m = {
                key: (self.m_adam[key] /
                      (1 - self.momentum_adam[0] ** self.n_updates_adam))
                for key in self.m_adam.keys()}
            bias_corrected_v = {
                key: (self.v_adam[key] /
                      (1 - self.momentum_adam[1] ** self.n_updates_adam))
                for key in self.v_adam.keys()}
            update = update = {
                key: (-1 * bias_corrected_m[key] * self.alpha_adam /
                      (np.sqrt(bias_corrected_v[key]) + self.eps_adam))
                for key in avg_grad.keys()}
        return update

    def append_avg_loss_and_accuracy(
            self, graphs, labels, data_ids, data_type):
        avg_loss, acc = self.calc_avg_loss_and_accuracy(
            graphs, labels, data_ids)
        self.avg_loss[data_type] += [avg_loss]
        self.accuracy[data_type] += [acc]

    def calc_avg_loss_and_accuracy(self, graphs, labels, data_ids):
        avg_loss = 0
        n_correct = 0
        for i, data_id in enumerate(data_ids, 1):
            graph = graphs[data_id]
            label = labels[data_id]
            self.load_graph(len(graph), graph, label)
            self.fit()
            avg_loss = self.update_avg_loss(avg_loss, i)
            n_correct += (self.predict(graph=graph, load=False) == label)
        acc = n_correct / len(data_ids)
        return avg_loss, acc

    def update_avg_loss(self, avg_loss, i):
        loss = self.cross_entropy()
        return (avg_loss * (i - 1) + loss) / i

    def update_paramters(self, update):
        for key in self.parameters.keys():
            self.parameters[key] += update[key]

    def predict(self, graph=None, load=True):
        if load:
            self.load_graph(len(graph), graph)
            self.fit()
        s = self.weighted_sum_readout()
        prob = self.sigmoid(s)
        label_pred = 1 if prob > 0.5 else 0
        return label_pred

    def update_average_grad(self, avg_grad, grad, i):
        return {
            key: (avg_grad[key] * (i - 1) + grad[key]) / i
            for key in avg_grad.keys()}

    def calc_grad(self):
        grad = {
            'W': np.empty([self.dim_feature_vectors,
                           self.dim_feature_vectors]),
            'A': np.empty(self.dim_feature_vectors),
            'b': 0}
        original_loss = self.cross_entropy()
        for i in range(self.dim_feature_vectors ** 2):
            row = i // self.dim_feature_vectors
            col = i % self.dim_feature_vectors
            self.parameters['W'][row, col] += self.eps
            self.fit()
            grad['W'][row, col] = (
                (self.cross_entropy() - original_loss) / self.eps)
            self.parameters['W'][row, col] -= self.eps
        self.fit()
        for i in range(self.dim_feature_vectors):
            self.parameters['A'][i] += self.eps
            grad['A'][i] = (self.cross_entropy() - original_loss) / self.eps
            self.parameters['A'][i] -= self.eps
        self.parameters['b'] += self.eps
        grad['b'] = (self.cross_entropy() - original_loss) / self.eps
        self.parameters['b'] -= self.eps
        return grad

    def update_feature_vector(self, func, a):
        return list(map(func, np.dot(self.parameters['W'], a)))

    def readout(self):
        self.h = sum(self.feature_vectors)

    def weighted_sum_readout(self):
        s = np.dot(self.parameters['A'], self.h) + self.parameters['b']
        return s

    def cross_entropy(self):
        s = self.weighted_sum_readout()
        return (
            self.label * self.softplus(-s) +
            (1 - self.label) * self.softplus(s))

    def softplus(self, x):
        if x >= 0:
            return x + np.log(1 + np.exp(-x))
        else:
            return np.log(1 + np.exp(x))

    def sigmoid(self, s):
        return 1 / (1 + np.exp(-s))

    def relu(self, x):
        return max(0, x)
