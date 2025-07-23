import java.util.LinkedList;
import java.util.Queue;

class BinaryTree {
    class Node {
        int value;
        Node left, right;

        Node(int val) {
            this.value = val;
            this.left = this.right = null;
        }

        int getValue() {
            return this.value;
        }
    }

    private Node root;

    // Inserta un nuevo nodo por niveles (usando BFS)
    void insert(int value) {
        Node newNode = new Node(value);

        if (this.root == null) {
            this.root = newNode;
            return;
        }

        Queue<Node> queue = new LinkedList<>();
        queue.add(root);

        while (queue.isEmpty() == false) {
            Node current = queue.poll();

            if (current.left == null) {
                current.left = newNode;
                return;
            } else {
                queue.add(current.left);
            }

            if (current.right == null) {
                current.right = newNode;
                return;
            } else {
                queue.add(current.right);
            }
        }
    }

    private int max(int a, int b) {
        return a >= b ? a : b;
    }

    int altura() {
        return altura(this.root);
    }

    private int altura(Node node) {
        if (node == null)
            return 0;
        return 1 + max(altura(node.left), altura(node.right));
    }

    private int factBalanceo() {
        return factBalanceo(this.root);
    }

    private int factBalanceo(Node node) {
        if(node == null) {
            return 0;
        }

        return altura(node.left) - altura(node.right);
    }

    int cantNodosDesbalanceados() {
        return this.cantNodosDesbalanceados(this.root);
    }

    private int cantNodosDesbalanceados(Node node) {
        if(node == null) {
            return 0;
        }

        int cantidad = 0;
        if(Math.abs(factBalanceo(node)) > 1) {
            cantidad++;
        }

        cantidad += cantNodosDesbalanceados(node.left);
        cantidad += cantNodosDesbalanceados(node.right);

        return cantidad;
    }

    int cantNodosConValorPar() {
        return this.cantNodosConValorPar(this.root);
    }

    private int cantNodosConValorPar(Node node) {
        if(node == null) {
            return 0;
        }

        int cantidad = 0;

        cantidad += cantNodosConValorPar(node.left);
        cantidad += cantNodosConValorPar(node.right);

        if((node.getValue() % 2) == 0) {
            cantidad++;
        }

        return cantidad;
    }

    int cantNodosUltNivel() {
        return cantNodosUltNivel(this.root);
    }

    private boolean esHoja(Node node) {
        if(node == null) {
            return false;
        }
        return ((node.left == null) && (node.right == null));
    }

    private int cantNodosUltNivel(Node node) {
        if(node == null) {
            return 0;
        }

        int cant = 0;

        if(esHoja(node)) {
            cant++;
        }
        cant += cantNodosUltNivel(node.left);
        cant += cantNodosUltNivel(node.right);
        return cant;
    }

    int cantNodos() {
        return cantNodos(this.root);
    }

    private int cantNodos(Node node) {
        if(node == null) {
            return 0;
        }
        int cant = 0;
        cant += cantNodos(node.left);
        return 1 + cantNodos(node.left) + cantNodos(node.right);
    }


    int cantDeNodosEnNivel(int n) {
        return cantDeNodosEnNivel(this.root, n);
    }

    private int cantDeNodosEnNivel(Node node, int n) {
        if (node == null) return 0;

        if (n == 1) {
            return 1;
        } else {
            return cantDeNodosEnNivel(node.left, n-1) +
                   cantDeNodosEnNivel(node.right, n-1);
        }
    }

    int cantNodosInternos() {
        return this.cantNodosInternos(this.root.left) + this.cantNodosInternos(this.root.right);
    }

    private int cantNodosInternos(Node node) {
        if((node == null) || ((node.left == null) && (node.right == null))) {
            return 0;
        }

        return 1 + cantNodosInternos(node.left) + cantNodosInternos(node.right);
    }

    int cantNodosCon2Hijos() {
        return cantNodosCon2Hijos(this.root);
    }

    // devuelve la cantidad de hijos (directos) de un nodo
    private int cantHijos(Node node) {
        if (node == null) {
            return 0;
        }

        int res = 0;
        if(node.left != null) {
            res++;
        }

        if(node.right != null) {
            res++;
        }

        return res;
    }

    private int cantNodosCon2Hijos(Node node) {
        if(node == null) {
            return 0;
        }

        int contador = 0;

        if(cantHijos(node) == 2) {
            contador++;
        }
        contador += cantNodosCon2Hijos(node.left);
        contador += cantNodosCon2Hijos(node.right);

        return contador;
    }

    // recorrido inorden (IRD) para mostrar el árbol
    void inorder(Node node) {
        if (node == null)
            return;
        inorder(node.left);
        System.out.print(node.value + " ");
        inorder(node.right);
    }

    // recorrido preorden (RID)
    void preorder(Node node) {
        if (node == null)
            return;
        System.out.print(node.value + " ");
        preorder(node.left);
        preorder(node.right);
    }

    void levelOrder(Node node) {
        if(node == null) {
            return;
        }

        Queue<Node> queue = new LinkedList<>();
        System.out.print("[");
        queue.add(root);

        while (!queue.isEmpty()) {
            Node current = queue.poll();
            System.out.print(current.value);

            if (current.left != null) {
                queue.add(current.left);
            }

            if (current.right != null) {
                queue.add(current.right);
            }

            if(!queue.isEmpty()) {
                System.out.print(", ");
            }
        }
        System.out.print("]\n");
    }

    void printLevelOrder() {
        levelOrder(this.root);
    }

    void printInOrder() {
        inorder(this.root);
        System.out.println();
    }

    void printPreOrder() {
        preorder(this.root);
        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {
        BinaryTree b = new BinaryTree();

        b.insert(10);
        b.insert(20);  //            _10_
        b.insert(30);  //           /    \
        b.insert(40);  //          20    30
        b.insert(50);  //         / \    / \
        b.insert(60);  //       40  50  60  70
        b.insert(70);

        b.printLevelOrder();

        // System.out.println(b.altura());
        // System.out.println(b.cantDeNodosEnNivel(3));
        // System.out.println(b.cantNodosInternos());
        // System.out.println(b.cantNodosConValorPar());
        System.out.println(b.cantNodosUltNivel());
        System.out.println(b.cantNodosCon2Hijos());
    }
}
