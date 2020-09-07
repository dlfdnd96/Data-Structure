package com.iwryu.ConvertBinaryTreeToLevelLinkedList;

import java.util.LinkedList;
import java.util.ArrayList;

class Tree {

    // class
    private class TreeNode {

        private int mTreeNodeData;
        private TreeNode mTreeNodeLeft;
        private TreeNode mTreeNodeRight;

        public TreeNode(int data) {
            this.mTreeNodeData = data;
        }

    } // end Node class

    // variable
    private TreeNode mTreeRoot;

    // function
    public Tree(int size) {
        this.mTreeRoot = MakeBST(0, size - 1);
    }
    public void PrintList(ArrayList<LinkedList<TreeNode>> arr) {
        for (LinkedList<TreeNode> list : arr) {
            for (TreeNode node : list) {
                System.out.print(node.mTreeNodeData + " ");
            } // end for (TreeNode node : list)
            System.out.println();
        } // end for (LinkedList<TreeNode> list : arr)
    }
    public ArrayList<LinkedList<TreeNode>> BSTToList() {
        ArrayList<LinkedList<TreeNode>> lists = new ArrayList<LinkedList<TreeNode>>();
        BSTToList(mTreeRoot, lists, 0);

        return lists;
    }
    public ArrayList<LinkedList<TreeNode>> BSTToList2() {
        ArrayList<LinkedList<TreeNode>> result = new ArrayList<LinkedList<TreeNode>>();
        LinkedList<TreeNode> current = new LinkedList<TreeNode>();
        if (mTreeRoot != null) {
            current.add(mTreeRoot);
        } // end if (mTreeRoot != null)

        while (current.size() > 0) {
            result.add(current);
            LinkedList<TreeNode> parents = current;
            current = new LinkedList<TreeNode>();
            for (TreeNode parent : parents) {
                if (parent.mTreeNodeLeft != null) {
                    current.add(parent.mTreeNodeLeft);
                } // end if (parent.mTreeNodeLeft != null)
                if (parent.mTreeNodeRight != null) {
                    current.add(parent.mTreeNodeRight);
                } // end if (parent.mTreeNodeRight != null)
            } // end for (TreeNode parent : parents)
        } // end while (current.size() > 0)

        return result;
    }
    private TreeNode MakeBST(int start, int end) {
        if (start > end) {
            return null;
        } // end if (start > end)

        int mid = (start + end) / 2;
        TreeNode node = new TreeNode(mid);
        node.mTreeNodeLeft = MakeBST(start, mid - 1);
        node.mTreeNodeRight = MakeBST(mid + 1, end);

        return node;
    }
    private void BSTToList(TreeNode root, ArrayList<LinkedList<TreeNode>> lists, int level) {
        if (root == null) {
            return;
        } // end if (root == null)

        LinkedList<TreeNode> list = null;
        if (lists.size() == level) {
            list = new LinkedList<TreeNode>();
            lists.add(list);
        } else {
            list = lists.get(level);
        } // end if (lists.size() == level)

        list.add(root);
        BSTToList(root.mTreeNodeLeft, lists, level + 1);
        BSTToList(root.mTreeNodeRight, lists, level + 1);
    }

} // end Tree class

public class ConvertBinaryTreeToLevelLinkedList {
    
    public static void main(String[] args) {
        Tree t = new Tree(10);
        t.PrintList(t.BSTToList2());
    }

} // end ConvertBinaryTreeToLevelLinkedList class
