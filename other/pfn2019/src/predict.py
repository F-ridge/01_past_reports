import argparse
import numpy as np
from graph_neural_network import GNN


def main(n_epochs, n_data, path_to_datasets):
    how = 'Adam'
    gnn = GNN()
    ids = list(range(n_data))
    gnn.train(ids, n_epochs=n_epochs, how=how)
    prediction = ''
    for data_id in range(500):
        graph = np.loadtxt(
            f'{path_to_datasets}/test/{data_id}_graph.txt',
            skiprows=1)
        prediction += str(gnn.predict(graph=graph)) + '\n'
    with open('prediction.txt', mode='w') as f:
        f.write(prediction)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-e', '--n_epochs', type=int, default=50,
        help='number of iterations over entire dataset')
    parser.add_argument(
        '-n', '--n_data', type=int, default=2000,
        help='path to datasets folder')
    parser.add_argument(
        '-p', '--path_to_datasets', default='datasets',
        help='path to datasets folder')
    args = parser.parse_args()
    main(args.n_epochs, args.n_data, args.path_to_datasets)
