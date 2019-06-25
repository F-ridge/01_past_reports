import unittest
import numpy as np
from graph_neural_network import GNN


class GNNTest(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_aggregate_1(self):
        gnn = GNN(n_iter=1, dim_feature_vectors=4, parameters='test')
        graph = np.array([
            [1, 1, 0, 0, 0, 0],
            [0, 1, 1, 0, 0, 0],
            [0, 0, 1, 1, 0, 0],
            [0, 0, 0, 1, 1, 0],
            [0, 0, 0, 0, 1, 1],
            [0, 0, 0, 0, 0, 1]])
        gnn.load_graph(len(graph), graph)
        gnn.fit()
        assumed_feature_vectors = np.array([
            [0., 1., 0., 0.],
            [0., 0., 1., 0.],
            [0., 0., 0., 1.],
            [1., 0., 0., 0.],
            [0., 1., 0., 0.],
            [0., 0., 0., 0.]])
        self.assertEqual(
            assumed_feature_vectors.tolist(),
            gnn.feature_vectors.tolist())

    def test_aggregate_2(self):
        gnn = GNN(n_iter=1, dim_feature_vectors=4, parameters='test')
        graph = np.array([
            [1, 1, 0, 0, 0, 1],
            [0, 1, 1, 0, 0, 0],
            [0, 0, 1, 1, 0, 0],
            [0, 0, 0, 1, 1, 0],
            [0, 0, 0, 0, 1, 1],
            [1, 0, 0, 0, 0, 1]])
        gnn.load_graph(len(graph), graph)
        gnn.fit()
        assumed_feature_vectors = np.array([
            [0., 2., 0., 0.],
            [0., 0., 1., 0.],
            [0., 0., 0., 1.],
            [1., 0., 0., 0.],
            [0., 1., 0., 0.],
            [1., 0., 0., 0.]])
        self.assertEqual(
            assumed_feature_vectors.tolist(),
            gnn.feature_vectors.tolist())

    def test_aggregate_3(self):
        gnn = GNN(n_iter=1, dim_feature_vectors=5, parameters='test')
        graph = np.array([
            [1, 1, 0, 0],
            [1, 1, 1, 1],
            [0, 1, 1, 1],
            [0, 1, 1, 1]])
        gnn.load_graph(len(graph), graph)
        gnn.fit()
        assumed_feature_vectors = np.array([
            [0., 1., 0., 0., 0.],
            [1., 0., 1., 1., 0.],
            [0., 1., 0., 1., 0.],
            [0., 1., 1., 0., 0.]])
        self.assertEqual(
            assumed_feature_vectors.tolist(),
            gnn.feature_vectors.tolist())

    def test_readout(self):
        gnn = GNN(dim_feature_vectors=5)
        feature_vectors = np.array([
            [0., 1., 0., 0., 0.],
            [1., 0., 1., 1., 0.],
            [0., 1., 0., 1., 0.],
            [0., 1., 1., 0., 0.]])
        gnn.feature_vectors = feature_vectors
        gnn.readout()
        assumed_readout = np.array([1., 3., 2., 2., 0.])
        self.assertEqual(assumed_readout.tolist(), gnn.h.tolist())


if __name__ == "__main__":
    unittest.main()
