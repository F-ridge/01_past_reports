import pandas as pd
import matplotlib.pyplot as plt


def show_fig(image_id, show_time):
    print(image_id)
    plt.imshow(plt.imread(f"test/{image_id}.png"))
    plt.axis('off')
    plt.pause(show_time)
    plt.close()


image_info = pd.read_csv('test.csv')
for _, row in image_info.reindex(index=image_info.index[::-1]).iterrows():
    image_id = str(int(row.image_id)).zfill(3)
    show_fig(image_id, 0.5)
    _ = input('数を入力後にEnterを押してください')
