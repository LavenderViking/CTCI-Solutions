    int depth(TreeNode *root) {
        if (root == NULL) return 0;
        return 1+max(depth(root->left), depth(root->right));
    }
