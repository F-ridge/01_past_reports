import os
import numpy as np
import pandas as pd
from itertools import product
import matplotlib.pyplot as plt


def main():
    make_datasets()


def make_datasets():
    np.random.seed(114514)
    i = 1
    for section, part in product(('1', '2'), ('A', 'B')):
        os.makedirs(f'../datasets/image/{section}/{part}', exist_ok=True)
        os.makedirs('../datasets/image_info', exist_ok=True)
        image_info = create_image_info(section, part)
        for _, row in image_info.iterrows():
            image_id = str(int(row.image_id)).zfill(3)
            num = row.num
            create_image(section, part, image_id, num)
            print(
                '\r',
                f"image {image_id} ({section}-{part}) "
                f"created ({i} / 500)",
                end='')
            i += 1


def create_image_info(section, part):
    params = {
        '1': {'n_min': 2, 'n_max': 20, 'size': 100,
              'time': [0.25, 0.5, 0.75, 1.0]},
        '2': {'n_min': 20, 'n_max': 500, 'size': 150, 'time': [0.5]}}
    starts = {
        '1': {'A': 0, 'B': 100},
        '2': {'A': 200, 'B': 350}}
    size = params[section]['size']
    n_min = params[section]['n_min']
    n_max = params[section]['n_max']
    time = params[section]['time']
    id_start = starts[section][part]
    image_info = pd.DataFrame({
        'image_id': [str(i).zfill(3)
                     for i in range(id_start, id_start+size)],
        'num': [np.random.randint(n_min, n_max+1)
                for _ in range(id_start, id_start+size)],
        'time': [np.random.choice(time)
                 for _ in range(id_start, id_start+size)]})
    image_info.to_csv(
        f'../datasets/image_info/{section}_{part}.csv', index=False)
    return image_info


def create_image(section, part, image_id, num):
    x = np.random.rand(num)
    y = np.random.rand(num)
    fig = plt.figure(frameon=False)
    fig.set_size_inches(20, 10)
    plt.axis('off')
    plt.xlim(0, 1)
    plt.ylim(0, 1)
    plt.plot(
        x, y, markeredgecolor='black', markerfacecolor='black',
        marker='o', markersize=8, linestyle='')
    plt.savefig(
        f'../datasets/image/{section}/{part}/{image_id}.png',
        bbox_inches='tight', pad_inches=0)
    plt.close()


if __name__ == '__main__':
    main()
