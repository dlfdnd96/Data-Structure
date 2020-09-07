package com.iwryu.FindPathOfTwoPointsInGraph;

import java.util.LinkedList;

class Graph {

    class Node {

        // variable
        private int mNodeData;
        private boolean mNodeMarked;
        private LinkedList<Node> mNodeAdjacent;

        // funciton
        public Node(int data) {
            this.mNodeData = data;
            this.mNodeMarked = false;
            this.mNodeAdjacent = new LinkedList<Node>();
        }

    } // end Node class

    // variable
    private Node[] nodes;

    // function
    public Graph(int size) {
        this.nodes = new Node[size];
        for (int index = 0; index < size; ++index) {
            nodes[index] = new Node(index);
        } // end for (int index = 0; index < size; ++index)
    }

    public void AddEdge(int index1, int index2) {
        Node n1 = nodes[index1];
        Node n2 = nodes[index2];
        if (!n1.mNodeAdjacent.contains(n2)) {
            n1.mNodeAdjacent.add(n2);
        } // end if (!n1.mNodeAdjacent.contains(n2))
        if (!n2.mNodeAdjacent.contains(n1)) {
            n2.mNodeAdjacent.add(n1);
        } // end if (!n2.mNodeAdjacent.contains(n1))
    }

    public boolean Search(int index1, int index2) {
        return search(nodes[index1], nodes[index2]);
    }

    private void initMarks() {
        for (Node n : nodes) {
            n.mNodeMarked = false;
        } // end for (Node n : nodes)
    }

    private boolean search(Node start, Node end) {
        initMarks();
        LinkedList<Node> queue = new LinkedList<Node>();
        queue.add(start);
        while (!queue.isEmpty()) {
            Node root = queue.removeFirst();
            if (root == end) {
                return true;
            } // end if (root == end)

            for (Node n : root.mNodeAdjacent) {
                if (n.mNodeMarked == false) {
                    n.mNodeMarked = true;
                    queue.add(n);
                }
            } // end for (Node n : root.mNodeAdjacent)
        } // end while (!queue.isEmpty())

        return false;
    }

} // end Graph class
public class FindPathOfTwoPointsInGraph {

    public static void main(String[] args) {
        Graph g = new Graph(9);
        g.AddEdge(0, 1);
        g.AddEdge(1, 2);
        g.AddEdge(1, 3);
        g.AddEdge(2, 4);
        g.AddEdge(2, 3);
        g.AddEdge(3, 4);
        g.AddEdge(3, 5);
        g.AddEdge(5, 6);
        g.AddEdge(5, 7);
        g.AddEdge(6, 8);

        System.out.println(g.Search(1, 8));
    }

} // end FindPathOfTwoPointsInGraph class
