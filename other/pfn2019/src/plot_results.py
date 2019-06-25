import os
import argparse
import pickle
import matplotlib.pyplot as plt
from graph_neural_network import GNN

plt.rcParams['savefig.bbox'] = 'tight'
plt.rcParams['savefig.transparent'] = True


def main(n_epochs, n_data, path_to_datasets, save_dir):
    os.makedirs(save_dir, exist_ok=True)
    optimizers = ['SGD', 'momentumSGD', 'Adam']
    results = get_results(n_data, n_epochs, optimizers)
    with open(f'{save_dir}/results.pickle', 'wb') as r:
        pickle.dump(results, r)
    for how in optimizers:
        plot_loss(results, how, save_dir)
        plot_accuracy(results, how, save_dir)
    for data_type in ['train', 'test']:
        plot_loss_compare(results, data_type, optimizers, save_dir)
        plot_accuracy_compare(results, data_type, optimizers, save_dir)


def get_results(n_data, n_epochs, optimizers):
    results = {}
    for how in optimizers:
        gnn = GNN()
        ids = list(range(n_data))
        gnn.train(ids, n_epochs=n_epochs, how=how)
        results[how] = {
            'loss':
                {'train': gnn.avg_loss['train'],
                 'test': gnn.avg_loss['test']},
            'accuracy':
                {'train': gnn.accuracy['train'],
                 'test': gnn.accuracy['test']}}
    return results


def plot_loss(results, how, save_dir):
    train_loss = results[how]['loss']['train']
    test_loss = results[how]['loss']['test']
    plt.figure(figsize=(6, 4))
    plt.plot(train_loss, label='train loss')
    plt.plot(test_loss, label='test loss')
    plt.xlim(0, len(train_loss) - 1)
    plt.legend(bbox_to_anchor=(1, 1), loc='upper left')
    plt.xlabel('iterations over entire dataset')
    plt.ylabel('binary closs-entropy loss')
    plt.title(f'GNN binary closs-entropy loss ({how})')
    plt.grid(linestyle=':')
    plt.savefig(f"{save_dir}/loss_{how}.png")


def plot_accuracy(results, how, save_dir):
    train_acc = results[how]['accuracy']['train']
    test_acc = results[how]['accuracy']['test']
    plt.figure(figsize=(6, 4))
    plt.plot(train_acc, label='train accuracy')
    plt.plot(test_acc, label='test accuracy')
    plt.xlim(0, len(train_acc) - 1)
    plt.ylim(0, 1)
    plt.legend(bbox_to_anchor=(1, 1), loc='upper left')
    plt.xlabel('iterations over entire dataset')
    plt.ylabel('accuracy')
    plt.title(f'GNN accuracy ({how})')
    plt.grid(linestyle=':')
    plt.savefig(f"{save_dir}/accuracy_{how}.png")


def plot_loss_compare(results, data_type, optimizers, save_dir):
    plt.figure(figsize=(6, 4))
    for how in optimizers:
        plt.plot(results[how]['loss'][data_type], label=how)
    plt.xlim(0, len(results[optimizers[0]]['loss'][data_type]) - 1)
    plt.legend(bbox_to_anchor=(1, 1), loc='upper left')
    plt.xlabel('iterations over entire dataset')
    plt.ylabel('binary closs-entropy loss')
    plt.title(
        f"GNN loss comparison among\n{', '.join(optimizers)}\n"
        f"(using {data_type} data)")
    plt.grid(linestyle=':')
    plt.savefig(f"{save_dir}/loss_compare_{data_type}.png")


def plot_accuracy_compare(results, data_type, optimizers, save_dir):
    plt.figure(figsize=(6, 4))
    for how in optimizers:
        plt.plot(results[how]['accuracy'][data_type], label=how)
    plt.xlim(0, len(results[optimizers[0]]['accuracy'][data_type]) - 1)
    plt.legend(bbox_to_anchor=(1, 1), loc='upper left')
    plt.xlabel('iterations over entire dataset')
    plt.ylabel('accuracy')
    plt.title(
        f"GNN accuracy comparison among\n{', '.join(optimizers)}\n"
        f"(using {data_type} data)")
    plt.grid(linestyle=':')
    plt.savefig(f"{save_dir}/accuracy_compare_{data_type}.png")


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-e', '--n_epochs', type=int, default=50,
        help='number of iterations over entire dataset')
    parser.add_argument(
        '-n', '--n_data', type=int, default=2000,
        help='number of data')
    parser.add_argument(
        '-p', '--path_to_datasets', default='datasets',
        help='path to datasets folder')
    parser.add_argument(
        '-s', '--save_dir', default='output',
        help='path to save figures')
    args = parser.parse_args()
    main(args.n_epochs, args.n_data, args.path_to_datasets, args.save_dir)
