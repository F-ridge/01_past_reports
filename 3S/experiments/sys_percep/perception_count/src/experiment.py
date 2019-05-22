import os
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def main(name, section, part, rev):
    expt = Experiment(name, section, part, rev)
    expt.run()


class Experiment:
    def __init__(self, name, section, part, rev):
        self.name = name
        self.section = section
        self.part = part
        self.rev = rev
        self.image_info = pd.read_csv(
            f"../datasets/image_info/{self.section}_{self.part}.csv")
        if rev == '1':
            self.image_info = self.image_info.reindex(
                index=self.image_info.index[::-1])
        self.result = pd.DataFrame({
            'image_id': self.image_info.image_id.apply(str).str.zfill(3),
            'num': self.image_info.num,
            f'pred_{name}': np.nan*len(self.image_info)})

    def run(self):
        for _, row in self.image_info.iterrows():
            image_id = str(int(row.image_id)).zfill(3)
            self.show_fig(image_id, row.time)
            num_pred = input('\r数を半角で入力後にEnterを押してください: ')
            sys.stdout.flush()
            print('------------------------------')
            self.result.loc[
                self.result.image_id == image_id, [f'pred_{name}']] = num_pred
        self.save_result()
        print('実験終了')

    def show_fig(self, image_id, show_time):
        mng = plt.get_current_fig_manager()
        mng.full_screen_toggle()
        sys.stdout.write('\r画像を表示しています…')
        plt.imshow(plt.imread(
            f"../datasets/image/{self.section}/{self.part}/{image_id}.png"))
        plt.axis('off')
        plt.pause(show_time)
        plt.close()
        sys.stdout.flush()

    def save_result(self):
        os.makedirs('../result', exist_ok=True)
        self.result.to_csv(
            f"../result/{self.name}_{self.section}_"
            f"{self.part}_{self.rev}.csv", index=False)


if __name__ == '__main__':
    name = input('名前を半角英字で入力してEnterを押してください: ').strip()
    section = input(
        'セクションを半角で入力してEnterを押してください (1 or 2): ').strip()
    assert section in ('1', '2'), '1か2を半角数字で入力してください'
    part = input(
        'パートを半角で入力してEnterを押してください (A or B): ').strip()
    assert part in ('A', 'B'), 'AかBを半角大文字で入力してください'
    rev = input(
        '番号が大きくなる順なら0を、'
        'その逆順なら1を入力してEnterを押してください (0 or 1): ').strip()
    assert rev in ('0', '1'), '0か1を半角数字で入力してください'
    print('------------------------------')
    main(name, section, part, rev)
