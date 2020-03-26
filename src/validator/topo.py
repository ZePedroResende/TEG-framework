from collections import defaultdict
import networkx as nx
import json
import matplotlib.pyplot as plt

if __name__ == '__main__':
    with open("../parser/teg.json") as file:
        data = json.load(file)
        G=nx.DiGraph()
        G.add_nodes_from(data.keys())
        topo = list(nx.topological_sort(G))

        for (k,v) in data.items():
            for e in v.keys() :
                G.add_edge(k,e)

        #nx.draw(G, with_labels = True)
        #plt.savefig("path_graph1.png")
        #plt.show()



        A = nx.nx_agraph.to_agraph(G)
        A.graph_attr.update(rankdir='LR')  # change direction of the layout
        for rank_of_nodes in topo:
            A.add_subgraph([rank_of_nodes], rank='same')
        # draw
        A.draw('example.png', prog='dot')


        print(nx.is_directed_acyclic_graph(G))
