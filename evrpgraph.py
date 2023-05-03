import numpy as np
import matplotlib.pyplot as plt

def argparser():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', type=str, help='input file', 
                        default='output_files/1/solution_HMAGS_E-n23-k3.evrp.txt')
    parser.add_argument('--output', type=str, help='output file', default=None)
    args = parser.parse_args()
    return args

def readfile(filename):
    with open(filename, 'r') as f:
        N = int(f.readline().strip())
        nodes = []
        for i in range(N):
            line = f.readline().strip().split()
            nodes.append([int(line[0]), float(line[1]), float(line[2])])
        M = int(f.readline().strip())
        ordered_nodes = []
        for i in range(M):
            line = f.readline().strip().split()
            ordered_nodes.append([float(line[0]), float(line[1])])
    return nodes, ordered_nodes

def plotgraph(nodes, ordered_nodes, output = None):
    """
    plot the graph
    """
    x = []
    y = []
    for node in nodes:
        x.append(node[1])
        y.append(node[2])
        type_ = node[0]
        if type_ == 0:
            plt.plot(node[1], node[2], 'ro', markersize=5, alpha=.8)
        elif type_ == 1:
            plt.plot(node[1], node[2], 'g^', markersize=3, alpha=.8)
        elif type_ == 2:
            plt.plot(node[1], node[2], 'bs', markersize=4, alpha=.8)
        else:
            raise ValueError('Node type is not correct')
        
    for i in range(len(ordered_nodes)-1):
        plt.plot([ordered_nodes[i][0], ordered_nodes[i + 1][0]], 
                 [ordered_nodes[i][1], ordered_nodes[i+1][1]], color = 'tomato', linewidth = 1)
    plt.plot([ordered_nodes[-1][0], ordered_nodes[0][0]],
                [ordered_nodes[-1][1], ordered_nodes[0][1]], color = 'tomato', linewidth = 1)
    if output is not None:
        plt.savefig(output)
    else:
        plt.show()
    
    
def main():
    args = argparser()
    nodes, ordered_nodes = readfile(args.input)
    output = args.output
    if output is None:
        output = ''.join(args.input.split('.')[:-1]) + '.png'
    plotgraph(nodes, ordered_nodes, output)
    
if __name__ == '__main__':
    main()