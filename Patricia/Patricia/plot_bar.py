"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

def find_delete():
    n_groups = 2

    Patricia = (0.000017, 0.000022)

    Trie = (0.000028, 0.000074)

    fig, ax = plt.subplots()

    index = np.arange(n_groups)
    bar_width = 0.25

    opacity = 0.4

    rects1 = plt.bar(index, Patricia, bar_width,
                     alpha=opacity,
                     color='b',
                     label='Patricia',
                     align = 'center')

    rects2 = plt.bar(index + bar_width, Trie, bar_width,
                     alpha=opacity,
                     color='r',
                     label='Trie',align = 'center')

    plt.xlabel('Operation')
    plt.ylabel('Perfomance')
    plt.title('Perfomance between Trie and Patricia')
    plt.xticks(index + bar_width / 2, ('Find', 'Delete'))
    # plt.yticks(np.arange(0,0.000100,0.00001))
    plt.legend()
    plt.tight_layout()
    plt.show()
    plt.grid()
    plt.savefig("Find_delete.png",dpi = 225)

def insert():
    n_groups = 1

    Patricia = (0.031245)
    Trie  = (0.015273)


    fig, ax = plt.subplots()

    index = np.arange(n_groups)
    bar_width = 0.25

    opacity = 0.4

    rects1 = plt.bar(index, Patricia, bar_width,
                     alpha=opacity,
                     color='b',
                     label='Patricia',
                     align = 'center')

    rects2 = plt.bar(index + bar_width + 0.5, Trie, bar_width,
                     alpha = opacity,
                     color = 'r',
                     label = 'Trie',
                     align = 'center')

    plt.xlabel('Insertion')
    plt.ylabel('Perfomance')
    plt.title('Perfomance between Trie and Patricia')
    plt.xticks((index + 0.008,index + 0.75), ('Patricia','Trie'))
    # plt.yticks(np.arange(0,0.0500,0.01))
    plt.legend()
    plt.tight_layout()
    plt.show()
    plt.grid()
    plt.savefig("Insert.png",dpi = 225)

def autolabel(rects): 
    for rect in rects:
        height = rect.get_height()
        plt.text(rect.get_x()+rect.get_width()/2., 1.03*height, '%s' % float(height))

def space():
    n_groups = 1

    Patricia = (508028 / (8 * 1024))
    Trie  = (1860140 / (8 * 1024))

    fig, ax = plt.subplots()

    index = np.arange(n_groups)
    bar_width = 0.25

    opacity = 0.4

    rects1 = plt.bar(index, Patricia, bar_width,
                     alpha=opacity,
                     color='b',
                     label='Patricia',
                     align = 'center')

    rects2 = plt.bar(index + bar_width + 0.5, Trie, bar_width,
                     alpha = opacity,
                     color = 'r',
                     label = 'Trie',
                     align = 'center')
    plt.xlabel('Space/M')
    plt.ylabel('Space')
    plt.title('Space of Trie and Patricia')
    plt.xticks((index + 0.008,index + 0.75), ('Patricia','Trie'))
    # plt.yticks(np.arange(0,20000000,10000))
    plt.legend()
    plt.tight_layout()
    plt.show()
    plt.grid()
    plt.savefig("Space.png",dpi = 225)

if __name__ == '__main__':
    find_delete()
    insert()
    space()