import sys
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f=float): return map(f, gets().split())
def gi(): return int(gets())

class DisjointSet:
    """
    This is a standard implementation of a disjoint set data structure.
    The structure is optimized using the path compression technique,
    with the Union and Intersection operations running in Amortized Constant Time.

    Creation of the Data Structure runs in linear time.
    """

    def __init__(self, size):
        """
        Constructor

        :param size: Size of the disjoint set structure
        """

        self.size = size
        self.set = list(range(size))

    def root(self, node):
        """
        Root finding function that also performs path compression on its execution

        :param node: The node to find the root of
        :return: The root of the node
        """

        if self.set[node] == node:
            return node

        self.set[node] = self.root(self.set[node])
        return self.set[node]

    def union(self, node1, node2):
        """
        Preforms the Union(u, v) operation, where u and v are two sets

        :param node1: The first set
        :param node2: The second set
        :return: Nothing
        """

        root1 = self.root(node1)
        root2 = self.root(node2)

        if root1 == root2:
            return

        if node1 < node2:
            self.set[root2] = root1
            self.root(node2)
        else:
            self.set[root1] = root2
            self.root(node1)

    def intersection(self, node1, node2):
        """
        Preforms the Intersection(u, v) operation, where u and v are two sets

        :param node1: The first set
        :param node2: The second set
        :return: Whether they are part of the same superset
        """

        return self.root(node1) == self.root(node2)


n, m = geti()
ds = DisjointSet(n + 1)
cnt = 0
edges = []

for i in range(1, m + 1):
    a, b = geti()

    if not ds.intersection(a, b):
        ds.union(a, b)
        edges.append(i)
        cnt += 1

if cnt == n - 1:
    print('\n'.join(map(str, edges)))
else:
    print('Disconnected Graph')
