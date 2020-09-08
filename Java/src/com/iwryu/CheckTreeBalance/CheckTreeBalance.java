package com.iwryu.CheckTreeBalance;

import java.lang.Math;
import java.lang.Integer;

class Tree {

    class Node {

        // variable
        private int mTreeData;
        private Node mTreeLeft;
        private Node mTreeRight;

        // function
        public Node (int data) {
            this.mTreeData = data;
        }

    } // Node class

    class Level {

        private int mLevelMin = Integer.MAX_VALUE;
        private int mLevelMax = Integer.MIN_VALUE;

    } // end Level class

    // variable
    public Node mTreeRoot;

    // function
    public Tree (int size) {
        this.mTreeRoot = makeBST(0, size - 1);
        this.mTreeRoot.mTreeRight.mTreeRight.mTreeRight.mTreeRight = new Node(10);
        this.mTreeRoot.mTreeRight.mTreeRight.mTreeLeft = new Node(11);
    }

    private Node makeBST(int start, int end) {
        if (start > end) {
            return null;
        } // end if (start > end)

        int mid = (start + end) / 2;
        Node node = new Node(mid);
        node.mTreeLeft = makeBST(start, mid - 1);
        node.mTreeRight = makeBST(mid + 1, end);

        return node;
    }

    public boolean IsBalanced(Node root) {
        if (root == null) {
            return true;
        } // end if (root == null)

        int heightDiff = getHeight(root.mTreeLeft) - getHeight(root.mTreeRight);
        if (Math.abs(heightDiff) > 1) {
            return false;
        } else {
            return IsBalanced(root.mTreeLeft) && IsBalanced(root.mTreeRight);
        } // end if (Math.abs(heightDiff) > 1)
    }

    private int getHeight(Node root) {
        if (root == null) {
            return -1;
        } // end if (root == null)

        return Math.max(getHeight(root.mTreeLeft), getHeight(root.mTreeRight)) + 1;
    }

    private int checkHeight(Node root) {
        if (root == null) {
            return -1;
        } // end if (root == null)

        int leftHeight = checkHeight(root.mTreeLeft);
        if (leftHeight == Integer.MIN_VALUE) {
            return Integer.MIN_VALUE;
        } // end if (leftHeight == Integer.MIN_VALUE)

        int rightHeight = checkHeight(root.mTreeRight);
        if (rightHeight == Integer.MIN_VALUE) {
            return Integer.MIN_VALUE;
        } // end if (rightHeight == Integer.MIN_VALUE)

        int heightDiff = leftHeight - rightHeight;
        if (Math.abs(heightDiff) > 1) {
            return Integer.MIN_VALUE;
        } else {
            return Math.max(leftHeight, rightHeight) + 1;
        } // end if (Math.abs(heightDiff) > 1)
    }

    public boolean IsBalanced2 (Node root) {
        return checkHeight(root) != Integer.MIN_VALUE;
    }

    public boolean IsBalanced3(Node root) {
        Level obj = new Level();
        checkBalanced(root, obj, 0);
        if (Math.abs(obj.mLevelMin - obj.mLevelMax) > 1) {
            return false;
        } else {
            return true;
        } // end if (Math.abs(obj.mLevelMin - obj.mLevelMax) > 1)
    }

    private void checkBalanced(Node node, Level obj, int level) {
        if (node == null) {
            if (level < obj.mLevelMin) {
                obj.mLevelMin = level;
            } else if (level > obj.mLevelMax) {
                obj.mLevelMax = level;
            } // end if (level < obj.mLevelMin)

            return;
        } // end if (node == null)

        checkBalanced(node.mTreeLeft, obj, level + 1);
        checkBalanced(node.mTreeRight, obj, level + 1);
    }

} // end Tree class
public class CheckTreeBalance {
    
    public static void main(String[] args) {
        Tree t = new Tree(10);
        System.out.println(t.IsBalanced(t.mTreeRoot));
        System.out.println(t.IsBalanced2(t.mTreeRoot));
        System.out.println(t.IsBalanced3(t.mTreeRoot));
    }

} // end CheckTreeBalance class
