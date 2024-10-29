class Polymorp {
    public static void main(String[] args) {
        calc ob = new calc();
        ob.add(5, 7);
        System.out.println(ob.add(12.3, 7.32));
        System.out.println(ob.add(3, 5, 5));
    }
}

class calc {
    int abc;
    void add(int a, int b) {
        System.out.println(a + b);
    }

    double add(double a, double b) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }
    // string[] add(string[] a, string[] b) {
    // return a + b;
    // }
}